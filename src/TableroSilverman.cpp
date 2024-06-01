#include "TableroSilverman.h"
#include "Rey.h"
#include "Reina.h"
#include "Torre.h"
#include "Peon.h"
#include <iostream>
#include <freeglut.h>
#include <windows.h>

TableroSilverman::TableroSilverman(bool esModoDemi) : Tablero(esModoDemi) {
    casillas.resize(5, std::vector<Pieza*>(4, nullptr));

    // Inicializar las piezas blancas
    casillas[0][0] = new Torre(0, 0, BLANCO);
    casillas[0][1] = new Reina(0, 1, BLANCO);
    casillas[0][2] = new Rey(0, 2, BLANCO);
    casillas[0][3] = new Torre(0, 3, BLANCO);
    for (int i = 0; i < 4; ++i) {
        casillas[1][i] = new Peon(1, i, BLANCO, esModoDemi);  // Modo no Demi
    }

    // Inicializar las piezas negras
    casillas[4][0] = new Torre(4, 0, NEGRO);
    casillas[4][1] = new Reina(4, 1, NEGRO);
    casillas[4][2] = new Rey(4, 2, NEGRO);
    casillas[4][3] = new Torre(4, 3, NEGRO);
    for (int i = 0; i < 4; ++i) {
        casillas[3][i] = new Peon(3, i, NEGRO, esModoDemi);  // Modo no Demi
    }
}

TableroSilverman::~TableroSilverman() {}
