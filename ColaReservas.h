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

    void imprimirCola() const;
    void eliminarReserva(int id);
    T buscarReserva(int id);
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
void ColaReservas<T>::imprimirCola() const {
    Nodo<T>* temp = frente;
    while (temp != NULL) {
        cout << temp->dato->toString() << endl;
        temp = temp->siguiente;
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
    Nodo<T>* temp = frente;
    while (temp != NULL) {
        if (temp->dato->getId() == id) {
            return temp->dato;
        }
        temp = temp->siguiente;
    }
}