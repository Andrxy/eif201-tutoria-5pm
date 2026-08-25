#include <iostream>
using namespace std;

enum Estados {
    OCUPADO,     // 0
    EN_MANTENIMIENTO,    // 1
    LIBRE,     // 2
};

template <T>
class Coleccion<T> {
    T** v;
    int tamanio;
    int capacidad;

    public: 
    Coleccion(int _capacidad) : capacidad(_capacidad), tamanio(0) {
        v = new T*[capacidad];

        for (int i = 0; i < capacidad; ++i) {
            v[i] = nullptr;
        }
    }

    bool estaOcupado(int horaInicio, int horaFinal) const {
        
        while () {...}

        return true;
    }

    bool apartarCancha(int horaInicio, int horaFinal) const {
        // implementacion
    }

    ~Coleccion() {
        // liberar memoria

        for (int i = 0; i < capacidad; ++i) {
            delete v[i];
        }

        delete[] v;
    }
};

class Horario {
    private:
    string fecha;
    Coleccion* horario; // se guardan estados

    public:

    Horario() {
        horario = new Coleccion();
    }

    bool estaOcupado(int horaInicio, int horaFinal) const {
        return horarios->estaOcupado(horaInicio, horaFinal);
    }

    bool apartarCancha(int horaInicio, int horaFinal) {
        return horarios->apartarCancha(horaInicio, horaFinal);
    }

    ~Horario() {
        delete horario,
    }
};


int main() {
    


    return 0;
}