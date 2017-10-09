param (
    [String]$FileName
)
Write-Host "Compiling GacUI Resource: $FileName ..."
$gacgen_32 = Start-Process "$PSScriptRoot\GacGen32.exe" -ArgumentList "/P $FileName" -PassThru
$gacgen_64 = Start-Process "$PSScriptRoot\GacGen64.exe" -ArgumentList "/P $FileName" -PassThru
$gacgen_32.WaitForExit()
$gacgen_64.WaitForExit()

if (Test-Path -Path "$($FileName).log\x32\Error.txt") {
    throw "Failed to compile GacUI Resource (x86): $FileName"
}
if (Test-Path -Path "$($FileName).log\x64\Error.txt") {
    throw "Failed to compile GacUI Resource (x64): $FileName"
}
    
$output_folder = Get-Content "$($FileName).log\x32\CppOutput.txt"
$x32_folder = "$($FileName).log\x32\Source"
$x64_folder = "$($FileName).log\x64\Source"
if (!(Test-Path -Path $output_folder)) {
    New-Item $output_folder -ItemType directory | Out-Null
}
Get-ChildItem -Path $output_folder -ErrorAction SilentlyContinue | %{
    Write-Host "    Merging C++ Source File: $($_.Name) ..."
    $cppmerge = Start-Process "$PSScriptRoot\CppMerge.exe" -ArgumentList "/P `"$x32_folder\$($_.Name)`" `"$x64_folder\$($_.Name)`" `"$output_folder\$($_.Name)`"" -PassThru
    $cppmerge.WaitForExit();
}