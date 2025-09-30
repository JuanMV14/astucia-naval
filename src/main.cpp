#include <iostream>
#include <string>
#include <cstdlib>
#include "Player.h"
#include "ValidacionesUtils.h"
#include "juego_base.cpp"

using namespace std;

// Colores para la interfaz
#define COLOR_TITULO    "\x1B[36m"
#define COLOR_MENU      "\x1B[33m"  
#define COLOR_ERROR     "\x1B[31m"
#define COLOR_EXITO     "\x1B[32m"
#define RESET           "\x1b[0m"

class MenuPrincipal {
private:
    Player* jugador1;
    Player* jugador2;
    bool partidaActiva;
    
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
    void JugarPartida();
    void Run();
};

MenuPrincipal::MenuPrincipal() {
    jugador1 = nullptr;
    jugador2 = nullptr;
    partidaActiva = false;
}

MenuPrincipal::~MenuPrincipal() {
    delete jugador1;
    delete jugador2;
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
    
    // Crear los jugadores
    delete jugador1;
    delete jugador2;
    jugador1 = new Player(nombreJugador1);
    jugador2 = new Player(nombreJugador2);
    partidaActiva = true;
    
    // Iniciar el juego
    JugarPartida();
}

void MenuPrincipal::CargarPartida() {
    system("clear || cls");
    cout << COLOR_TITULO << " CARGAR PARTIDA" << RESET << endl << endl;
    
    cout << COLOR_ERROR << " Funcionalidad de cargar partida no implementada aún." << RESET << endl;
    cout << "Presione Enter para continuar...";
    cin.get();
    cin.get();
}

void MenuPrincipal::MostrarCreditos() {
    system("clear || cls");
    cout << COLOR_TITULO;
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║                CRÉDITOS              ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║                                      ║" << endl;
    cout << "║     EQUIPO DE DESARROLLO:            ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Ivan - Menú Principal             ║" << endl;
    cout << "║           Integración General        ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Stella - Lógica del Juego         ║" << endl;
    cout << "║             Sistema de Archivos      ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Juan - Gestión de Jugadores       ║" << endl;
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

void MenuPrincipal::JugarPartida() {
    if (!partidaActiva || !jugador1 || !jugador2) {
        cout << COLOR_ERROR << " No hay partida activa." << RESET << endl;
        return;
    }
    
    cout << COLOR_TITULO << " INICIANDO JUEGO" << RESET << endl << endl;
    
    // Fase 1: Colocación de barcos
    cout << "=== FASE DE COLOCACIÓN DE BARCOS ===" << endl;
    
    cout << "\n" << jugador1->GetNombre() << ", coloca tus barcos:" << endl;
    jugador1->ColocarBarco();
    
    cout << "\n" << jugador2->GetNombre() << ", coloca tus barcos:" << endl;
    jugador2->ColocarBarco();
    
    // Fase 2: Juego principal
    cout << "\n=== INICIANDO BATALLA ===" << endl;
    
    Player* jugadorActual = jugador1;
    Player* jugadorEnemigo = jugador2;
    
    while (!jugador1->TodosLosBarcosDerrotados() && !jugador2->TodosLosBarcosDerrotados()) {
        system("clear || cls");
        
        cout << COLOR_TITULO << " TURNO DE " << jugadorActual->GetNombre() << RESET << endl;
        
        // Mostrar tableros
        jugadorActual->MostarTablerosPropio();
        cout << "\n";
        jugadorActual->MostrarTableroEnemigo();
        
        // Pedir coordenadas de disparo
        int x, y;
        cout << "\n" << jugadorActual->GetNombre() << ", ingresa coordenadas de disparo:" << endl;
        cout << "X (0-19): ";
        cin >> x;
        cout << "Y (0-19): ";
        cin >> y;
        
        // Realizar disparo
        if (jugadorActual->RealizarDisparo(x, y)) {
            bool impacto = jugadorEnemigo->RecibirDisparo(x, y);
            jugadorActual->AgregarDisparo(x, y, impacto);
            
            if (impacto) {
                cout << COLOR_EXITO << "¡IMPACTO!" << RESET << endl;
            } else {
                cout << COLOR_ERROR << "Agua..." << RESET << endl;
            }
        }
        
        // Mostrar estadísticas
        jugadorActual->MostrarEstadisticas();
        
        cout << "\nPresione Enter para continuar...";
        cin.get();
        cin.get();
        
        // Cambiar turno
        if (jugadorActual == jugador1) {
            jugadorActual = jugador2;
            jugadorEnemigo = jugador1;
        } else {
            jugadorActual = jugador1;
            jugadorEnemigo = jugador2;
        }
    }
    
    // Determinar ganador
    system("clear || cls");
    cout << COLOR_TITULO << " ¡JUEGO TERMINADO!" << RESET << endl;
    
    if (jugador1->TodosLosBarcosDerrotados()) {
        cout << COLOR_EXITO << "¡" << jugador2->GetNombre() << " GANA!" << RESET << endl;
    } else {
        cout << COLOR_EXITO << "¡" << jugador1->GetNombre() << " GANA!" << RESET << endl;
    }
    
    cout << "\nPresione Enter para volver al menú principal...";
    cin.get();
    cin.get();
    
    partidaActiva = false;
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
