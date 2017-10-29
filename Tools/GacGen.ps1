param (
    [String]$FileName
)

. $PSScriptRoot\StartProcess.ps1

Write-Host "Compiling GacUI Resource: $FileName ..."
Start-Process-And-Wait (,("$PSScriptRoot\GacGen32.exe", "/P $FileName"))
Start-Process-And-Wait (,("$PSScriptRoot\GacGen64.exe", "/P $FileName"))

if (Test-Path -Path "$($FileName).log\x32\Errors.txt") {
    Write-Host (Get-Content "$($FileName).log\x32\Errors.txt") -ForegroundColor Red -Separator "`r`n"
    throw "Failed to compile GacUI Resource (x86): $FileName"
}
if (Test-Path -Path "$($FileName).log\x64\Errors.txt") {
    Write-Host (Get-Content "$($FileName).log\x64\Errors.txt") -ForegroundColor Red -Separator "`r`n"
    throw "Failed to compile GacUI Resource (x64): $FileName"
}
    
$output_folder = Get-Content "$($FileName).log\x32\CppOutput.txt"
$x32_folder = "$($FileName).log\x32\Source"
$x64_folder = "$($FileName).log\x64\Source"
if (!(Test-Path -Path $output_folder)) {
    New-Item $output_folder -ItemType directory | Out-Null
}
Get-ChildItem -Path $x32_folder -ErrorAction SilentlyContinue | %{
    Write-Host "    Merging C++ Source File: $($_.Name) ..."
    Start-Process-And-Wait (,("$PSScriptRoot\CppMerge.exe", "`"$x32_folder\$($_.Name)`" `"$x64_folder\$($_.Name)`" `"$output_folder\$($_.Name)`""))
}

$deploy = "$($FileName).log\x32\Deploy.bat"
if (Test-Path -Path $deploy) {
    Write-Host "    Deploying ..."
    Start-Process-And-Wait (,($env:ComSpec, "/c `"$deploy`"")) $true
}