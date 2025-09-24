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

string Colors[] = {BG_RED, BG_WHITE, BG_GRAY, BG_BLUE};

class Casilla{
    
    private:
    /*
        estado
         0:I: Impacto.  Rojo
         1:N: Sin impacto. Blanco
         2:B: Barco. Gris
         3:M: Mar (Vacio). Azul
    */
        int estado;
    
    public:
    
        Casilla();
        void MarcarImpacto();
        void PonerBarco();
        void MarcarSinImpacto();
        void Mar();
        void Mostrar(bool tipo); // True: tablero propio. False: tablero enemigo.
        
        // Métodos adicionales para integración
        int GetEstado() const { return estado; }
        void SetEstado(int nuevoEstado) { estado = nuevoEstado; }
        
};

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

class Barco{	
		
	public:
		Barco();
		int coordenadas[2][4];

};

Barco::Barco(){
	
	cout << "Ingrese las coordenadas del barco" << endl;
	
	for(int i=0; i<4; i++){
		
		cout << "Posicion " << i << ": "<<endl;
		cout << " x: ";
		cin >> coordenadas[0][i];
		cout << " y: ";
		cin >> coordenadas[1][i];
		cout << endl;
	
	}
}

class Tablero{
    
    private:
        bool tipo;
    
    public:
        Casilla Core[20][20];
        
        Tablero(bool tipo_);
        Tablero(const Tablero& other); // Constructor de copia
        Tablero& operator=(const Tablero& other); // Operador de asignación
        
        void Mostrar();
        void PonerBarco(Barco b);
        
        // Métodos adicionales para integración
        bool VerificarImpacto(int x, int y);
        bool TieneBarco(int x, int y) const;
        void LimpiarTablero();
};

Tablero::Tablero(bool tipo_){
    
    tipo = tipo_;
    
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            Core[i][j].Mar();
        }
    }
}

// Constructor de copia
Tablero::Tablero(const Tablero& other) : tipo(other.tipo) {
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            Core[i][j] = other.Core[i][j];
        }
    }
}

// Operador de asignación
Tablero& Tablero::operator=(const Tablero& other) {
    if (this != &other) {
        tipo = other.tipo;
        for(int i=0; i<20; i++){
            for(int j=0; j<20; j++){
                Core[i][j] = other.Core[i][j];
            }
        }
    }
    return *this;
}

void Tablero::Mostrar(){
    
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            Core[j][i].Mostrar(tipo);
        }
        cout << endl;
    }
    
    cout << endl; 
    cout << endl;
}

void Tablero::PonerBarco(Barco b){
    for(int i=0; i<4; i++){
        Core[b.coordenadas[0][i]][b.coordenadas[1][i]].PonerBarco();
    }
}

bool Tablero::VerificarImpacto(int x, int y) {
    if (x >= 0 && x < 20 && y >= 0 && y < 20) {
        return Core[x][y].GetEstado() == 2; // Estado 2 = Barco
    }
    return false;
}

bool Tablero::TieneBarco(int x, int y) const {
    if (x >= 0 && x < 20 && y >= 0 && y < 20) {
        return Core[x][y].GetEstado() == 2; // Estado 2 = Barco
    }
    return false;
}

void Tablero::LimpiarTablero() {
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            Core[i][j].Mar();
        }
    }
}

#endif