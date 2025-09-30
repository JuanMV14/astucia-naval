#include "Tablero.h"
#include <iostream>
#include <iomanip>

Tablero::Tablero() {
    casillas.resize(TAMANO, std::vector<char>(TAMANO, '~'));
}

Tablero::~Tablero() {
}

void Tablero::Limpiar() {
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            casillas[i][j] = '~';
        }
    }
}

void Tablero::Mostrar() const {
    std::cout << "   ";
    for (int j = 0; j < TAMANO; j++) {
        std::cout << std::setw(3) << j;
    }
    std::cout << std::endl;
    
    for (int i = 0; i < TAMANO; i++) {
        std::cout << std::setw(2) << i << " ";
        for (int j = 0; j < TAMANO; j++) {
            std::cout << std::setw(3) << casillas[i][j];
        }
        std::cout << std::endl;
    }
}

char Tablero::ObtenerCasilla(int x, int y) const {
    if (!EsValida(x, y)) return '?';
    return casillas[y][x];
}

void Tablero::EstablecerCasilla(int x, int y, char valor) {
    if (EsValida(x, y)) {
        casillas[y][x] = valor;
    }
}

bool Tablero::EsValida(int x, int y) const {
    return x >= 0 && x < TAMANO && y >= 0 && y < TAMANO;
}

bool Tablero::EstaVacia(int x, int y) const {
    return EsValida(x, y) && casillas[y][x] == '~';
}
