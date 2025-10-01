// Implementación de la clase Player para el juego Astucia Naval
#include "Player.h"
#include "ValidacionesUtils.h"
#include <cstdlib>  // Para numeros aleatorios
#include <ctime>    // Para inicializar numeros aleatorios
#include <algorithm> // Para funciones de busqueda
#include <iomanip>   // Para formatear numeros
#include <sstream>   // Para istringstream

// Colores para mostrar mensajes en consola
#define COLOR_PLAYER  "\x1B[33m"  // Amarillo para el jugador
#define COLOR_SUCCESS  "\x1B[32m"  // Verde para éxito
#define COLOR_ERROR  "\x1B[31m"  // Rojo para errores
#define COLOR_INFO   "\x1B[36m"  // Azul para información
#define COLOR_WARNING  "\x1B[93m"  // Amarillo para advertencias
#define RESET           "\x1B[0m"  // Resetear color

// Constructor - crear un jugador nuevo
Player::Player(const string& nombre) : nombre(nombre) {
    // Crear los dos tableros del jugador
    tableroPropio = new Tablero();  // Su tablero donde coloca barcos
    tableroEnemigo = new Tablero(); // Tablero para ver disparos al enemigo
    barcosHundidos = 0;  // Empezar con 0 barcos hundidos
    barcosRestantes = 5; // Empezar con 5 barcos
    InicializarBarcos(); // Crear los barcos iniciales

    cout << COLOR_SUCCESS << "Jugador creado: " << nombre << RESET << endl;
}

// Constructor de copia - copiar un jugador
Player::Player(const Player& other) : nombre(other.nombre) {
    // Copiar los tableros
    tableroPropio = new Tablero(*other.tableroPropio);
    tableroEnemigo = new Tablero(*other.tableroEnemigo);
    // Copiar la información del jugador
    misbarcos = other.misbarcos;
    misDisparos = other.misDisparos;
    barcosHundidos = other.barcosHundidos;
    barcosRestantes = other.barcosRestantes;
}

// Operador de asignación - asignar un jugador a otro
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        nombre = other.nombre;

        // Eliminar tableros antiguos
        delete tableroPropio;
        delete tableroEnemigo;

        // Crear nuevos tableros copiando los del otro jugador
        tableroPropio = new Tablero(*other.tableroPropio);
        tableroEnemigo = new Tablero(*other.tableroEnemigo);
        // Copiar toda la información
        misbarcos = other.misbarcos;
        misDisparos = other.misDisparos;
        barcosHundidos = other.barcosHundidos;
        barcosRestantes = other.barcosRestantes;
    }
    return *this;
}

// Destructor - limpiar memoria cuando se elimina el jugador
Player::~Player() {
    delete tableroPropio;  // Eliminar su tablero
    delete tableroEnemigo; // Eliminar tablero enemigo
}

