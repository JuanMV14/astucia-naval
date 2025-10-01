#include "ValidacionesUtils.h"
#include <cctype>
#include <algorithm>
#include <sstream>
#include <fstream>

// Colores para mostrar mensajes en consola
#define COLOR_ERROR "\x1B[1;31m"  // Rojo para errores
#define COLOR_SUCCESS "\x1B[1;32m"  // Verde para éxito
#define COLOR_WARNING "\x1B[1;33m"  // Amarillo para advertencias
#define COLOR_INFO "\x1B[1;36m"  // Azul para información
#define RESET "\x1B[0m"  // Resetear color

// Verificar si las coordenadas están dentro del tablero
bool ValidacionesUtils::ValidarCoordenadas(int x, int y) {
    // Comprobar que x e y estén entre 0 y 19
    if(x < TABLERO_MIN || x > TABLERO_MAX || y < TABLERO_MIN || y > TABLERO_MAX) {
        MostrarError("Coordenadas fuera de rango valido (0-9)");
        return false;
    }
    return true;
}

bool ValidacionesUtils::ValidarRangoCoordenadas(int x, int y, int minX, int minY, int maxX, int maxY) {
    if (x < minX || x > maxX || y < minY || y > maxY) {
        MostrarError("Coordenadas fuera del rango especificado");
        return false;
    }
    return true;
}

bool ValidacionesUtils::CoordenadasDentroDelTablero(int x, int y, int tamano) {
    return (x >= 0 && x < tamano && y >= 0 && y < tamano);

}

//Validacion entrada de usuario
// Convertir texto a número y validar que sea correcto
bool ValidacionesUtils::ValidarEntradaNumerica(const string& entrada, int& numero) {
    // Verificar que no esté vacío y que contenga solo números
    if (entrada.empty() || !EsNumero(entrada)) {
        MostrarError("La entrada no es un numero valido.");
        return false;
    }

    // Intentar convertir el texto a número
    try {
        numero = stoi(entrada);
        return true;
    }catch (const exception& e) {
        MostrarError("Error al convertir la entrada a numero.");
        return false;
    }
}

bool ValidacionesUtils::ValidarRangoNumerico(int numero, int min, int max) {
    if (numero < min || numero > max) {
        MostrarError("El numero esta fuera del rango permitido.");
        return false;
    }
    return true;


}
// Validar comandos del juego como SAVE, QUIT, HELP, etc.
bool ValidacionesUtils::ValidarComandoJuego(const string& comando) {
    if (comando.empty()) {
        MostrarError("Comando vacío");
        return false;
    }
    
    // Convertir a mayúsculas para comparar
    string comandoUpper = ConvertirAMayusculas(comando);
    
    // Lista de comandos que acepta el juego
    vector<string> comandosValidos = {
        "SAVE", "QUIT", "HELP", "EXIT", "LOAD", "GUARDAR", "SALIR", "AYUDA", 
        "STATUS", "STATS", "RESTART", "CLEAR"
    };
    
    // Buscar si el comando está en la lista de comandos válidos
    for (const string& cmd : comandosValidos) {
        if (comandoUpper.find(cmd) == 0) {
            return true;
        }
    }
    
    // Si no es comando, verificar si son coordenadas (formato: "X Y" o "X Y V")
    istringstream iss(comando);
    int x, y;
    string orientacion;
    
    if (iss >> x >> y) {
        if (ValidarCoordenadas(x, y)) {
            // Opcional: verificar orientación
            if (iss >> orientacion) {
                return ValidarOrientacionBarco(orientacion);
            }
            return true;
        }
    }
    
    MostrarError("Comando no reconocido: " + comando);
    return false;
}

// VALIDACIONES DE NOMBRES Y STRINGS

// Validar nombre del jugador - debe tener entre 2 y 20 caracteres
bool ValidacionesUtils::ValidarNombre(const string& nombre) {
    // Verificar que no esté vacío
    if (EsStringVacio(nombre)) {
        MostrarError("El nombre no puede estar vacío");
        return false;
    }
    
    // Verificar longitud del nombre
    if (nombre.length() < NOMBRE_MIN_LENGTH || nombre.length() > NOMBRE_MAX_LENGTH) {
        MostrarError("El nombre debe tener entre " + to_string(NOMBRE_MIN_LENGTH) + 
                    " y " + to_string(NOMBRE_MAX_LENGTH) + " caracteres");
        return false;
    }
    
    // Verificar que solo tenga letras y números
    if (!ContieneSoloLetrasYNumeros(nombre)) {
        MostrarError("El nombre solo puede contener letras y números");
        return false;
    }
    
    return true;
}

