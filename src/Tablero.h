#pragma once

#include <vector>
#include "Pieza.h"

using namespace std;

class Tablero {
protected:
    vector<vector<Pieza*>> casillas;
    Color turno;
    int seleccionadoX, seleccionadoY;
    bool esModoDemi;

public:
    Tablero(bool _esModoDemi);
    virtual ~Tablero();

     void dibujar();
    void cambiarTurno();
    bool moverPieza(int xInicial, int yInicial, int xFinal, int yFinal);
    int getSeleccionadoX() const;
    int getSeleccionadoY() const;
    void setSeleccionadoX(int x);
    void setSeleccionadoY(int y);
};

