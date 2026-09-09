#include <iostream>
using namespace std;

int main() {
    int num = 5;

    /*
    *: es un puntero, guarda una direccion de memoria

    &: obteniendo la direccion de memoria
     */
    int* x = &num; 

    cout << "Contenido de x: " << x << endl;

    // *: desreferenciacion
    cout << "Desreferencio x: " << *x << endl;

    // &: alias/apodo
    int& y = num;
    
    ++y;

    cout << "contenido de y: " << y << endl;
    cout << "desreferenciar x: " << *x << endl;


    return 0;
}