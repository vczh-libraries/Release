param(
    [Parameter(Mandatory=$true)][string]$FileName,
    [string]$MappingFileName
)

$ErrorActionPreference = 'Stop'
$arguments = @(
    '-mode:GacGen',
    ('-pathGacGen:' + [System.IO.Path]::GetFullPath("$PSScriptRoot/GacGen.exe")),
    ('-pathCppMerge:' + [System.IO.Path]::GetFullPath("$PSScriptRoot/CppMerge.exe")),
    '-FileName', $FileName
)
if ($MappingFileName) { $arguments += @('-MappingFileName', $MappingFileName) }
& "$PSScriptRoot/GacBuild.exe" @arguments
if ($LASTEXITCODE -ne 0) { throw "GacGen orchestration failed with exit code $LASTEXITCODE." }
