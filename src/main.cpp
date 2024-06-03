#include <iostream>
#include <freeglut.h>
#include "TableroSilverman.h"
#include "TableroDemi.h"
#include "Windows.h"

void display();
void inicializarJuego();
void displayText(float x, float y, const char* text);
void onMouseClick(int button, int state, int x, int y);




void displayText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
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
    }
    
    glutSwapBuffers();
}

void inicializarJuego() {
    if (tipoJuego == 1) {
        glutInitWindowSize(480, 600);
        int newWindow = glutCreateWindow("Silverman 4x5");
        tablero = new TableroSilverman(false);  // Modo no Demi
        glutDestroyWindow(mainWindow);
        glutSetWindow(newWindow);
    }
    else if (tipoJuego == 2) {
        glutInitWindowSize(480, 960);
        int newWindow = glutCreateWindow("Demi");
        tablero = new TableroDemi(true);  // Modo Demi
        glutDestroyWindow(mainWindow);
        glutSetWindow(newWindow);
    }
    
    if (tablero) {
        glutDisplayFunc(display);
        glutMouseFunc(onMouseClick);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 480.0, 0.0, tipoJuego == 1 ? 600.0 : 960.0);
        glutPostRedisplay();
    }
    
}

void onMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (menuActivo) {
            // Convertir coordenadas de pantalla a coordenadas de OpenGL
            int glY = 600 - y;

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
        }
        else if (tablero) {
            int tableroX = x / 120;
            int tableroY = ((tipoJuego == 1 ? 610 : 865) - y) / 110;

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
                    tablero->setSeleccionadoX(-1);
                    tablero->setSeleccionadoY(-1);
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


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(480, 600);
    mainWindow = glutCreateWindow("Ajedrez");
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 480.0, 0.0, 600.0);
    glutMainLoop();
    delete tablero;
    return 0;
}
