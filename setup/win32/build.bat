rem Setup the default colors for rxvt.
set MSYSBGCOLOR=White
set MSYSFGCOLOR=Black
set MINGW32BGCOLOR=Black
set MINGW32FGCOLOR=Green
set BGCOLOR=%MSYSBGCOLOR%
set FGCOLOR=%MSYSFGCOLOR%
set BGCOLOR=%MINGW32BGCOLOR%
set FGCOLOR=%MINGW32FGCOLOR%

set WD=%~dp0\..\..\platform\windows\support\msys\1.0\bin\

call %WD%rxvt -backspacekey  -sl 2500 -fg %FGCOLOR% -bg %BGCOLOR% -sr -fn Courier-12 -tn msys -geometry 80x25 -e /bin/sh --login -i %~dp0\..\sdl2.sh
