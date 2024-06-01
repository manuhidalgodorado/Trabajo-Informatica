#include "Tablero.h"
#include "Rey.h"
#include "Reina.h"
#include "Torre.h"
#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include <iostream>
#include <freeglut.h>
#include <string>
#include <vector>

using namespace std;

Tablero::Tablero(bool Demi) : turno(BLANCO), seleccionadoX(-1), seleccionadoY(-1) Demi(es_Demi) {}
Tablero::~Tablero() {
    for (auto& fila : casillas) {
        for (auto& pieza : fila) {
            delete pieza;
        }
    }
}

int Tablero::getSeleccionadoX() const {
    return seleccionadoX;
}

int Tablero::getSeleccionadoY() const {
    return seleccionadoY;
}

void Tablero::setSeleccionadoX(int x) {
    seleccionadoX = x;
}

void Tablero::setSeleccionadoY(int y) {
    seleccionadoY = y;
}
