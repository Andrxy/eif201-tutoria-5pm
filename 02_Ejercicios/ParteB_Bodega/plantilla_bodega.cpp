#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

class Producto {
protected:
    string codigo;
    string nombre;
    int cantidad;
    double precio;                         // precio unitario
public:
    Producto(string codigo, string nombre, int cantidad, double precio)
        : codigo(codigo), nombre(nombre), cantidad(cantidad), precio(precio) {}
    virtual ~Producto() {}
    string getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    virtual double valorInventario() const = 0;
    virtual char getSimbolo() const = 0;
};

// Perecedero: si vence en 3 días o menos se liquida a mitad de precio;
// si ya venció (días <= 0) no tiene valor.
class ProductoPerecedero : public Producto {
private:
    int diasParaVencer;
public:
    ProductoPerecedero(string codigo, string nombre, int cantidad, double precio, int dias)
        : Producto(codigo, nombre, cantidad, precio), diasParaVencer(dias) {}
    int getDiasParaVencer() const { return diasParaVencer; }
    bool estaVencido() const { return diasParaVencer <= 0; }
    double valorInventario() const override {
        if (estaVencido())
            return 0;
        double valor = cantidad * precio;
        return diasParaVencer <= 3 ? valor * 0.5 : valor;
    }
    char getSimbolo() const override { return 'P'; }
};

class ProductoElectronico : public Producto {
private:
    int mesesGarantia;
public:
    ProductoElectronico(string codigo, string nombre, int cantidad, double precio, int meses)
        : Producto(codigo, nombre, cantidad, precio), mesesGarantia(meses) {}
    int getMesesGarantia() const { return mesesGarantia; }
    double valorInventario() const override { return cantidad * precio; }
    char getSimbolo() const override { return 'E'; }
};

class Bodega {
private:
    Producto*** estantes;        // estantes[fila][columna]
    int filas;                   // cantidad de estantes
    int columnas;                // espacios por estante
public:
    Bodega(int filas, int columnas);
    ~Bodega();
    bool posicionValida(int f, int c) const;
    bool ubicar(int f, int c, Producto* p);
    bool retirar(int f, int c);
    bool buscarPorCodigo(string codigo, int& f, int& c) const;
    double valorTotal() const;
    int estanteMasLleno() const;
    bool mover(int f1, int c1, int f2, int c2);
    int contarPorVencer(int dias) const;
    int retirarVencidos();
    string mapa() const;
};

string Bodega::mapa() const {
    stringstream s;
    for (int f = 0; f < filas; f++) {
        s << "Estante " << f << ":";
        for (int c = 0; c < columnas; c++)
            s << " " << (estantes[f][c] == nullptr ? '.' : estantes[f][c]->getSimbolo());
        s << "\n";
    }
    return s.str();
}

// ===== B1: constructor y destructor =====
Bodega::Bodega(int filas, int columnas) : filas(filas), columnas(columnas) {
    // Cree el arreglo de estantes, cada estante y deje todos los espacios en nullptr.
    estantes = nullptr;
}

Bodega::~Bodega() {
    // Libere los productos, luego cada estante y al final el arreglo de estantes.
}

// ===== B2: validar, ubicar y retirar =====
bool Bodega::posicionValida(int f, int c) const {
    return false;
}

bool Bodega::ubicar(int f, int c, Producto* p) {
    // false si la posición no es válida o está ocupada.
    return false;
}

bool Bodega::retirar(int f, int c) {
    // Libera el producto y deja el espacio en nullptr.
    return false;
}

// ===== B3: búsqueda con posición por referencia =====
bool Bodega::buscarPorCodigo(string codigo, int& f, int& c) const {
    // Si lo encuentra, deja la posición en f y c y retorna true.
    return false;
}

// ===== B4: recorridos =====
double Bodega::valorTotal() const {
    // Suma valorInventario() de cada producto (polimorfismo).
    return 0;
}

int Bodega::estanteMasLleno() const {
    // Estante (fila) con más espacios ocupados; -1 si la bodega está vacía.
    return -1;
}

// ===== B5: mover sin crear ni liberar =====
bool Bodega::mover(int f1, int c1, int f2, int c2) {
    // Origen ocupado, destino libre y ambas posiciones válidas.
    return false;
}

// ===== B6: downcasting =====
int Bodega::contarPorVencer(int dias) const {
    // Perecederos NO vencidos que vencen en 'dias' días o menos.
    return 0;
}

int Bodega::retirarVencidos() {
    // Libera los perecederos vencidos y retorna cuántos retiró.
    return 0;
}

int main() {
    cout << fixed << setprecision(0) << boolalpha;
    Bodega bodega(3, 4);
    bodega.ubicar(0, 0, new ProductoPerecedero("P01", "Leche", 20, 950, 10));
    bodega.ubicar(0, 1, new ProductoPerecedero("P02", "Yogur", 15, 700, 2));
    bodega.ubicar(1, 2, new ProductoElectronico("E01", "Audifonos", 5, 12000, 12));
    bodega.ubicar(2, 3, new ProductoPerecedero("P03", "Queso", 8, 3200, 0));
    bodega.ubicar(1, 0, new ProductoElectronico("E02", "Cargador", 10, 4500, 6));
    bodega.ubicar(0, 3, new ProductoPerecedero("P04", "Pan", 30, 500, 1));
    cout << bodega.mapa();

    Producto* extra = new ProductoElectronico("E03", "Cable", 40, 1500, 3);
    cout << "Ubicar en (0,0) ocupado: " << bodega.ubicar(0, 0, extra) << endl;
    cout << "Ubicar en (5,1) invalido: " << bodega.ubicar(5, 1, extra) << endl;
    delete extra;                          // no quedo en la bodega

    cout << "Valor total: " << bodega.valorTotal() << endl;
    cout << "Estante mas lleno: " << bodega.estanteMasLleno() << endl;
    int f = -1, c = -1;
    bool ok = bodega.buscarPorCodigo("E01", f, c);
    cout << "Buscar E01: " << ok << " en (" << f << "," << c << ")" << endl;
    cout << "Buscar X99: " << bodega.buscarPorCodigo("X99", f, c) << endl;
    cout << "Por vencer en 3 dias o menos: " << bodega.contarPorVencer(3) << endl;
    cout << "Vencidos retirados: " << bodega.retirarVencidos() << endl;
    cout << "Mover (1,2) a (2,0): " << bodega.mover(1, 2, 2, 0) << endl;
    cout << "Mover (2,0) a (0,0): " << bodega.mover(2, 0, 0, 0) << endl;
    cout << "Retirar (1,0): " << bodega.retirar(1, 0) << endl;
    cout << "Retirar (1,0) otra vez: " << bodega.retirar(1, 0) << endl;
    cout << bodega.mapa();
    cout << "Valor total: " << bodega.valorTotal() << endl;
    return 0;
}
