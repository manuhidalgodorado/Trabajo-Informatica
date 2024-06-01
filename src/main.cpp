#include <iostream>
#include <freeglut.h>
#include "TableroSilverman.h"
#include "TableroDemi.h"
#include "Windows.h"

void display();
void displayText(float x, float y, const char* text);

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
