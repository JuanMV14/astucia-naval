# Script de compilación para Astucia Naval
Write-Host "Compilando Astucia Naval..." -ForegroundColor Green

# Intentar encontrar Visual Studio
$vsPath = $null
$possiblePaths = @(
    "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat",
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat",
    "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat",
    "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
)

foreach ($path in $possiblePaths) {
    if (Test-Path $path) {
        $vsPath = $path
        break
    }
}

if ($vsPath) {
    Write-Host "Encontrado Visual Studio en: $vsPath" -ForegroundColor Yellow
    cmd /c "`"$vsPath`" && cl /EHsc /std:c++17 src\main.cpp src\FileManager.cpp src\GameManager.cpp src\Player.cpp src\Tablero.cpp src\ValidacionesUtils.cpp /Fe:astucia_naval.exe"
} else {
    Write-Host "Visual Studio no encontrado. Intentando compilar directamente..." -ForegroundColor Yellow
    cl /EHsc /std:c++17 src\main.cpp src\FileManager.cpp src\GameManager.cpp src\Player.cpp src\Tablero.cpp src\ValidacionesUtils.cpp /Fe:astucia_naval.exe
}

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "¡COMPILACION EXITOSA!" -ForegroundColor Green
    Write-Host "Ejecutable creado: astucia_naval.exe" -ForegroundColor Cyan
    
    # Limpiar archivos temporales
    Write-Host "Limpiando archivos temporales..." -ForegroundColor Yellow
    Get-ChildItem -Path "." -Filter "*.obj" | Remove-Item -Force -ErrorAction SilentlyContinue
    Get-ChildItem -Path "." -Filter "*.pdb" | Remove-Item -Force -ErrorAction SilentlyContinue
    Get-ChildItem -Path "." -Filter "*.ilk" | Remove-Item -Force -ErrorAction SilentlyContinue
    Get-ChildItem -Path "." -Filter "*.exp" | Remove-Item -Force -ErrorAction SilentlyContinue
    Get-ChildItem -Path "." -Filter "*.lib" | Remove-Item -Force -ErrorAction SilentlyContinue
    Write-Host "Archivos temporales eliminados" -ForegroundColor Green
    
    Write-Host ""
    Write-Host "Para ejecutar: .\astucia_naval.exe" -ForegroundColor Yellow
} else {
    Write-Host ""
    Write-Host "Error en la compilacion." -ForegroundColor Red
}