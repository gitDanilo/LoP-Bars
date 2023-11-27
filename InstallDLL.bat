@echo off

if [%1]==[] goto :usage
if [%2]==[] goto :usage
if [%3]==[] goto :usage
if [%4]==[] goto :usage

set install_dir=C:\Program Files (x86)\Steam\steamapps\common\Lies of P\LiesofP\Binaries\Win64
set platform=%1
set config=%2
set dll_name=%3
set install_name=%4
set dll_path=".\%platform%\%config%\%dll_name%"
set dll_install_path="%install_dir%\%install_name%"

if not exist %dll_path% goto :invalid_param

if exist %dll_install_path% del /Q %dll_install_path%
copy /Y %dll_path% %dll_install_path% 1>NUL
echo DLL %install_name% installed!
goto :end

:invalid_param
echo Invalid parameters. Could not find: %dll_path%

:usage
echo Usage: %~nx0 [PLATFORM] [CONFIG] [DLL_NAME] [INSTALL_NAME]
echo Example: %~nx0 x64 Debug lop_bars.dll xinput1_3.dll

:end
