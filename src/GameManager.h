#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <string>
#include "Player.h"
#include "FileManager.h"

class GameManager {
private:
    Player* jugador1;
    Player* jugador2;
    Player* jugadorActual;
    bool turnoJugador1;
    bool juegoTerminado;
    string nombrePartida;
    FileManager* fileManager;
    
    // Métodos privados para la lógica del juego
    void CambiarTurno();
    bool VerificarVictoria(Player* jugador);
    void MostrarEstadoJuego();
    void ProcesarComandoEspecial(const string& comando);
    
public:
    GameManager();
    ~GameManager();
    
    // Gestión de partidas
    void IniciarNuevaPartida(const string& nombre1, const string& nombre2);
    bool CargarPartida(const string& nombreArchivo);
    bool GuardarPartida(const string& nombreArchivo);
    void ContinuarPartida();
    
    // Lógica principal del juego
    void FaseColocarBarcos();
    void FaseJuego();
    void ProcesarTurno();
    bool ProcesarDisparo(int x, int y);
    
    // Getters
    Player* GetJugador1() const { return jugador1; }
    Player* GetJugador2() const { return jugador2; }
    Player* GetJugadorActual() const { return jugadorActual; }
    bool IsJuegoTerminado() const { return juegoTerminado; }
    bool IsTurnoJugador1() const { return turnoJugador1; }
    
    // Setters para carga de partidas
    void SetTurnoJugador1(bool turno);
    void SetJuegoTerminado(bool terminado);
};

#endif