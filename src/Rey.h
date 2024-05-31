#pragma once

#include "Pieza.h"
using namespace std;

class Rey : public Pieza {
public:
    Rey(int _x, int _y, Color _color);
    virtual bool esMovimientoValido(int nuevoX, int nuevoY) override;
    virtual string obtenerNombre() const override;
};

