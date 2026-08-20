#include <iostream>
#include <string>

using namespace std;

class Persona {
private:
    string nombre;

public:
    Persona(string n) : nombre(n) {
        cout << "instanciado persona" << endl;
    }

    string getNombre() { return nombre; }

    string toString() {
        return "Persona{ " + nombre + " }";
    }

    ~Persona() {
        cout << "destruyendo a " << nombre << endl;
    }
};

class Coleccion {
private:
    int capacidad; 
    int tamanio;    
    Persona** v; 

public:
    Coleccion(int _capacidad) : capacidad(_capacidad), tamanio(0) {
        cout << "instanciando coleccion" << endl;
        
        v = new Persona*[capacidad];

        for (int i = 0; i < capacidad; ++i) {
            v[i] = nullptr;
        }        
    }

    void mostrarColeccion() {
        for (int i = 0; i < capacidad; ++i) {
            if (v[i] != nullptr) {
                cout << "valor en la pos #" << i << ": " << v[i]->toString() << endl;
            } else {
                cout << "posicion nullptr" << endl;
            }
        }
    }

    ~Coleccion() {
        cout << "eliminando coleccion" << endl;

        for (int i = 0; i < capacidad; ++i) {
            if (v[i] != nullptr) {
                cout << "Se elimino a " << v[i]->getNombre() << endl; 
                delete v[i];
            }
        }

        delete[] v;
    }

    void setPosicion(Persona* p, int index) {
        if (v[index] != nullptr) {
            delete v[index];
        }
        
        v[index] = p;
    }
};

int main() {
    Coleccion* c = new Coleccion(5); 

    Persona* p1 = new Persona("Juan"); 
    c->setPosicion(p1, 0);

    delete c; 

    return 0;
}