#include "Pieza.h"
#include <freeglut.h>
#include <iostream>
#define byte my_byte //Definicion de byte para que no entre en conflicto al usar using namespace
#include "ETSIDI.h"
#undef byte

Pieza::Pieza(int _x, int _y, Color _color) : x(_x), y(_y), color(_color) {}
Pieza::Pieza(const Pieza* pieza) {
    this->x = pieza->x;
    this->y = pieza->y;
    this->color = pieza->color;
}
Pieza& Pieza::operator=(const Pieza* pieza)
{
    this->x = pieza->x;
    this->y = pieza->y;
    this->color = pieza->color;
    return *this;
}

int Pieza::getX() const { return x; }
int Pieza::getY() const { return y; }
const char* Pieza::getSonido() const { return dirSon; };
Color Pieza::getColor() const { return color; }

void Pieza::setPosicion(int nuevoX, int nuevoY) {
    x = nuevoX;
    y = nuevoY;
}
void Pieza::dibujarPieza(float anchoCasilla, float altoCasilla)
{
    glEnable(GL_TEXTURE_2D);
    GLuint textureID = ETSIDI::getTexture(dirImg).id;
    if (textureID == 0) {
        std::cerr << "Error loading texture: " << dirImg << std::endl;
        return;
    }
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    // Guardar la matriz actual
    glPushMatrix();

    // Trasladar al centro del cuadrado y aplicar la rotación
    glTranslatef(y * anchoCasilla + anchoCasilla / 1.27, x * altoCasilla + altoCasilla / 1.30, 0.0f); // Mover al centro del cuadrado
    glRotatef(180, 0.0f, 0.0f, 1.0f); // Rotar en el eje Z
    glTranslatef(-25.0f, -25.0f, 0.0f); // Mover de vuelta para dibujar el cuadrado

    // Dibujar el cuadrado con la textura aplicada
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(anchoCasilla, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(anchoCasilla, altoCasilla);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, altoCasilla);
    glEnd();

    // Restaurar la matriz original
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

