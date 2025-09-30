# Script para limpiar archivos temporales de compilación
Write-Host "Limpiando archivos temporales..." -ForegroundColor Yellow

# Eliminar archivos .obj
Get-ChildItem -Path "." -Filter "*.obj" | Remove-Item -Force
Write-Host "Archivos .obj eliminados" -ForegroundColor Green

# Eliminar archivos .pdb (si existen)
Get-ChildItem -Path "." -Filter "*.pdb" | Remove-Item -Force
Write-Host "Archivos .pdb eliminados" -ForegroundColor Green

# Eliminar archivos .ilk (si existen)
Get-ChildItem -Path "." -Filter "*.ilk" | Remove-Item -Force
Write-Host "Archivos .ilk eliminados" -ForegroundColor Green

# Eliminar archivos .exp (si existen)
Get-ChildItem -Path "." -Filter "*.exp" | Remove-Item -Force
Write-Host "Archivos .exp eliminados" -ForegroundColor Green

# Eliminar archivos .lib (si existen)
Get-ChildItem -Path "." -Filter "*.lib" | Remove-Item -Force
Write-Host "Archivos .lib eliminados" -ForegroundColor Green

Write-Host "¡Limpieza completada!" -ForegroundColor Green
Write-Host "Archivos restantes:" -ForegroundColor Cyan
Get-ChildItem -Path "." | Where-Object { $_.Name -notlike "src" -and $_.Name -notlike "logs" -and $_.Name -notlike "saves" } | Select-Object Name, Length
