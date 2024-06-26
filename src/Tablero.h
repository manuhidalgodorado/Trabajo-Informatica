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

    void dibujar(int anchoPantalla, int altoPantalla);
    Pieza* obtenerPieza(int x, int y);
    void seleccionarPieza(int x, int y);
    bool caminoDespejado(int xInicial, int yInicial, int xFinal, int yFinal);
    bool esTurnoValido(int x, int y);
    void cambiarTurno();
    bool compMovePieza(int xInicial, int yInicial, int xFinal, int yFinal);
    bool moverPieza(int xInicial, int yInicial, int xFinal, int yFinal);
    bool esCapturaAlPaso(int xInicial, int yInicial, int xFinal, int yFinal) const;
    vector<pair<int, int>> obtenerMovimientosPosibles(int x, int y);
    pair<int, int> peonCorona(bool& coronacion);
    bool hayJaque();
    bool hayMate_Ahogado();
    void resetearPassant(Color turno);
    void Coronar(std::pair<int, int> pos, char opci);
    bool noMatMate();
    Color getTurno() const;


    int getSeleccionadoX() const;
    int getSeleccionadoY() const;
    void setSeleccionadoX(int x);
    void setSeleccionadoY(int y);
};

