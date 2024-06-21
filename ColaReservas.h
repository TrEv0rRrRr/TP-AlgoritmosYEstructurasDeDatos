#pragma once
#include "Reserva.h"
typedef unsigned int uint;

template<class T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo(T v, Nodo<T>* sig = NULL) {
        dato = v;
        siguiente = sig;
    }
};

template<class T>
class ColaReservas {
private:
    Nodo<T>* frente;
    Nodo<T>* fin;
    uint longitud;

public:
    ColaReservas() : frente(NULL), fin(NULL), longitud(0) {}
    ~ColaReservas();

    void encolar(T v);
    T desencolar();
    bool estaVacia() const;
    uint obtenerLongitud() const;
    T obtenerPos(uint pos) const;

    void imprimirCola(uint pagina, bool paginacion) const;
    void eliminarReserva(int id);
    T buscarReserva(int id);
    int contarElementos() const;
};

template<class T>
ColaReservas<T>::~ColaReservas() { while (!estaVacia()) desencolar(); }

template<class T>
void ColaReservas<T>::encolar(T v) {
    Nodo<T>* nuevo = new Nodo<T>(v);
    if (estaVacia()) {
        frente = fin = nuevo;
    }
    else {
        fin->siguiente = nuevo;
        fin = nuevo;
    }
    longitud++;
}

template<class T>
T ColaReservas<T>::desencolar() {
    Nodo<T>* temp = frente;
    T dato = frente->dato;
    frente = frente->siguiente;
    if (frente == NULL) {
        fin = NULL;
    }
    delete temp;
    longitud--;
    return dato;
}

template<class T>
bool ColaReservas<T>::estaVacia() const { return frente == NULL; }

template<class T>
uint ColaReservas<T>::obtenerLongitud() const { return longitud; }

template<class T>
T ColaReservas<T>::obtenerPos(uint pos) const {
    Nodo<T>* temp = frente;
    for (unsigned int i = 0; i < pos; ++i) {
        temp = temp->siguiente;
    }
    return temp->dato;
}

template<class T>
int ColaReservas<T>::contarElementos() const {
    int contador = 0;
    Nodo<T>* actual = frente;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

template<class T>
void ColaReservas<T>::imprimirCola(uint pagina, bool paginacion) const {
    system("cls");
    Nodo<T>* actual = frente;
    uint elementosPorPagina = 10;
    uint totalElementos = contarElementos();
    uint totalPaginas = (totalElementos + elementosPorPagina - 1) / elementosPorPagina;
    uint inicio = (pagina - 1) * elementosPorPagina;
    uint fin = inicio + elementosPorPagina;
    uint indice = 0;

    cout << "Lista de Reservas:\n";
    cout << "  ID\tNombre\tApellido    Num. Habitacion\tFecha de Entrada - Fecha de Salida\n";
    while (actual != nullptr && indice < fin) {
        if (indice >= inicio) {
            cout << actual->dato->getId() << "\t" << actual->dato->getNombreCliente() << "\t  " << actual->dato->getApellidoCliente() << "\t\t  " << actual->dato->getNumHabitacion() << "\t\t    " << actual->dato->getFechaInicio() << "  -  " << actual->dato->getFechaFin() << "\n\n";
        }
        actual = actual->siguiente;
        indice++;
    }

    cout << "\nPágina " << pagina << " de " << totalPaginas << "\n";

    if (paginacion) {
        cout << "Presione 'N' para la siguiente pagina, 'P' para la pagina anterior, 'M' para el menu principal.\n";

        char tecla = _getch();
        if (tecla == 'N' || tecla == 'n') {
            if (pagina < totalPaginas) imprimirCola(pagina + 1, true);
            else imprimirCola(pagina, true);
        }
        else if (tecla == 'P' || tecla == 'p') {
            if (pagina > 1) imprimirCola(pagina - 1, true);
            else imprimirCola(pagina, true);
        }
        else if (tecla == 'M' || tecla == 'm') return;
        else imprimirCola(pagina, true);
    }
}

template<class T>
void ColaReservas<T>::eliminarReserva(int id) {
    if (frente->dato->getId() == id) {
        desencolar();
        return;
    }

    Nodo<T>* temp = frente;
    Nodo<T>* anterior = NULL;
    while (temp != NULL && temp->dato->getId() != id) {
        anterior = temp;
        temp = temp->siguiente;
    }

    anterior->siguiente = temp->siguiente;
    if (temp == fin) {
        fin = anterior;
    }
    delete temp;
    longitud--;
}

template<class T>
T ColaReservas<T>::buscarReserva(int id) {
    Nodo<T>* actual = frente;
    while (actual != nullptr) {
        if (actual->dato->getId() == id) {
            return actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}