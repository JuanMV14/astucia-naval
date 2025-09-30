@echo off
echo Compilando Astucia Naval...

REM Intentar encontrar Visual Studio
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
) else (
    echo No se encontro Visual Studio. Intentando compilar directamente...
)

REM Compilar el proyecto
cl /EHsc src\main.cpp src\ValidacionesUtils.cpp src\Player.cpp src\juego_base.cpp /Fe:astucia_naval.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ¡Compilacion exitosa! Ejecutable creado: astucia_naval.exe
    echo.
    pause
) else (
    echo.
    echo Error en la compilacion.
    echo.
    pause
)
