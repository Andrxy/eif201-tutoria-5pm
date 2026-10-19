// A5. ¿Válido o nullptr?
// Primero complete la tabla del PDF; después compile y compruebe.
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

// Clase base abstracta: toda reserva tiene un cliente y un precio.
class Reserva {
protected:
    string cedula;
    string nombre;
public:
    Reserva(string cedula, string nombre) : cedula(cedula), nombre(nombre) {}
    virtual ~Reserva() {}
    string getCedula() const { return cedula; }
    string getNombre() const { return nombre; }
    virtual double calcularPrecio() const = 0;
    virtual char getSimbolo() const = 0;     // letra para el mapa de la sala
};

class ReservaGeneral : public Reserva {
public:
    ReservaGeneral(string cedula, string nombre) : Reserva(cedula, nombre) {}
    double calcularPrecio() const override { return 3500; }
    char getSimbolo() const override { return 'G'; }
};

class ReservaEstudiante : public Reserva {
private:
    string carne;
public:
    ReservaEstudiante(string cedula, string nombre, string carne)
        : Reserva(cedula, nombre), carne(carne) {}
    string getCarne() const { return carne; }
    double calcularPrecio() const override { return 3500 * 0.6; }   // 40 % menos
    char getSimbolo() const override { return 'E'; }
};

class ReservaVIP : public Reserva {
private:
    bool combo;
public:
    ReservaVIP(string cedula, string nombre, bool combo)
        : Reserva(cedula, nombre), combo(combo) {}
    bool tieneCombo() const { return combo; }
    double calcularPrecio() const override { return 6500 + (combo ? 2500 : 0); }
    char getSimbolo() const override { return 'V'; }
};

void mostrar(int n, const void* p) {
    cout << n << ". " << (p != nullptr ? "puntero valido" : "nullptr") << endl;
}

int main() {
    Reserva* r1 = new ReservaVIP("1-1111-1111", "Ana", false);
    Reserva* r2 = new ReservaGeneral("2-2222-2222", "Luis");
    Reserva* r3 = new ReservaEstudiante("3-3333-3333", "Sofia", "B12345");
    Reserva* r4 = nullptr;

    mostrar(1, dynamic_cast<ReservaVIP*>(r1));
    mostrar(2, dynamic_cast<ReservaVIP*>(r2));
    mostrar(3, dynamic_cast<ReservaEstudiante*>(r3));
    mostrar(4, dynamic_cast<ReservaEstudiante*>(r1));
    mostrar(5, dynamic_cast<ReservaVIP*>(r4));

    // 6. Descomente la siguiente línea para ver el error de compilación:
    // r1->tieneCombo();
    cout << "6. (ver el comentario en el codigo)" << endl;

    try {
        ReservaVIP& vip = dynamic_cast<ReservaVIP&>(*r2);
        cout << "7. sin excepcion " << vip.tieneCombo() << endl;
    } catch (const bad_cast& e) {
        cout << "7. se lanzo bad_cast" << endl;
    }

    delete r1;
    delete r2;
    delete r3;
    return 0;
}
