#include "GameManager.h"
#include "ValidacionesUtils.h"
#include <cstdlib>
#include <sstream>

// Colores para interfaz
#define COLOR_TURNO     "\x1B[35m"
#define COLOR_IMPACTO   "\x1B[31m"
#define COLOR_AGUA      "\x1B[34m"
#define COLOR_HUNDIDO   "\x1B[91m"
#define COLOR_VICTORIA  "\x1B[32m"
#define COLOR_INFO      "\x1B[36m"
#define RESET           "\x1b[0m"

GameManager::GameManager() {
    jugador1 = nullptr;
    jugador2 = nullptr;
    jugadorActual = nullptr;
    turnoJugador1 = true;
    juegoTerminado = false;
    nombrePartida = "";
    fileManager = new FileManager();
}

GameManager::~GameManager() {
    delete jugador1;
    delete jugador2;
    delete fileManager;
}

void GameManager::IniciarNuevaPartida(const string& nombre1, const string& nombre2) {
    cout << COLOR_INFO << "\nIniciando nueva partida..." << RESET << endl;
    
    // Crear jugadores
    if (jugador1) delete jugador1;
    if (jugador2) delete jugador2;
    
    jugador1 = new Player(nombre1);
    jugador2 = new Player(nombre2);
    
    turnoJugador1 = true;
    jugadorActual = jugador1;
    juegoTerminado = false;
    
    // Generar nombre único para la partida
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y%m%d_%H%M%S", timeinfo);
    nombrePartida = "partida_" + string(buffer);
    
    cout << COLOR_INFO << "Partida creada: " << nombrePartida << RESET << endl;
    
    // Iniciar fases del juego
    FaseColocarBarcos();
    if (!juegoTerminado) {
        FaseJuego();
    }
}

bool GameManager::CargarPartida(const string& nombreArchivo) {
    cout << COLOR_INFO << "\nCargando partida: " << nombreArchivo << RESET << endl;
    
    if (!fileManager->ValidarArchivo(nombreArchivo)) {
        cout << COLOR_IMPACTO << "Archivo no encontrado o inválido." << RESET << endl;
        return false;
    }
    
    // Limpiar jugadores existentes
    if (jugador1) delete jugador1;
    if (jugador2) delete jugador2;
    
    if (fileManager->CargarPartida(nombreArchivo, this)) {
        nombrePartida = nombreArchivo;
        jugadorActual = turnoJugador1 ? jugador1 : jugador2;
        cout << COLOR_VICTORIA << "Partida cargada exitosamente!" << RESET << endl;
        return true;
    } else {
        cout << COLOR_IMPACTO << "Error al cargar la partida." << RESET << endl;
        return false;
    }
}

bool GameManager::GuardarPartida(const string& nombreArchivo) {
    cout << COLOR_INFO << "\nGuardando partida..." << RESET << endl;
    
    if (fileManager->GuardarPartida(nombreArchivo, this)) {
        cout << COLOR_VICTORIA << "Partida guardada como: " << nombreArchivo << RESET << endl;
        return true;
    } else {
        cout << COLOR_IMPACTO << "Error al guardar la partida." << RESET << endl;
        return false;
    }
}

void GameManager::ContinuarPartida() {
    cout << COLOR_INFO << "\nContinuando partida..." << RESET << endl;
    MostrarEstadoJuego();
    
    if (!juegoTerminado) {
        FaseJuego();
    } else {
        cout << COLOR_VICTORIA << "Esta partida ya ha terminado." << RESET << endl;
    }
}

void GameManager::FaseColocarBarcos() {
    cout << COLOR_INFO << "\nFASE: COLOCAR BARCOS" << RESET << endl;
    cout << "════════════════════════════════════" << endl;
    
    // Jugador 1 coloca barcos
    cout << COLOR_TURNO << "\nTurno de " << jugador1->GetNombre() 
         << " para colocar barcos" << RESET << endl;
    jugador1->ColocarBarco();
    
    // Limpiar pantalla
    cout << "\nPresione Enter para continuar con el siguiente jugador...";
    cin.get();
    system("clear || cls");
    
    // Jugador 2 coloca barcos  
    cout << COLOR_TURNO << "\nTurno de " << jugador2->GetNombre() 
         << " para colocar barcos" << RESET << endl;
    jugador2->ColocarBarco();
    
    cout << "\nPresione Enter para comenzar la batalla...";
    cin.get();
    system("clear || cls");
}

void GameManager::FaseJuego() {
    cout << COLOR_INFO << "\nFASE: BATALLA NAVAL" << RESET << endl;
    cout << "════════════════════════════════════" << endl;
    
    while (!juegoTerminado) {
        MostrarEstadoJuego();
        ProcesarTurno();
        
        if (VerificarVictoria(jugador1)) {
            cout << COLOR_VICTORIA << "\n ¡" << jugador1->GetNombre() 
                 << " ha ganado la batalla!" << RESET << endl;
            juegoTerminado = true;
        } else if (VerificarVictoria(jugador2)) {
            cout << COLOR_VICTORIA << "\n ¡" << jugador2->GetNombre() 
                 << " ha ganado la batalla!" << RESET << endl;
            juegoTerminado = true;
        }
        
        if (!juegoTerminado) {
            CambiarTurno();
        }
    }
    
    // Ofrecer guardar partida final
    string respuesta;
    cout << "\n¿Desea guardar esta partida terminada? (s/n): ";
    cin >> respuesta;
    if (respuesta == "s" || respuesta == "S") {
        GuardarPartida(nombrePartida + "_final");
    }
}

