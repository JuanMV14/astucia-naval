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
    static bool CoordenadaDentroDelTablero(int x, int y, int tamaño = 20);

    //Validacion entrada de usuario
    stactic bool ValidarEntradaNumerica(const string& entrada, int& numero);
    stactic bool ValidarRangoNumerico(int numero, int min, int max);
    stactic bool ValidarComandoJuego(const string& comando);

    //Validacion de nombre
    stactic bool ValidarNombre(const string& nombre);
    stactic bool ValidarNombreArchivo(const string& nombreArchivo);
    stactic bool ContieneCaracteresEspeciales(const string& texto);
    stactic bool EsStringVacio(const string& texto);

    //Validacion de barco
    stactic bool ValidarTamañoBarco(int tamaño);
    stactic bool ValidarOrientacionBarco(const string& orientacion);
    stactic bool ValidarCoordendasBarco(int x, int y, int tamaño, bool vertical, int tableroSize = 20);

    //Validacion de disparo
    stactic bool ValidarDisparo(int x, int y, const vector<pair<int, int>>& disparosAnteriores);
    stactic bool CoordenadaYaDisparada(int x, int y, const vector<pair<int, int>>& disparos);

    //validar archivo
    stactic bool ValidarExtensionArchivo(const string& nombreArchivo, const string& extension);
    stactic bool ValidarRutaArchivo(const string& ruta);
    stactic bool ArchivoExiste(const string& rutaCompleta);

    //Utilidades de formato y limpieza
    stactic sting LimpiarString(const string& entrada);
    stactic string ConvertirAMayuscula(const string& entrada);
    stactic string ConvertirAMinuscula(const string& entrada);
    stactic vector<string> SepararString(const string& entrada, char delimitador);

    //Validadciones de menu
    stactic bool ValidarOpcionMenu(int opcion, int minOpcion, int maxOpcion);
    stactic bool ValidarRespiestasSiNo(const string& respuesta);

    //utilidades de debug y log
    stactic void LogValidacion(const string& mensaje, bool esValido);
    stactic void MostarError(const string& mensaje);
    stactic void MostarAdvertencia(const string& mensaje);
    stactic void MostarExito(const string& mensaje);

    //constantes de validacion
    stactic const int TABLERO_MIN = 0;
    stactic const int TABLERO_MAX = 19;
    stactic const int BARCO_MIN_SIZE = 1;
    stactic const int BARCO_MAX_SIZE = 5;
    stactic const int NOMBRE_MIN_LENGTH = 2;
    stactic const int NOMBRE_MAX_LENGTH = 20;

private:
    //Metodos Privados
    stactic bool EsCaracterValido(char c);
    stactic bool EsNumero(const string& str);
    stactic bool ContieneSoloLetrasYNumeros(const string& str);

};

#endif // VALIDACIONESUTILS_H
