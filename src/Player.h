#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "juego_base.h"
#include "ValidacionesUtils.h"

using namespace std;

// Estructura para almacenar información de disparos realizados
struct DisparoRealizado {
    int x, y;
    bool impacto;
    time_t timestamp;
    
    DisparoRealizado(int x, int y, bool impacto) : x(x), y(y), impacto(impacto) {
        timestamp = time(0);
    }
};

// Estructura para información de barcos del jugador
struct BarcoJugador {
    Barco* barco;
    bool hundido;
    int casillasGolpeadas;
    
    BarcoJugador(Barco* b) : barco(b), hundido(false), casillasGolpeadas(0) {}
};

class Player {
private:
    string nombre;
    Tablero* tableroPropio;      // Tablero donde coloca sus barcos
    Tablero* tableroEnemigo;     // Tablero donde registra sus disparos
    vector<BarcoJugador> barcos; // Lista de barcos del jugador
    vector<DisparoRealizado> disparos; // Historial de disparos
    int barcosRestantes;         // Contador de barcos no hundidos
    int disparosRealizados;      // Total de disparos realizados
    int disparosAcertados;       // Total de disparos acertados
    
    // Métodos privados para lógica interna
    void InicializarBarcos();
    bool TieneBarcoEn(int x, int y);
    
public:
    // Constructores y destructor
    Player(const string& nombre);
    Player(const Player& other);
    ~Player();
    Player& operator=(const Player& other);
    
    // Funciones principales del juego
    void ColocarBarcos();                    // Colocar barcos manual o automáticamente
    void ColocarBarco();                     // Colocar un barco específico
    void ColocarBarcosAutomaticos();         // Colocar todos los barcos automáticamente
    bool RealizarDisparo(int x, int y);      // Realizar un disparo
    bool RecibirDisparo(int x, int y);       // Recibir un disparo del enemigo
    void RegistrarDisparo(int x, int y, bool impacto);  // Registrar disparo
    bool VerificarBarcoHundido(int x, int y); // Verificar si barco está hundido
    
    // Verificación de estado del juego
    bool TodosLosBarcosDerrotados() const;   // Verificar si perdió
    int GetBarcosRestantes() const;          // Obtener barcos restantes
    
    // Mostrar información
    void MostrarTableroPropio() const;       // Mostrar su tablero
    void MostrarTableroEnemigo() const;      // Mostrar tablero de disparos
    void MostrarBarcosRestantes() const;     // Mostrar estado de barcos
    void MostrarEstadisticas() const;        // Mostrar estadísticas del jugador
    
    // Getters
    string GetNombre() const { return nombre; }
    Tablero& GetTableroPropio() const { return *tableroPropio; }
    Tablero& GetTableroEnemigo() const { return *tableroEnemigo; }
    int GetDisparosRealizados() const { return disparosRealizados; }
    int GetDisparosAcertados() const { return disparosAcertados; }
    double GetPorcentajeAcierto() const;     // Calcular porcentaje de aciertos
    
    // Funciones adicionales
    void ReiniciarTableros();                // Reiniciar para nueva partida
    void AgregarDisparo(int x, int y, bool impacto); // Agregar disparo al historial
};

#endif
