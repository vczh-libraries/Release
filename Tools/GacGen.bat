del *.wait.tmp
start %~dp0RunAndLock %RANDOM% "%~dp0GacGen32.exe /P %1"
start %~dp0RunAndLock %RANDOM% "%~dp0GacGen64.exe /P %1"
call %~dp0WaitForLock

@if exist %1.log\x32\Error.txt (
	@echo "Error occurs: %1.log\x32\Error.txt"
	@exit
)

@if exist %1.log\x64\Error.txt (
	@echo "Error occurs: %1.log\x64\Error.txt"
	@exit
)

call %~dp0GacMerge %1