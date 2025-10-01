# Makefile para Astucia Naval
# Compilador y flags
CXX = cl
CXXFLAGS = /EHsc /std:c++17 /W3
TARGET = astucia_naval.exe

# Archivos fuente
SOURCES = src/main.cpp src/FileManager.cpp src/GameManager.cpp src/Player.cpp src/Tablero.cpp src/ValidacionesUtils.cpp

# Archivos objeto (se generan automáticamente)
OBJECTS = $(SOURCES:.cpp=.obj)

# Regla principal
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) /Fe:$(TARGET)
	@echo Compilacion exitosa: $(TARGET)

# Compilar archivos objeto
%.obj: %.cpp
	$(CXX) $(CXXFLAGS) /c $< /Fo$@

# Limpiar archivos temporales
clean:
	@if exist "*.obj" del /q "*.obj"
	@if exist "*.pdb" del /q "*.pdb"
	@if exist "*.ilk" del /q "*.ilk"
	@if exist "*.exp" del /q "*.exp"
	@if exist "*.lib" del /q "*.lib"
	@echo Archivos temporales eliminados

# Limpiar todo (incluyendo ejecutable)
distclean: clean
	@if exist "$(TARGET)" del /q "$(TARGET)"
	@echo Ejecutable eliminado

# Ayuda
help:
	@echo Comandos disponibles:
	@echo   make        - Compilar el juego
	@echo   make clean  - Limpiar archivos temporales
	@echo   make distclean - Limpiar todo
	@echo   make help   - Mostrar esta ayuda

# Marcar como phony
.PHONY: all clean distclean help
