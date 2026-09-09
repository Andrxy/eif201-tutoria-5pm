#include <iostream>
using namespace std;

class A {
public:
    static int* x; 
};

int* A::x = new int(6);


int main() {
    
    cout << *(A::x) << endl;

    return 0;
}