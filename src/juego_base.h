#ifndef JUEGO_BASE_H
#define JUEGO_BASE_H

#include <iostream>
#include <string>

//===Código de fondo de color===/
#define  BG_RED      "\x1B[41m"
#define  BG_WHITE    "\x1B[47m"
#define  BG_GRAY     "\x1B[48;2;176;174;174m"
#define  BG_BLUE     "\x1B[44m"
#define  RESET       "\x1b[0m"

using namespace std;

class Casilla {
private:
    int estado; // 0:Impacto, 1:Sin impacto, 2:Barco, 3:Mar
    
public:
    Casilla();
    void MarcarImpacto();
    void PonerBarco();
    void MarcarSinImpacto();
    void Mar();
    void Mostrar(bool tipo);
    
    // Métodos adicionales para integración
    int GetEstado() const { return estado; }
    void SetEstado(int nuevoEstado) { estado = nuevoEstado; }
};

class Barco {
public:
    Barco();
    Barco(int tamano);
    int coordenadas[2][4];
    int GetTamano() const { return 4; } // Simplificado para compatibilidad
};

class Tablero {
public:
    Casilla Core[20][20];
    
    Tablero();
    void Mostrar(bool tipo);
    bool PonerBarco(int x, int y, int tamano, bool horizontal);
    void MarcarImpacto(int x, int y);
    void MarcarSinImpacto(int x, int y);
    Casilla& GetCasilla(int x, int y) { return Core[x][y]; }
};

#endif
