#include <iostream>
using namespace std;

class A {
public:
    int* x;

    A(int* _x) : x(_x) {}
};


int main() {
    int b = 5;

    A a1(&b), a2(&b);

    ++(*(a1.x));

    cout << *(a2.x) << ' ' << *(a1.x);

    return 0;
}