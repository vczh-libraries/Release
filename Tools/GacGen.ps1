param(
    [Parameter(Mandatory=$true)][string]$FileName,
    [string]$MappingFileName
)

$ErrorActionPreference = 'Stop'
$arguments = @(
    '-mode:GacGen',
    "-pathGacGen:$PSScriptRoot/GacGen.exe",
    "-pathCppMerge:$PSScriptRoot/CppMerge.exe",
    '-FileName', $FileName
)
if ($MappingFileName) { $arguments += @('-MappingFileName', $MappingFileName) }
& "$PSScriptRoot/GacBuild.exe" @arguments
if ($LASTEXITCODE -ne 0) { throw "GacGen orchestration failed with exit code $LASTEXITCODE." }
