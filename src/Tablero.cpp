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

Tablero::Tablero(bool _esModoDemi) : turno(BLANCO), seleccionadoX(-1), seleccionadoY(-1) esModoDemi(_esModoDemi) {}
Tablero::~Tablero() {
    for (auto& fila : casillas) {
        for (auto& pieza : fila) {
            delete pieza;
        }
    }
}

void Tablero::dibujar() {
    // Dibujar tablero
    int filas = casillas.size();
    int columnas = casillas[0].size();
    glColor3f(0.8f, 0.8f, 0.8f);
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if ((i + j) % 2 == 0) glColor3f(0.9f, 0.9f, 0.9f);
            else glColor3f(0.3f, 0.3f, 0.3f);
            glBegin(GL_QUADS);
            glVertex2f(j * 120, i * 120);
            glVertex2f((j + 1) * 120, i * 120);
            glVertex2f((j + 1) * 120, (i + 1) * 120);
            glVertex2f(j * 120, (i + 1) * 120);
            glEnd();
        }
    }

    // Dibujar piezas
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (casillas[i][j] != nullptr) {
                std::string nombrePieza = casillas[i][j]->obtenerNombre();
                Color colorPieza = casillas[i][j]->getColor();
                if (colorPieza == BLANCO) glColor3f(1.0f, 1.0f, 1.0f);
                else glColor3f(0.0f, 0.0f, 0.0f);
                // Dibujar la pieza como un texto en la casilla
                glRasterPos2f(j * 120 + 50, i * 120 + 50);
                for (char c : nombrePieza) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
                }
            }
        }
    }

    // Dibujar selección
    if (seleccionadoX != -1 && seleccionadoY != -1) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(seleccionadoY * 120, seleccionadoX * 120);
        glVertex2f((seleccionadoY + 1) * 120, seleccionadoX * 120);
        glVertex2f((seleccionadoY + 1) * 120, (seleccionadoX + 1) * 120);
        glVertex2f(seleccionadoY * 120, (seleccionadoX + 1) * 120);
        glEnd();
    }

    // Dibujar movimientos posibles
    if (seleccionadoX != -1 && seleccionadoY != -1) {
        glColor3f(0.0f, 1.0f, 0.0f);  // Color verde para movimientos posibles
        std::vector<std::pair<int, int>> movimientos = obtenerMovimientosPosibles(seleccionadoX, seleccionadoY);
        for (const auto& mov : movimientos) {
            glBegin(GL_LINE_LOOP);
            glVertex2f(mov.second * 120, mov.first * 120);
            glVertex2f((mov.second + 1) * 120, mov.first * 120);
            glVertex2f((mov.second + 1) * 120, (mov.first + 1) * 120);
            glVertex2f(mov.second * 120, (mov.first + 1) * 120);
            glEnd();
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
