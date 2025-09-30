#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

// Colores para la interfaz
#define COLOR_TITULO    "\x1B[36m"
#define COLOR_MENU      "\x1B[33m"  
#define COLOR_ERROR     "\x1B[31m"
#define COLOR_EXITO     "\x1B[32m"
#define COLOR_INFO      "\x1B[34m"
#define COLOR_WARNING   "\x1B[35m"
#define RESET           "\x1b[0m"

// Tamaño del tablero
const int TAMANO_TABLERO = 10;

class Tablero {
private:
    vector<vector<char>> casillas;
    int tamano;
    
public:
    Tablero() : tamano(TAMANO_TABLERO) {
        casillas.resize(tamano, vector<char>(tamano, '~'));
    }
    
    void Limpiar() {
        for (int i = 0; i < tamano; i++) {
            for (int j = 0; j < tamano; j++) {
                casillas[i][j] = '~';
            }
        }
    }
    
    void Mostrar(bool mostrarBarcos = false) {
        cout << "   ";
        for (int j = 0; j < tamano; j++) {
            cout << setw(3) << j;
        }
        cout << endl;
        
        for (int i = 0; i < tamano; i++) {
            cout << setw(2) << i << " ";
            for (int j = 0; j < tamano; j++) {
                char valor = casillas[i][j];
                if (!mostrarBarcos && valor == 'B') {
                    valor = '~'; // Ocultar barcos en tablero enemigo
                }
                cout << setw(3) << valor;
            }
            cout << endl;
        }
    }
    
    char ObtenerCasilla(int x, int y) {
        if (x >= 0 && x < tamano && y >= 0 && y < tamano) {
            return casillas[y][x];
        }
        return '?';
    }
    
    void EstablecerCasilla(int x, int y, char valor) {
        if (x >= 0 && x < tamano && y >= 0 && y < tamano) {
            casillas[y][x] = valor;
        }
    }
    
    bool EsValida(int x, int y) {
        return x >= 0 && x < tamano && y >= 0 && y < tamano;
    }
    
    bool EstaVacia(int x, int y) {
        return EsValida(x, y) && casillas[y][x] == '~';
    }
    
    int ObtenerTamano() { return tamano; }
};

class Barco {
public:
    int tamano;
    string nombre;
    vector<pair<int, int>> posiciones;
    vector<bool> partesHundidas;
    
    Barco(int t, string n) : tamano(t), nombre(n) {
        partesHundidas.resize(tamano, false);
    }
    
    bool EstaHundido() {
        for (bool hundido : partesHundidas) {
            if (!hundido) return false;
        }
        return true;
    }
    
    bool RecibirDisparo(int x, int y) {
        for (int i = 0; i < posiciones.size(); i++) {
            if (posiciones[i].first == x && posiciones[i].second == y) {
                partesHundidas[i] = true;
                return true;
            }
        }
        return false;
    }
};

class Player {
private:
    string nombre;
    Tablero tableroPropio;
    Tablero tableroEnemigo;
    vector<Barco> barcos;
    int barcosHundidos;
    
public:
    Player(string n) : nombre(n), barcosHundidos(0) {
        InicializarBarcos();
    }
    
    void InicializarBarcos() {
        barcos.clear();
        barcos.push_back(Barco(5, "Portaaviones"));
        barcos.push_back(Barco(4, "Acorazado"));
        barcos.push_back(Barco(3, "Crucero"));
        barcos.push_back(Barco(3, "Submarino"));
        barcos.push_back(Barco(2, "Destructor"));
    }
    
    string GetNombre() { return nombre; }
    
    void MostrarTableros() {
        cout << COLOR_INFO << "\n=== TABLERO DE " << nombre << " ===" << RESET << endl;
        cout << "\nTu tablero (con barcos):" << endl;
        tableroPropio.Mostrar(true);
        
        cout << "\nTablero enemigo (disparos):" << endl;
        tableroEnemigo.Mostrar(false);
    }
    
    void MostarTablerosPropio() {
        MostrarTableros();
    }
    
    void MostrarTableroEnemigo() {
        cout << "\nTablero enemigo:" << endl;
        tableroEnemigo.Mostrar(false);
    }
    
    bool ColocarBarco(Barco& barco, int x, int y, bool vertical) {
        vector<pair<int, int>> posiciones;
        
        // Verificar si cabe
        for (int i = 0; i < barco.tamano; i++) {
            int nx = vertical ? x : x + i;
            int ny = vertical ? y + i : y;
            
            if (!tableroPropio.EsValida(nx, ny) || !tableroPropio.EstaVacia(nx, ny)) {
                return false;
            }
            
            posiciones.push_back({nx, ny});
        }
        
        // Colocar el barco
        barco.posiciones = posiciones;
        for (auto pos : posiciones) {
            tableroPropio.EstablecerCasilla(pos.first, pos.second, 'B');
        }
        
        return true;
    }
    
    void ColocarBarco() {
        cout << COLOR_INFO << "\n" << nombre << ", coloca tus barcos:" << RESET << endl;
        
        for (auto& barco : barcos) {
            bool colocado = false;
            
            while (!colocado) {
                MostrarTableros();
                cout << "\nColoca tu " << barco.nombre << " (tamaño: " << barco.tamano << ")" << endl;
                cout << "Ingresa coordenada X (0-" << (TAMANO_TABLERO-1) << "): ";
                int x;
                cin >> x;
                
                cout << "Ingresa coordenada Y (0-" << (TAMANO_TABLERO-1) << "): ";
                int y;
                cin >> y;
                
                cout << "¿Vertical? (1=Si, 0=No): ";
                int v;
                cin >> v;
                bool vertical = (v == 1);
                
                colocado = ColocarBarco(barco, x, y, vertical);
                
                if (!colocado) {
                    cout << COLOR_ERROR << "Posición inválida. Intenta de nuevo." << RESET << endl;
                    cout << "Presiona Enter para continuar...";
                    cin.get();
                    cin.get();
                } else {
                    cout << COLOR_EXITO << barco.nombre << " colocado exitosamente!" << RESET << endl;
                }
            }
        }
    }
    
