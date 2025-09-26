#include "juego_base.h"
#include <iomanip>

//===Código de fondo de color===/

#define  BG_RED      "\x1B[41m"
#define  BG_WHITE    "\x1B[47m"
#define  BG_GRAY     "\x1B[48;2;176;174;174m"
#define  BG_BLUE     "\x1B[44m"
#define  RESET       "\x1b[0m"

using namespace std;

string Colors[] = {BG_RED, BG_WHITE, BG_GRAY, BG_BLUE};

// Implementaciones de Casilla

Casilla::Casilla(){
    estado = 3;
}

void Casilla::MarcarImpacto(){
    estado = 0;
}

void Casilla::PonerBarco(){
    estado = 2;
}

void Casilla::MarcarSinImpacto(){
    estado = 1;
}

void Casilla::Mar(){
    estado = 3;
}

Tablero::Tablero()
{
    // Inicializar todas las casillas como mar
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            Core[i][j].Mar();
        }
    }
}

void Casilla::Mostrar(bool tipo){
    
    if(tipo){
        cout << Colors[estado] << ". " << RESET;
    }else{
        if(estado == 2){
            cout << Colors[3] << ". " << RESET;
        }else{
            cout << Colors[estado] << ". " << RESET;
        }
    }
}

bool Tablero::PonerBarco(int x, int y, int tamano, bool horizontal)
{
    // Verificar que las coordenadas estén dentro del tablero
    if (x < 0 || x >= 20 || y < 0 || y >= 20) {
        return false;
    }
    
    // Verificar que el barco quepa en el tablero
    if (horizontal) {
        if (x + tamano - 1 >= 20) return false;
    } else {
        if (y + tamano - 1 >= 20) return false;
    }
    
    // Colocar el barco
    for (int i = 0; i < tamano; i++) {
        if (horizontal) {
            Core[x + i][y].PonerBarco();
        } else {
            Core[x][y + i].PonerBarco();
        }
    }
    
    return true;
}

void Tablero::MarcarImpacto(int x, int y)
{
    if (x >= 0 && x < 20 && y >= 0 && y < 20) {
        Core[x][y].MarcarImpacto();
    }
}

void Tablero::MarcarSinImpacto(int x, int y)
{
    if (x >= 0 && x < 20 && y >= 0 && y < 20) {
        Core[x][y].MarcarSinImpacto();
    }
}

// Implementaciones de Barco

Barco::Barco(){
	// Constructor por defecto
}

Barco::Barco(int tamano){
	// Constructor con tamaño - simplificado para compatibilidad
}

// Implementaciones adicionales de Tablero

void Tablero::Mostrar(bool tipo){
    
    cout << "   ";
    for(int i=0; i<20; i++){
        cout << " " << i;
    }
    cout << endl;
    
    for(int i=0; i<20; i++){
        cout << " " << i;
        for(int j=0; j<20; j++){
            Core[i][j].Mostrar(tipo);
        }
        cout << endl;
    }
}

// Métodos adicionales no declarados en el header - eliminados