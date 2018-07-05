<#
Do an incremental build to all GacUI Xml Resource files directly or indirectly in the folder containing $FileName.
If you set -Dump, then this scripts stops before the real building process, it outputs following files for debug:
    $($FileName).log\ResourceFiles.txt: All resource files that are found
    $($FileName).log\BuildCandidates.txt: All resource files that are outdated, so they will be build
    $($FileName).log\ResourceAnonymousFiles.txt: All anonymous resource files
    $($FileName).log\ResourceNamedFiles.txt: All named resource files in the correct order sorted using dependencies
    $($FileName).log\ResourceNamedMapping.txt: Resource name to full path mappings for GacGen.exe /P <resource-xml> <HERE>

$FileName should points to an Xml file with this format:
<GacUI>
    <Exclude Pattern="...."/>
    ...
</GacUI>

GacBuild.ps1 searches all GacUI Xml Resource files, but whose full patch matches one of the pattern will be ignored.
You should use "/" instead of "\" in the pattern attribute.

In order to make your resource file, be able to depend on others, or be able to be depended by others,
you should add the following metadata in GacGenConfig like this:

<Resource>
  <Folder name="GacGenConfig">
    <Xml name="Metadata">
      <ResourceMetadata Name="NAME" Version="1.0">
        <Dependencies>
          <Resource Name="NAME-OF-RESOURCE-YOU-WANT-TO-DEPEND"/>
          ....
        </Dependencies>
      </ResourceMetadata>
    </Xml>
    <Folder name="Cpp">...</Folder>
    <Folder name="ResX86">...</Folder>
    <Folder name="ResX64">...</Folder>
    </Folder>
  </Folder>
  ...
</Resource>
#>
[CmdLetBinding()]
param (
    [Parameter(Mandatory=$true)][String]$FileName,
    [Switch]$Dump
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
        New-Item -ItemType Directory "$($FileName).log" | Out-Null
    }

    EnumerateResourceFiles $FileName
    if (-not (Test-Path -Path "$($FileName).log\ResourceFiles.txt")) {
        throw "Failed to enumerate GacUI Xml Resource files"
    }
    
    $resource_dump_files = @{}
    $resource_dumps = @{}
    DumpResourceFiles $FileName $resource_dump_files
    $resource_dump_files.Keys | ForEach-Object {
        $resource_dumps[$_] = [Xml](Get-Content $resource_dump_files[$_])
    }

    $build_candidates_file = "$($FileName).log\BuildCandidates.txt"
    $anonymous_file = "$($FileName).log\ResourceAnonymousFiles.txt"
    $named_file = "$($FileName).log\ResourceNamedFiles.txt"
    $mapping_file = "$($FileName).log\ResourceNamedMapping.txt"

    EnumerateBuildCandidates $resource_dumps $build_candidates_file
    EnumerateAnonymousResources $resource_dumps $anonymous_file
    EnumerateNamedResources $resource_dumps $named_file $mapping_file

    if ($dump) {
        Write-Host "Dumps:"
        Write-Host "    $($build_candidates_file)"
        Write-Host "    $($anonymous_file)"
        Write-Host "    $($named_file)"
        Write-Host "    $($mapping_file)"
    }

    if (-not $dump) {
        Write-Host "Rebuilding all outdated binaries ..."
        $build_candidates = Get-Content $build_candidates_file

        (@() + (ForceArray (Get-Content $anonymous_file)) + (ForceArray(Get-Content $named_file))) | ForEach-Object {
            try {
                if ($build_candidates -contains $_) {
                    Write-Host "[BUILD] $($_)"
                    & $PSScriptRoot\GacGen.ps1 -FileName $_ -MappingFileName $mapping_file
                } else {
                    Write-Host "[SKIPPED] $($_)"
                }
            } catch {
                Write-Host $_.Exception.Message -ForegroundColor Red
            }
        }
    }
}
catch {
    Write-Host $_.Exception.Message -ForegroundColor Red
}

Set-ItemProperty $dontshowui_key -Name DontShowUI -Value $dontshowui_value
[Console]::ResetColor()