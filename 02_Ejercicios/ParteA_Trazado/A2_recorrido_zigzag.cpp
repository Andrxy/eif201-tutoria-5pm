// A2. Recorrido en zigzag
// Primero prediga la salida en papel; después compile y compruebe.
#include <iostream>
using namespace std;

int main() {
        int m[3][4] = {{1, 2, 3, 4},
                       {5, 6, 7, 8},
                       {9, 10, 11, 12}};
        for (int f = 0; f < 3; f++) {
            if (f % 2 == 0)
                for (int c = 0; c < 4; c++)
                    cout << m[f][c] << " ";
            else
                for (int c = 3; c >= 0; c--)
                    cout << m[f][c] << " ";
        }
    cout << endl;
    return 0;
}
