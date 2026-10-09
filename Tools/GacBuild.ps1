<#
Incrementally compile resources below a GacUI driver XML.
-Dump writes discovery, dependency and candidate manifests without compiling resources.
The adjacent native GacBuild owns planning, generation, merging and deployment.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory=$true)][string]$FileName,
    [switch]$Dump
)

$ErrorActionPreference = 'Stop'
$arguments = @(
    '-mode:GacBuild',
    "-pathGacGen:$PSScriptRoot/GacGen.exe",
    "-pathCppMerge:$PSScriptRoot/CppMerge.exe",
    '-FileName', $FileName
)
if ($Dump) { $arguments += '-Dump' }
& "$PSScriptRoot/GacBuild.exe" @arguments
if ($LASTEXITCODE -ne 0) { throw "GacBuild failed with exit code $LASTEXITCODE." }
