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


Tablero::Tablero(bool _esModoDemi) : turno(BLANCO), seleccionadoX(-1), seleccionadoY(-1), esModoDemi(_esModoDemi) {}

Tablero::~Tablero() {
    for (auto& fila : casillas) {
        for (auto& pieza : fila) {
            delete pieza;
        }
    }
}

void Tablero::dibujar(int anchoPantalla, int altoPantalla) {
    // Dibujar tablero
    int filas = casillas.size();
    int columnas = casillas[0].size();

    // Determinar el tamaño de las casillas según el tipo de juego
    float anchoCasilla = static_cast<float>(anchoPantalla) / columnas;
    float altoCasilla = static_cast<float> (altoPantalla) / filas;

    // Dibujar tablero
    glColor3f(0.8f, 0.8f, 0.8f);
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if ((i + j) % 2 == 0) glColor3f(0.9f, 0.9f, 0.9f);
            else glColor3f(0.3f, 0.3f, 0.3f);
            glBegin(GL_QUADS);
            glVertex2f(j * anchoCasilla, i * altoCasilla);
            glVertex2f((j + 1) * anchoCasilla, i * altoCasilla);
            glVertex2f((j + 1) * anchoCasilla, (i + 1) * altoCasilla);
            glVertex2f(j * anchoCasilla, (i + 1) * altoCasilla);
            glEnd();
        }
    }

    // Dibujar piezas
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (casillas[i][j] != nullptr) {
                casillas[i][j]->dibujarPieza(anchoCasilla, altoCasilla);
            }
        }
    }


    // Dibujar selección
    if (seleccionadoX != -1 && seleccionadoY != -1) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(seleccionadoY * anchoCasilla, seleccionadoX * altoCasilla);
        glVertex2f((seleccionadoY + 1) * anchoCasilla, seleccionadoX * altoCasilla);
        glVertex2f((seleccionadoY + 1) * anchoCasilla, (seleccionadoX + 1) * altoCasilla);
        glVertex2f(seleccionadoY * anchoCasilla, (seleccionadoX + 1) * altoCasilla);
        glEnd();
    }

    // Dibujar movimientos posibles
    if (seleccionadoX != -1 && seleccionadoY != -1) {
        glColor3f(0.0f, 1.0f, 0.0f);  // Color verde para movimientos posibles
        std::vector<std::pair<int, int>> movimientos = obtenerMovimientosPosibles(seleccionadoX, seleccionadoY);
        for (const auto& mov : movimientos) {
            glBegin(GL_LINE_LOOP);
            glVertex2f(mov.second * anchoCasilla, mov.first * altoCasilla);
            glVertex2f((mov.second + 1) * anchoCasilla, mov.first * altoCasilla);
            glVertex2f((mov.second + 1) * anchoCasilla, (mov.first + 1) * altoCasilla);
            glVertex2f(mov.second * anchoCasilla, (mov.first + 1) * altoCasilla);
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
    hayMate_Ahogado();
    resetearPassant(turno);
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
            peon->setEnPassant(true);
        }
        else if (abs(xFinal - xInicial) == 1 && abs(yFinal - yInicial) == 1) {
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
    if (dynamic_cast<Peon*>(pieza) && abs(xFinal - xInicial) == 1 && abs(yFinal - yInicial) == 1 && esModoDemi && casillas[xFinal][yFinal] == nullptr)
    {
        Pieza* piezaprov = casillas[xInicial][yFinal];
        casillas[xInicial][yFinal] = nullptr;
        casillas[xFinal][yFinal] = pieza;
        casillas[xInicial][yInicial] = nullptr;
        pieza->setPosicion(xFinal, yFinal);
        bool hacke = hayJaque();
        casillas[xInicial][yInicial] = pieza;
        casillas[xFinal][yFinal] = nullptr;
        casillas[xInicial][yFinal] = piezaprov;
        pieza->setPosicion(xInicial, yInicial);
        if (hacke)return false;
        return true;
    }
    Pieza* piezaprov = casillas[xFinal][yFinal];
    casillas[xFinal][yFinal] = pieza;
    casillas[xInicial][yInicial] = nullptr;
    pieza->setPosicion(xFinal, yFinal);
    bool hacke = hayJaque();
    casillas[xInicial][yInicial] = pieza;
    casillas[xFinal][yFinal] = piezaprov;
    pieza->setPosicion(xInicial, yInicial);
    if (hacke)return false;
    return true;
}

bool Tablero::moverPieza(int xInicial, int yInicial, int xFinal, int yFinal) {

    Pieza* pieza = casillas[xInicial][yInicial];
    if (compMovePieza(xInicial, yInicial, xFinal, yFinal))
    {
        // Mover la pieza a la nueva posición y capturar cualquier pieza en la posición final
        //Elimicacion en caso de captura en paso
        if (dynamic_cast<Peon*>(pieza) && std::abs(xFinal - xInicial) == 1 && std::abs(yFinal - yInicial) == 1 && esModoDemi && casillas[xFinal][yFinal] == nullptr)
        {
            delete casillas[xInicial][yFinal];  // Eliminar la pieza capturada
            casillas[xInicial][yFinal] = nullptr;
            casillas[xFinal][yFinal] = pieza;
            casillas[xInicial][yInicial] = nullptr;
            pieza->setPosicion(xFinal, yFinal);
        }
        else {//Captura clasica
            delete casillas[xFinal][yFinal];  // Eliminar la pieza capturada
            casillas[xFinal][yFinal] = pieza;
            casillas[xInicial][yInicial] = nullptr;
            pieza->setPosicion(xFinal, yFinal);
        }
        string jugador = (turno == BLANCO) ? "Blancas" : "Negras";
        cout << jugador << ": " << pieza->obtenerNombre() << (char)(pieza->getY() + 97) << pieza->getX() << endl;
    }
    else
    {
        return false;
    }
}
vector<pair<int, int>> Tablero::obtenerMovimientosPosibles(int x, int y) {
    vector<pair<int, int>> movimientos;
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
//Función para comprobar Jaque
bool Tablero::hayJaque()
{
    Pieza* piezabus;
    Pieza* turnoRey;
    //Buscamos el rey
    for (int i = 0; i < casillas.size(); ++i) {
        for (int j = 0; j < casillas[0].size(); ++j) {
            piezabus = casillas[i][j];
            if (piezabus = dynamic_cast<Rey*>(casillas[i][j]))
            {
                if (piezabus->getColor() == turno)
                {
                    turnoRey = piezabus;
                }
            }

        }
    }
    Pieza* piezacom;
    //Comprobamos si el rey esta amenazado por alguna de las piezas.
    for (int i = 0; i < casillas.size(); ++i) {
        for (int j = 0; j < casillas[0].size(); ++j) {
            piezacom = casillas[i][j];
            if (piezacom != nullptr && piezacom->getColor() != turno)
            {
                if (piezacom->esMovimientoValido(turnoRey->getX(), turnoRey->getY()))
                {
                    //Comprobamos Alfil, torre y reina
                    if (!dynamic_cast<Peon*>(piezacom) && !dynamic_cast<Caballo*>(piezacom) && caminoDespejado(piezacom->getX(), piezacom->getY(), turnoRey->getX(), turnoRey->getY()))
                    {
                        return true;
                    }
                    //Comprobamos posible captura de peon
                    if (std::abs(turnoRey->getX() - piezacom->getX()) == 1 && std::abs(turnoRey->getY() - piezacom->getY()) == 1) {
                        // Captura en diagonal
                        return true;
                    }
                    //Comprobamos posible captura con caballo
                    if (dynamic_cast<Caballo*>(piezacom))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool Tablero::hayMate_Ahogado()
{
    vector <pair<int, int>> movpieza;
    int nummov = 0;
    Pieza* pieza;
    for (int i = 0; i < casillas.size(); ++i) {
        for (int j = 0; j < casillas[0].size(); ++j) {
            pieza = casillas[i][j];
            if (pieza != nullptr)
            {
                movpieza = obtenerMovimientosPosibles(pieza->getX(), pieza->getY());
                nummov += movpieza.size();
            }
        }
    }
    if (nummov == 0)
    {
        if (hayJaque())
        {
            string ganador = (turno == BLANCO) ? "Negras" : "Blancas";
            string mensaje = "Jaque Mate! Ganador " + ganador;
            MessageBoxA(nullptr, mensaje.c_str(), "Fin de Partida", MB_OK);
            cout << "Jaque Mate, Ganan " << ganador << endl;
            return true;
        }
        else
        {
            string ganador = (turno == NEGRO) ? "Negras" : "Blancas";
            string mensaje = "Ahogado " + ganador + " ¡TABLAS!";
            MessageBoxA(nullptr, mensaje.c_str(), "Fin de Partida", MB_OK);
            cout << "Ahogado " << ganador << endl << "TABLAS";
            return true;
        }
    }
    else if (noMatMate())
    {
        std::string ganador = (turno == NEGRO) ? "Negras" : "Blancas";
        std::string mensaje = "No hay material suficiente ¡TABLAS!";
        MessageBoxA(nullptr, mensaje.c_str(), "Fin de Partida", MB_OK);
        std::cout << "No hay material " << ganador << std::endl << "TABLAS";
        return true;
    }
    return false;
}
void Tablero::resetearPassant(Color turno) {
    Pieza* posiblePeon;
    Peon* confirmadoPeon;
    for (int i = 0; i < casillas.size(); ++i) {
        for (int j = 0; j < casillas[0].size(); ++j) {
            posiblePeon = casillas[i][j];
            if (dynamic_cast<Peon*>(posiblePeon) && posiblePeon->getColor() == turno)
            {
                confirmadoPeon = dynamic_cast<Peon*>(posiblePeon);
                confirmadoPeon->setEnPassant(false);
            }

        }
    }
}
std::pair<int, int> Tablero::peonCorona(bool& coronacion)
{
    Pieza* posiblePeon;
    Peon* confirmadoPeon;
    int LineaFinal = (turno == BLANCO) ? (casillas.size() - 1) : 0;
    bool coronado = false;
    for (int j = 0; j < casillas[0].size(); ++j) {
        posiblePeon = casillas[LineaFinal][j];
        if (dynamic_cast<Peon*>(posiblePeon) && posiblePeon->getColor() == turno)
        {
            delete casillas[LineaFinal][j];
            casillas[LineaFinal][j] = nullptr;
            MessageBoxA(nullptr, "Peon Corona", "Corona", MB_OK);
            if (esModoDemi) MessageBoxA(nullptr, "Torre: t, Alfil: a, Caballo: c\n INTRODUCIR EN PANTALLA DE COMPILACION", "Corona", MB_OK);
            else MessageBoxA(nullptr, "Torre: t, Reina: r\n INTRODUCIR EN PANTALLA DE COMPILACION", "Corona", MB_OK);
            coronacion = true;
            return { LineaFinal, j };
        }
    }
    coronacion = false;
    return{ -1,-1 };
}
void Tablero::Coronar(std::pair<int, int> pos, char opci)
{
    if (esModoDemi)
    {
        switch (opci)
        {
        case 't':
            casillas[pos.first][pos.second] = new Torre(pos.first, pos.second, turno);
            break;
        case 'a':
            casillas[pos.first][pos.second] = new Alfil(pos.first, pos.second, turno);
            break;
        case 'c':
            casillas[pos.first][pos.second] = new Caballo(pos.first, pos.second, turno);
            break;
        }
    }
    else
    {
        switch (opci)
        {
        case 'r':
            casillas[pos.first][pos.second] = new Reina(pos.first, pos.second, turno);
            break;
        case 't':
            casillas[pos.first][pos.second] = new Torre(pos.first, pos.second, turno);
            break;
        }
    }
}
bool Tablero::noMatMate()
{
    Pieza* pieza;
    int matN = 0, matB = 0;
    for (int i = 0; i < casillas.size(); ++i) {
        for (int j = 0; j < casillas[0].size(); ++j) {
            pieza = casillas[i][j];
            if (dynamic_cast<Peon*>(casillas[i][j]) || dynamic_cast<Reina*>(casillas[i][j]) || dynamic_cast<Torre*>(casillas[i][j]))
            {
                return false;
            }
            if ((dynamic_cast<Caballo*>(casillas[i][j]) || dynamic_cast<Alfil*>(casillas[i][j])) && pieza->getColor() == BLANCO) {
                matB++;
            }
            if ((dynamic_cast<Caballo*>(casillas[i][j]) || dynamic_cast<Alfil*>(casillas[i][j])) && pieza->getColor() == NEGRO) {
                matN++;
            }
        }
    }
    if (matN > 1 || matB > 1)
    {
        return false;
    }
    return true;
}
Color Tablero::getTurno() const {
    return turno;
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
