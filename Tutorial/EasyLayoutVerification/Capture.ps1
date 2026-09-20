param(
    [string]$Application,
    [int]$Port = 8901,
    [string]$Phase = 'before',
    [string]$State = 'initial',
    [string]$OutputDirectory = '',
    [string[]]$ClickText = @(),
    [string[]]$Commands = @(),
    [int]$Width = 0,
    [int]$Height = 0
)

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
if (-not ('EasyLayoutCapture' -as [type])) {
    Add-Type -TypeDefinition @'
using System;
using System.Text;
using System.Runtime.InteropServices;
public static class EasyLayoutCapture {
    public delegate bool EnumWindowProc(IntPtr window, IntPtr data);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [DllImport("user32.dll")] public static extern bool EnumWindows(EnumWindowProc callback, IntPtr data);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr window, out uint process);
    [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr window, StringBuilder text, int count);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr window, out RECT rect);
    [DllImport("user32.dll")] public static extern uint GetDpiForWindow(IntPtr window);
    [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr window, IntPtr after, int x, int y, int width, int height, uint flags);
    [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr window, IntPtr dc, uint flags);
}
'@
}

$tutorialRoot = [IO.Path]::GetFullPath("$PSScriptRoot/../GacUI_Controls")
$targetProcess = Get-Process -Name $Application -ErrorAction SilentlyContinue | Select-Object -First 1
if (!$targetProcess) {
    $targetProcess = Start-Process -FilePath "$tutorialRoot/x64/Debug/$Application.exe" -WorkingDirectory "$tutorialRoot/$Application" -ArgumentList "/AsPort:$Port" -WindowStyle Hidden -PassThru
}
$script:targetWindows = [Collections.Generic.List[object]]::new()
function Read-TargetWindows {
    $script:targetWindows.Clear()
    [void][EasyLayoutCapture]::EnumWindows({param($window,$data)
        [uint32]$owner = 0
        [void][EasyLayoutCapture]::GetWindowThreadProcessId($window,[ref]$owner)
        if ($owner -eq $targetProcess.Id) {
            $title = [Text.StringBuilder]::new(2048)
            [void][EasyLayoutCapture]::GetWindowText($window,$title,$title.Capacity)
            $script:targetWindows.Add(@{Handle=$window;Title=$title.ToString()})
        }
        return $true
    },[IntPtr]::Zero)
    if ($script:targetWindows.Title -contains 'Microsoft Visual C++ Runtime Library') { throw 'Tutorial has a blocking native runtime error dialog.' }
}
$endpoint = "http://localhost:$Port/Automation/$Application.exe"
$ready = $false
for ($attempt=0; $attempt -lt 20; $attempt++) {
    Read-TargetWindows
    if ($targetProcess.HasExited) { throw "Tutorial exited: $($targetProcess.ExitCode)" }
    try {
        $response = (Invoke-WebRequest "$endpoint/Controls" -TimeoutSec 30).Content
        $initialDump=$response|ConvertFrom-Json -Depth 1024
        Read-TargetWindows
        if ($initialDump.MainWindow.title -and ($script:targetWindows | Where-Object Title -eq $initialDump.MainWindow.title)) { $ready=$true; break }
    } catch { Read-TargetWindows }
    Start-Sleep -Milliseconds 200
}
if (!$ready) { Read-TargetWindows; throw 'Automation endpoint did not become ready.' }
$executedCommands=[Collections.Generic.List[string]]::new()
foreach ($label in $ClickText) {
    $current=(Invoke-WebRequest "$endpoint/Controls" -TimeoutSec 30).Content|ConvertFrom-Json -Depth 1024
    function Find-Label($node) {
        if ($node.elementText -ceq $label) { return $node }
        foreach ($child in $node.children) { $match=Find-Label $child; if ($match) { return $match } }
    }
    $matched=$null
    foreach ($candidate in @($current.Popups)+@($current.SubWindows)+@($current.MainWindow)) {
        $matched=Find-Label $candidate.composition
        if ($matched) { $targetId=$candidate.windowId; break }
    }
    if (!$matched) { throw "No visible label: $label" }
    $clickX=[int](($matched.bounds.x1+$matched.bounds.x2)/2)
    $clickY=[int](($matched.bounds.y1+$matched.bounds.y2)/2)
    $command="!LeftClick:$clickX,$clickY"
    $ioEndpoint=if($targetId -eq $current.MainWindow.windowId) { "$endpoint/IO" } else { "$endpoint/IO/$targetId" }
    $answer=(Invoke-WebRequest $ioEndpoint -Method Post -ContentType 'application/json; charset=utf8' -SkipHeaderValidation -Body $command -TimeoutSec 10).Content
    if ($answer -ne 'Queued') { throw "IO failed: $answer" }
    $executedCommands.Add("Click label '$label': $command")
    Start-Sleep -Milliseconds 200
}
foreach ($command in $Commands) {
    $answer=(Invoke-WebRequest "$endpoint/IO" -Method Post -ContentType 'application/json; charset=utf8' -SkipHeaderValidation -Body ([Text.Encoding]::UTF8.GetBytes($command)) -TimeoutSec 10).Content
    if ($answer -ne 'Queued') { throw "IO failed: $answer" }
    $executedCommands.Add($command)
    Start-Sleep -Milliseconds 150
}
$window = $script:targetWindows | Where-Object Title -eq $initialDump.MainWindow.title | Select-Object -First 1
if ($Width -gt 0 -and $Height -gt 0) {
    [void][EasyLayoutCapture]::SetWindowPos($window.Handle,[IntPtr]::Zero,0,0,$Width,$Height,6)
}
Start-Sleep -Milliseconds 250
Read-TargetWindows
$response=(Invoke-WebRequest "$endpoint/Controls" -TimeoutSec 30).Content
$dump=$response|ConvertFrom-Json -Depth 1024
$outputRoot=if ($OutputDirectory) { [IO.Path]::GetFullPath($OutputDirectory) } else { $PSScriptRoot }
$outputFolder=Join-Path $outputRoot "$Phase/$Application"
[void][IO.Directory]::CreateDirectory($outputFolder)
[IO.File]::WriteAllText("$outputFolder/$State.json",$response)
$rect=New-Object EasyLayoutCapture+RECT
[void][EasyLayoutCapture]::GetWindowRect($window.Handle,[ref]$rect)
$bitmap=[Drawing.Bitmap]::new($rect.Right-$rect.Left,$rect.Bottom-$rect.Top)
$graphics=[Drawing.Graphics]::FromImage($bitmap)
$dc=$graphics.GetHdc()
$captured=[EasyLayoutCapture]::PrintWindow($window.Handle,$dc,2)
$graphics.ReleaseHdc($dc)
$nonblack=$false
for ($y=0; $y -lt $bitmap.Height -and !$nonblack; $y+=3) {
    for ($x=0; $x -lt $bitmap.Width; $x+=3) {
        $pixel=$bitmap.GetPixel($x,$y)
        if ($pixel.R -ne 0 -or $pixel.G -ne 0 -or $pixel.B -ne 0) { $nonblack=$true; break }
    }
}
if ($captured -and $nonblack) { $bitmap.Save("$outputFolder/$State.png") }
$graphics.Dispose()
$bitmap.Dispose()
$metadata=@{
    Revision=(& git -C "$PSScriptRoot/../.." rev-parse HEAD)
    Renderer='Windows Direct2D'; Skin='darkskin::Theme'; Architecture='x64'; Configuration='Debug'
    Dpi=[EasyLayoutCapture]::GetDpiForWindow($window.Handle)
    WindowBounds=$rect; ClientBounds=$dump.MainWindow.bounds; Commands=$executedCommands.ToArray()
    CapturedAt=[DateTime]::UtcNow.ToString('O'); ProcessId=$targetProcess.Id
    RequestedSize=@{Width=$Width;Height=$Height}; ImageAvailable=($captured -and $nonblack)
    FontSettings='Fonts and sizes recorded on each Label element in the accompanying geometry JSON.'
}
$metadata|ConvertTo-Json -Depth 10|Set-Content -LiteralPath "$outputFolder/$State.metadata.json"
[pscustomobject]@{Application=$Application; State=$State; Process=$targetProcess.Id; Bounds=$dump.MainWindow.bounds; ImageAvailable=$metadata.ImageAvailable}
