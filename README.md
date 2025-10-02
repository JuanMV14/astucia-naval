# astucia-naval

##  Descripción del Proyecto

Astucia Naval es una implementación del clásico juego de batalla naval desarrollada en C++ como proyecto académico para la materia de Programación. El juego permite a dos jugadores enfrentarse en una batalla naval estratégica con funcionalidades avanzadas de guardado y cargado de partidas.

##  Equipo de Desarrollo

| Desarrollador | Rol | Responsabilidades |
|---------------|-----|------------------|
| *Iván* | Integrador del Proyecto | Menú Principal, Integración, Documentación |
| *Stella* | Desarrolladora Backend | Lógica del Juego, Sistema de Archivos |
| *Juan* | Desarrollador Frontend | Gestión de Jugadores, Validaciones |

##  Características del Juego

###  Funcionalidades Principales
-  *Tablero 10x10*: Espacio de batalla optimizado
-  *Múltiples Barcos*: Diferentes tipos y tamaños
-  *Sistema de Disparos*: Mecánica precisa de impactos
-  *Guardar/Cargar*: Persistencia de partidas
-  *Interfaz Colorida*: Experiencia visual mejorada
-  *Validaciones*: Sistema robusto de verificación

###  Funcionalidades Técnicas
- *Arquitectura Modular*: Código organizado en clases especializadas
- *Manejo de Archivos*: Sistema completo de persistencia
- *Gestión de Memoria*: Uso eficiente de recursos
- *Control de Errores*: Manejo robusto de excepciones

##  Arquitectura del Proyecto

```
astucia-naval/
├── src/                      # Código fuente C++ (100%)
│   ├── main.cpp              # Punto de entrada y menú principal
│   ├── GameManager.h/cpp     # Lógica central del juego
│   ├── FileManager.h/cpp     # Sistema de archivos
│   ├── Player.h/cpp          # Gestión de jugadores
│   ├── Tablero.h/cpp         # Lógica del tablero
│   └── ValidacionesUtils.h/cpp # Utilidades de validación
├── saves/                    # Archivos de partidas guardadas
├── logs/                     # Archivos de log del sistema
├── astucia_naval.exe         # Ejecutable del juego
├── Makefile                  # Script de compilación (Linux/Mac)
├── compilar.bat              # Script de compilación (Windows)
├── limpiar.bat               # Script de limpieza (Windows)
└── README.md                 # Este archivo
```

###  **100% C++ - Sin dependencias externas**
- **Código fuente**: 100% C++ estándar
- **Compilación**: Makefile y scripts batch nativos
- **Ejecutable**: Binario independiente
- **Sin PowerShell**: Eliminados todos los scripts PowerShell


##  Diagrama de Clases UML

```mermaid
classDiagram
    class MenuPrincipal {
        -GameManager gameManager
        +MostrarTitulo()
        +MostrarMenu()
        +EjecutarOpcion(int)
        +Run()
    }
    
    class GameManager {
        -Player jugador1
        -Player jugador2
        -bool turnoJugador1
        +IniciarNuevaPartida(string, string)
        +CargarPartida(string)
        +GuardarPartida(string)
        +ProcesarDisparo(int, int)
    }
    
    class Player {
        -string nombre
        -Tablero tableroPropio
        -Tablero tableroEnemigo
        +ColocarBarcos()
        +RealizarDisparo()
        +RecibirDisparo(int, int)
    }
    
    class Tablero {
        -Casilla Core[20][20]
        -bool tipo
        +Mostrar()
        +PonerBarco(Barco)
        +VerificarImpacto(int, int)
    }
    
    class Casilla {
        -int estado
        +MarcarImpacto()
        +PonerBarco()
        +MarcarSinImpacto()
        +Mostrar(bool)
    }
    
    class FileManager {
        +GuardarPartida(GameManager)
        +CargarPartida(string)
        +ValidarArchivo(string)
    }
    
    MenuPrincipal --> GameManager
    GameManager --> Player
    GameManager --> FileManager
    Player --> Tablero
    Tablero --> Casilla
```

### Prerrequisitos
- Compilador C++ compatible con C++11 o superior
- Git para control de versiones
- Terminal/Línea de comandos

### Instalación

#### Opción 1: Ejecutar directamente (Recomendado)
```bash
# Clonar el repositorio
git clone https://github.com/JuanMV14/astucia-naval.git

# Navegar al directorio
cd astucia-naval

# Ejecutar el juego (ya compilado)
./astucia_naval.exe
```

