#pragma once

#include "Pieza.h"
class Torre : public Pieza {
public:
    Torre(int _x, int _y, Color _color);
    virtual bool esMovimientoValido(int nuevoX, int nuevoY) override;
    virtual std::string obtenerNombre() const override;
};


