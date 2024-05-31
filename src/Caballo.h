#pragma once

#include "Pieza.h"
using namespace std;

class Caballo : public Pieza {
public:
    Caballo(int _x, int _y, Color _color);
    virtual bool esMovimientoValido(int nuevoX, int nuevoY) override;
    virtual string obtenerNombre() const override;
};





