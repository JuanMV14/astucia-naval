#include "Player.h"
#include "ValidacionesUtils.h"
#include "../juego_base.cpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

//Colores
#define COLOR_PLAYER  "\x1B[33m"
#define COLOR_SUCCESS  "\x1B[32m"
#define COLOR_ERROR  "\x1B[31m"
#define COLOR_INFO   "\x1B[36m"
#define COLOR_WARNING  "\x1B[93m"
#define RESET           "\x1B[0m"

Player::Player(const string& nombre) : nombre(nombre) {
    tableroPropio = new Tablero(true); // Tablero propio con barcos
    tableroEnemigo = new Tablero(false); // Tablero enemigo sin barcos
    barcosRestantes = 0;
    inicializarBarcos();

    cout << COLOR_SUCCESS << "Jugador creado: " << nombre << RESET << endl;

}

Player:: Player(const Player& other)  : nombre(other.nombre){
    tableroPropio = new Tablero(*otther.tableroPropio);
    tableroEnemigo = new Tablero(*other.tableroEnemigo);
    misBarcos = other.misBarcos;
    MisDisparos = other.misDisparos;
    barcosRestantes = other.barcosRestantes;
}

Player& Player ::operator=(const Player& other) {
    if (this != &other) {
        nombre = other.nombre;

        delete tableroPropio;
        delete tableroEnemigo;

        tableroPropio = new Tablero(*other.tableroPropio);
        tableroEnemigo = new Tablero(*other.tableroEnemigo);
        misBarcos = other.misBarcos;
        MisDisparos = other.misDisparos;
        barcosRestantes = other.barcosRestantes;
    }
    return *this;
}

Player ::~Player() {
    delete tableroPropio;
    delete tableroEnemigo;
}

