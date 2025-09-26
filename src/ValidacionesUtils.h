#ifndef VALIDACIONESUTILS_H
#define VALIDACIONESUTILS_H

#include <string>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

class ValidacionesUtils {
public:
//Validacion de coordenadas
    static bool ValidarCoordenadas(int x, int y);
    static bool ValidarRangoCoordenadas(int x, int y, int minX, int minY, int maxX, int maxY);
    static bool CoordenadasDentroDelTablero(int x, int y, int tamano = 20);

    //Validacion entrada de usuario
    static bool ValidarEntradaNumerica(const string& entrada, int& numero);
    static bool ValidarRangoNumerico(int numero, int min, int max);
    static bool ValidarComandoJuego(const string& comando);

    //Validacion de nombre
    static bool ValidarNombre(const string& nombre);
    static bool ValidarNombreArchivo(const string& nombreArchivo);
    static bool ContieneCaracteresEspeciales(const string& texto);
    static bool EsStringVacio(const string& texto);

    //Validacion de barco
    static bool ValidarTamanoBarco(int tamano);
    static bool ValidarOrientacionBarco(const string& orientacion);
    static bool ValidarCoordenadasBarco(int x, int y, int tamano, bool vertical, int tableroSize = 20);

    //Validacion de disparo
    static bool ValidarDisparo(int x, int y, const vector<pair<int, int>>& disparosAnteriores);
    static bool CoordenadaYaDisparada(int x, int y, const vector<pair<int, int>>& disparos);

    //validar archivo
    static bool ValidarExtensionArchivo(const string& nombreArchivo, const string& extension);
    static bool ValidarRutaArchivo(const string& ruta);
    static bool ArchivoExiste(const string& rutaCompleta);

    //Utilidades de formato y limpieza
    static string LimpiarString(const string& entrada);
    static string ConvertirAMayusculas(const string& entrada);
    static string ConvertirAMinuscula(const string& entrada);
    static vector<string> SepararString(const string& entrada, char delimitador);

    //Validadciones de menu
    static bool ValidarOpcionMenu(int opcion, int minOpcion, int maxOpcion);
    static bool ValidarRespuestasSiNo(const string& respuesta);

    //utilidades de debug y log
    static void LogValidacion(const string& mensaje, bool esValido);
    static void MostrarError(const string& mensaje);
    static void MostrarAdvertencia(const string& mensaje);
    static void MostrarExito(const string& mensaje);

    //constantes de validacion
    static const int TABLERO_MIN = 0;
    static const int TABLERO_MAX = 19;
    static const int BARCO_MIN_SIZE = 1;
    static const int BARCO_MAX_SIZE = 5;
    static const int NOMBRE_MIN_LENGTH = 2;
    static const int NOMBRE_MAX_LENGTH = 20;

private:
    //Metodos Privados
    static bool EsCaracterValido(char c);
    static bool EsNumero(const string& str);
    static bool ContieneSoloLetrasYNumeros(const string& str);
    static string LimpiarString(const string& entrada);
    static bool ValidarRespuestaSiNo(const string& entrada);

};

#endif // VALIDACIONESUTILS_H
