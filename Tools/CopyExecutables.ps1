$ErrorActionPreference = "Stop"
$executables = @("CodePack", "CppMerge", "GacGen", "GacBuild", "GlrParserGen", "UiaListApp", "UiaListCli", "GitTui")

foreach ($name in $executables) {
    $source = Join-Path $PSScriptRoot "Executables\x64\Release\$name.exe"
    if (-not (Test-Path -LiteralPath $source -PathType Leaf)) {
        throw "Missing $source. Build Executables.sln in Release|x64 first."
    }
}

foreach ($name in $executables) {
    Copy-Item -LiteralPath (Join-Path $PSScriptRoot "Executables\x64\Release\$name.exe") -Destination $PSScriptRoot -Force
}
