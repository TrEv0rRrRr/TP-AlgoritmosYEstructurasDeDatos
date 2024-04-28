#pragma once
#include "Cliente.h"

class ListaClientes
{
private:
    struct Nodo {
        Cliente* dataCliente;
        Nodo* next;

        Nodo(Cliente* cliente, Nodo* next = nullptr) {
            this->dataCliente = cliente;
            this->next = next;
        }
    };

    Nodo* start;
    int length;

public:
    ListaClientes();
	~ListaClientes();

    bool isEmpty() const {
        return length == 0;
    }

    void agregarCliente(Cliente* cliente) {
        Nodo* nuevoNodo = new Nodo(cliente);
        if (nuevoNodo != nullptr) {
            nuevoNodo->next = start;
            start = nuevoNodo;
            length++;
        }
    }

    void eliminarCliente(string nombre) {
        if (isEmpty()) {
            cout << "La lista de clientes está vacía." << endl;
            return;
        }

        Nodo* current = start;
        Nodo* prev = nullptr;

        // Buscar el cliente por su nombre
        while (current != nullptr && current->dataCliente->getNombre() != nombre) {
            prev = current;
            current = current->next;
        }

        // Si encontramos al cliente, lo eliminamos
        if (current != nullptr) {
            // Si el cliente es el primero en la lista
            if (prev == nullptr) {
                start = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current->dataCliente;
            delete current;
            length--;
            cout << "Cliente " << nombre << " eliminado correctamente." << endl;
        }
        else {
            cout << "Cliente " << nombre << " no encontrado en la lista." << endl;
        }
    }

    void addClienteStart(Cliente* cliente) {
        Nodo* newNodo = new Nodo(cliente, start);
        if (newNodo != nullptr) {
            start = newNodo;
            length++;
        }
    }

    void addClienteEnd(Cliente* cliente) {
        if (length == 0) addClienteStart(cliente);
        else {
            Nodo* aux = start;
            while (aux->next != nullptr) {
                aux = aux->next;
            }
            aux->next = new Nodo(cliente);
            length++;
        }
    }
};

ListaClientes::ListaClientes() {
    this->start = nullptr;
    this->length = 0;
}

ListaClientes::~ListaClientes() {}