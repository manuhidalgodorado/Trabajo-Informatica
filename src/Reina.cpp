#include "Reina.h"
#include <cmath>

using namespace std;
Reina::Reina(int _x, int _y, Color _color) : Pieza(_x, _y, _color) {}

bool Reina::esMovimientoValido(int nuevoX, int nuevoY) {
    return (x == nuevoX || y == nuevoY || std::abs(nuevoX - x) == std::abs(nuevoY - y));
}

string Reina::obtenerNombre() const {
    return "Reina";
}

