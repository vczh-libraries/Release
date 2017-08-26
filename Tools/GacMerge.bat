@set /P CppOutput=< %1.log\x32\CppOutput.txt
@for %%i in (%1.log\x32\Source\*.*) do @(
	echo Processing %%~nxi ...
	%~dp0CppMerge.exe %1.log\x32\Source\%%~nxi %1.log\x64\Source\%%~nxi %CppOutput%\%%~nxi
)