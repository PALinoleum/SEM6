@echo off
set loopcount=10000
:loop
start /b client < input.txt
set /a loopcount=loopcount-1
if %loopcount%==0 goto exitloop
goto loop
:exitloop
pause


