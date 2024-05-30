#include "Pieza.h"

Pieza::Pieza(int _x, int _y, Color _color) : x(_x), y(_y), color(_color) {}

int Pieza::getX() const { return x; }
int Pieza::getY() const { return y; }
Color Pieza::getColor() const { return color; }

void Pieza::setPosicion(int nuevoX, int nuevoY) {
    x = nuevoX;
    y = nuevoY;
}

