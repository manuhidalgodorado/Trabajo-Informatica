#pragma once

#include <string>

using namespace std;
enum Color { BLANCO, NEGRO };

class Pieza {
protected:
    int x, y;
    Color color;
    const char* dirImg;
    const char* dirSon;

public:
    Pieza(int _x, int _y, Color _color);
    Pieza(const Pieza* pieza);
    virtual ~Pieza() = default;

    virtual bool esMovimientoValido(int nuevoX, int nuevoY) = 0;
    virtual std::string obtenerNombre() const = 0;
    void dibujarPieza(float, float);
    Pieza& operator=(const Pieza* pieza);

    int getX() const;
    int getY() const;
    Color getColor() const;
    void setPosicion(int nuevoX, int nuevoY);
};

