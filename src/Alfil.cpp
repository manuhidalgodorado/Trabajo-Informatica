#include "Alfil.h"
#include <cmath>
using namespace std;

Alfil::Alfil(int _x, int _y, Color _color) : Pieza(_x, _y, _color) {}

bool Alfil::esMovimientoValido(int nuevoX, int nuevoY) {
    // El alfil se mueve en diagonal
    return std::abs(nuevoX - x) == std::abs(nuevoY - y);
}

string Alfil::obtenerNombre() const {
    return "Alfil";
}

