#pragma once
#include "Tarifas.h"

class ListaTarifas {
private:
    struct Nodo {
        string tipoHabitacion;
        Tarifas* tarifas;
        Nodo* siguiente;

        Nodo(const string& tipoHabitacion, Tarifas* tarifas, Nodo* siguiente = nullptr)
            : tipoHabitacion(tipoHabitacion), tarifas(tarifas), siguiente(siguiente) {}
    };

    Nodo* inicio;

public:
    ListaTarifas() : inicio(nullptr) {}
    ~ListaTarifas() {
        while (inicio != nullptr) {
            Nodo* temp = inicio;
            inicio = inicio->siguiente;
            delete temp->tarifas;
            delete temp;
        }
    }

   
    void agregarTarifas(const string& tipoHabitacion, double tarifaBase) {
        Tarifas* tarifas = new Tarifas(tarifaBase);
        Nodo* nuevoNodo = new Nodo(tipoHabitacion, tarifas, inicio);
        inicio = nuevoNodo;
    }

   
    Tarifas* obtenerTarifas(const string& tipoHabitacion) const {
        Nodo* actual = inicio;
        while (actual != nullptr) {
            if (actual->tipoHabitacion == tipoHabitacion) {
                return actual->tarifas;
            }
            actual = actual->siguiente;
        }
        return nullptr; 
    }
};