void Player :: ColorBarco() {
    cout << COLOR_PLAYER <<  << nombre << ", es tu turno de colocar barcos" << RESET << endl;

    //Tablero incial
    cout << "Tu tablero actual" << endl;
    MostrarTableroPropio();

    cout << "\nOpciones:" << endl;
    cout << "1. Colocar barcos manualmente" << endl;
    cout << "2. Colocar barcos aleatoriamente" << endl;

    int opcion;
    count << "Seleciona una opcion (1 o 2): ";
    cin >> opcion;

    if (opcion == 2){
        ColocarBarcosAleatoriamente();
        return;
    }

    for (size_t i = 0; i < misBarcos.size(); i++) {
        bool barcoColocado = false;

        while (!barcoColocado) {
            cout << COLOR_INFO << "Coloca tu barco:" << misbarcos[i].nombre
                 << " (" << misBarcos[i]. tamaño << "casillas)" << RESET << endl;
                
            cout << "Opciones de colocacion:" << endl;
            cout << "Horizontal: Ingrese X Y (coordenada inicial)" << endl;
            cout << "Vertical: Ingrese X Y (coordenada inicial)" << endl;
            cout << "SKIP: Colocar barco aleatoriamente" << endl;
            
            string entrada;
            cout << "Ingrese comando:";
            cin.ignore();
            getline(cin, entrada);

            if (entrada == "SKIP") {
                barcoloColocado = IntentarColocarBarco(misBarcos[i].tamaño, misBarcos[i].nombre);
                if (!barcoColocado) {
                    cout << COLOR_ERROR << "No se pudo colocar el barco aleatoriamente. Intente de nuevo." << RESET << endl;
                }
                continue;
            }
            istringstream iss(entrada);
            int x, y;
            string orientacion = "";
            iss >> x >> y >> orientacion;

            if (!ValidacionesUtils::ValidarCoodenadas(x, y)) {
                cout << COLOR_ERROR << "Coordenadas invalidas. Intente de nuevo." << RESET << endl;
                continue;
            }

            // Generar coordenadas del barco
            vector<pair<int, int>> coordenadas;
            bool vertical = (orientacion == "V" || orientacion == "v");

            for (int j = 0; j < misBarcos[i].tamaño; j++) {
                if (vertical) {
                    coodenadas.push_back({x, y + j});
                } else {
                    coordenadas.push_back({x + j, y});
                }
            }

            // Validar posicion
            if (ValidarPosicionBarco(coordenadas)) {
                //Colocar barco
                misBarcos[i].coordenadas = coordenadas;
                for (const auto& coord : coordenadas) {
                    tableroPropio->Core[coord.first][coord.second] .PonerBarco();
                }

                cout << COLOR_SUCESS << << misBarcos[i].nombre << "colocado exitosamente" << RESET << endl;

            }
            
            bool Player :: ValidarPosicionBarco(const vector<pair<int, int>>& coordenadas) {
                //Verificar que  las coordenadas esten dentro del tablero
                for (const auto& coord : coordenadas) {
                    if (!ValidacionesUtils :: ValdiarCoordenadas(coord.first, coord.second)) {
                        cout << COLOR_ERROR << "Coordenada fuera del tablero: ("
                             << coord.first << ", " << coord.second << ")" << RESET << endl;
                        return false;
                    }
                }

                //Verificar solapamiento
                if (!VerificarSolapamiento(coodenadas)) {
                    return false;
                }

                //Verificar adyacencia
                if (!VerificarAdyacencia(coordenadas)) {
                    return false;
                }

                return true;

            }

            bool Player :: VerificarSolapamiento(const vector<pairs<int, intz>>& coordenadas) {
                for (const auto& coord : coordenadas) {
                    if (TieneBarcoEn(coord.first, coord.second)) {
                        cout << COLOR_ERROR << "Eror: Ya existe un barco en ("
                             << cord.first << "," << coord.second << ")" << RESET << endl;
                        return false;
                    
                    }
                }
                return true;
            }

            bool Player :: VerificarAdyacencia(const vector<pair<int, int>>& coordenadas) {
                for(const auto& coord : coordenasas) {
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (dx == 0 && dy == 0)continue;

                            int nx = coord.first + dx;
                            int ny = coord.second + dy;

                            if(validacionesUtils ::ValidarCoordenadas (nx, ny)) {
                                //verificar si esta coordenada tiene barco
                                bool esParteDelBarcoActual = false;
                                for (const auto& currentCoord : coordenadas) {
                                    if(currentCoord.first == nx && currentCoord.second == ny) {
                                        esParteDelBarcoActual = true;
                                        break;
                                    }
                                }

                                if (!esParteDelBarcoActual && TieneBarcoEn(nx, ny)) {
                                    cout << COLOR_WARNING << "Advertencia: Barco muy cerca. Se permite pero no es recomendado." << RESET << endl;
                                    
                                }
                            }
                        }
                    }
                }

            bool Player :: VerificarBarcoHundido(int x, int y) {
                //saber qu barco fue impactado
                for (auto& barco : misBarcos) {
                    bool coordenadaEncontrada = false;
                    for (const auto& coord : barco.coordenadas) {
                        if (coor.first == x && coord.second == y) {
                            coordenadaEncontrada = true;
                            break;
                        }
                    }

                    if (!coordenadaEncontrada || barco.hundido) {
                        continue;
                    }

                    //Verificar si todo el barco esta impactado
                    bool todoImpactado = true;
                    for (const auto& coord : barco.coordenadas){

                    }

                    if (todoImpactado) {
                        barco.hundido = true;
                        barcosRestantes--;
                        cout << COLOR_SUCCESS << "Has hundido el barco: " << barco.nombre << RESET << endl;
                        return true;
                    }
                }

                return false;
            }

            bool Player :: TodosLosBarcosDerrotados() const {
                return barcosRestantes == 0;
            }

            void Player ::MostrarTableroPropio() const {
                cout << " Tablero de " << nombre << ":" << endl;
                cout << "   ";
                for (int i = 0; i < 20; i++) {
                    cout << stew(2) << i << " ";
                }
                cout << endl;

                for (int i = 0; i < 20; i++) {
                    cout << setw(2) << i << " ";
                    tableroPropio->Core[i][0].Mostrar(true);
                    for (int j= 1; j < 20; j++) {
                        tableroPropio->Core[i][j].Mostrar(true);
                    }
                    cout << endl;
                }
            }

            void Player :: MostrarTableroEnemigo() const {
                cout << "Tus disparos:" << endl;
                cout << "   ";
                for (int i = 0; i < 20; i++) {
                    cout << setw(2) << i << " ";
                }
                cout << endl;

                for (int i = 0 i < 20; i++) {
                    cout << stew(2) << i << " ";
                    tableroEnemigo->Core[i][0].Mostrar(false);
                    for (int j = 1; j < 20; j++) {
                        tableroEnemigo->Core[i][j].Mostrar(false);
                    }
                    cout << endl;
                }
            }
            void Player :: MostrarEstadisticas() const {
                cout << COLOR_INFO << "Estadisticas de " << nombre << ";" << RESET << endl;
                cout << "Barcos restantes: " << barcosRestantes << "/" << misBarcos.size() << endl;
                cout << "Total disparos: " << GetTotalDisparos() << endl;
                cout << "Disparos acertados: " << GetDisparosAcertados() << endl;
                cout << "Porcentaje acieto: " << fixed <<setprecision(1)
                     << GetPorcentajeAcierto() << "%" << endl;   
                
            }

            void Player :: MostrarBarcosRestantes() const {
                int aciertos = 0;
                for (const auto& disparo : misDisparos) {
                    if (disparo.impacto) {
                        aciertos++;
                    }
                }
                return aciertos;
            }

            double Player :: GetPorcentajeAcierto() const {
                if (misDisparos.empty()) {
                    return 0.0;
                }
                return (double)GetDisparosAcertados() / misDisparos.size() * 100.0;

            }

            bool Player :: CoordenadaYaDisparada(int x, int y) {
                for (const auto& disparo : misDisparos) {
                    if (disparo.x == x && disparo.y == y) {
                        return true;
                    }
                }
                return false;
            }

            void Player :: ColocarBarcoAutomatico(){
                cout << COLOR_INFO << "Colocando barco automaticamente..." << RESET << endl;

                srand(time(nullptr));

                for(auto& barco : misBarcos) {
                    bool colocado = false;
                    int intentos = 0;
                    const int maxIntestos = 100;

                    while (!colocado && intentos < maxIntentos) {
                        vector<pair<int, int>> coordenadas;
                        int x = rand() % 20;
                        int y = rand() % 20;
                        bool vertical = rand() % 2;

                        //Generar coordenadas del barco
                        for (int j = 0; j < barco.tamaño; j++) {
                            if (vertical) {
                                coordenadas.push_back({x, y + j});
                            } else {
                                coordenadas.push_back({x + j, y});
                            }
                        }

                        if (ValidarPosicionBarco(coordenadas)) {
                            barco.coordenadas = coordenadas;
                            for (const auto& coord : coordenadas) {
                                tableroPropio->Core[coord.first][coord.second].PonerBarco();
                            }
                            colocado = true;
                            cout << COLOR_SUCCESS << barco.nombre << " colocado " << RESET << endl;

                        }

                        intentos++;
                    }

                    if (!colocado) {
                        cout << COLOR_ERROR << "No se pudo colocar el barco: " << barco.nombre << RESET << endl;
                    }
                }

                //Mostrar tablero final
                MostrarTableroPropio();
                cout << COLOR_SUCCESS << "Todos los barcos colocados exitosamente!" << RESET << endl;
            }
            
            bool Player :: IntentarColocarBarco(int tamaño, const string& nombre) {
                vsrand(time(nullptr) + rand());

                for (int intento = 0; intento < 50; intento++) {
                    vector<pair<int, int>> coordenadas;
                    int x = rand() % 20;
                    int y = rand() % 20;
                    bool vertical = rand() % 2;

                    for (int i = 0; i < tamaño; i++) {
                        if (vertical) {
                            coordenadas.push_back({x, y + i});
                        } else {
                            coordenadas.push_back({x + i, y});
                        }
                    }

                    if (ValidarPosicionBarco(coordenadas)) {
                        //Encontrar el barco y actualziar coordenadas
                        for (auto& barco : misBarcos) {
                            if (barco.nombre == nombre && barco.coordenadas.empty()) {
                                barco.coordenadas = coordenadas;
                                for (const auto& coord : coordenadas) {
                                    tableroPropio->Core[coord.first][coor.second].PonerBarco();
                                }
                                return true;
                                
                            }
                        }
                    }
                }
            }

            void Player :: AgregarDisparo(int z, int y, bool impacto) {
                misDisparos.push_back(DisparoRealizado(x, y, impacto));
                RegistrarDisparo(x, y, impacto);
            }

            void Player :: AgregarBarco(const vector<pair<int, int >>& coordenadas, const string& nombre) {
                for (auto& barco : misBarcos) {
                    if (barco.nombre == nombre) {
                        barco.coordenadas = coordenadas;
                        for ( const auto& coord : coordenadas) {
                            tableroPropio->Core[coord.first][coord.second].PonerBarco();

                        }
                        break;
                    }
                }
            }
            void Player :: LimpiarDisparos() {
                misDisparos.clear();
                //Reiniciar tablero rival
                delete tableroEnemigo;
                tableroEnemigo = new Tablero(false);
            }

            void Player :: Reiniciar() {
                delete tableroPropio;
                delete tableroEnemigo;
                tableroPropio = new Tablero(true);
                tableroEnemigo = new Tablero(false);

                misBarcos.clear();
                misDisparos.clear();
                InicialziarBarcos();
            }
    }
}