@echo off
echo Compilando Astucia Naval...

REM Intentar encontrar Visual Studio
set VS_PATH=
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    set VS_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
    set VS_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
    set VS_PATH="C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat" (
    set VS_PATH="C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
)

if defined VS_PATH (
    echo Encontrado Visual Studio en: %VS_PATH%
    call %VS_PATH%
    cl /EHsc /std:c++17 src\main.cpp src\FileManager.cpp src\GameManager.cpp src\Player.cpp src\Tablero.cpp src\ValidacionesUtils.cpp /Fe:astucia_naval.exe
) else (
    echo Visual Studio no encontrado. Intentando compilar directamente...
    cl /EHsc /std:c++17 src\main.cpp src\FileManager.cpp src\GameManager.cpp src\Player.cpp src\Tablero.cpp src\ValidacionesUtils.cpp /Fe:astucia_naval.exe
)

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ¡COMPILACION EXITOSA!
    echo Ejecutable creado: astucia_naval.exe
    
    REM Limpiar archivos temporales
    echo Limpiando archivos temporales...
    del /q *.obj 2>nul
    del /q *.pdb 2>nul
    del /q *.ilk 2>nul
    del /q *.exp 2>nul
    del /q *.lib 2>nul
    echo Archivos temporales eliminados
    
    echo.
    echo Para ejecutar: astucia_naval.exe
) else (
    echo.
    echo Error en la compilacion.
)

pause
