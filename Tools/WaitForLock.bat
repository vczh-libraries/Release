@timeout 1 > nul
:wait_for_lock
@if not exist *.wait.tmp goto :finish_lock
	@timeout 1 > nul
@goto wait_for_lock
:finish_lock