#pragma once

#include "Pieza.h"
using namespace std;
class Torre : public Pieza {
public:
    Torre(int _x, int _y, Color _color);
    virtual bool esMovimientoValido(int nuevoX, int nuevoY) override;
    virtual string obtenerNombre() const override;
};