    bool RealizarDisparo(int x, int y) {
        if (!tableroEnemigo.EsValida(x, y)) {
            cout << COLOR_ERROR << "Coordenadas inválidas." << RESET << endl;
            return false;
        }
        
        char estado = tableroEnemigo.ObtenerCasilla(x, y);
        if (estado != '~') {
            cout << COLOR_ERROR << "Ya disparaste ahí antes." << RESET << endl;
            return false;
        }
        
        return true;
    }
    
    bool RecibirDisparo(int x, int y) {
        // Verificar impacto
        bool impacto = false;
        for (auto& barco : barcos) {
            if (barco.RecibirDisparo(x, y)) {
                impacto = true;
                tableroPropio.EstablecerCasilla(x, y, 'X');
                
                cout << COLOR_EXITO << "¡IMPACTO!" << RESET << endl;
                
                if (barco.EstaHundido()) {
                    cout << COLOR_WARNING << "¡" << barco.nombre << " hundido!" << RESET << endl;
                    barcosHundidos++;
                }
                break;
            }
        }
        
        if (!impacto) {
            cout << COLOR_INFO << "Agua..." << RESET << endl;
            tableroPropio.EstablecerCasilla(x, y, 'O');
        }
        
        return impacto;
    }
    
    void AgregarDisparo(int x, int y, bool impacto) {
        if (impacto) {
            tableroEnemigo.EstablecerCasilla(x, y, 'X');
        } else {
            tableroEnemigo.EstablecerCasilla(x, y, 'O');
        }
    }
    
    bool TodosLosBarcosDerrotados() {
        return barcosHundidos == barcos.size();
    }
    
    int GetBarcosRestantes() {
        return barcos.size() - barcosHundidos;
    }
    
    void MostrarEstadisticas() {
        cout << "\nBarcos restantes: " << GetBarcosRestantes() << endl;
    }
};

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
    cout << "║    • Ivan                            ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << RESET << endl;
}

void MenuPrincipal::MostrarMenu() {
    cout << COLOR_MENU;
    cout << "┌─────────────────────────────┐" << endl;
    cout << "│         MENU PRINCIPAL      │" << endl;
    cout << "├─────────────────────────────┤" << endl;
    cout << "│  1. Nueva Partida           │" << endl;
    cout << "│  2. Cargar Partida          │" << endl;
    cout << "│  3. Creditos                │" << endl;
    cout << "│  4. Salir                   │" << endl;
    cout << "└─────────────────────────────┘" << endl;
    cout << RESET;
}

int MenuPrincipal::ObtenerOpcion() {
    int opcion;
    cout << "\nSeleccione una opcion (1-4): ";
    cin >> opcion;
    
    if (cin.fail() || opcion < 1 || opcion > 4) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << COLOR_ERROR << "  Opcion invalida. Intente nuevamente." << RESET << endl;
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
    
    cout << COLOR_ERROR << " Funcionalidad de cargar partida no implementada aun." << RESET << endl;
    cout << "Presione Enter para continuar...";
    cin.get();
    cin.get();
}

void MenuPrincipal::MostrarCreditos() {
    system("clear || cls");
    cout << COLOR_TITULO;
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║                CREDITOS              ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║                                      ║" << endl;
    cout << "║     EQUIPO DE DESARROLLO:            ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Ivan - Menu Principal             ║" << endl;
    cout << "║           Integracion General        ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Stella - Logica del Juego         ║" << endl;
    cout << "║             Sistema de Archivos      ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║  • Juan - Gestion de Jugadores       ║" << endl;
    cout << "║           Validaciones               ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "║     Ingenieria en Ciencia de Datos   ║" << endl;
    cout << "║     Tercer Semestre - 2024           ║" << endl;
    cout << "║                                      ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << RESET << endl;
    
    cout << "Presione Enter para volver al menu principal...";
    cin.get();
    cin.get();
}

void MenuPrincipal::JugarPartida() {
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
        
        // Mostrar tableros
        jugadorActual->MostarTablerosPropio();
        cout << "\n";
        jugadorActual->MostrarTableroEnemigo();
        
        // Pedir coordenadas de disparo
        int x, y;
        cout << "\n" << jugadorActual->GetNombre() << ", ingresa coordenadas de disparo:" << endl;
        cout << "X (0-" << (TAMANO_TABLERO-1) << "): ";
        cin >> x;
        cout << "Y (0-" << (TAMANO_TABLERO-1) << "): ";
        cin >> y;
        
        // Realizar disparo
        if (jugadorActual->RealizarDisparo(x, y)) {
            bool impacto = jugadorEnemigo->RecibirDisparo(x, y);
            jugadorActual->AgregarDisparo(x, y, impacto);
        }
        
        // Mostrar estadisticas
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
    
    cout << "\nPresione Enter para volver al menu principal...";
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
        
        // Pausa antes de mostrar el menu nuevamente
        if (opcion != 4) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
            if (opcion != -1) cin.get(); // Extra get si la entrada fue valida
        }
    }
}

int main() {
    srand(time(0));
    MenuPrincipal menu;
    menu.Run();
    return 0;
}