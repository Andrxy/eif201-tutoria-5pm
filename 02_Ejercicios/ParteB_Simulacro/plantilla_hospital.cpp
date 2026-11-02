#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

// ---------- Jerarquía de pacientes (dada) ----------
class Paciente {
protected:
    string cedula;
    string nombre;
    int dias;                              // días de internamiento
public:
    Paciente(string cedula, string nombre, int dias)
        : cedula(cedula), nombre(nombre), dias(dias) {}
    virtual ~Paciente() {}
    string getCedula() const { return cedula; }
    string getNombre() const { return nombre; }
    virtual double calcularCosto() const = 0;
    virtual char getSimbolo() const = 0;
};

// General: 45 000 colones por día.
class PacienteGeneral : public Paciente {
public:
    PacienteGeneral(string cedula, string nombre, int dias)
        : Paciente(cedula, nombre, dias) {}
    double calcularCosto() const override { return dias * 45000; }
    char getSimbolo() const override { return 'G'; }
};

// Urgencia: 45 000 por día más 30 000 por cada nivel de gravedad (1 a 5).
class PacienteUrgencia : public Paciente {
private:
    int nivel;
public:
    PacienteUrgencia(string cedula, string nombre, int dias, int nivel)
        : Paciente(cedula, nombre, dias), nivel(nivel) {}
    int getNivel() const { return nivel; }
    double calcularCosto() const override { return dias * 45000 + nivel * 30000; }
    char getSimbolo() const override { return 'U'; }
};

// ---------- Lista enlazada de espera (cola: entra al final, sale del inicio) ----------
class Nodo {
private:
    Paciente* info;
    Nodo* sig;
public:
    Nodo(Paciente* info) : info(info), sig(nullptr) {}
    Paciente* getInfo() const { return info; }
    Nodo* getSig() const { return sig; }
    void setSig(Nodo* sig) { this->sig = sig; }
};

class ListaEspera {
private:
    Nodo* primero;
public:
    ListaEspera();
    ~ListaEspera();
    bool estaVacia() const;
    int cantidad() const;
    void agregar(Paciente* p);           // al final
    Paciente* sacarPrimero();            // saca el nodo, NO libera al paciente
};

// ---------- Pabellón: matriz de camas más lista de espera ----------
class Pabellon {
private:
    Paciente*** camas;                   // camas[sala][cama]
    int salas;
    int camasPorSala;
    ListaEspera espera;
public:
    Pabellon(int salas, int camasPorSala);
    ~Pabellon();
    void ingresar(Paciente* p);          // a la lista de espera
    int enEspera() const;
    bool asignarCama();
    bool darDeAlta(string cedula);
    double costoTotal() const;
    int urgenciasCriticas(int nivelMinimo) const;
    string mapa() const;
};

void Pabellon::ingresar(Paciente* p) {
    espera.agregar(p);                   // Ley de Deméter: el pabellón delega
}

int Pabellon::enEspera() const {
    return espera.cantidad();
}

string Pabellon::mapa() const {
    stringstream s;
    for (int f = 0; f < salas; f++) {
        s << "Sala " << f << ":";
        for (int c = 0; c < camasPorSala; c++)
            s << " " << (camas[f][c] == nullptr ? '.' : camas[f][c]->getSimbolo());
        s << "\n";
    }
    return s.str();
}

// ===== Ejercicio 1: lista de espera =====
ListaEspera::ListaEspera() : primero(nullptr) {}

ListaEspera::~ListaEspera() {
    // Libere cada nodo y el paciente que contiene.
}

bool ListaEspera::estaVacia() const {
    return true;
}

int ListaEspera::cantidad() const {
    return 0;
}

void ListaEspera::agregar(Paciente* p) {
    // Inserte al final de la lista.
}

Paciente* ListaEspera::sacarPrimero() {
    // Saque el primer nodo y retorne su paciente SIN liberarlo; nullptr si está vacía.
    return nullptr;
}

// ===== Ejercicio 2: constructor y destructor del pabellón =====
Pabellon::Pabellon(int salas, int camasPorSala) : salas(salas), camasPorSala(camasPorSala) {
    // Cree la matriz de camas y deje todas en nullptr.
    camas = nullptr;
}

Pabellon::~Pabellon() {
    // Libere los pacientes de las camas, cada sala y el arreglo de salas.
}

// ===== Ejercicio 3: asignar cama =====
bool Pabellon::asignarCama() {
    // Pase el primer paciente en espera a la primera cama libre (recorrido por filas).
    // Si no hay espera o no hay camas libres, retorne false sin sacar a nadie.
    return false;
}

// ===== Ejercicio 4: dar de alta =====
bool Pabellon::darDeAlta(string cedula) {
    return false;
}

// ===== Ejercicio 5: costo total (polimorfismo) =====
double Pabellon::costoTotal() const {
    return 0;
}

// ===== Ejercicio 6: urgencias críticas (dynamic_cast) =====
int Pabellon::urgenciasCriticas(int nivelMinimo) const {
    return 0;
}

int main() {
    cout << fixed << setprecision(0) << boolalpha;
    Pabellon pabellon(2, 3);
    pabellon.ingresar(new PacienteGeneral("1-1111-1111", "Ana", 3));
    pabellon.ingresar(new PacienteUrgencia("2-2222-2222", "Luis", 2, 4));
    pabellon.ingresar(new PacienteUrgencia("3-3333-3333", "Sofia", 5, 2));
    pabellon.ingresar(new PacienteGeneral("4-4444-4444", "Pedro", 1));
    pabellon.ingresar(new PacienteUrgencia("5-5555-5555", "Marta", 4, 5));
    pabellon.ingresar(new PacienteGeneral("6-6666-6666", "Carlos", 2));
    pabellon.ingresar(new PacienteGeneral("7-7777-7777", "Elena", 6));
    cout << "En espera: " << pabellon.enEspera() << endl;

    int asignados = 0;
    while (pabellon.asignarCama())
        asignados++;
    cout << "Asignados: " << asignados << endl;
    cout << "En espera: " << pabellon.enEspera() << endl;
    cout << pabellon.mapa();
    cout << "Costo total: " << pabellon.costoTotal() << endl;
    cout << "Urgencias con nivel 4 o mas: " << pabellon.urgenciasCriticas(4) << endl;

    cout << "Alta de Luis: " << pabellon.darDeAlta("2-2222-2222") << endl;
    cout << "Alta de alguien inexistente: " << pabellon.darDeAlta("9-9999-9999") << endl;
    cout << "Asignar cama: " << pabellon.asignarCama() << endl;
    cout << "Asignar cama sin espera: " << pabellon.asignarCama() << endl;
    cout << pabellon.mapa();
    cout << "Costo total: " << pabellon.costoTotal() << endl;
    cout << "Urgencias con nivel 4 o mas: " << pabellon.urgenciasCriticas(4) << endl;
    return 0;
}
