#include <iostream>
using namespace std;

class Math {
    public:
    static int suma(int a, int b) { return a + b; }
};

int main() {
    cout << Math::suma(3, 4);

    return 0;
}