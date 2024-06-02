#include "TableroDemi.h"
#include "Rey.h"
#include "Alfil.h"
#include "Caballo.h"
#include "Torre.h"
#include "Peon.h"
#include <iostream>
#include <freeglut.h>

using namespace std;

TableroDemi::TableroDemi(bool esModoDemi) : Tablero(esModoDemi) {
    casillas.resize(8, std::vector<Pieza*>(4, nullptr));

    // Construcción de las piezas blancas en su posición correcta
    casillas[0][0] = new Rey(0, 0, BLANCO);
    casillas[0][1] = new Alfil(0, 1, BLANCO);
    casillas[0][2] = new Caballo(0, 2, BLANCO);
    casillas[0][3] = new Torre(0, 3, BLANCO);
  // Construcción de la pieza peón blanco con un bucle for
    for (int i = 0; i < 4; i++) {
        casillas[1][i] = new Peon(1, i, BLANCO, esModoDemi);  
    }

    // Construcción de las piezas negras en su posición correcta
    casillas[7][0] = new Rey(7, 0, NEGRO);
    casillas[7][1] = new Alfil(7, 1, NEGRO);
    casillas[7][2] = new Caballo(7, 2, NEGRO);
    casillas[7][3] = new Torre(7, 3, NEGRO);
  // Construcción de la pieza peón negro con un bucle for
    for (int i = 0; i < 4; i++) {
        casillas[6][i] = new Peon(6, i, NEGRO, esModoDemi);  
    }
}

TableroDemi::~TableroDemi() {}
