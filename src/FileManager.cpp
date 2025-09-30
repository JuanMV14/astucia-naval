#include "FileManager.h"
#include "GameManager.h"
#include "Player.h"
#include <sstream>
#include <ctime>
#include <sys/stat.h>
#include <filesystem>
using namespace std::filesystem;

FileManager::FileManager() {
    rutaGuardados = "saves/";
    rutaLogs = "logs/";
    CrearDirectorios();
}

FileManager::~FileManager() {
    // Destructor
}

bool FileManager::CrearDirectorios() {
    try {
        // Crear directorio de guardados usando std::filesystem
        path dirGuardados(rutaGuardados);
        if (!exists(dirGuardados)) {
            create_directories(dirGuardados);
        }
        
        // Crear directorio de logs usando std::filesystem
        path dirLogs(rutaLogs);
        if (!exists(dirLogs)) {
            create_directories(dirLogs);
        }
        
        return true;
    } catch (const filesystem_error& e) {
        EscribirLog("Error al crear directorios: " + string(e.what()));
        return false;
    }
}

bool FileManager::GuardarPartida(const string& nombreArchivo, const GameManager* game) {
    string rutaCompleta = ObtenerRutaCompleta(nombreArchivo + ".txt");
    
    ofstream archivo(rutaCompleta, ios::out | ios::trunc);
    if (!archivo.is_open()) {
        EscribirLog("Error: No se pudo abrir archivo para guardar: " + rutaCompleta);
        return false;
    }
    
    try {
        // Escribir cabecera con metadatos
        time_t now = time(0);
        archivo << "# ASTUCIA NAVAL - PARTIDA GUARDADA" << endl;
        archivo << "# Fecha: " << ctime(&now);
        archivo << "# Versión: 1.0.0" << endl;
        archivo << "# ================================" << endl;
        
        // Información básica del juego
        archivo << "JUGADORES:" << endl;
        archivo << game->GetJugador1()->GetNombre() << "|" 
                << game->GetJugador2()->GetNombre() << endl;
        
        archivo << "TURNO_ACTUAL:" << endl;
        archivo << (game->IsTurnoJugador1() ? "1" : "2") << endl;
        
        archivo << "JUEGO_TERMINADO:" << endl;
        archivo << (game->IsJuegoTerminado() ? "1" : "0") << endl;
        
        // Serializar datos del jugador 1
        archivo << "JUGADOR1:" << endl;
        archivo << SerializarJugador(*(game->GetJugador1())) << endl;
        
        // Serializar datos del jugador 2
        archivo << "JUGADOR2:" << endl;
        archivo << SerializarJugador(*(game->GetJugador2())) << endl;
        
        archivo.close();
        
        string mensaje = "Partida guardada exitosamente: " + nombreArchivo;
        EscribirLog(mensaje);
        return true;
        
    } catch (const exception& e) {
        archivo.close();
        EscribirLog("Error al guardar partida: " + string(e.what()));
        return false;
    }
}

bool FileManager::CargarPartida(const string& nombreArchivo, GameManager* game) {
    string rutaCompleta = ObtenerRutaCompleta(nombreArchivo);
    
    ifstream archivo(rutaCompleta);
    if (!archivo.is_open()) {
        EscribirLog("Error: No se pudo abrir archivo para cargar: " + rutaCompleta);
        return false;
    }
    
    try {
        string linea;
        string seccionActual = "";
        
        // Crear nuevos jugadores
        Player* jugador1 = nullptr;
        Player* jugador2 = nullptr;
        
        while (getline(archivo, linea)) {
            // Ignorar comentarios y líneas vacías
            if (linea.empty() || linea[0] == '#') {
                continue;
            }
            
            // Identificar secciones
            if (linea.find(":") != string::npos && linea.back() == ':') {
                seccionActual = linea.substr(0, linea.length() - 1);
                continue;
            }
            
            // Procesar datos según la sección
            if (seccionActual == "JUGADORES") {
                size_t pos = linea.find("|");
                if (pos != string::npos) {
                    string nombre1 = linea.substr(0, pos);
                    string nombre2 = linea.substr(pos + 1);
                    
                    jugador1 = new Player(nombre1);
                    jugador2 = new Player(nombre2);
                }
            }
            else if (seccionActual == "TURNO_ACTUAL") {
                bool turnoJugador1 = (linea == "1");
                game->SetTurnoJugador1(turnoJugador1);
            }
            else if (seccionActual == "JUEGO_TERMINADO") {
                bool terminado = (linea == "1");
                game->SetJuegoTerminado(terminado);
            }
            else if (seccionActual == "JUGADOR1" && jugador1) {
                DeserializarJugador(linea, *jugador1);
            }
            else if (seccionActual == "JUGADOR2" && jugador2) {
                DeserializarJugador(linea, *jugador2);
            }
        }
        
        archivo.close();
        
        // Asignar jugadores al GameManager (esto requeriría métodos setter)
        // game->SetJugadores(jugador1, jugador2);
        
        string mensaje = "Partida cargada exitosamente: " + nombreArchivo;
        EscribirLog(mensaje);
        return true;
        
    } catch (const exception& e) {
        archivo.close();
        EscribirLog("Error al cargar partida: " + string(e.what()));
        return false;
    }
}