// Función principal para colocar barcos
void Player::ColocarBarco() {
    cout << COLOR_PLAYER << nombre << ", es tu turno de colocar barcos" << RESET << endl;

    // Mostrar el tablero actual
    cout << "Tu tablero actual" << endl;
    MostarTablerosPropio();

    // Mostrar opciones al jugador
    cout << "\nOpciones:" << endl;
    cout << "1. Colocar barcos manualmente" << endl;
    cout << "2. Colocar barcos aleatoriamente" << endl;

    int opcion;
    cout << "Selecciona una opcion (1 o 2): ";
    cin >> opcion;

    // Si elige opción 2, colocar automáticamente
    if (opcion == 2){
        ColocarBarcosAutomaticos();
        return;
    }

    // Colocar cada barco uno por uno
    for (size_t i = 0; i < misbarcos.size(); i++) {
        bool barcoColocado = false;

        // Repetir hasta que el barco se coloque correctamente
        while (!barcoColocado) {
            cout << COLOR_INFO << "Coloca tu barco: " << misbarcos[i].nombre
                 << " (" << misbarcos[i].tamano << " casillas)" << RESET << endl;
                
            // Mostrar instrucciones al jugador
            cout << "Opciones de colocacion:" << endl;
            cout << "Horizontal: Ingrese X Y (coordenada inicial)" << endl;
            cout << "Vertical: Ingrese X Y (coordenada inicial)" << endl;
            cout << "SKIP: Colocar barco aleatoriamente" << endl;
            
            string entrada;
            cout << "Ingrese comando:";
            cin.ignore();
            getline(cin, entrada);

            // Si el jugador escribe SKIP, colocar automáticamente
            if (entrada == "SKIP") {
                barcoColocado = IntegrarColocarBarco(misbarcos[i].tamano, misbarcos[i].nombre);
                if (!barcoColocado) {
                    cout << COLOR_ERROR << "No se pudo colocar el barco aleatoriamente. Intente de nuevo." << RESET << endl;
                }
                continue;
            }
            
            // Leer las coordenadas que escribió el jugador
            istringstream iss(entrada);
            int x, y;
            string orientacion = "";
            iss >> x >> y >> orientacion;

            // Verificar que las coordenadas sean válidas
            if (!ValidacionesUtils::ValidarCoordenadas(x, y)) {
                cout << COLOR_ERROR << "Coordenadas invalidas. Intente de nuevo." << RESET << endl;
                continue;
            }

            // Calcular todas las coordenadas que ocupará el barco
            vector<pair<int, int>> coordenadas;
            bool vertical = (orientacion == "V" || orientacion == "v");

            // Generar las coordenadas según la orientación
            for (int j = 0; j < misbarcos[i].tamano; j++) {
                if (vertical) {
                    coordenadas.push_back({x, y + j});  // Vertical: mismo X, Y aumenta
                } else {
                    coordenadas.push_back({x + j, y});  // Horizontal: X aumenta, mismo Y
                }
            }

            // Verificar si la posición es válida
            if (ValidarPosicionBarco(coordenadas)) {
                // Colocar el barco en el tablero
                misbarcos[i].coordenadas = coordenadas;
                for (const auto& coord : coordenadas) {
                    tableroPropio->EstablecerCasilla(coord.first, coord.second, 'B');
                }

                barcoColocado = true;
                cout << COLOR_SUCCESS << misbarcos[i].nombre << " colocado exitosamente" << RESET << endl;
            }
        }
    }
}

// Verificar si una posición de barco es válida
bool Player::ValidarPosicionBarco(const vector<pair<int, int>>& coordenadas) {
    // Verificar que todas las coordenadas estén dentro del tablero
    for (const auto& coord : coordenadas) {
        if (!ValidacionesUtils::ValidarCoordenadas(coord.first, coord.second)) {
            cout << COLOR_ERROR << "Coordenada fuera del tablero: ("
                 << coord.first << ", " << coord.second << ")" << RESET << endl;
            return false;
        }
    }

    // Verificar que no se superponga con otro barco
    if (!VerificarSolapamiento(coordenadas)) {
        return false;
    }

    // Verificar que no esté muy cerca de otro barco
    if (!VerificarAdyacencia(coordenadas)) {
        return false;
    }

    return true;
}

// Verificar que no haya otro barco en las mismas coordenadas
bool Player::VerificarSolapamiento(const vector<pair<int, int>>& coordenadas) {
    for (const auto& coord : coordenadas) {
        if (TieneBarcoEn(coord.first, coord.second)) {
            cout << COLOR_ERROR << "Error: Ya existe un barco en ("
                 << coord.first << "," << coord.second << ")" << RESET << endl;
            return false;
        }
    }
    return true;
}

// Verificar que no haya barcos muy cerca (adyacentes)
bool Player::VerificarAdyacencia(const vector<pair<int, int>>& coordenadas) {
    for(const auto& coord : coordenadas) {
        // Revisar las 8 posiciones alrededor de cada coordenada
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue; // Saltar la posición actual

                int nx = coord.first + dx;
                int ny = coord.second + dy;

                // Verificar si la posición está en el tablero
                if(ValidacionesUtils::ValidarCoordenadas(nx, ny)) {
                    // Verificar si esta coordenada es parte del barco actual
                    bool esParteDelBarcoActual = false;
                    for (const auto& currentCoord : coordenadas) {
                        if(currentCoord.first == nx && currentCoord.second == ny) {
                            esParteDelBarcoActual = true;
                            break;
                        }
                    }

                    // Si hay otro barco cerca, mostrar advertencia
                    if (!esParteDelBarcoActual && TieneBarcoEn(nx, ny)) {
                        cout << COLOR_WARNING << "Advertencia: Barco muy cerca. Se permite pero no es recomendado." << RESET << endl;
                    }
                }
            }
        }
    }
    return true;
}

