// A3. Diagonales
// Primero prediga la salida en papel; después compile y compruebe.
#include <iostream>
using namespace std;

int main() {
        int m[4][4] = {{1, 2, 3, 4},
                       {5, 6, 7, 8},
                       {9, 10, 11, 12},
                       {13, 14, 15, 16}};
        int principal = 0, secundaria = 0;
        for (int i = 0; i < 4; i++) {
            principal += m[i][i];
            secundaria += m[i][3 - i];
        }
        cout << principal << " " << secundaria;
    cout << endl;
    return 0;
}
