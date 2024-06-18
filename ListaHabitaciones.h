#pragma once
#include "Habitacion.h"

typedef unsigned int uint;
template<typename T, T NADA = 0>
class ListaHabitaciones {
private:
    struct Nodo;
    uint longitud;
    Nodo* ini;

public:
    ListaHabitaciones() : ini(nullptr), longitud(0) {}
    ~ListaHabitaciones();

    uint getLongitud();
    bool isEmpty();
    void agregarHabitacion(T elem);
    T buscarHabitacion(int numHabitacion);
    void eliminarHabitacion(int numHabitacion);
    T obtenerPos(uint pos);
    void intercambiar(uint pos1, uint pos2);
};

template <typename T, T NADA>
struct ListaHabitaciones<T, NADA>::Nodo {
    T elem;
    Nodo* sig;
    Nodo(T elem = NADA, Nodo* sig = nullptr) : elem(elem), sig(sig) {}
};

template <typename T, T NADA>
ListaHabitaciones<T, NADA>::~ListaHabitaciones() {
    Nodo* aux = ini;
    while (aux != nullptr) {
        aux = ini;
        ini = ini->sig;
        delete aux;
    }
}

template <typename T, T NADA>
uint ListaHabitaciones<T, NADA>::getLongitud() { return longitud; }

template <typename T, T NADA>
bool ListaHabitaciones<T, NADA>::isEmpty() { return longitud == 0; }

template <typename T, T NADA>
void ListaHabitaciones<T, NADA>::agregarHabitacion(T elem) {
    Nodo* nuevoNodo = new Nodo(elem, ini);
    if (nuevoNodo != nullptr) {
        ini = nuevoNodo;
        longitud++;
    }
}

template <typename T, T NADA>
T ListaHabitaciones<T, NADA>::buscarHabitacion(int numHabitacion) {
    Nodo* aux = ini;
    while (aux != nullptr) {
        if (aux->elem->getNumHab() == numHabitacion) {
            return aux->elem;
        }
        aux = aux->sig;
    }
    return nullptr;
}

template <typename T, T NADA>
void ListaHabitaciones<T, NADA>::eliminarHabitacion(int numHabitacion) {
    Nodo* actual = ini;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->elem->getNumHab() == numHabitacion) {
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
T ListaHabitaciones<T, NADA>::obtenerPos(uint pos) {
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

template<typename T, T NADA>
void ListaHabitaciones<T, NADA>::intercambiar(uint pos1, uint pos2) {
    if (pos1 >= longitud || pos2 >= longitud) {
        return; // Posiciones fuera de rango
    }

    Nodo* nodo1 = ini;
    Nodo* nodo2 = ini;
    for (uint i = 0; i < pos1; ++i) {
        nodo1 = nodo1->sig;
    }
    for (uint i = 0; i < pos2; ++i) {
        nodo2 = nodo2->sig;
    }

    T temp = nodo1->elem;
    nodo1->elem = nodo2->elem;
    nodo2->elem = temp;
}