// Verificar si un barco se hundió después de un disparo
bool Player::VerificarBarcoHundido(int x, int y) {
    // Buscar qué barco fue impactado
    for (auto& barco : misbarcos) {
        bool coordenadaEncontrada = false;
        for (const auto& coord : barco.coordenadas) {
            if (coord.first == x && coord.second == y) {
                coordenadaEncontrada = true;
                break;
            }
        }

        // Si no es este barco o ya está hundido, continuar
        if (!coordenadaEncontrada || barco.hundido) {
            continue;
        }

        // Verificar si todo el barco está impactado
        bool todoImpactado = true;
        for (const auto& coord : barco.coordenadas){
            // Aquí se verificaría si cada parte del barco fue impactada
            // (esta lógica se completaría según el sistema de impactos)
        }

        // Si todo el barco está impactado, hundirlo
        if (todoImpactado) {
            barco.hundido = true;
            barcosHundidos++;
            cout << COLOR_SUCCESS << "Has hundido el barco: " << barco.nombre << RESET << endl;
            return true;
        }
    }

    return false;
}

// Verificar si el jugador perdió (todos sus barcos hundidos)
bool Player::TodosLosBarcosDerrotados() const {
    return barcosHundidos == misbarcos.size();
}

// Mostrar el tablero propio con barcos
void Player::MostarTablerosPropio() const {
    cout << " Tablero de " << nombre << ":" << endl;
    cout << "   ";
    // Mostrar números de columnas (0-9)
    for (int i = 0; i < 10; i++) {
        cout << setw(2) << i << " ";
    }
    cout << endl;

    // Mostrar cada fila del tablero
    for (int i = 0; i < 10; i++) {
        cout << setw(2) << i << " "; // Número de fila
        cout << setw(3) << tableroPropio->ObtenerCasilla(0, i);
        for (int j= 1; j < 10; j++) {
            cout << setw(3) << tableroPropio->ObtenerCasilla(j, i);
        }
        cout << endl;
    }
}

// Mostrar el tablero enemigo con disparos realizados
void Player::MostrarTableroEnemigo() const {
    cout << "Tus disparos:" << endl;
    cout << "   ";
    // Mostrar números de columnas (0-9)
    for (int i = 0; i < 10; i++) {
        cout << setw(2) << i << " ";
    }
    cout << endl;

    // Mostrar cada fila del tablero enemigo
    for (int i = 0; i < 10; i++) {
        cout << setw(2) << i << " "; // Número de fila
        cout << setw(3) << tableroEnemigo->ObtenerCasilla(0, i);
        for (int j = 1; j < 10; j++) {
            cout << setw(3) << tableroEnemigo->ObtenerCasilla(j, i);
        }
        cout << endl;
    }
}

// Mostrar estadísticas del jugador
void Player::MostrarEstadisticas() const {
    cout << COLOR_INFO << "Estadisticas de " << nombre << ":" << RESET << endl;
    cout << "Barcos restantes: " << (misbarcos.size() - barcosHundidos) << "/" << misbarcos.size() << endl;
    cout << "Total disparos: " << GetTotalDisparos() << endl;
    cout << "Disparos acertados: " << GetDisparosAcertados() << endl;
    cout << "Porcentaje acierto: " << fixed << setprecision(1)
         << GetProcentajeAcierto() << "%" << endl;   
}

// Contar cuántos disparos dieron en barcos
int Player::GetDisparosAcertados() const {
    int aciertos = 0;
    for (const auto& disparo : misDisparos) {
        if (disparo.impacto) {
            aciertos++;
        }
    }
    return aciertos;
}

