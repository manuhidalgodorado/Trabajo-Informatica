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
    Pieza* obtenerpieza(int x, int y);
    void seleccionarPieza(int x, int y);
    bool caminoDespejado(int xInicial, int yInicial, int xFinal, int yFinal);
    bool esTurnoValido(int x, int y);
    bool caminoDespejado(int xInicial, int yInicial, int xFinal, int yFinal);
    void cambiarTurno();
    bool moverPieza(int xInicial, int yInicial, int xFinal, int yFinal);
    int getSeleccionadoX() const;
    int getSeleccionadoY() const;
    void setSeleccionadoX(int x);
    void setSeleccionadoY(int y);
};

