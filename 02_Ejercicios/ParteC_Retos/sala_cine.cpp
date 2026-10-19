#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
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

class SalaCine {
private:
    Reserva*** asientos;     // matriz dinámica de punteros a Reserva
    int filas;
    int columnas;
public:
    SalaCine(int filas, int columnas);
    ~SalaCine();
    bool posicionValida(int f, int c) const;
    bool reservar(int f, int c, Reserva* r);
    bool cancelar(int f, int c);
    int libresEnFila(int f) const;
    int ocupadosEnColumna(int c) const;
    int filaMasOcupada() const;
    bool buscarPorCedula(string cedula, int& f, int& c) const;
    bool mover(int f1, int c1, int f2, int c2);
    double recaudacion() const;
    int contarVIPConCombo() const;
    int estudiantesEnFila(int f) const;
    string mapa() const;
};

SalaCine::SalaCine(int filas, int columnas) : filas(filas), columnas(columnas) {
    asientos = new Reserva**[filas];              // 1. arreglo de filas
    for (int f = 0; f < filas; f++) {
        asientos[f] = new Reserva*[columnas];     // 2. cada fila
        for (int c = 0; c < columnas; c++)
            asientos[f][c] = nullptr;             // 3. asiento libre
    }
}

SalaCine::~SalaCine() {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++)
            delete asientos[f][c];                // 1. objetos
        delete[] asientos[f];                     // 2. cada fila
    }
    delete[] asientos;                            // 3. arreglo de filas
}

bool SalaCine::posicionValida(int f, int c) const {
    return f >= 0 && f < filas && c >= 0 && c < columnas;
}

// Si retorna false, la reserva NO quedó en la sala: quien llama debe liberarla.
bool SalaCine::reservar(int f, int c, Reserva* r) {
    if (!posicionValida(f, c) || asientos[f][c] != nullptr)
        return false;
    asientos[f][c] = r;
    return true;
}

bool SalaCine::cancelar(int f, int c) {
    if (!posicionValida(f, c) || asientos[f][c] == nullptr)
        return false;
    delete asientos[f][c];
    asientos[f][c] = nullptr;                     // el asiento vuelve a estar libre
    return true;
}

int SalaCine::libresEnFila(int f) const {
    if (f < 0 || f >= filas)
        return -1;
    int libres = 0;
    for (int c = 0; c < columnas; c++)            // fila fija, se mueve la columna
        if (asientos[f][c] == nullptr)
            libres++;
    return libres;
}

int SalaCine::ocupadosEnColumna(int c) const {
    if (c < 0 || c >= columnas)
        return -1;
    int ocupados = 0;
    for (int f = 0; f < filas; f++)               // columna fija, se mueve la fila
        if (asientos[f][c] != nullptr)
            ocupados++;
    return ocupados;
}

int SalaCine::filaMasOcupada() const {
    int mejor = -1, maximo = 0;
    for (int f = 0; f < filas; f++) {
        int ocupados = columnas - libresEnFila(f);
        if (ocupados > maximo) {
            maximo = ocupados;
            mejor = f;
        }
    }
    return mejor;                                 // -1 si la sala está vacía
}

bool SalaCine::buscarPorCedula(string cedula, int& f, int& c) const {
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            if (asientos[i][j] != nullptr && asientos[i][j]->getCedula() == cedula) {
                f = i;                            // se "retorna" la posición
                c = j;                            // por medio de las referencias
                return true;
            }
    return false;
}

bool SalaCine::mover(int f1, int c1, int f2, int c2) {
    if (!posicionValida(f1, c1) || !posicionValida(f2, c2))
        return false;
    if (asientos[f1][c1] == nullptr || asientos[f2][c2] != nullptr)
        return false;
    asientos[f2][c2] = asientos[f1][c1];          // se mueve el puntero, no el objeto
    asientos[f1][c1] = nullptr;
    return true;
}

double SalaCine::recaudacion() const {
    double total = 0;
    for (int f = 0; f < filas; f++)
        for (int c = 0; c < columnas; c++)
            if (asientos[f][c] != nullptr)
                total += asientos[f][c]->calcularPrecio();   // enlace dinámico
    return total;
}

int SalaCine::contarVIPConCombo() const {
    int n = 0;
    for (int f = 0; f < filas; f++)
        for (int c = 0; c < columnas; c++) {
            ReservaVIP* v = dynamic_cast<ReservaVIP*>(asientos[f][c]);
            if (v != nullptr && v->tieneCombo())
                n++;
        }
    return n;
}

int SalaCine::estudiantesEnFila(int f) const {
    if (f < 0 || f >= filas)
        return -1;
    int n = 0;
    for (int c = 0; c < columnas; c++)
        if (dynamic_cast<ReservaEstudiante*>(asientos[f][c]) != nullptr)
            n++;
    return n;
}

string SalaCine::mapa() const {
    stringstream s;
    for (int f = 0; f < filas; f++) {
        s << "Fila " << f << ":";
        for (int c = 0; c < columnas; c++)
            s << " " << (asientos[f][c] == nullptr ? '.' : asientos[f][c]->getSimbolo());
        s << "\n";
    }
    return s.str();
}




int main() {
    cout << fixed << setprecision(0) << boolalpha;
    SalaCine sala(4, 6);
    sala.reservar(0, 1, new ReservaGeneral("1-1111-1111", "Ana"));
    sala.reservar(0, 2, new ReservaEstudiante("2-2222-2222", "Luis", "B12345"));
    sala.reservar(0, 3, new ReservaEstudiante("3-3333-3333", "Sofia", "B23456"));
    sala.reservar(1, 4, new ReservaVIP("4-4444-4444", "Marta", true));
    sala.reservar(2, 0, new ReservaVIP("5-5555-5555", "Pedro", false));
    sala.reservar(2, 5, new ReservaGeneral("6-6666-6666", "Carlos"));
    sala.reservar(3, 2, new ReservaVIP("7-7777-7777", "Elena", true));
    cout << sala.mapa();

    Reserva* r = new ReservaGeneral("8-8888-8888", "Jose");
    bool ok = sala.reservar(0, 2, r);              // asiento ocupado
    cout << "Reservar (0,2) ocupado: " << ok << endl;
    if (!ok)
        delete r;
    r = new ReservaGeneral("8-8888-8888", "Jose");
    ok = sala.reservar(9, 9, r);                   // fuera de rango
    cout << "Reservar (9,9) invalido: " << ok << endl;
    if (!ok)
        delete r;

    cout << "Libres en fila 0: " << sala.libresEnFila(0) << endl;
    cout << "Ocupados en columna 2: " << sala.ocupadosEnColumna(2) << endl;
    cout << "Fila mas ocupada: " << sala.filaMasOcupada() << endl;
    cout << "Recaudacion: " << sala.recaudacion() << endl;
    cout << "VIP con combo: " << sala.contarVIPConCombo() << endl;
    cout << "Estudiantes en fila 0: " << sala.estudiantesEnFila(0) << endl;

    int f, c;
    if (sala.buscarPorCedula("5-5555-5555", f, c))
        cout << "Pedro esta en (" << f << "," << c << ")" << endl;
    cout << "Mover (2,0) a (3,5): " << sala.mover(2, 0, 3, 5) << endl;
    cout << "Cancelar (0,1): " << sala.cancelar(0, 1) << endl;
    cout << "Cancelar (0,1) otra vez: " << sala.cancelar(0, 1) << endl;
    cout << sala.mapa();
    cout << "Recaudacion: " << sala.recaudacion() << endl;
    return 0;
}