// Calcular el porcentaje de disparos acertados
double Player::GetProcentajeAcierto() const {
    if (misDisparos.empty()) {
        return 0.0; // Si no ha disparado, 0%
    }
    return (double)GetDisparosAcertados() / misDisparos.size() * 100.0;
}

// Verificar si ya se disparó a una coordenada
bool Player::CoordenadaYaDisparada(int x, int y) {
    for (const auto& disparo : misDisparos) {
        if (disparo.x == x && disparo.y == y) {
            return true;
        }
    }
    return false;
}

// Colocar todos los barcos automáticamente
void Player::ColocarBarcosAutomaticos(){
    cout << COLOR_INFO << "Colocando barco automaticamente..." << RESET << endl;

    srand(time(nullptr)); // Inicializar números aleatorios

    // Colocar cada barco
    for(auto& barco : misbarcos) {
        bool colocado = false;
        int intentos = 0;
        const int maxIntentos = 100; // Máximo 100 intentos por barco

        // Intentar colocar el barco hasta que se logre
        while (!colocado && intentos < maxIntentos) {
            vector<pair<int, int>> coordenadas;
            int x = rand() % 10; // Posición aleatoria X
            int y = rand() % 10; // Posición aleatoria Y
            bool vertical = rand() % 2; // Orientación aleatoria

            // Generar coordenadas del barco según su orientación
            for (int j = 0; j < barco.tamano; j++) {
                if (vertical) {
                    coordenadas.push_back({x, y + j}); // Vertical
                } else {
                    coordenadas.push_back({x + j, y}); // Horizontal
                }
            }

            // Si la posición es válida, colocar el barco
            if (ValidarPosicionBarco(coordenadas)) {
                barco.coordenadas = coordenadas;
                for (const auto& coord : coordenadas) {
                    tableroPropio->EstablecerCasilla(coord.first, coord.second, 'B');
                }
                colocado = true;
                cout << COLOR_SUCCESS << barco.nombre << " colocado " << RESET << endl;
            }

            intentos++;
        }

        // Si no se pudo colocar después de muchos intentos
        if (!colocado) {
            cout << COLOR_ERROR << "No se pudo colocar el barco: " << barco.nombre << RESET << endl;
        }
    }

    // Mostrar el tablero final
    MostarTablerosPropio();
    cout << COLOR_SUCCESS << "Todos los barcos colocados exitosamente!" << RESET << endl;
}

// Intentar colocar un barco específico automáticamente
bool Player::IntegrarColocarBarco(int tamano, const string& nombre) {
    srand(time(nullptr) + rand()); // Inicializar números aleatorios

    // Intentar hasta 50 veces
    for (int intento = 0; intento < 50; intento++) {
        vector<pair<int, int>> coordenadas;
        int x = rand() % 10; // Posición aleatoria X
        int y = rand() % 10; // Posición aleatoria Y
        bool vertical = rand() % 2; // Orientación aleatoria

        // Generar coordenadas del barco
        for (int i = 0; i < tamano; i++) {
            if (vertical) {
                coordenadas.push_back({x, y + i}); // Vertical
            } else {
                coordenadas.push_back({x + i, y}); // Horizontal
            }
        }

        // Si la posición es válida, colocar el barco
        if (ValidarPosicionBarco(coordenadas)) {
            // Encontrar el barco y actualizar coordenadas
            for (auto& barco : misbarcos) {
                if (barco.nombre == nombre && barco.coordenadas.empty()) {
                    barco.coordenadas = coordenadas;
                    for (const auto& coord : coordenadas) {
                        tableroPropio->EstablecerCasilla(coord.first, coord.second, 'B');
                    }
                    return true;
                }
            }
        }
    }
    return false; // No se pudo colocar
}

// Agregar un disparo a la lista
void Player::AgregarDisparo(int x, int y, bool impacto) {
    misDisparos.push_back(DisparoRelizado(x, y, impacto));
    RegistrarDisparo(x, y, impacto);
}

