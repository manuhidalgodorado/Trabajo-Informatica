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
    Pieza* obtenerPieza(int x, int y);
    void seleccionarPieza(int x, int y);
    bool caminoDespejado(int xInicial, int yInicial, int xFinal, int yFinal);
    bool esTurnoValido(int x, int y);
    void cambiarTurno();
    bool compMovePieza(int xInicial, int yInicial, int xFinal, int yFinal);
    bool moverPieza(int xInicial, int yInicial, int xFinal, int yFinal);
    bool esCapturaAlPaso(int xInicial, int yInicial, int xFinal, int yFinal) const;
    vector<std::pair<int, int>> obtenerMovimientosPosibles(int x, int y);


    int getSeleccionadoX() const;
    int getSeleccionadoY() const;
    void setSeleccionadoX(int x);
    void setSeleccionadoY(int y);
};

