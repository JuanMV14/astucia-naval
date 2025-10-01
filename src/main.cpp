#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include "FileManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Tablero.h"
#include "ValidacionesUtils.h"

using namespace std;

// Instancia global del FileManager
FileManager* fileManager = nullptr;

// Colores para la interfaz
#define COLOR_TITULO    "\x1B[36m"
#define COLOR_MENU      "\x1B[33m"  
#define COLOR_ERROR     "\x1B[31m"
#define COLOR_EXITO     "\x1B[32m"
#define COLOR_INFO      "\x1B[34m"
#define COLOR_WARNING   "\x1B[35m"
#define RESET           "\x1b[0m"

class MenuPrincipal {
private:
    bool partidaActiva;
    Player* jugador1;
    Player* jugador2;
    
public:
    MenuPrincipal() : partidaActiva(false), jugador1(nullptr), jugador2(nullptr) {}
    
    void Run() {
        while (true) {
            MostrarTitulo();
            MostrarMenu();
            int opcion = ObtenerOpcion();
            ProcesarOpcion(opcion);
        }
    }
    
    void MostrarTitulo() {
        system("clear || cls");
        cout << COLOR_TITULO;
        cout << "========================================" << endl;
        cout << "|            ASTUCIA NAVAL             |" << endl;
        cout << "|          Battleship Game             |" << endl;
        cout << "|                                      |" << endl;
        cout << "|    Desarrollado por:                 |" << endl;
        cout << "|    - Juan                            |" << endl;
        cout << "|    - Stella                          |" << endl;
        cout << "|    - Ivan                            |" << endl;
        cout << "========================================" << endl;
        cout << RESET << endl;
    }
    
    void MostrarMenu() {
        cout << COLOR_MENU;
        cout << "+-----------------------------+" << endl;
        cout << "|         MENU PRINCIPAL      |" << endl;
        cout << "+-----------------------------+" << endl;
        cout << "|  1. Nueva Partida           |" << endl;
        cout << "|  2. Cargar Partida          |" << endl;
        cout << "|  3. Creditos                |" << endl;
        cout << "|  4. Salir                   |" << endl;
        cout << "+-----------------------------+" << endl;
        cout << RESET;
    }
    
    int ObtenerOpcion() {
        int opcion;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        return opcion;
    }
    
    void ProcesarOpcion(int opcion) {
        switch (opcion) {
            case 1:
                NuevaPartida();
                break;
            case 2:
                CargarPartida();
                break;
            case 3:
                MostrarCreditos();
                break;
            case 4:
                cout << COLOR_EXITO << "!Gracias por jugar Astucia Naval!" << RESET << endl;
                exit(0);
                break;
        }
    }
    
    void NuevaPartida() {
        system("clear || cls");
        cout << COLOR_TITULO << " NUEVA PARTIDA" << RESET << endl << endl;
        
        // Crear jugadores
        string nombre1, nombre2;
        cout << "Ingrese nombre del Jugador 1: ";
        cin >> nombre1;
        cout << "Ingrese nombre del Jugador 2: ";
        cin >> nombre2;
        
        jugador1 = new Player(nombre1);
        jugador2 = new Player(nombre2);
        partidaActiva = true;
        
        // Iniciar el juego
        JugarPartida();
    }
    
    void CargarPartida() {
        system("clear || cls");
        cout << COLOR_TITULO << " CARGAR PARTIDA" << RESET << endl << endl;
        
        if (!fileManager) {
            fileManager = new FileManager();
        }
        
        // Listar partidas guardadas
        vector<string> partidas = fileManager->ListarPartidas();
        
        if (partidas.empty()) {
            cout << COLOR_WARNING << " No hay partidas guardadas." << RESET << endl;
            cout << "Presione Enter para continuar...";
            cin.get();
            cin.get();
            return;
        }
        
        cout << COLOR_INFO << " Partidas disponibles:" << RESET << endl;
        for (size_t i = 0; i < partidas.size(); i++) {
            cout << " " << (i + 1) << ". " << partidas[i] << endl;
        }
        
        cout << "\nSeleccione una partida (0 para cancelar): ";
        int opcion;
        cin >> opcion;
        
        if (opcion < 1 || opcion > (int)partidas.size()) {
            cout << COLOR_ERROR << " Opcion invalida." << RESET << endl;
            cout << "Presione Enter para continuar...";
            cin.get();
            cin.get();
            return;
        }
        
        string nombreArchivo = partidas[opcion - 1];
        
        // Crear un GameManager temporal para cargar la partida
        GameManager* game = new GameManager();
        
        if (game->CargarPartida(nombreArchivo)) {
            cout << COLOR_EXITO << " Partida cargada exitosamente!" << RESET << endl;
            cout << "Presione Enter para continuar...";
            cin.get();
            cin.get();
            
            // Continuar la partida cargada
            game->ContinuarPartida();
        } else {
            cout << COLOR_ERROR << " Error al cargar la partida." << RESET << endl;
            cout << "Presione Enter para continuar...";
            cin.get();
            cin.get();
        }
        
        delete game;
    }
    
