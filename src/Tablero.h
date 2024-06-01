#pragma once

#include <vector>
#include "Pieza.h"

class Tablero {
protected:
    std::vector<std::vector<Pieza*>> casillas;
    Color turno;
    int seleccionadoX, seleccionadoY;

public:
    Tablero();
    virtual ~Tablero();

    int getSeleccionadoX() const;
    int getSeleccionadoY() const;
    void setSeleccionadoX(int x);
    void setSeleccionadoY(int y);
};

