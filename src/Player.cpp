#include "Player.h"
#include <iomanip>
#include <sstream>

// Colores para la interfaz
#define COLOR_BARCO      "\x1B[32m"
#define COLOR_IMPACTO    "\x1B[31m"
#define COLOR_AGUA       "\x1B[34m"
#define COLOR_HUNDIDO    "\x1B[91m"
#define COLOR_INFO       "\x1B[36m"
#define COLOR_WARNING    "\x1B[33m"
#define RESET            "\x1b[0m"

Player::Player(const string& nombre) : nombre(nombre) {
    // Crear tableros
    tableroPropio = new Tablero();
    tableroEnemigo = new Tablero();
    
    // Inicializar contadores
    barcosRestantes = 5;
    disparosRealizados = 0;
    disparosAcertados = 0;
    
    // Inicializar barcos
    InicializarBarcos();
}

Player::Player(const Player& other) : nombre(other.nombre) {
    // Crear nuevos tableros
    tableroPropio = new Tablero(*(other.tableroPropio));
    tableroEnemigo = new Tablero(*(other.tableroEnemigo));
    
    // Copiar contadores
    barcosRestantes = other.barcosRestantes;
    disparosRealizados = other.disparosRealizados;
    disparosAcertados = other.disparosAcertados;
    
    // Copiar barcos
    barcos.clear();
    for (const auto& barco : other.barcos) {
        barcos.push_back(BarcoJugador(barco.barco));
    }
    
    // Copiar disparos
    disparos = other.disparos;
}

Player::~Player() {
    delete tableroPropio;
    delete tableroEnemigo;
    
    // Limpiar barcos
    for (auto& barco : barcos) {
        delete barco.barco;
    }
    barcos.clear();
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        // Limpiar recursos actuales
        delete tableroPropio;
        delete tableroEnemigo;
        for (auto& barco : barcos) {
            delete barco.barco;
        }
        
        // Copiar datos
        nombre = other.nombre;
        tableroPropio = new Tablero(*(other.tableroPropio));
        tableroEnemigo = new Tablero(*(other.tableroEnemigo));
        barcosRestantes = other.barcosRestantes;
        disparosRealizados = other.disparosRealizados;
        disparosAcertados = other.disparosAcertados;
        
        // Copiar barcos
        barcos.clear();
        for (const auto& barco : other.barcos) {
            barcos.push_back(BarcoJugador(barco.barco));
        }
        
        // Copiar disparos
        disparos = other.disparos;
    }
    return *this;
}

void Player::InicializarBarcos() {
    // Limpiar barcos existentes
    for (auto& barco : barcos) {
        delete barco.barco;
    }
    barcos.clear();
    
    // Crear los 5 barcos estándar
    barcos.push_back(BarcoJugador(new Barco(5))); // Portaaviones
    barcos.push_back(BarcoJugador(new Barco(4))); // Acorazado
    barcos.push_back(BarcoJugador(new Barco(3))); // Crucero
    barcos.push_back(BarcoJugador(new Barco(3))); // Submarino
    barcos.push_back(BarcoJugador(new Barco(2))); // Destructor
    
    barcosRestantes = 5;
}

void Player::ColocarBarcos() {
    cout << COLOR_INFO << "\n" << nombre << ", es hora de colocar tus barcos!" << RESET << endl;
    cout << "Tienes " << barcos.size() << " barcos para colocar:" << endl;
    
    for (size_t i = 0; i < barcos.size(); i++) {
        cout << (i + 1) << ". Barco de tamano " << barcos[i].barco->GetTamano() << endl;
    }
    
    cout << "\n¿Cómo deseas colocar los barcos?" << endl;
    cout << "1. Manual (tú eliges las posiciones)" << endl;
    cout << "2. Automático (el sistema los coloca aleatoriamente)" << endl;

    int opcion;
    cout << "Selecciona una opción (1-2): ";
    cin >> opcion;

    if (opcion == 1) {
        ColocarBarco();
    } else {
        ColocarBarcosAutomaticos();
    }
}