    void MostrarCreditos() {
        system("clear || cls");
        cout << COLOR_TITULO;
        cout << "========================================" << endl;
        cout << "|                CREDITOS              |" << endl;
        cout << "========================================" << endl;
        cout << "|                                      |" << endl;
        cout << "|     EQUIPO DE DESARROLLO:            |" << endl;
        cout << "|                                      |" << endl;
        cout << "|  - Ivan - Menu Principal             |" << endl;
        cout << "|           Integracion General        |" << endl;
        cout << "|                                      |" << endl;
        cout << "|  - Stella - Logica del Juego         |" << endl;
        cout << "|             Sistema de Archivos      |" << endl;
        cout << "|                                      |" << endl;
        cout << "|  - Juan - Gestion de Jugadores       |" << endl;
        cout << "|           Validaciones               |" << endl;
        cout << "|                                      |" << endl;
        cout << "|     Ingenieria en Ciencia de Datos   |" << endl;
        cout << "|     Tercer Semestre - 2025           |" << endl;
        cout << "|                                      |" << endl;
        cout << "========================================" << endl;
        cout << RESET << endl;
        
        cout << "Presione Enter para volver al menu principal...";
        cin.get();
        cin.get();
    }
    
    void JugarPartida() {
        if (!partidaActiva || !jugador1 || !jugador2) {
            cout << COLOR_ERROR << " No hay partida activa." << RESET << endl;
            return;
        }
        
        cout << COLOR_TITULO << " INICIANDO JUEGO" << RESET << endl << endl;
        
        // Fase 1: Colocacion de barcos
        cout << "=== FASE DE COLOCACION DE BARCOS ===" << endl;
        
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
            
            // Opción para guardar partida
            cout << COLOR_INFO << " Opciones: [1] Continuar | [2] Guardar y salir" << RESET << endl;
            cout << "Seleccione opcion: ";
            int opcion;
            cin >> opcion;
            
            if (opcion == 2) {
                // Guardar partida
                if (!fileManager) {
                    fileManager = new FileManager();
                }
                
                cout << "Ingrese nombre para la partida: ";
                string nombrePartida;
                cin.ignore();
                getline(cin, nombrePartida);
                
                // Crear un GameManager temporal para guardar
                GameManager* game = new GameManager();
                // Aquí necesitarías configurar el GameManager con los datos actuales
                
                if (fileManager->GuardarPartida(nombrePartida, game)) {
                    cout << COLOR_EXITO << " Partida guardada exitosamente!" << RESET << endl;
                } else {
                    cout << COLOR_ERROR << " Error al guardar la partida." << RESET << endl;
                }
                
                delete game;
                cout << "Presione Enter para volver al menu principal...";
                cin.get();
                return;
            }
            
            // Mostrar tableros
            jugadorActual->MostarTablerosPropio();
            cout << "\n";
            jugadorActual->MostrarTableroEnemigo();
            
            // Solicitar disparo
            cout << "\n" << jugadorActual->GetNombre() << ", ingresa coordenadas para disparar:" << endl;
            cout << "X: ";
            int x;
            cin >> x;
            cout << "Y: ";
            int y;
            cin >> y;
            
            // Realizar disparo
            if (jugadorActual->RealizarDisparo(x, y)) {
                bool impacto = jugadorEnemigo->RecibirDisparo(x, y);
                jugadorActual->AgregarDisparo(x, y, impacto);
                
                if (impacto) {
                    cout << COLOR_EXITO << "!IMPACTO!" << RESET << endl;
                } else {
                    cout << COLOR_INFO << "Agua" << RESET << endl;
                }
            }
            
            cout << "Presione Enter para continuar...";
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
        cout << COLOR_TITULO << " !JUEGO TERMINADO!" << RESET << endl;
        
        if (jugador1->TodosLosBarcosDerrotados()) {
            cout << COLOR_EXITO << "!" << jugador2->GetNombre() << " GANA!" << RESET << endl;
        } else {
            cout << COLOR_EXITO << "!" << jugador1->GetNombre() << " GANA!" << RESET << endl;
        }
        
        cout << "\nPresione Enter para volver al menu principal...";
        cin.get();
        cin.get();
        
        // Limpiar jugadores
        delete jugador1;
        delete jugador2;
        jugador1 = nullptr;
        jugador2 = nullptr;
        partidaActiva = false;
    }
};

int main() {
    srand(time(0));
    
    // Inicializar FileManager
    fileManager = new FileManager();
    
    MenuPrincipal menu;
    menu.Run();
    
    // Limpiar FileManager
    if (fileManager) {
        delete fileManager;
        fileManager = nullptr;
    }
    
    return 0;
}
