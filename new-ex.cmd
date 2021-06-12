@echo off

set exname=
if %1.==. (
    set /P exname=Name of example, preferrably without whitespace: 
) else (
    set exname=%1
)

if exist %exname%\ (
    echo Folder with name '%exname%' already exists! Aborting...
    exit /B 1
)

echo Generating new folder for example called '%exname%'
mkdir %exname%

echo Copying template files over...
xcopy /S .\templates\ .\%exname%\

echo Setting up environment...
cd %exname%
make mkdir
cd ..

echo Done!
exit /B 0

@echo on
