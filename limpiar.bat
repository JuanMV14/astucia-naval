@echo off
echo Limpiando archivos temporales...

REM Eliminar archivos .obj
if exist "*.obj" (
    del /q "*.obj"
    echo Archivos .obj eliminados
)

REM Eliminar archivos .pdb
if exist "*.pdb" (
    del /q "*.pdb"
    echo Archivos .pdb eliminados
)

REM Eliminar archivos .ilk
if exist "*.ilk" (
    del /q "*.ilk"
    echo Archivos .ilk eliminados
)

REM Eliminar archivos .exp
if exist "*.exp" (
    del /q "*.exp"
    echo Archivos .exp eliminados
)

REM Eliminar archivos .lib
if exist "*.lib" (
    del /q "*.lib"
    echo Archivos .lib eliminados
)

echo ¡Limpieza completada!
echo Archivos restantes:
dir /b | findstr /v "src logs saves"

pause
