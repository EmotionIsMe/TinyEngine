@echo off
pushd ..\
call vendor\premake\bin\premake5.exe vs2017
popd
PAUSE