bool ValidacionesUtils::ValidarNombreArchivo(const string& nombreArchivo) {
    if (EsStringVacio(nombreArchivo)) {
        MostrarError("El nombre de archivo no puede estar vacío");
        return false;
    }
    
    // Caracteres no permitidos en nombres de archivo
    string caracteresProhibidos = "<>:\"/\\|?*";
    for (char c : caracteresProhibidos) {
        if (nombreArchivo.find(c) != string::npos) {
            MostrarError("El nombre de archivo contiene caracteres no permitidos");
            return false;
        }
    }
    
    if (nombreArchivo.length() > 50) {
        MostrarError("El nombre de archivo es demasiado largo (máximo 50 caracteres)");
        return false;
    }
    
    return true;
}

bool ValidacionesUtils::ContieneCaracteresEspeciales(const string& texto) {
    for (char c : texto) {
        if (!isalnum(c) && c != ' ' && c != '_' && c != '-') {
            return true;
        }
    }
    return false;
}

bool ValidacionesUtils::EsStringVacio(const string& texto) {
    string textoLimpio = LimpiarString(texto);
    return textoLimpio.empty();
}

// VALIDACIONES DE BARCOS

// Verificar que el tamano del barco este entre 1 y 5 casillas
bool ValidacionesUtils::ValidarTamanoBarco(int tamano) {
    if (tamano < TABLERO_MIN || tamano > TABLERO_MAX) {
        ValidacionesUtils::MostrarError("Tamano de barco invalido. Rango valido: 1-5");
        return false;
    }
    return true;
}

// Validar orientación del barco - solo H (horizontal) o V (vertical)
bool ValidacionesUtils::ValidarOrientacionBarco(const string& orientacion) {
    string orientacionUpper = ConvertirAMayusculas(orientacion);
    
    // Aceptar H, HORIZONTAL, V o VERTICAL
    if (orientacionUpper == "H" || orientacionUpper == "HORIZONTAL" ||
        orientacionUpper == "V" || orientacionUpper == "VERTICAL") {
        return true;
    }
    
    MostrarError("Orientación inválida. Use 'H' (horizontal) o 'V' (vertical)");
    return false;
}

// Verificar que el barco quepa en el tablero según su orientación
bool ValidacionesUtils::ValidarCoordenadaBarco(int x, int y, int tamano, bool vertical, int tableroSize) {
    // Primero verificar que las coordenadas iniciales sean válidas
    if (!ValidarCoordenadas(x, y)) {
        return false;
    }
    
    // Verificar que el barco no se salga del tablero
    if (vertical) {
        // Si es vertical, verificar que no se salga por abajo
        if (y + tamano - 1 > tableroSize - 1) {
            MostrarError("El barco se sale del tablero verticalmente");
            return false;
        }
    } else {
        // Si es horizontal, verificar que no se salga por la derecha
        if (x + tamano - 1 > tableroSize - 1) {
            MostrarError("El barco se sale del tablero horizontalmente");
            return false;
        }
    }
    
    return true;
}

// VALIDACIONES DE DISPAROS

// Validar que el disparo sea a coordenadas válidas y no repetidas
bool ValidacionesUtils::ValidarDisparo(int x, int y, const vector<pair<int, int>>& disparosAnteriores) {
    // Verificar que las coordenadas estén en el tablero
    if (!ValidarCoordenadas(x, y)) {
        return false;
    }
    
    // Verificar que no se haya disparado antes a esa posición
    if (CoordenadaYaDisparada(x, y, disparosAnteriores)) {
        MostrarError("Ya has disparado a esa coordenada");
        return false;
    }
    
    return true;
}

bool ValidacionesUtils::CoordenadaYaDisparada(int x, int y, const vector<pair<int, int>>& disparos) {
    for (const auto& disparo : disparos) {
        if (disparo.first == x && disparo.second == y) {
            return true;
        }
    }
    return false;
}

// VALIDACIONES DE ARCHIVOS

bool ValidacionesUtils::ValidarExtensionArchivo(const string& nombreArchivo, const string& extension) {
    if (nombreArchivo.length() < extension.length()) {
        return false;
    }
    
    string extensionArchivo = nombreArchivo.substr(nombreArchivo.length() - extension.length());
    return ConvertirAMinusculas(extensionArchivo) == ConvertirAMinusculas(extension);
}

