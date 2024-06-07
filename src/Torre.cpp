#include "Torre.h"

using namespace std;
Torre::Torre(int _x, int _y, Color _color) : Pieza(_x, _y, _color) { 
    dirImg = (_color == BLANCO) ? "imagenes/TorreBlanca.png" : "imagenes/TorreNegra.png";
    dirSon = (_color == BLANCO) ? "sonidos/TorreBlanca.wav" : "sonidos/TorreNegra.wav";
}

bool Torre::esMovimientoValido(int nuevoX, int nuevoY) {
    return (x == nuevoX || y == nuevoY);
}

string Torre::obtenerNombre() const {
    return "Torre";
}

