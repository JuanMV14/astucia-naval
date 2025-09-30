#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Forward declaration para evitar dependencia circular
class GameManager;
class Player;
class Tablero;

class FileManager {
private:
    string rutaGuardados;
    string rutaLogs;
    
    // Métodos privados para serialización
    string SerializarTablero(const Tablero& tablero);
    bool DeserializarTablero(const string& data, Tablero& tablero);
    string SerializarJugador(const Player& jugador);
    bool DeserializarJugador(const string& data, Player& jugador);
    void EscribirLog(const string& mensaje);
    
public:
    FileManager();
    ~FileManager();
    
    // Métodos principales
    bool GuardarPartida(const string& nombreArchivo, const GameManager* game);
    bool CargarPartida(const string& nombreArchivo, GameManager* game);
    bool ValidarArchivo(const string& nombreArchivo);
    
    // Utilidades de archivos
    vector<string> ListarPartidas();
    bool EliminarPartida(const string& nombreArchivo);
    string ObtenerRutaCompleta(const string& nombreArchivo);
    bool CrearDirectorios();
    
    // Información de archivo
    long ObtenerTamanoArchivo(const string& nombreArchivo);
    string ObtenerFechaModificacion(const string& nombreArchivo);
    
    // Configuración
    void SetRutaGuardados(const string& ruta) { rutaGuardados = ruta; }
    void SetRutaLogs(const string& ruta) { rutaLogs = ruta; }
    string GetRutaGuardados() const { return rutaGuardados; }
    string GetRutaLogs() const { return rutaLogs; }
};

#endif