void Player::ColocarBarco() {
    cout << COLOR_INFO << "\nColocación manual de barcos" << RESET << endl;
    
    for (size_t i = 0; i < barcos.size(); i++) {
        bool barcoColocado = false;

        while (!barcoColocado) {
            system("clear || cls");
            cout << COLOR_INFO << "Colocando barco " << (i + 1) << " de " << barcos.size() << RESET << endl;
            cout << "Tamaño del barco: " << barcos[i].barco->GetTamano() << endl;
            
            // Mostrar tablero actual
            tableroPropio->Mostrar(true);
            
            int x, y;
            char orientacion;
            
            cout << "\nIngresa las coordenadas de inicio:" << endl;
            cout << "X (0-19): ";
            cin >> x;
            cout << "Y (0-19): ";
            cin >> y;
            
            cout << "Orientación (H=Horizontal, V=Vertical): ";
            cin >> orientacion;
            
            // Validar entrada
            if (!ValidacionesUtils::ValidarCoordenadas(x, y)) {
                cout << COLOR_WARNING << "Coordenadas inválidas. Intenta nuevamente." << RESET << endl;
                continue;
            }

            if (!ValidacionesUtils::ValidarOrientacionBarco(string(1, orientacion))) {
                cout << COLOR_WARNING << "Orientación inválida. Usa H o V." << RESET << endl;
                continue;
            }

            // Intentar colocar el barco
            if (tableroPropio->PonerBarco(x, y, barcos[i].barco->GetTamano(), orientacion == 'H')) {
                cout << COLOR_BARCO << "¡Barco colocado exitosamente!" << RESET << endl;
                barcoColocado = true;
                } else {
                cout << COLOR_WARNING << "No se puede colocar el barco en esa posición." << RESET << endl;
                cout << "Presiona Enter para intentar nuevamente...";
                cin.get();
                cin.get();
            }
        }
    }
    
    cout << COLOR_BARCO << "\n¡Todos los barcos han sido colocados!" << RESET << endl;
    cout << "Presiona Enter para continuar...";
    cin.get();
    cin.get();
}

void Player::ColocarBarcosAutomaticos() {
    cout << COLOR_INFO << "\nColocando barcos automáticamente..." << RESET << endl;
    
    srand(time(0));
    
    for (size_t i = 0; i < barcos.size(); i++) {
        bool barcoColocado = false;
        int intentos = 0;
        
        while (!barcoColocado && intentos < 100) {
            int x = rand() % 20;
            int y = rand() % 20;
            bool horizontal = (rand() % 2 == 0);
            
            if (tableroPropio->PonerBarco(x, y, barcos[i].barco->GetTamano(), horizontal)) {
                barcoColocado = true;
            }
            intentos++;
        }
        
        if (!barcoColocado) {
            cout << COLOR_WARNING << "No se pudo colocar el barco " << (i + 1) << " automáticamente." << RESET << endl;
        }
    }
    
    cout << COLOR_BARCO << "¡Barcos colocados automáticamente!" << RESET << endl;
    cout << "Presiona Enter para continuar...";
    cin.get();
    cin.get();
}

bool Player::RealizarDisparo(int x, int y) {
    // Verificar si ya disparó en esa posición
    for (const auto& disparo : disparos) {
        if (disparo.x == x && disparo.y == y) {
            cout << COLOR_WARNING << "Ya disparaste en esa posición." << RESET << endl;
            return false;
        }
    }
    
    // Validar coordenadas
    if (!ValidacionesUtils::ValidarCoordenadas(x, y)) {
        cout << COLOR_WARNING << "Coordenadas inválidas." << RESET << endl;
                return false;
            }

    disparosRealizados++;
    return true;
}

