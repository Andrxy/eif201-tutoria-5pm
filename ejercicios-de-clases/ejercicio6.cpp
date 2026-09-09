#include <iostream>
using namespace std;

class Persona {
    private:
    int edad;

    public:

    Persona(int _edad) : edad(_edad) {}

    int getEdad() const {
        // ERROR
        // edad = 8;

        return edad;
    }

    int obtenerEdad() {
        return edad;
    }
};

int main() {
    const int x = 6;

    // ERROR, read-only
    // x = x + 1;

    // ERROR, No inicializada
    // const int y;

    Persona p1(10);
    cout << p1.getEdad() << endl;


    // excepcion
    const Persona p2(20);
    // cout << p2.obtenerEdad();
    cout << p2.getEdad();


    return 0;
}