#### Opción 2: Compilar desde código fuente

**En Windows (con Visual Studio):**
```bash
# Usar el script batch
compilar.bat

# O usar Makefile
make

# O compilación manual
cl /EHsc /std:c++17 src\main.cpp src\FileManager.cpp src\GameManager.cpp src\Player.cpp src\Tablero.cpp src\ValidacionesUtils.cpp /Fe:astucia_naval.exe
```

**En Linux/Mac:**
```bash
# Compilar con g++
g++ -std=c++17 -o astucia_naval src/*.cpp

# Ejecutar
./astucia_naval
```

#### Limpiar archivos temporales
```bash
# Windows
limpiar.bat
# O con Makefile
make clean

# Linux/Mac
make clean
```


### Uso del Juego
1. *Nueva Partida*: Inicia un juego nuevo entre dos jugadores
2. *Cargar Partida*: Continúa una partida previamente guardada
3. *Durante el Juego*: 
   - Coloca tus barcos estratégicamente
   - Realiza disparos en el tablero enemigo
   - Guarda tu progreso en cualquier momento

##  Desarrollo y Contribución

### Estructura de Ramas Git
- main: Rama principal estable
- feature/menu-principal: Desarrollo del menú (Juan)
- feature/logica-juego: Lógica del juego (Stella)  
- feature/jugadores-validaciones: Gestión de jugadores (Iván)

### Flujo de Desarrollo
1. Cada desarrollador trabaja en su rama específica
2. Commits frecuentes con mensajes descriptivos
3. Pull requests para revisión de código
4. Merge a main después de aprobación

### Comandos Git Útiles
bash
# Cambiar a tu rama de desarrollo
git checkout feature/tu-rama

# Agregar cambios
git add .
git commit -m "Descripción del cambio"

# Subir cambios
git push origin feature/tu-rama

# Actualizar desde main
git pull origin main


##  Sistema de Archivos

### Formato de Guardado
Las partidas se guardan en formato texto estructurado en la carpeta saves/:

nombreJugador1|nombreJugador2
turnoActual
estadoTablero1...
estadoTablero2...


### Archivos de Configuración
- Partidas guardadas: saves/partida_YYYYMMDD_HHMMSS.txt
- Logs del sistema: logs/game.log

##  Manual de Usuario

### Controles del Juego
- *Navegación*: Números (1-4) para opciones de menú
- *Coordenadas*: Formato (x,y) para posiciones
- *Comandos especiales*: 
  - GUARDAR nombre: Guardar partida (G)
  - SALIR: Salir del juego (S)

### Reglas del Juego
1. Cada jugador coloca sus barcos en el tablero
2. Los jugadores se turnan para disparar
3. Objetivo: Hundir todos los barcos del oponente
4. Tipos de impacto:
   - 🔴 Rojo: Impacto exitoso
   - ⚪ Blanco: Disparo al agua
   - 🔵 Azul: Mar (sin disparar)
   - ⚫ Gris: Barco propio

##  Testing

### Casos de Prueba
-  Creación de partida nueva
-  Guardado y cargado de partidas
-  Validación de coordenadas
-  Detección de victoria
-  Manejo de errores

### Ejecutar Pruebas
bash
# Compilar con flags de debug
g++ -g -Wall -o astucia_naval_debug src/*.cpp

# Ejecutar con valgrind (si está disponible)
valgrind ./astucia_naval_debug


##  Métricas del Proyecto

- *Líneas de Código*: ~800 líneas
- *Archivos Source*: 8 archivos
- *Classes*: 6 clases principales
- *Métodos*: 45+ métodos implementados
- *Commits*: 30+ commits colaborativos

##  Problemas Conocidos

- [ ] Validación mejorada para solapamiento de barcos
- [ ] Interfaz gráfica más avanzada
- [ ] Modo de juego contra IA
- [ ] Sonidos y efectos

##  Changelog

### Versión 1.0.0 (Actual)
-  Implementación completa del juego básico
-  Sistema de guardado/cargado
-  Interfaz de usuario mejorada
-  Validaciones robustas



## Licencia

Este proyecto es desarrollado con fines académicos para la materia de Esturcturas de datos en C++.

---

*Desarrollado con ❤️ por el equipo de Astucia Naval*  
Ingeniería en Ciencia de Datos - Tercer Semestre - 2025
