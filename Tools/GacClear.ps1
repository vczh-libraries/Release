<#
See comments in GacBuild.ps1 for $FileName.
GacClear.ps1 deletes all cached compile result of all GacUI Xml Resource files, to cause GacBuild.ps1 do a full build.
If your resource files named Resource.xml, then the Resource.xml.log folder cached all files, which will be deleted.
#>
param (
    [String]$FileName
)

. $PSScriptRoot\StartProcess.ps1
. $PSScriptRoot\GacCommon.ps1

# Prevent from displaying "Debug or Close Application" dialog on crash
$dontshowui_key = "HKCU:\Software\Microsoft\Windows\Windows Error Reporting"
$dontshowui_value = (Get-ItemProperty $dontshowui_key).DontShowUI
Set-ItemProperty $dontshowui_key -Name DontShowUI -Value 1

try {
    if (-not (Test-Path -Path $FileName)) {
        throw "Input does not exist: $FileName"
    }
    $FileName = (Resolve-Path -Path $FileName).Path
    if (Test-Path -Path "$($FileName).log") {
        Remove-Item -Path "$($FileName).log" -Recurse | Out-Null
    }
    New-Item -ItemType Directory "$($FileName).log" | Out-Null

    EnumerateResourceFiles $FileName
    if (-not (Test-Path -Path "$($FileName).log\ResourceFiles.txt")) {
        throw "Failed to enumerate GacUI Xml Resource files"
    }
    
    $search_directory = Split-Path -Parent (Resolve-Path $FileName)
    Get-Content "$($FileName).log\ResourceFiles.txt" | ForEach-Object {
        $input_file = Join-Path -Path $search_directory -ChildPath $_
        $log_folder = "$($input_file).log"
        if (Test-Path -Path $log_folder) {
            Write-Host "Deleting: " $log_folder
            Remove-Item -Path $log_folder -Recurse
        }
    }
}
catch {
    Write-Host $_.Exception.Message -ForegroundColor Red
}

Set-ItemProperty $dontshowui_key -Name DontShowUI -Value $dontshowui_value
[Console]::ResetColor()