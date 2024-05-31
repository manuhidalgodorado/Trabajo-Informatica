#include "Caballo.h"
#include <cmath>

Caballo::Caballo(int _x, int _y, Color _color) : Pieza(_x, _y, _color) {}

bool Caballo::esMovimientoValido(int nuevoX, int nuevoY) {
    // El caballo se mueve en forma de L: dos casillas en una dirección y una casilla en la otra
    int dx = std::abs(nuevoX - x);
    int dy = std::abs(nuevoY - y);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

std::string Caballo::obtenerNombre() const {
    return "Caballo";
}


