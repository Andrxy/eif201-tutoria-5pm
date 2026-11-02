// A1. Polimorfismo: prediga la salida en papel y después compile para comprobar.
#include <iostream>
#include <string>
using namespace std;

class Figura {
public:
    virtual string nombre() const { return "Figura"; }
    string tipo() const { return "generica"; }          // NO virtual
    virtual double area() const = 0;
    virtual ~Figura() {}
};

class Rectangulo : public Figura {
protected:
    double base, altura;
public:
    Rectangulo(double b, double h) : base(b), altura(h) {}
    string nombre() const override { return "Rectangulo"; }
    string tipo() const { return "rect"; }              // oculta, no sobrescribe
    double area() const override { return base * altura; }
};

class Cuadrado : public Rectangulo {
public:
    Cuadrado(double lado) : Rectangulo(lado, lado) {}
    string nombre() const override { return "Cuadrado"; }
};

int main() {
    Figura* f = new Cuadrado(3);
    Rectangulo* r = new Rectangulo(2, 5);
    Rectangulo* q = new Cuadrado(4);
    cout << f->nombre() << " " << f->tipo() << " " << f->area() << endl;   // 1
    cout << r->nombre() << " " << r->tipo() << " " << r->area() << endl;   // 2
    cout << q->nombre() << " " << q->tipo() << " " << q->area() << endl;   // 3
    cout << (dynamic_cast<Cuadrado*>(r) != nullptr) << " "
         << (dynamic_cast<Rectangulo*>(f) != nullptr) << endl;             // 4
    delete f;
    delete r;
    delete q;
    return 0;
}
