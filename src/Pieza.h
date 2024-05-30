#pragma once

#include <string>

enum Color { BLANCO, NEGRO };

class Pieza {
protected:
    int x, y;
    Color color;

public:
    Pieza(int _x, int _y, Color _color);
    virtual ~Pieza() = default;

    virtual bool esMovimientoValido(int nuevoX, int nuevoY) = 0;
    virtual std::string obtenerNombre() const = 0;

    int getX() const;
    int getY() const;
    Color getColor() const;
    void setPosicion(int nuevoX, int nuevoY);
};

