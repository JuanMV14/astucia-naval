#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>

class Tablero {
private:
    static const int TAMANO = 20;
    std::vector<std::vector<char>> casillas;
    
public:
    Tablero();
    ~Tablero();
    
    // Métodos básicos
    void Limpiar();
    void Mostrar() const;
    char ObtenerCasilla(int x, int y) const;
    void EstablecerCasilla(int x, int y, char valor);
    
    // Validaciones
    bool EsValida(int x, int y) const;
    bool EstaVacia(int x, int y) const;
    
    // Propiedades
    int ObtenerTamano() const { return TAMANO; }
};

#endif // TABLERO_H
