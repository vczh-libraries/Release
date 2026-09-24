$ErrorActionPreference = "Stop"
$executables = @("CodePack", "CppMerge", "GacGen", "GlrParserGen", "UiaListApp", "GitTui")

foreach ($name in $executables) {
    $source = Join-Path $PSScriptRoot "Executables\Release\$name.exe"
    if (-not (Test-Path -LiteralPath $source -PathType Leaf)) {
        throw "Missing $source. Build Executables.sln in Release|x86 first."
    }
}

foreach ($name in $executables) {
    Copy-Item -LiteralPath (Join-Path $PSScriptRoot "Executables\Release\$name.exe") -Destination $PSScriptRoot -Force
}