bool Player::RecibirDisparo(int x, int y) {
    // Verificar si hay un barco en esa posición
    if (TieneBarcoEn(x, y)) {
        // Marcar impacto en el tablero propio
        tableroPropio->MarcarImpacto(x, y);
        
        // Verificar si se hundió un barco
        if (VerificarBarcoHundido(x, y)) {
            barcosRestantes--;
        }
        
        return true;
    } else {
        // Marcar agua en el tablero propio
        tableroPropio->MarcarSinImpacto(x, y);
        return false;
    }
}

bool Player::TieneBarcoEn(int x, int y) {
    // Verificar si hay un barco en las coordenadas dadas
    return tableroPropio->Core[x][y].GetEstado() == 1; // 1 = barco presente
}

void Player::RegistrarDisparo(int x, int y, bool impacto) {
    disparos.push_back(DisparoRealizado(x, y, impacto));
    
    if (impacto) {
        disparosAcertados++;
        tableroEnemigo->MarcarImpacto(x, y);
    } else {
        tableroEnemigo->MarcarSinImpacto(x, y);
    }
}

bool Player::VerificarBarcoHundido(int x, int y) {
    // Encontrar el barco en esa posición
    for (auto& barco : barcos) {
        if (!barco.hundido) {
            // Verificar si el barco está en esa posición
            // Esta es una implementación simplificada
            barco.casillasGolpeadas++;
            if (barco.casillasGolpeadas >= barco.barco->GetTamano()) {
                barco.hundido = true;
                return true;
            }
                    }
                }
                return false;
            }

bool Player::TodosLosBarcosDerrotados() const {
    return barcosRestantes == 0;
}

int Player::GetBarcosRestantes() const {
    return barcosRestantes;
}

void Player::MostrarTableroPropio() const {
    cout << COLOR_INFO << "\nTablero de " << nombre << " (tus barcos):" << RESET << endl;
    tableroPropio->Mostrar(true);
}

void Player::MostrarTableroEnemigo() const {
    cout << COLOR_INFO << "\nTablero enemigo (tus disparos):" << RESET << endl;
    tableroEnemigo->Mostrar(false);
}

void Player::MostrarBarcosRestantes() const {
    cout << COLOR_INFO << "\nEstado de barcos de " << nombre << ":" << RESET << endl;
    cout << "Barcos restantes: " << barcosRestantes << "/" << barcos.size() << endl;
    
    for (size_t i = 0; i < barcos.size(); i++) {
        cout << "Barco " << (i + 1) << " (tamano " << barcos[i].barco->GetTamano() << "): ";
        if (barcos[i].hundido) {
            cout << COLOR_HUNDIDO << "HUNDIDO" << RESET << endl;
                        } else {
            cout << COLOR_BARCO << "ACTIVO" << RESET << endl;
        }
    }
}

void Player::MostrarEstadisticas() const {
    cout << COLOR_INFO << "\nEstadísticas de " << nombre << ":" << RESET << endl;
    cout << "Disparos realizados: " << disparosRealizados << endl;
    cout << "Disparos acertados: " << disparosAcertados << endl;
    cout << "Porcentaje de acierto: " << fixed << setprecision(1) << GetPorcentajeAcierto() << "%" << endl;
    cout << "Barcos restantes: " << barcosRestantes << endl;
}

double Player::GetPorcentajeAcierto() const {
    if (disparosRealizados == 0) return 0.0;
    return (double)disparosAcertados / disparosRealizados * 100.0;
}

void Player::ReiniciarTableros() {
                delete tableroPropio;
                delete tableroEnemigo;
    
    tableroPropio = new Tablero();
    tableroEnemigo = new Tablero();
    
    barcosRestantes = 5;
    disparosRealizados = 0;
    disparosAcertados = 0;
    
    disparos.clear();
    InicializarBarcos();
}

void Player::AgregarDisparo(int x, int y, bool impacto) {
    RegistrarDisparo(x, y, impacto);
}
