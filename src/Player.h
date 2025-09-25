// Archivo de cabecera para la clase Player del juego Astucia Naval
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

// Declaraciones de clases que se usan en el juego
class Tablero;  // El tablero donde se colocan los barcos
class Barco;    // Los barcos del juego

using namespace std;

// Estructura para guardar información de cada disparo
struct DisparoRelizado {
    int x, y;        // Coordenadas donde se disparó
    bool impacto;    // Si el disparo dio en un barco o no

    // Constructor para crear un disparo
    DisparoRelizado(int x, int y, bool impacto) : x(x), y(y), impacto(impacto) {}
};

// Estructura para guardar información de cada barco del jugador
struct BarcoJugador { 
    vector<pair<int, int>> coordenadas;  // Posiciones que ocupa el barco en el tablero
    int tamaño;                          // Cuántas casillas ocupa el barco
    bool hundido;                        // Si el barco ya fue hundido
    string nombre;                       // Nombre del barco

    // Constructor para crear un barco
    BarcoJugador(int tam, const string& nom) : tamaño(tam), hundido(false), nombre(nom){}
};

// Clase principal del jugador - maneja todo lo relacionado con un jugador
class Player {
private:
    // Información básica del jugador
    string nombre;                        // Nombre del jugador
    Tablero* tableroPropio;              // Su tablero donde tiene sus barcos
    Tablero* tableroEnemigo;             // Tablero donde ve los disparos al enemigo
    vector<BarcoJugador> misbarcos;      // Lista de sus barcos
    vector<DisparoRelizado> misDisparos; // Lista de disparos que ha hecho
    int barcosHundidos;                  // Cuántos barcos ha perdido

    // Funciones privadas para validar posiciones de barcos
    bool ValidarPosicionBarco(const vector<pair<int, int>>& coordenadas);  // Ver si la posición es válida
    bool VerificarSolapamiento(const vector<pair<int, int>>& coordenadas); // Ver si se superpone con otro barco
    bool VerificarAdyacencia(const vector<pair<int, int>>& coordenadas);   // Ver si está muy cerca de otro barco
    bool CoordenadasYaDisparadas(int x, int y);                            // Ver si ya disparó ahí
    void InicializarBarcos();                                              // Crear los barcos iniciales

public:
    // Constructores y destructor
    Player(const string& nombre);        // Crear un jugador nuevo
    Player(const Player& other);         // Copiar un jugador
    Player& operator=(const Player& other); // Asignar un jugador a otro
    ~Player();                           // Destruir el jugador

    // Funciones principales del juego
    void ColocarBarco();                    // Colocar barcos en el tablero
    bool RealizarDisparo(int x, int y);     // Disparar a una posición
    bool RecibirDisparo(int x, int y);      // Recibir un disparo del enemigo
    void RegistrarDisparo(int x, int y, bool impacto); // Guardar un disparo

    // Funciones para verificar estado del juego
    bool VerificarBarcoHundido(int x, int y);  // Ver si un barco se hundió
    bool TodosLosBarcosDerrotados() const;     // Ver si perdió el juego
    bool TieneBarcoEn(int x, int y) const;     // Ver si hay un barco en esa posición

    // Funciones para mostrar información
    void MostarTablerosPropio() const;    // Mostrar su tablero con barcos
    void MostrarTableroEnemigo() const;   // Mostrar tablero de disparos al enemigo
    void MostrarEstadisticas() const;     // Mostrar estadísticas del jugador
    void MostrarBarcosRestantes() const;  // Mostrar cuántos barcos le quedan

    // Funciones para obtener información del jugador
    string GetNombre() const { return nombre; }                    // Obtener nombre
    int GetBarcosRestantes() const { return barcosRestantes; }     // Obtener barcos restantes
    int GetTotalDisparos() const { return misDisparos.size(); }    // Obtener total de disparos
    int GetDisparosAcertados() const;                              // Obtener disparos que dieron
    const Tablero& GetTableroPropio() const { return *tableroPropio; }   // Obtener su tablero
    const Tablero& GetTableroEnemigo() const { return *tableroEnemigo; } // Obtener tablero enemigo
    
    // Funciones para modificar información del jugador
    void SetBarcosRestantes(int cantidad) { barcosRestantes = cantidad; } // Cambiar barcos restantes
    void AgregarDisparo(int x, int y, bool impacto);                     // Agregar un disparo
    void AgregarBarco(const vector<pair<int, int>>& coordenadas, const string& nombre); // Agregar un barco

    // Funciones adicionales del juego
    double GetProcentajeAcierto() const;                    // Calcular porcentaje de aciertos
    void LimpiarDisparos();                                 // Limpiar lista de disparos
    void ReiniciarTableros();                               // Reiniciar tableros para nueva partida

    void ColocarBarcosAutomaticos();                        // Colocar barcos automáticamente
    bool IntegrarColocarBarco(int tamaño, const string& nombre); // Intentar colocar un barco

};

#endif // PLAYER_H