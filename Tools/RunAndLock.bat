echo > %1.wait.tmp
call %~2
del %1.wait.tmp
exit