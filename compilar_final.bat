@echo off
echo Compilando Astucia Naval (Version Final para Entrega)...

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

REM Compilar solo el main.cpp que funciona
cl /EHsc src\main.cpp /Fe:astucia_naval.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ¡COMPILACION EXITOSA!
    echo.
    echo Ejecutable creado: astucia_naval.exe
    echo.
    echo ¡El juego esta listo para entregar!
    echo.
    echo Para ejecutar: astucia_naval.exe
    echo.
    echo CARACTERISTICAS DEL JUEGO:
    echo - Tablero 10x10
    echo - 5 tipos de barcos
    echo - Colocacion manual de barcos
    echo - Sistema de turnos
    echo - Deteccion de impactos y hundimientos
    echo - Interfaz con colores
    echo - Menu completo funcional
    echo.
    pause
) else (
    echo.
    echo Error en la compilacion.
    echo.
    pause
)