bool ValidacionesUtils::ValidarRutaArchivo(const string& ruta) {
    if (EsStringVacio(ruta)) {
        MostrarError("La ruta del archivo no puede estar vacía");
        return false;
    }
    
    // Verificar caracteres ilegales para rutas
    string caracteresIlegales = "<>|?*\"";
    for (char c : caracteresIlegales) {
        if (ruta.find(c) != string::npos) {
            MostrarError("La ruta contiene caracteres ilegales");
            return false;
        }
    }
    
    return true;
}

bool ValidacionesUtils::ArchivoExiste(const string& rutaCompleta) {
    ifstream archivo(rutaCompleta);
    bool existe = archivo.good();
    archivo.close();
    return existe;
}

// UTILIDADES DE FORMATO Y LIMPIEZA

// Quitar espacios al inicio y final del texto
string ValidacionesUtils::LimpiarString(const string& entrada) {
    string resultado = entrada;
    
    // Eliminar espacios al inicio del texto
    resultado.erase(resultado.begin(), 
                   find_if(resultado.begin(), resultado.end(), [](unsigned char ch) {
                       return !isspace(ch);
                   }));
    
    // Eliminar espacios al final del texto
    resultado.erase(find_if(resultado.rbegin(), resultado.rend(), [](unsigned char ch) {
                       return !isspace(ch);
                   }).base(), resultado.end());
    
    return resultado;
}

string ValidacionesUtils::ConvertirAMayusculas(const string& entrada) {
    string resultado = entrada;
    transform(resultado.begin(), resultado.end(), resultado.begin(), ::toupper);
    return resultado;
}

string ValidacionesUtils::ConvertirAMinusculas(const string& entrada) {
    string resultado = entrada;
    transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}

vector<string> ValidacionesUtils::SepararString(const string& entrada, char delimitador) {
    vector<string> tokens;
    istringstream stream(entrada);
    string token;
    
    while (getline(stream, token, delimitador)) {
        token = LimpiarString(token);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

// VALIDACIONES DE MENÚ

bool ValidacionesUtils::ValidarOpcionMenu(int opcion, int minOpcion, int maxOpcion) {
    if (opcion < minOpcion || opcion > maxOpcion) {
        MostrarError("Opción inválida. Seleccione entre " + 
                    to_string(minOpcion) + " y " + to_string(maxOpcion));
        return false;
    }
    return true;
}

bool ValidacionesUtils::ValidarRespuestaSiNo(const string& respuesta) {
    string respuestaLimpia = ConvertirAMayusculas(LimpiarString(respuesta));
    
    return (respuestaLimpia == "S" || respuestaLimpia == "SI" || respuestaLimpia == "Y" || 
            respuestaLimpia == "YES" || respuestaLimpia == "N" || respuestaLimpia == "NO");
}

// UTILIDADES DE DEBUGGING Y LOGGING

void ValidacionesUtils::LogValidacion(const string& mensaje, bool esValido) {
    if (esValido) {
        cout << COLOR_SUCCESS << "✅ [VALIDACIÓN] " << mensaje << RESET << endl;
    } else {
        cout << COLOR_ERROR << "❌ [VALIDACIÓN] " << mensaje << RESET << endl;
    }
}

void ValidacionesUtils::MostrarError(const string& mensaje) {
    cout << COLOR_ERROR << "❌ Error: " << mensaje << RESET << endl;
}

void ValidacionesUtils::MostrarAdvertencia(const string& mensaje) {
    cout << COLOR_WARNING << "⚠️  Advertencia: " << mensaje << RESET << endl;
}

void ValidacionesUtils::MostrarExito(const string& mensaje) {
    cout << COLOR_SUCCESS << "✅ " << mensaje << RESET << endl;
}

// MÉTODOS PRIVADOS DE UTILIDAD

bool ValidacionesUtils::EsCaracterValido(char c) {
    return isalnum(c) || c == ' ' || c == '_' || c == '-';
}

// Verificar si un texto contiene solo números (puede tener + o - al inicio)
bool ValidacionesUtils::EsNumero(const string& str) {
    if (str.empty()) {
        return false;
    }
    
    size_t start = 0;
    // Si empieza con + o -, empezar a verificar desde la segunda posición
    if (str[0] == '-' || str[0] == '+') {
        start = 1;
        if (str.length() == 1) {
            return false;  // Solo tiene + o -
        }
    }
    
    // Verificar que el resto sean solo dígitos
    for (size_t i = start; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    
    return true;
}

bool ValidacionesUtils::ContieneSoloLetrasYNumeros(const string& str) {
    for (char c : str) {
        if (!isalnum(c) && c != ' ' && c != '_') {
            return false;
        }
    }
    return true;
}