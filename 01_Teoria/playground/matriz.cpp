#include <iostream>
using namespace std;

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
};

int main() {

    Matriz* m = new Matriz(3, 3);
    


    return 0;
}