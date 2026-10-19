// A4. ¿Qué parte de la matriz se suma?
// Primero prediga la salida en papel; después compile y compruebe.
#include <iostream>
using namespace std;

int main() {
        int m[4][4] = {{1, 2, 3, 4},
                       {5, 6, 7, 8},
                       {9, 10, 11, 12},
                       {13, 14, 15, 16}};
        int suma = 0;
        for (int f = 0; f < 4; f++)
            for (int c = f + 1; c < 4; c++)
                suma += m[f][c];
        cout << suma;
    cout << endl;
    return 0;
}
