#include <iostream>
using namespace std;

class Persona {
    private:
    int edad;
    string nombre;

    public:
    Persona(int _edad, string _nombre) : edad(_edad), nombre(_nombre) {}
}


int main() {
    
    Persona array[3];

    Persona p1(10, "juan"), p2(18, "jose"), p3(20, "andrey");
    array[0] = p1;
    array[1] = p2;
    array[2] = p3;


    return 0;
}