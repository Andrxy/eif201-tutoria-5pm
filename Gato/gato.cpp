#include <iostream>
using namespace std;

class Simbolo {
    public:
    virtual char getSimbolo() = 0;
};

class SimboloX : public Simbolo {
    char getSimbolo() {
        return 'X';
    }
};

class SimboloO : public Simbolo {
    char getSimbolo() {
        return 'O';
    }
};


class Matriz {
    protected:
    Simbolo*** matriz;
    int filas;
    int columnas;

    public:
    Matriz(int _filas, int _columnas) : filas(_filas), columnas(_columnas) {
        matriz = new Simbolo**[filas];

        for (int i = 0; i < filas; ++i) {
            matriz[i] = new Simbolo*[columnas];
            for (int j = 0; j < columnas; ++j) {
                matriz[i][j] = nullptr;
            }
        }
    }

    ~Matriz() {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                delete matriz[i][j];
            }
            delete[] matriz[i];
        }

        delete[] matriz;
    }
};

class MatrizGato : public Matriz {
    public:
    MatrizGato() : Matriz(3, 3) {}

    void mostrar() {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                if (matriz[i][j] != nullptr) {
                    cout << matriz[i][j]->getSimbolo() << ' ';
                }
                else {
                    cout << "  ";
                }

                if (j + 1 != columnas) cout << " | ";
            }

            if (i + 1 != filas) cout << "\n-------------\n";
        }
    }

    bool setPosicion(int f, int c, Simbolo* s) {
        // validaciones
        if (matriz[f][c] != nullptr) return false;
        
        matriz[f][c] = s;

        return true;
    }

    Simbolo* verificarGanador() {
        return nullptr;
    }
};

class Juego {
    private:
    MatrizGato* m;
public:
    Juego() {
        m = new MatrizGato();
    }

    ~Juego() {
        delete m;
    }

    void empezar() {
        int contador = 0;

        while (true) {
            Simbolo* ganador = m->verificarGanador();
            if (ganador != nullptr) {
                cout << "El ganador fue " << ganador->getSimbolo();
                break;
            }

            m->mostrar();

            if (contador % 2 == 0) {
                cout << "\nTurno de X, elija una posicion (fila, columna): ";
            }
            else {
                cout << "\nTurno de O, elija una posicion (fila, columna): ";
            }

            int fila, columna; 
            cout << "\nfila: "; cin >> fila;
            cout << "\ncolumna: "; cin >> columna;

            if (contador % 2 == 0) m->setPosicion(fila, columna, new SimboloX());
            else m->setPosicion(fila, columna, new SimboloO());

            ++contador;

        }
    }

};

int main() {

    Juego* partida = new Juego();

    partida->empezar();

    delete partida;

    return 0;
}