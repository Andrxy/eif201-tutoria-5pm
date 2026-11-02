// A2. Listas enlazadas: dibuje la lista después de cada operación y después compile para comprobar.
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Nodo {
private:
    int dato;
    Nodo* sig;
public:
    Nodo(int dato, Nodo* sig = nullptr) : dato(dato), sig(sig) {}
    int getDato() const { return dato; }
    void setDato(int dato) { this->dato = dato; }
    Nodo* getSig() const { return sig; }
    void setSig(Nodo* sig) { this->sig = sig; }
};

class Lista {
private:
    Nodo* primero;   // único punto de acceso a la lista
public:
    Lista();
    ~Lista();
    bool estaVacia() const;
    int cantidad() const;
    void insertarInicio(int valor);
    void insertarFinal(int valor);
    string toString() const;

    // Búsqueda
    bool existe(int valor) const;
    int posicionDe(int valor) const;

    // Eliminación
    bool eliminarInicio();
    bool eliminarFinal();
    bool eliminar(int valor);
    int eliminarTodos(int valor);

    // Sustitución
    bool sustituir(int viejo, int nuevo);
    bool sustituirEnPosicion(int pos, int nuevo);
};

Lista::Lista() : primero(nullptr) {}

bool Lista::estaVacia() const {
    return primero == nullptr;
}

int Lista::cantidad() const {
    int n = 0;
    Nodo* actual = primero;
    while (actual != nullptr) {
        n++;
        actual = actual->getSig();
    }
    return n;
}

void Lista::insertarInicio(int valor) {
    primero = new Nodo(valor, primero);
}

void Lista::insertarFinal(int valor) {
    Nodo* nuevo = new Nodo(valor);
    if (primero == nullptr) {
        primero = nuevo;
        return;
    }
    Nodo* actual = primero;
    while (actual->getSig() != nullptr)
        actual = actual->getSig();
    actual->setSig(nuevo);
}

string Lista::toString() const {
    if (primero == nullptr)
        return "(vacia)";
    stringstream s;
    Nodo* actual = primero;
    while (actual != nullptr) {
        s << actual->getDato();
        if (actual->getSig() != nullptr)
            s << " -> ";
        actual = actual->getSig();
    }
    return s.str();
}

Lista::~Lista() {
    while (primero != nullptr) {
        Nodo* borrar = primero;
        primero = primero->getSig();
        delete borrar;
    }
}

bool Lista::existe(int valor) const {
    Nodo* actual = primero;
    while (actual != nullptr) {
        if (actual->getDato() == valor)
            return true;
        actual = actual->getSig();
    }
    return false;
}

int Lista::posicionDe(int valor) const {
    Nodo* actual = primero;
    int pos = 0;
    while (actual != nullptr) {
        if (actual->getDato() == valor)
            return pos;
        actual = actual->getSig();
        pos++;
    }
    return -1;   // no se encontró
}

bool Lista::eliminarInicio() {
    if (primero == nullptr)          // lista vacía
        return false;
    Nodo* borrar = primero;          // 1. guardar el nodo
    primero = primero->getSig();     // 2. reenlazar
    delete borrar;                   // 3. liberar
    return true;
}

bool Lista::eliminarFinal() {
    if (primero == nullptr)                  // lista vacía
        return false;
    if (primero->getSig() == nullptr) {      // un solo nodo
        delete primero;
        primero = nullptr;
        return true;
    }
    Nodo* actual = primero;                  // buscar el penúltimo
    while (actual->getSig()->getSig() != nullptr)
        actual = actual->getSig();
    delete actual->getSig();
    actual->setSig(nullptr);
    return true;
}

bool Lista::eliminar(int valor) {
    Nodo* anterior = nullptr;
    Nodo* actual = primero;
    while (actual != nullptr && actual->getDato() != valor) {
        anterior = actual;
        actual = actual->getSig();
    }
    if (actual == nullptr)               // vacía o no existe
        return false;
    if (anterior == nullptr)             // era el primero
        primero = actual->getSig();
    else                                 // en medio o al final
        anterior->setSig(actual->getSig());
    delete actual;
    return true;
}

int Lista::eliminarTodos(int valor) {
    int eliminados = 0;
    // 1. Coincidencias al inicio: cambian a 'primero'
    while (primero != nullptr && primero->getDato() == valor) {
        Nodo* borrar = primero;
        primero = primero->getSig();
        delete borrar;
        eliminados++;
    }
    if (primero == nullptr)
        return eliminados;
    // 2. Resto: se revisa siempre el SIGUIENTE de 'anterior'
    Nodo* anterior = primero;
    while (anterior->getSig() != nullptr) {
        if (anterior->getSig()->getDato() == valor) {
            Nodo* borrar = anterior->getSig();
            anterior->setSig(borrar->getSig());
            delete borrar;
            eliminados++;
        } else {
            anterior = anterior->getSig();
        }
    }
    return eliminados;
}

bool Lista::sustituir(int viejo, int nuevo) {
    Nodo* actual = primero;
    while (actual != nullptr && actual->getDato() != viejo)
        actual = actual->getSig();
    if (actual == nullptr)
        return false;
    actual->setDato(nuevo);
    return true;
}

bool Lista::sustituirEnPosicion(int pos, int nuevo) {
    if (pos < 0)
        return false;
    Nodo* actual = primero;
    int i = 0;
    while (actual != nullptr && i < pos) {
        actual = actual->getSig();
        i++;
    }
    if (actual == nullptr)               // posición fuera de rango
        return false;
    actual->setDato(nuevo);
    return true;
}





int main() {
    Lista lista;
    int valores[] = {7, 3, 9, 3, 5};
    for (int v : valores)
        lista.insertarFinal(v);
    lista.insertarInicio(1);
    lista.eliminar(3);
    lista.sustituir(9, 4);
    lista.eliminarFinal();
    lista.eliminarTodos(1);
    cout << lista.toString() << endl;
    cout << lista.cantidad() << " " << lista.posicionDe(3) << endl;
    return 0;
}
