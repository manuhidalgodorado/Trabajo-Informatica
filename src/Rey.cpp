    #include "Rey.h"
    #include <cmath>
    using namespace std;

    Rey::Rey(int _x, int _y, Color _color) : Pieza(_x, _y, _color) {}

    bool Rey::esMovimientoValido(int nuevoX, int nuevoY) {
        return (abs(nuevoX - x) <= 1 && abs(nuevoY - y) <= 1);
    }

    string Rey::obtenerNombre() const {
        return "Rey";
    }

