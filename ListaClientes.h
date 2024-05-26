#pragma once
#include "Cliente.h"

typedef unsigned int uint;
template<typename T, T NADA = 0>
class ListaClientes
{
private:
    struct Nodo;
    uint longitud;
    Nodo* ini;

public:
    ListaClientes() : ini(nullptr), longitud(0) {}
	~ListaClientes();

    uint getLongitud();
    bool isEmpty();
    void agregarCliente(T elem);
    T buscarCliente(string nombre);
    void eliminarCliente(string nombre);
    T obtenerPos(uint pos);
    void agregarEnPosicion(T elem, uint pos);
    void agregaClienteAlFinal(T elem);
};

template <typename T, T NADA>
struct ListaClientes<T, NADA>::Nodo {
    T elem;
    Nodo* sig;
    Nodo(T elem = NADA, Nodo* sig = nullptr) : elem(elem), sig(sig) {}
};

template <typename T, T NADA>
ListaClientes<T, NADA>::~ListaClientes() {
    Nodo* aux = ini;
    while (aux != nullptr) {
        aux = ini;
        ini = ini->sig;
        delete aux;
    }
}

template <typename T, T NADA>
uint ListaClientes<T, NADA>::getLongitud() { return longitud; }

template <typename T, T NADA>
bool ListaClientes<T, NADA>::isEmpty() { return longitud == 0; }

template <typename T, T NADA>
void ListaClientes<T, NADA>::agregarCliente(T elem) {
    Nodo* nuevoNodo = new Nodo(elem, ini);
    if (nuevoNodo != nullptr) {
        ini = nuevoNodo;
        longitud++;
    }
}

template <typename T, T NADA>
T ListaClientes<T, NADA>::buscarCliente(string nombre) {
    Nodo* aux = ini;
    while (aux != nullptr) {
        if (aux->elem->getNombre() == nombre) {
            return aux->elem;
        }
        aux = aux->sig;
    }
    return nullptr;
}

template <typename T, T NADA>
void ListaClientes<T, NADA>::eliminarCliente(string nombre) {
    Nodo* actual = ini;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->elem->getNombre() == nombre) {
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
T ListaClientes<T, NADA>::obtenerPos(uint pos) {
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
void ListaClientes<T, NADA>::agregarEnPosicion(T elem, uint pos) {
    if (pos > longitud) return;
    if (pos == 0) {
        agregarCliente(elem);
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
void ListaClientes<T, NADA>::agregaClienteAlFinal(T elem) { agregarEnPosicion(elem, longitud); }