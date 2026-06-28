@echo off
setlocal

set "ROOT=%~dp0.."
set "VSDEVCMD=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

if not exist "%VSDEVCMD%" (
    echo Visual Studio developer command script not found:
    echo %VSDEVCMD%
    exit /b 1
)

call "%VSDEVCMD%" -arch=x64 -host_arch=x64
if errorlevel 1 exit /b %errorlevel%

msbuild "%ROOT%\Pocket Cube.sln" /p:Configuration=Debug /p:Platform=x64 /m
exit /b %errorlevel%
