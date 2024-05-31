#include "Peon.h"
#include <cmath>
#include <vector>

using namespace std;
Peon::Peon(int _x, int _y, Color _color, bool _esModoDemi) : Pieza(_x, _y, _color), esModoDemi(_esModoDemi) {}

bool Peon::esMovimientoValido(int nuevoX, int nuevoY) {
    int dir = (color == BLANCO) ? 1 : -1;

    // Movimiento hacia adelante
    if (nuevoX == x + dir && nuevoY == y) {
        return true;
    }

    // Movimiento inicial de dos casillas solo en modo Demi
    if (esModoDemi && esPrimerMovimiento() && nuevoX == x + 2 * dir && nuevoY == y) {
        return true;
    }

    // Captura en diagonal
    if (nuevoX == x + dir && std::abs(nuevoY - y) == 1) {
        return true;
    }

    return false;
}

string Peon::obtenerNombre() const {
    return "Peon";
}

bool Peon::esCapturaAlPaso(int nuevoX, int nuevoY, const vector<vector<Pieza*>>& casillas) const {
    if (!esModoDemi) return false;  // Captura al paso solo en modo Demi
    int dir = (color == BLANCO) ? 1 : -1;
    if (nuevoX == x + dir && std::abs(nuevoY - y) == 1) {
        // Verificar si la captura al paso es posible
        int peonX = x;
        int peonY = nuevoY;
        Pieza* posiblePeon = casillas[peonX][peonY];
        if (posiblePeon != nullptr && dynamic_cast<Peon*>(posiblePeon) && posiblePeon->getColor() != color) {
            return true;
        }
    }
    return false;
}

bool Peon::esPrimerMovimiento() const {
    return (color == BLANCO && x == 1) || (color == NEGRO && x == 6);
}






