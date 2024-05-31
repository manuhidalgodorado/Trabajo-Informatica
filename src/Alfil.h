#pragma once

#include "Pieza.h"
using namespace std;

class Alfil : public Pieza {
public:
    Alfil(int _x, int _y, Color _color);
    virtual bool esMovimientoValido(int nuevoX, int nuevoY) override;
    virtual string obtenerNombre() const override;
};

