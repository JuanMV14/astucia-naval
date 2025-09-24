#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

class Tablero;
class Barco;

using namespace std;

struct DisparoRelizado {
    int x, y;
    bool impacto;

    DisparoRelizado(int x, int y, bool impacto) : x(x), y(y), impacto(impacto) {}
};

struct BarcoJugador { 
    vector<pair<int, int>> coordenadas;
    int tamaño;
    bool hundido;
    string nombre;

    BarcoJugador(int tam, const string& nom) : tamaño(tam), hundido(false), nombre(nom){}
};

class Player {
private:
    string nombre;
    Tablero* tableroPropio;
    Tablero* tableroEnemigo;
    vector<BarcoJugador> misbarcos;
    vector<DisparoRelizado> misDisparos;
    int barcosHundidos;

    bool ValidarPosicionBarco(const vector<pair<int, int>>& coordenadas);
    bool VerificarSolapamiento(const vector<pair<int, int>>& coordenadas);
    bool VerificarAdyacencia(const vector<pair<int, int>>& coordenadas);
    bool CoordenadasYaDisparadas(int x, int y);
    void InicializarBarcos();

public:
    Player(const string& nombre);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();

    void ColocarBarco();
    bool RealizarDisparo(int x, int y);
    bool RecibirDisparo(int x, int y);
    void RegistrarDisparo(int x, int y, bool impacto);

    bool VerificarBarcoHundido(int x, int y);
    bool TodosLosBarcosDerrotados() const;
    bool TieneBarcoEn(int x, int y) const;

    void MostarTablerosPropio() const;
    void MostrarTableroEnemigo() const;
    void MostrarEstadisticas() const;
    void MostrarBarcosRestantes() const;

    string GetNombre() const { return nombre; }
    int GetBarcosRestantes() const { return barcosRestantes; }
    int GetTotalDisparos() const { return misDisparos.size(); }
    int GetDisparosAcertados() const;
    const Tablero& GetTableroPropio() const { return *tableroPropio; }
    const Tablero& GetTableroEnemigo() const { return *tableroEnemigo; }
    
    void SetBarcosRestantes(int cantidad) { barcosRestantes = cantidad; }
    void AgregarDisparo(int x, int y, bool impacto);
    void AgregarBarco(const vector<pair<int, int>>& coordenadas, const string& nombre);

    double GetProcentajeAcierto() const;
    void LimpiarDisparos();
    void ReiniciarTableros();

    void ColocarBarcosAutomaticos();
    bool IntegrarColocarBarco(int tamaño, const string& nombre);

};

#endif // PLAYER_H