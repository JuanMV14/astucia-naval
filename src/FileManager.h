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
    std::string rutaGuardados;
    std::string rutaLogs;
    
    // Métodos privados para serialización
    std::string SerializarTablero(const Tablero& tablero);
    bool DeserializarTablero(const std::string& data, Tablero& tablero);
    std::string SerializarJugador(const Player& jugador);
    bool DeserializarJugador(const std::string& data, Player& jugador);
    void EscribirLog(const std::string& mensaje);
    
public:
    FileManager();
    ~FileManager();
    
    // Métodos principales
    bool GuardarPartida(const std::string& nombreArchivo, const GameManager* game);
    // Sobrecarga: guardar directamente desde jugadores (sin GameManager)
    bool GuardarPartida(const std::string& nombreArchivo,
                        const Player& jugador1,
                        const Player& jugador2,
                        bool turnoJugador1,
                        bool juegoTerminado);
    bool CargarPartida(const std::string& nombreArchivo, GameManager* game);
    bool ValidarArchivo(const std::string& nombreArchivo);
    
    // Utilidades de archivos
    std::vector<std::string> ListarPartidas();
    bool EliminarPartida(const std::string& nombreArchivo);
    std::string ObtenerRutaCompleta(const std::string& nombreArchivo);
    bool CrearDirectorios();
    
    // Información de archivo
    long ObtenerTamanoArchivo(const std::string& nombreArchivo);
    std::string ObtenerFechaModificacion(const std::string& nombreArchivo);
    
    // Configuración
    void SetRutaGuardados(const std::string& ruta) { rutaGuardados = ruta; }
    void SetRutaLogs(const std::string& ruta) { rutaLogs = ruta; }
    std::string GetRutaGuardados() const { return rutaGuardados; }
    std::string GetRutaLogs() const { return rutaLogs; }
};

#endif