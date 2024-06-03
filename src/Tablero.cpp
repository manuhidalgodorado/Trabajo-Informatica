#include "Tablero.h"
#include "Rey.h"
#include "Reina.h"
#include "Torre.h"
#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include <iostream>
#include "freeglut.h"
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

Tablero::Tablero(bool _esModoDemi) : turno(BLANCO), seleccionadoX(-1), seleccionadoY(-1), esModoDemi(_esModoDemi) {}
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
                string nombrePieza = casillas[i][j]->obtenerNombre();
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
        vector<pair<int, int>> movimientos = obtenerMovimientosPosibles(seleccionadoX, seleccionadoY);
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

Pieza* Tablero::obtenerPieza(int x, int y) {
    return casillas[x][y];
}

void Tablero::seleccionarPieza(int x, int y) {
    if (esTurnoValido(x, y)) {
        seleccionadoX = x;
        seleccionadoY = y;
    }
}
//Verifica si la casilla está despejada, para que no colisionen dos piezas del mismo color.
bool Tablero::caminoDespejado(int xInicial, int yInicial, int xFinal, int yFinal) {
    int dx = xFinal - xInicial;
    int dy = yFinal - yInicial;

    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    int x = xInicial + stepX;
    int y = yInicial + stepY;

    while (x != xFinal || y != yFinal) {
        if (casillas[x][y] != nullptr) {
            return false;
        }
        x += stepX;
        y += stepY;
    }

    return true;
}
//Verifica si el turno es para las piezas negras o para las piezas blancas
bool Tablero::esTurnoValido(int x, int y) {
    Pieza* pieza = obtenerPieza(x, y);
    return pieza != nullptr && pieza->getColor() == turno;
}

bool Tablero::esCapturaAlPaso(int xInicial, int yInicial, int xFinal, int yFinal) const {
    Pieza* pieza = casillas[xInicial][yInicial];
    if (Peon* peon = dynamic_cast<Peon*>(pieza)) {
        return peon->esCapturaAlPaso(xFinal, yFinal, casillas);
    }
    return false;
}


void Tablero::cambiarTurno() {
    turno = (turno == BLANCO) ? NEGRO : BLANCO;
}
bool Tablero::compMovePieza(int xInicial, int yInicial, int xFinal, int yFinal)
{
    Pieza* pieza = casillas[xInicial][yInicial];
    if (pieza == nullptr || pieza->getColor() != turno || !pieza->esMovimientoValido(xFinal, yFinal)) {
        return false;
    }

    // Verificar si el camino está despejado para todas las piezas excepto el peón y el caballo
    if (!dynamic_cast<Peon*>(pieza) && !dynamic_cast<Caballo*>(pieza) && !caminoDespejado(xInicial, yInicial, xFinal, yFinal)) {
        return false;
    }

    // Verificar si la casilla de destino tiene una pieza del mismo color
    if (casillas[xFinal][yFinal] != nullptr && casillas[xFinal][yFinal]->getColor() == turno) {
        return false;  // No se puede capturar una pieza del mismo color
    }

    // Verificar si un rey está siendo capturado
    // Validar movimiento del peón
    if (Peon* peon = dynamic_cast<Peon*>(pieza)) {
        // Movimiento hacia adelante
        if (xFinal == xInicial + ((peon->getColor() == BLANCO) ? 1 : -1) && yFinal == yInicial) {
            if (casillas[xFinal][yFinal] != nullptr) {
                return false;  // Casilla no está vacía
            }
        }
        else if (esModoDemi && peon->esPrimerMovimiento() && xFinal == xInicial + 2 * ((peon->getColor() == BLANCO) ? 1 : -1) && yFinal == yInicial) {
            if (casillas[xFinal][yFinal] != nullptr || casillas[xInicial + ((peon->getColor() == BLANCO) ? 1 : -1)][yFinal] != nullptr) {
                return false;  // Casilla no está vacía
            }
        }
        else if (std::abs(xFinal - xInicial) == 1 && std::abs(yFinal - yInicial) == 1) {
            // Captura en diagonal
            if (casillas[xFinal][yFinal] == nullptr || casillas[xFinal][yFinal]->getColor() == turno) {
                // Verificar captura al paso
                if (!esCapturaAlPaso(xInicial, yInicial, xFinal, yFinal)) {
                    return false;  // No hay pieza para capturar o es una pieza del mismo color
                }
            }
        }
        else {
            return false;  // Movimiento no válido para el peón
        }
    }
}

bool Tablero::moverPieza(int xInicial, int yInicial, int xFinal, int yFinal) {

    Pieza* pieza = casillas[xInicial][yInicial];
    if (compMovePieza(xInicial, yInicial, xFinal, yFinal))
    {
        delete casillas[xFinal][yFinal];  // Eliminar la pieza capturada
        casillas[xFinal][yFinal] = pieza;
        casillas[xInicial][yInicial] = nullptr;
        pieza->setPosicion(xFinal, yFinal);
        return true;
    }
    else
    {
        return false;
    }
}
vector<std::pair<int, int>> Tablero::obtenerMovimientosPosibles(int x, int y) {
    std::vector<std::pair<int, int>> movimientos;
    Pieza* pieza = casillas[x][y];
    if (!pieza) return movimientos;

    for (int i = 0; i < casillas.size(); ++i) {
        for (int j = 0; j < casillas[0].size(); ++j) {
            if (compMovePieza(pieza->getX(), pieza->getY(), i, j))
            {
                movimientos.push_back({ i,j });
            }
        }
    }
    return movimientos;
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
