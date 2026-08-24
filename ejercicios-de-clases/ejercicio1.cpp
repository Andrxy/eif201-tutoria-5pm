#include <iostream>
using namespace std;

class Contador {
    public:
    static int cnt;
};

int Contador::cnt = 0;

int main() {
    Contador c1, c2;

    c1.cnt++;

    cout << c2.cnt << endl;
    cout << c1.cnt << endl; 

    return 0;
}