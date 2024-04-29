#pragma once
#include "Habitacion.h"

template<typename T1, typename T2>
class ListaHabitaciones {
private:
    struct Nodo {
        Habitacion<T1, T2>* dataHabitacion;
        Nodo* next;

        Nodo(Habitacion<T1, T2>* habitacion, Nodo* next = nullptr) {
            this->dataHabitacion = habitacion;
            this->next = next;
        }
    };

    Nodo* start;
    int length;

public:
    ListaHabitaciones() : start(nullptr), length(0) {}
    ~ListaHabitaciones() {
        while (start != nullptr) {
            Nodo* temp = start;
            start = start->next;
            delete temp->dataHabitacion;
            delete temp;
        }
    }

    bool isEmpty() const {
        return length == 0;
    }

    void agregarHabitacion(Habitacion<T1, T2>* habitacion) {
        Nodo* nuevoNodo = new Nodo(habitacion);
        if (nuevoNodo != nullptr) {
            nuevoNodo->next = start;
            start = nuevoNodo;
            length++;
        }
    }

    bool buscarHabitacion(T1 numHabitacion) const {
        Nodo* actual = start;
        while (actual != nullptr) {
            if (actual->dataHabitacion->getNumHab() == numHabitacion) {
                return true;
            }
            actual = actual->next;
        }
        return false;
    }

    void eliminarHabitacion(T1 numHabitacion) {
        if (isEmpty()) {
            cout << "La lista de habitaciones está vacía." << endl;
            return;
        }

        Nodo* current = start;
        Nodo* prev = nullptr;

        // Buscar la habitación por su número
        while (current != nullptr && current->dataHabitacion->getNumHab() != numHabitacion) {
            prev = current;
            current = current->next;
        }

        // Si encontramos la habitación, la eliminamos
        if (current != nullptr) {
            // Si la habitación es la primera en la lista
            if (prev == nullptr) {
                start = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current->dataHabitacion;
            delete current;
            length--;
            cout << "Habitación " << numHabitacion << " eliminada correctamente." << endl;
        }
        else {
            cout << "Habitación " << numHabitacion << " no encontrada en la lista." << endl;
        }
    }
};
