#pragma once

#include "Pieza.h"
#include <vector>

class Peon : public Pieza {
public:
    Peon(int _x, int _y, Color _color, bool _esModoDemi);
    virtual bool esMovimientoValido(int nuevoX, int nuevoY) override;
    virtual std::string obtenerNombre() const override;
    bool esCapturaAlPaso(int nuevoX, int nuevoY, const std::vector<std::vector<Pieza*>>& casillas) const;
    bool esPrimerMovimiento() const;

private:
    bool esModoDemi;
};