// Agregar un barco con coordenadas específicas
void Player::AgregarBarco(const vector<pair<int, int>>& coordenadas, const string& nombre) {
    for (auto& barco : misbarcos) {
        if (barco.nombre == nombre) {
            barco.coordenadas = coordenadas;
            // Colocar el barco en el tablero
            for ( const auto& coord : coordenadas) {
                tableroPropio->EstablecerCasilla(coord.first, coord.second, 'B');
            }
            break;
        }
    }
}

// Limpiar todos los disparos realizados
void Player::LimpiarDisparos() {
    misDisparos.clear();
    // Reiniciar tablero enemigo
    delete tableroEnemigo;
    tableroEnemigo = new Tablero();
}

// Reiniciar todo para una nueva partida
void Player::ReiniciarTableros() {
    // Eliminar tableros antiguos
    delete tableroPropio;
    delete tableroEnemigo;
    // Crear nuevos tableros
    tableroPropio = new Tablero();
    tableroEnemigo = new Tablero();

    // Limpiar listas y reinicializar
    misbarcos.clear();
    misDisparos.clear();
    InicializarBarcos();
}

// Crear los barcos iniciales del jugador
void Player::InicializarBarcos() {
    // Crear los barcos estándar del juego
    misbarcos.push_back(BarcoJugador(5, "Portaaviones"));
    misbarcos.push_back(BarcoJugador(4, "Acorazado"));
    misbarcos.push_back(BarcoJugador(3, "Crucero"));
    misbarcos.push_back(BarcoJugador(3, "Submarino"));
    misbarcos.push_back(BarcoJugador(2, "Destructor"));
}

// Verificar si hay un barco en una posición específica
bool Player::TieneBarcoEn(int x, int y) const {
    for (const auto& barco : misbarcos) {
        for (const auto& coord : barco.coordenadas) {
            if (coord.first == x && coord.second == y) {
                return true;
            }
        }
    }
    return false;
}

// Registrar un disparo en el tablero enemigo
void Player::RegistrarDisparo(int x, int y, bool impacto) {
    if (impacto) {
        // Marcar como impacto en el tablero enemigo
        tableroEnemigo->EstablecerCasilla(x, y, 'X');
    } else {
        // Marcar como agua en el tablero enemigo
        tableroEnemigo->EstablecerCasilla(x, y, 'O');
    }
}

// Realizar un disparo a una posición
bool Player::RealizarDisparo(int x, int y) {
    // Verificar que no se haya disparado antes a esa posición
    if (CoordenadaYaDisparada(x, y)) {
        cout << COLOR_ERROR << "Ya has disparado a esa posición" << RESET << endl;
        return false;
    }

    // Verificar que las coordenadas sean válidas
    if (!ValidacionesUtils::ValidarCoordenadas(x, y)) {
        cout << COLOR_ERROR << "Coordenadas inválidas" << RESET << endl;
        return false;
    }

    // Agregar el disparo a la lista
    AgregarDisparo(x, y, false); // Por ahora siempre false, se actualizará según el resultado
    return true;
}

// Recibir un disparo del enemigo
bool Player::RecibirDisparo(int x, int y) {
    // Verificar si hay un barco en esa posición
    bool impacto = TieneBarcoEn(x, y);
    
    if (impacto) {
        // Marcar como impacto en el tablero propio
        tableroPropio->EstablecerCasilla(x, y, 'X');
        cout << COLOR_ERROR << "¡Impacto!" << RESET << endl;
        
        // Verificar si se hundió algún barco
        VerificarBarcoHundido(x, y);
    } else {
        // Marcar como agua en el tablero propio
        tableroPropio->EstablecerCasilla(x, y, 'O');
        cout << COLOR_INFO << "Agua" << RESET << endl;
    }
    
    return impacto;
}

// Mostrar cuántos barcos le quedan al jugador
void Player::MostrarBarcosRestantes() const {
    cout << COLOR_INFO << "Barcos restantes de " << nombre << ":" << RESET << endl;
    for (const auto& barco : misbarcos) {
        if (!barco.hundido) {
            cout << "- " << barco.nombre << " (" << barco.tamano << " casillas)" << endl;
        }
    }
    cout << "Total: " << (misbarcos.size() - barcosHundidos) << " barcos restantes" << endl;
}