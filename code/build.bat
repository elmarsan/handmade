::Usage: execute from root directory

:: do not output each command of the script
@echo off

:: Require cl (Microsoft visual studio tool for compiling using command line)

:: Push directory
mkdir ..\build
pushd ..\build
pwd
cl -Zi ..\code\win32_handmade.cpp user32.lib gdi32.lib
:: Come back to the above directory
popd
