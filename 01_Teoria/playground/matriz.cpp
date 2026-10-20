#include <iostream>
using namespace std;

class Persona {
    public:
    string nombre;

    Persona(string nombre) : nombre(nombre) {}
};

class Matriz {
    int*** matriz;
    int filas;
    int columnas;

    public:
    Matriz(int filas, int columnas) : filas(filas), columnas(columnas) {
        matriz = new int**[filas];

        for (int f = 0; f < filas; ++f) {
            matriz[f] = new int*[columnas];

            for (int c = 0; c < columnas; ++c) {
                matriz[f][c] = nullptr;
            }
        }
    }

    void colocarEn(int fila, int col, Persona* p) {
        /* Validaciones */

        if (m[fila][col] != nullptr) {
            delete m[fila][col];
        }

        m[fila][col] = p;
    }

    Persona* obtenerEn(int fila, int col) {
        /* Validaciones */

        return m[fila][col];
    }

    bool posicionVacia(int fila, int col) {
        /* Validaciones */

        return m[fila][col] == nullptr;
    }

    int cantidadPersonasEnFila(int fila) {
        /* Validaciones */

        int noNulos = 0;
        for (int c = 0; c < columnas; ++c) {
            if (m[fila][c] != nullptr) {
                ++noNulos;
            }
        }
        
        return noNulos;
    }

    int cantidadPersonas() {
        int total = 0;

        /* V1

        for (int f = 0; f < filas; ++f) {
            for (int c = 0; c < columnas; ++c) {
                if (m[f][c] != nullptr) {
                    ++total;
                }
            }
        }
        */

        for (int f = 0; f < filas; ++f) {
            total += cantidadPersonasEnFila(f);
        }

        return total;
    }

    ~Matriz() {
        for (int f = 0; f < filas; ++f) {
            for (int c = 0; c < columnas; ++c) {
                if (!posicionVacia(f, c)) {
                    delete m[f][c];
                }
            } 

            delete[] m[f];
        }

        delete[] m;
    }

};

int main() {

    Matriz* m = new Matriz(3, 3);
    


    return 0;
}