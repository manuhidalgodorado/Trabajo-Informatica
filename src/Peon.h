#pragma once

#include "Pieza.h"
#include <vector>

using namespace std;
class Peon : public Pieza {
public:
    Peon(int _x, int _y, Color _color, bool _esModoDemi);
    virtual bool esMovimientoValido(int nuevoX, int nuevoY) override;
    virtual string obtenerNombre() const override;
    bool esCapturaAlPaso(int nuevoX, int nuevoY, const vector<vector<Pieza*>>& casillas) const;
    bool esPrimerMovimiento() const;

private:
    bool esModoDemi;
};





