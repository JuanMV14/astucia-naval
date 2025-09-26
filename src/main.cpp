#include <iostream>
#include <string>
#include <cstdlib>
#include "GameManager.h"
#include "Player.h"
#include "ValidacionesUtils.h"

using namespace std;

// Colores para la interfaz
#define COLOR_TITULO    "\x1B[36m"
#define COLOR_MENU      "\x1B[33m"  
#define COLOR_ERROR     "\x1B[31m"
#define COLOR_EXITO     "\x1B[32m"
#define RESET           "\x1b[0m"

class MenuPrincipal {
private:
    GameManager* gameManager;
    
public:
    MenuPrincipal();
    ~MenuPrincipal();
    void MostrarTitulo();
    void MostrarMenu();
    int ObtenerOpcion();
    void EjecutarOpcion(int opcion);
    void IniciarNuevaPartida();
    void CargarPartida();
    void MostrarCreditos();
    void Run();
};

MenuPrincipal::MenuPrincipal() {
    gameManager = new GameManager();
}

MenuPrincipal::~MenuPrincipal() {
    delete gameManager;
}

void MenuPrincipal::MostrarTitulo() {
    system("clear || cls"); // Limpiar pantalla
    cout << COLOR_TITULO;
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║            ASTUCIA NAVAL             ║" << endl;
    cout << "║          Battleship Game             ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║    Desarrollado por:                 ║" << endl;
    cout << "║    • Juan                            ║" << endl;
    cout << "║    • Stella                          ║" << endl;
    cout << "║    • Iván                            ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << RESET << endl;
}

void MenuPrincipal::MostrarMenu() {
    cout << COLOR_MENU;
    cout << "┌─────────────────────────────┐" << endl;
    cout << "│         MENÚ PRINCIPAL      │" << endl;
    cout << "├─────────────────────────────┤" << endl;
    cout << "│  1. Nueva Partida           │" << endl;
    cout << "│  2. Cargar Partida          │" << endl;
    cout << "│  3. Créditos                │" << endl;
    cout << "│  4. Salir                   │" << endl;
    cout << "└─────────────────────────────┘" << endl;
    cout << RESET;
}

int MenuPrincipal::ObtenerOpcion() {
    int opcion;
    cout << "\nSeleccione una opción (1-4): ";
    cin >> opcion;
    
    if (cin.fail() || opcion < 1 || opcion > 4) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << COLOR_ERROR << "  Opción inválida. Intente nuevamente." << RESET << endl;
        return -1;
    }
    
    return opcion;
}

void MenuPrincipal::EjecutarOpcion(int opcion) {
    switch(opcion) {
        case 1:
            IniciarNuevaPartida();
            break;
        case 2:
            CargarPartida();
            break;
        case 3:
            MostrarCreditos();
            break;
        case 4:
            cout << COLOR_EXITO << "¡Gracias por jugar Astucia Naval!" << RESET << endl;
            exit(0);
            break;
    }
}

void MenuPrincipal::IniciarNuevaPartida() {
    system("clear || cls");
    cout << COLOR_TITULO << " NUEVA PARTIDA" << RESET << endl << endl;
    
    string nombreJugador1, nombreJugador2;
    
    cout << "Ingrese nombre del Jugador 1: ";
    cin >> nombreJugador1;
    cout << "Ingrese nombre del Jugador 2: ";
    cin >> nombreJugador2;
    
    // Validar nombres
    if (!ValidacionesUtils::ValidarNombre(nombreJugador1) || 
        !ValidacionesUtils::ValidarNombre(nombreJugador2)) {
        cout << COLOR_ERROR << " Nombres inválidos. Presione Enter para continuar." << RESET;
        cin.get();
        cin.get();
        return;
    }
    
    cout << COLOR_EXITO << " Iniciando partida entre " << nombreJugador1 
         << " y " << nombreJugador2 << "..." << RESET << endl;
    
    gameManager->IniciarNuevaPartida(nombreJugador1, nombreJugador2);
}

void MenuPrincipal::CargarPartida() {
    system("clear || cls");
    cout << COLOR_TITULO << " CARGAR PARTIDA" << RESET << endl << endl;
    
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo de guardado: ";
    cin >> nombreArchivo;
    
    if (gameManager->CargarPartida(nombreArchivo)) {
        cout << COLOR_EXITO << " Partida cargada exitosamente!" << RESET << endl;
        gameManager->ContinuarPartida();
    } else {
        cout << COLOR_ERROR << " Error al cargar la partida. Presione Enter para continuar." << RESET;
        cin.get();
        cin.get();
    }
}

void MenuPrincipal::MostrarCreditos() {
    system("clear || cls");
    cout << COLOR_TITULO;
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║                CRÉDITOS              ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║                                      ║" << endl;
    cout << "║     EQUIPO DE DESARROLLO:              ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Juan - Menú Principal             ║" << endl;
    cout << "║           Integración General        ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Stella - Lógica del Juego         ║" << endl;
    cout << "║             Sistema de Archivos      ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Iván - Gestión de Jugadores       ║" << endl;
    cout << "║           Validaciones               ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║     Ingeniería en Ciencia de Datos   ║" << endl;
    cout << "║     Tercer Semestre - 2024           ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << RESET << endl;
    
    cout << "Presione Enter para volver al menú principal...";
    cin.get();
    cin.get();
}

void MenuPrincipal::Run() {
    while (true) {
        MostrarTitulo();
        MostrarMenu();
        
        int opcion = ObtenerOpcion();
        if (opcion != -1) {
            EjecutarOpcion(opcion);
        }
        
        // Pausa antes de mostrar el menú nuevamente
        if (opcion != 4) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
            if (opcion != -1) cin.get(); // Extra get si la entrada fue válida
        }
    }
}

int main() {
    MenuPrincipal menu;
    menu.Run();
    return 0;
}