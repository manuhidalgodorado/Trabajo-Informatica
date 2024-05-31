#pragma once

#include "Pieza.h"

class Reina : public Pieza {
public:
    Reina(int _x, int _y, Color _color);
    virtual bool esMovimientoValido(int nuevoX, int nuevoY) override;
    virtual std::string obtenerNombre() const override;
};