void GameManager::ProcesarTurno() {
    cout << COLOR_TURNO << "\nTurno de: " << jugadorActual->GetNombre() << RESET << endl;
    cout << "Comandos disponibles:" << endl;
    cout << "• Coordenadas (ej: 5 10) - Disparar" << endl;
    cout << "• SAVE nombre - Guardar partida" << endl;
    cout << "• QUIT - Salir del juego" << endl;
    cout << "• HELP - Mostrar ayuda" << endl;
    
    string entrada;
    cout << "\nIngrese comando: ";
    getline(cin, entrada);
    
    // Verificar comandos especiales
    if (entrada.find("SAVE") == 0) {
        ProcesarComandoEspecial(entrada);
        return;
    } else if (entrada == "QUIT") {
        cout << "¿Guardar partida antes de salir? (s/n): ";
        string respuesta;
        cin >> respuesta;
        if (respuesta == "s" || respuesta == "S") {
            GuardarPartida(nombrePartida + "_temp");
        }
        exit(0);
    } else if (entrada == "HELP") {
        cout << COLOR_INFO << "\nAYUDA:" << endl;
        cout << "• Ingrese coordenadas X Y para disparar" << endl;
        cout << "• Las coordenadas van de 0 a 9" << endl;
        cout << "• Rojo = Impacto, Blanco = Agua" << RESET << endl;
        return;
    }
    
    // Procesar disparo
    istringstream iss(entrada);
    int x, y;
    if (iss >> x >> y) {
        if (ValidacionesUtils::ValidarCoordenadas(x, y)) {
            ProcesarDisparo(x, y);
        } else {
            cout << COLOR_IMPACTO << "Coordenadas inválidas. Rango: 0-9" << RESET << endl;
        }
    } else {
        cout << COLOR_IMPACTO << "Formato incorrecto. Use: X Y" << RESET << endl;
    }
}

bool GameManager::ProcesarDisparo(int x, int y) {
    Player* objetivo = turnoJugador1 ? jugador2 : jugador1;
    
    cout << COLOR_INFO << "\n" << jugadorActual->GetNombre() 
         << " dispara a (" << x << ", " << y << ")" << RESET << endl;
    
    bool impacto = objetivo->RecibirDisparo(x, y);
    jugadorActual->RegistrarDisparo(x, y, impacto);
    
    if (impacto) {
        cout << COLOR_IMPACTO << "¡IMPACTO!" << RESET << endl;
        
        // Verificar si se hundió un barco
        if (objetivo->VerificarBarcoHundido(x, y)) {
            cout << COLOR_HUNDIDO << "¡BARCO HUNDIDO!" << RESET << endl;
        }
        
        return true;
    } else {
        cout << COLOR_AGUA << "Agua..." << RESET << endl;
        return false;
    }
}

void GameManager::CambiarTurno() {
    turnoJugador1 = !turnoJugador1;
    jugadorActual = turnoJugador1 ? jugador1 : jugador2;
    
    cout << "\n" << COLOR_TURNO << "Cambio de turno" << RESET;
    cout << "\nPresione Enter para continuar...";
    cin.get();
    system("clear || cls");
}

bool GameManager::VerificarVictoria(Player* jugador) {
    return jugador->TodosLosBarcosDerrotados();
}

void GameManager::MostrarEstadoJuego() {
    cout << COLOR_INFO << "\nESTADO DEL JUEGO" << RESET << endl;
    cout << "════════════════════════════════════" << endl;
    cout << "Partida: " << nombrePartida << endl;
    cout << "Jugador 1: " << jugador1->GetNombre() 
         << " | Barcos restantes: " << jugador1->GetBarcosRestantes() << endl;
    cout << "Jugador 2: " << jugador2->GetNombre() 
         << " | Barcos restantes: " << jugador2->GetBarcosRestantes() << endl;
    cout << "Turno actual: " << jugadorActual->GetNombre() << endl;
    cout << "════════════════════════════════════" << endl;
    
    // Mostrar tablero del jugador actual
    cout << "\nSu tablero:" << endl;
    jugadorActual->MostarTablerosPropio();
    
    cout << "\nTablero enemigo (sus disparos):" << endl;
    jugadorActual->MostrarTableroEnemigo();
}

void GameManager::ProcesarComandoEspecial(const string& comando) {
    if (comando.find("SAVE ") == 0) {
        string nombreArchivo = comando.substr(5);
        if (nombreArchivo.empty()) {
            nombreArchivo = nombrePartida + "_manual";
        }
        GuardarPartida(nombreArchivo);
    }
}

// Setters para carga de partidas
void GameManager::SetTurnoJugador1(bool turno) {
    turnoJugador1 = turno;
    jugadorActual = turnoJugador1 ? jugador1 : jugador2;
}

void GameManager::SetJuegoTerminado(bool terminado) {
    juegoTerminado = terminado;
}

void GameManager::SetJugadores(Player* j1, Player* j2) {
    // Limpiar jugadores existentes
    if (jugador1) delete jugador1;
    if (jugador2) delete jugador2;
    
    // Asignar nuevos jugadores
    jugador1 = j1;
    jugador2 = j2;
    
    // Actualizar jugador actual
    jugadorActual = turnoJugador1 ? jugador1 : jugador2;
}