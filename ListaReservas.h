#pragma once
#include "Reserva.h"

template<typename T1, typename T2>
class ListaReservas {
private:
    struct Nodo {
        Reserva<T1, T2>* dataReserva;
        Nodo* next;

        Nodo(Reserva<T1, T2>* reserva, Nodo* next = nullptr) {
            this->dataReserva = reserva;
            this->next = next;
        }
    };

    Nodo* start;
    int length;

public:
    ListaReservas() : start(nullptr), length(0) {}
    ~ListaReservas() {
        while (start != nullptr) {
            Nodo* temp = start;
            start = start->next;
            delete temp->dataReserva;
            delete temp;
        }
    }

    bool isEmpty() const {
        return length == 0;
    }

    void agregarReserva(Reserva<T1, T2>* reserva) {
        Nodo* nuevoNodo = new Nodo(reserva);
        if (nuevoNodo != nullptr) {
            nuevoNodo->next = start;
            start = nuevoNodo;
            length++;
        }
    }

    bool buscarReserva(int idReserva) const {
        Nodo* actual = start;
        while (actual != nullptr) {
            if (actual->dataReserva->getId() == idReserva) {
                return true;
            }
            actual = actual->next;
        }
        return false;
    }

    void eliminarReserva(int idReserva) {
        if (isEmpty()) {
            cout << "La lista de reservas está vacía." << endl;
            return;
        }

        Nodo* current = start;
        Nodo* prev = nullptr;

        // Buscar la reserva por su ID
        while (current != nullptr && current->dataReserva->getId() != idReserva) {
            prev = current;
            current = current->next;
        }

        // Si encontramos la reserva, la eliminamos
        if (current != nullptr) {
            // Si la reserva es la primera en la lista
            if (prev == nullptr) {
                start = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current->dataReserva;
            delete current;
            length--;
            cout << "Reserva " << idReserva << " eliminada correctamente." << endl;
        }
        else {
            cout << "Reserva " << idReserva << " no encontrada en la lista." << endl;
        }
    }
};