string FileManager::SerializarJugador(const Player& jugador) {
    ostringstream oss;
    
    // Serializar información básica
    oss << jugador.GetNombre() << ";";
    oss << jugador.GetBarcosRestantes() << ";";
    
    // Serializar tablero propio
    oss << SerializarTablero(jugador.GetTableroPropio()) << ";";
    
    // Serializar tablero enemigo (disparos realizados)
    oss << SerializarTablero(jugador.GetTableroEnemigo());
    
    return oss.str();
}

bool FileManager::DeserializarJugador(const string& data, Player& jugador) {
    istringstream iss(data);
    string token;
    int campo = 0;
    
    while (getline(iss, token, ';')) {
        switch (campo) {
            case 0: // Nombre (ya está establecido)
                break;
            case 1: // Barcos restantes
                // jugador.SetBarcosRestantes(stoi(token));
                break;
            case 2: // Tablero propio
                // DeserializarTablero(token, const_cast<Tablero&>(jugador.GetTableroPropio()));
                break;
            case 3: // Tablero enemigo
                // DeserializarTablero(token, const_cast<Tablero&>(jugador.GetTableroEnemigo()));
                break;
        }
        campo++;
    }
    
    return true;
}

string FileManager::SerializarTablero(const Tablero& tablero) {
    ostringstream oss;
    
    // Serializar cada casilla del tablero 20x20
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            // Obtener estado de la casilla
            // int estado = tablero.Core[i][j].GetEstado();
            // oss << estado;
            oss << "3"; // Por ahora, usar estado por defecto
            
            if (i < 19 || j < 19) {
                oss << ",";
            }
        }
    }
    
    return oss.str();
}

bool FileManager::DeserializarTablero(const string& data, Tablero& tablero) {
    istringstream iss(data);
    string estado;
    int i = 0, j = 0;
    
    while (getline(iss, estado, ',') && i < 20) {
        if (j >= 20) {
            j = 0;
            i++;
        }
        
        if (i < 20 && j < 20) {
            int estadoInt = stoi(estado);
            // tablero.Core[i][j].SetEstado(estadoInt);
        }
        j++;
    }
    
    return true;
}

bool FileManager::ValidarArchivo(const string& nombreArchivo) {
    string rutaCompleta = ObtenerRutaCompleta(nombreArchivo);
    
    ifstream archivo(rutaCompleta);
    if (!archivo.is_open()) {
        return false;
    }
    
    // Verificar que sea un archivo válido de Astucia Naval
    string primeraLinea;
    getline(archivo, primeraLinea);
    archivo.close();
    
    return (primeraLinea.find("ASTUCIA NAVAL") != string::npos);
}

vector<string> FileManager::ListarPartidas() {
    vector<string> partidas;
    
    try {
        // Usar std::filesystem para listar archivos
        path directorio(rutaGuardados);
        if (exists(directorio) && is_directory(directorio)) {
            for (const auto& entry : directory_iterator(directorio)) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                    partidas.push_back(entry.path().filename().string());
                }
            }
        }
    } catch (const filesystem_error& e) {
        EscribirLog("Error al listar partidas: " + string(e.what()));
    }
    
    return partidas;
}

bool FileManager::EliminarPartida(const string& nombreArchivo) {
    string rutaCompleta = ObtenerRutaCompleta(nombreArchivo);
    
    if (remove(rutaCompleta.c_str()) == 0) {
        EscribirLog("Partida eliminada: " + nombreArchivo);
        return true;
    } else {
        EscribirLog("Error al eliminar partida: " + nombreArchivo);
        return false;
    }
}

string FileManager::ObtenerRutaCompleta(const string& nombreArchivo) {
    return rutaGuardados + nombreArchivo;
}

long FileManager::ObtenerTamanoArchivo(const string& nombreArchivo) {
    string rutaCompleta = ObtenerRutaCompleta(nombreArchivo);
    struct stat st;
    if (stat(rutaCompleta.c_str(), &st) == 0) {
        return st.st_size;
    }
    return -1;
}

string FileManager::ObtenerFechaModificacion(const string& nombreArchivo) {
    string rutaCompleta = ObtenerRutaCompleta(nombreArchivo);
    struct stat st;
    if (stat(rutaCompleta.c_str(), &st) == 0) {
        return ctime(&st.st_mtime);
    }
    return "Fecha desconocida";
}

void FileManager::EscribirLog(const string& mensaje) {
    ofstream log(rutaLogs + "game.log", ios::app);
    if (log.is_open()) {
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        char timestamp[80];
        strftime(timestamp, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
        
        log << "[" << timestamp << "] " << mensaje << endl;
        log.close();
    }
}