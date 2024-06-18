#pragma once
#include "Reserva.h"
typedef unsigned int uint;
template<typename T, T NADA = 0>
class ListaReservas {
private:
    struct Nodo;
    uint longitud;
    Nodo* ini;

public:
    ListaReservas() : ini(nullptr), longitud(0) {}
    ~ListaReservas();

    uint getLongitud();
    bool isEmpty();
    void agregarReserva(T elem);
    T buscarReserva(int idReserva);
    void eliminarReserva(int idReserva);
    T obtenerPos(uint pos);
    void agregarEnPosicion(T elem, uint pos);
    void agregaReservaAlFinal(T elem);
    void vaciar();
};

template <typename T, T NADA>
struct ListaReservas<T, NADA>::Nodo {
    T elem;
    Nodo* sig;
    Nodo(T elem = NADA, Nodo* sig = nullptr) : elem(elem), sig(sig) {}
};

template <typename T, T NADA>
ListaReservas<T, NADA>::~ListaReservas() {
    Nodo* aux = ini;
    while (aux != nullptr) {
        aux = ini;
        ini = ini->sig;
        delete aux;
    }
}

template <typename T, T NADA>
uint ListaReservas<T, NADA>::getLongitud() { return longitud; }

template <typename T, T NADA>
bool ListaReservas<T, NADA>::isEmpty() { return longitud == 0; }

template <typename T, T NADA>
void ListaReservas<T, NADA>::agregarReserva(T elem) {
    Nodo* nuevoNodo = new Nodo(elem, ini);
    if (nuevoNodo != nullptr) {
        ini = nuevoNodo;
        longitud++;
    }
}

template <typename T, T NADA>
T ListaReservas<T, NADA>::buscarReserva(int idReserva) {
    Nodo* aux = ini;
    while (aux != nullptr) {
        if (aux->elem->getId() == idReserva) {
            return aux->elem;
        }
        aux = aux->sig;
    }
    return nullptr;
}

template <typename T, T NADA>
void ListaReservas<T, NADA>::eliminarReserva(int idReserva) {
    Nodo* actual = ini;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->elem->getId() == idReserva) {
            if (anterior != nullptr) {
                anterior->sig = actual->sig;
            }
            else {
                ini = actual->sig;
            }
            delete actual;
            longitud--;
            return;
        }
        anterior = actual;
        actual = actual->sig;
    }
}

template <typename T, T NADA>
T ListaReservas<T, NADA>::obtenerPos(uint pos) {
    if (pos >= 0 && pos < longitud) {
        Nodo* aux = ini;
        for (int i = 0; i < pos; i++) {
            aux = aux->sig;
        }
        return aux->elem;
    }
    else {
        return NADA;
    }
}

template <typename T, T NADA>
void ListaReservas<T, NADA>::agregarEnPosicion(T elem, uint pos) {
    if (pos > longitud) return;
    if (pos == 0) {
        agregarReserva(elem);
    }
    else {
        Nodo* aux = ini;
        for (int i = 1; i < pos; i++) {
            aux = aux->sig;
        }
        Nodo* nuevo = new Nodo(elem, aux->sig);
        if (nuevo != nullptr) {
            aux->sig = nuevo;
            longitud++;
        }
    }
}

template <typename T, T NADA>
void ListaReservas<T, NADA>::agregaReservaAlFinal(T elem) { agregarEnPosicion(elem, longitud); }

template<typename T, T NADA>
void ListaReservas<T, NADA>::vaciar() {
    Nodo* aux;
    while (ini != nullptr) {
        aux = ini;
        ini = ini->sig;
        delete aux;
    }
    longitud = 0;
}