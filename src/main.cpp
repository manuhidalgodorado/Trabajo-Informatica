#include <iostream>
#include <freeglut.h>
#include "TableroSilverman.h"
#include "TableroDemi.h"
#include <algorithm>
#include <random>


// Declaraciones de funciones
void display();
void onMouseClick(int button, int state, int x, int y);
void handleKeypress(unsigned char, int, int);
void inicializarJuego();
void displayText(float x, float y, const char* text);
void jugar_contra_ordenador();

Tablero* tablero = nullptr;
int tipoJuego = 0;
bool menuActivo = true;
bool ordenador = false;
int mainWindow;
std::pair<int, int> peonCorona;
bool coronacion;
bool finPartida;

// Variables para controlar el tamaño de las pantallas
const int anchoPantallaSilverman = 480;
const int anchoPantallaDemi = 480;
const int altoPantallaSilverman = 600;
const int altoPantallaDemi = 700;

void displayText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (finPartida)exit(0);
    if (menuActivo) {
        // Dibujar pantalla de menú
        glColor3f(0.0f, 0.0f, 0.0f);
        displayText(130, 370, "Seleccione el tipo de juego:");

        // Dibujar botón Silverman 4x5
        glColor3f(0.6f, 0.6f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(150, 300);
        glVertex2f(330, 300);
        glVertex2f(330, 350);
        glVertex2f(150, 350);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        displayText(180, 320, " Silverman 4x5");

        // Dibujar botón Demi 4x8
        glColor3f(0.6f, 0.6f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(150, 200);
        glVertex2f(330, 200);
        glVertex2f(330, 250);
        glVertex2f(150, 250);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        displayText(190, 220, "      Demi");
   
        // Dibujar botón Demi contra ordenador
        glColor3f(0.6f, 0.6f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(150, 100);
        glVertex2f(330, 100);
        glVertex2f(330, 150);
        glVertex2f(150, 150);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        displayText(162, 120, "Demi vs Ordenador");

    }
    else if (tablero) {
        tablero->dibujar((tipoJuego==1)?anchoPantallaSilverman:anchoPantallaDemi, (tipoJuego == 1) ? altoPantallaSilverman : altoPantallaDemi);
        finPartida=tablero->hayMate_Ahogado();
    }
    glutSwapBuffers();
}

void inicializarJuego() {
    if (tipoJuego == 1) {
        glutInitWindowSize(anchoPantallaSilverman, altoPantallaSilverman);
        int newWindow = glutCreateWindow("Silverman 4x5");
        tablero = new TableroSilverman(false);  // Modo no Demi
        glutDestroyWindow(mainWindow);
        glutSetWindow(newWindow);
    }
    else if (tipoJuego == 2 || tipoJuego == 3) {
        glutInitWindowSize(anchoPantallaDemi, altoPantallaDemi);
        int newWindow = glutCreateWindow("Demi");
        tablero = new TableroDemi(true);
        glutDestroyWindow(mainWindow);
        glutSetWindow(newWindow);
    }

    if (tablero) {
        glutDisplayFunc(display);
        glutKeyboardFunc(handleKeypress);
        glutMouseFunc(onMouseClick);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, tipoJuego == 1 ? anchoPantallaSilverman : anchoPantallaDemi, 0.0, tipoJuego == 1 ? altoPantallaSilverman : altoPantallaDemi);
        glutPostRedisplay();

        // Si el ordenador tiene turno, realiza su primer movimiento
        if (tipoJuego == 3 && tablero->getTurno() == NEGRO) {
            jugar_contra_ordenador();
        }
    }
}

void handleKeypress(unsigned char key, int x, int y)
{
    if (tablero && tablero->getSeleccionadoX() != -1 && tablero->getSeleccionadoY() != -1)
    {
        if (coronacion)
        {
            tablero->Coronar(peonCorona, key);
            tablero->cambiarTurno();
            tablero->setSeleccionadoX(-1);
            tablero->setSeleccionadoY(-1);
            coronacion = false;
            glutPostRedisplay();

            // Si el ordenador tiene turno, realiza su movimiento despues de la coronación
            if (tipoJuego == 3 && tablero->getTurno() == NEGRO) {
                jugar_contra_ordenador();
            }
        }
    }

}
int calcularTableroY(int y, int altoPantallaSilverman, int altoPantallaDemi, int tipoJuego, int filas) {
    // Determinar el tamaño de las casillas según el tipo de juego
    float altoCasilla = tipoJuego == 1 ? static_cast<float>(altoPantallaSilverman) / filas : static_cast<float>(altoPantallaDemi) / filas;

    // Calcular la coordenada Y de la casilla
    int tableroY = static_cast<int>((tipoJuego == 1 ? altoPantallaSilverman : altoPantallaDemi) - y) / altoCasilla;

    return tableroY;
}
void onMouseClick(int button, int state, int x, int y) {
    char a = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (menuActivo) {
            // Convertir coordenadas de pantalla a coordenadas de OpenGL
            int glY = altoPantallaSilverman - y;

            // Verificar si se hizo clic en el botón Silverman 4x5
            if (x >= 150 && x <= 330 && glY >= 300 && glY <= 350) {
                tipoJuego = 1;
                menuActivo = false;
                inicializarJuego();
            }
            // Verificar si se hizo clic en el botón Demi 4x8
            else if (x >= 150 && x <= 330 && glY >= 200 && glY <= 250) {
                tipoJuego = 2;
                menuActivo = false;
                inicializarJuego();
            }
            // Verificar si se hizo clic en el botón Demi vs Ordenador
            else if (x >= 150 && x <= 330 && glY >= 100 && glY <= 150) {
                tipoJuego = 3;
                menuActivo = false;
                ordenador = true;
                inicializarJuego();
            }
        }
        else if (tablero) {
            if (ordenador && tablero->getTurno() == NEGRO) return; // Nos aseguramos de que el jugador no mueve pieza mientras que el turno es del ordenador
            int tableroX = 4*x / ((tipoJuego==1)?anchoPantallaSilverman:anchoPantallaDemi);
            int tableroY = calcularTableroY(y, altoPantallaSilverman, altoPantallaDemi, tipoJuego, (tipoJuego == 1) ? 5 : 8);

            if (tableroX < 0 || tableroX >= 4 || tableroY < 0 || (tipoJuego == 1 ? tableroY >= 5 : tableroY >= 8)) return;

            if (tablero->getSeleccionadoX() == -1 && tablero->getSeleccionadoY() == -1) {
                if (tablero->esTurnoValido(tableroY, tableroX)) {
                    tablero->seleccionarPieza(tableroY, tableroX);
                }
            }
            else {
                int seleccionadoX = tablero->getSeleccionadoX();
                int seleccionadoY = tablero->getSeleccionadoY();
                if (tablero->moverPieza(seleccionadoX, seleccionadoY, tableroY, tableroX)) {
                    peonCorona = tablero->peonCorona(coronacion);
                    if (coronacion)
                    {
                        if (tipoJuego == 2 || tipoJuego == 3)
                        {
                            while (a != 'c' && a != 'a' && a != 't')
                            {
                                std::cout << (char)168 << "A que quieres promover?: ";
                                std::cin >> a;
                                if (a != 'c' && a != 'a' && a != 't')
                                {
                                    std::cout << std::endl << "Seleccione entre Torre: t, Alfil: a, Caballo: c" << std::endl;
                                }
                                else
                                {
                                    std::cout << std::endl << "Coronacion correcta, vuelva al juego" << std::endl;
                                }
                            }
                        }
                        if (tipoJuego == 1)
                        {
                            while (a != 't' && a != 'r')
                            {
                                std::cout << (char)168 << "A que quieres promover?: ";
                                std::cin >> a;
                                if (a != 't' && a != 'r')
                                {
                                    std::cout << std::endl << "Seleccione entre Torre: t, Reina: r" << std::endl;
                                }
                                else
                                {
                                    std::cout << std::endl << "Coronacion correcta, vuelva al juego" << std::endl;
                                }
                            }
                        }
                    }
                    if (!coronacion) {
                        tablero->cambiarTurno();
                        tablero->setSeleccionadoX(-1);
                        tablero->setSeleccionadoY(-1);

                        // Si el ordenador tiene turno, realiza su movimiento después del jugador
                        if (ordenador && tablero->getTurno() == NEGRO) {
                            jugar_contra_ordenador();
                        }
                    }
                    handleKeypress(a, 0, 0);
                }
                else {
                    tablero->setSeleccionadoX(-1);
                    tablero->setSeleccionadoY(-1);
                }
            }
            glutPostRedisplay();
        }    
    }
}

void jugar_contra_ordenador()
{
    std::vector<std::pair<int, int>> piezas;

    // Recopilar piezas negras
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            Pieza* pieza = tablero->obtenerPieza(i, j);
            if (pieza && pieza->getColor() == NEGRO) {
                piezas.emplace_back(i, j);
            }
        }
    }

    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 g(rd());

    // Mezclar piezas
    std::shuffle(piezas.begin(), piezas.end(), g);

    // Intentar mover una pieza
    for (const auto& [x, y] : piezas) {
        auto movimientos = tablero->obtenerMovimientosPosibles(x, y);
        if (!movimientos.empty()) {
            std::shuffle(movimientos.begin(), movimientos.end(), g);
            auto [nuevoX, nuevoY] = movimientos.front();
            tablero->moverPieza(x, y, nuevoX, nuevoY);
            tablero->cambiarTurno();
            break;
        }
    }

    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(anchoPantallaSilverman, altoPantallaSilverman);
    mainWindow = glutCreateWindow("Ajedrez");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(onMouseClick);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, anchoPantallaSilverman, 0.0, altoPantallaSilverman);
    glutMainLoop();
    delete tablero;
    return 0;
}

