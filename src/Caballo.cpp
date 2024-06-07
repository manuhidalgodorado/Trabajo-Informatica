#include "Caballo.h"
#include <cmath>
using namespace std;
Caballo::Caballo(int _x, int _y, Color _color) : Pieza(_x, _y, _color) {
     dirImg = (_color == BLANCO) ? "imagenes/CaballoBlanco.png" : "imagenes/CaballoNegro.png";
     dirSon = (_color == BLANCO) ? "sonidos/CaballoBlanco.wav" : "sonidos/CaballoNegro.wav";
}

bool Caballo::esMovimientoValido(int nuevoX, int nuevoY) {
    // El caballo se mueve en forma de L: dos casillas en una dirección y una casilla en la otra
    int dx = abs(nuevoX - x);
    int dy = abs(nuevoY - y);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

string Caballo::obtenerNombre() const {
    return "Caballo";
}


