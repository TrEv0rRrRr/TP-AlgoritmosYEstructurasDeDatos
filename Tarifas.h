#pragma once
#include "Librerias.h"

class Tarifas {
private:
    unordered_map<string, double> tarifasPorTipo; 
    double tarifaBase; 

public:
    Tarifas(double tarifaBase) : tarifaBase(tarifaBase) {}

    
    void setTarifaPorTipo(const string& tipoHabitacion, double tarifa) {
        tarifasPorTipo[tipoHabitacion] = tarifa;
    }

  
    double getTarifaPorTipo(const string& tipoHabitacion) const {
        auto it = tarifasPorTipo.find(tipoHabitacion);
        if (it != tarifasPorTipo.end()) {
            return it->second;
        }
        else {
           
            return tarifaBase;
        }
    }

    
    double calcularCostoReserva(double tarifa, int duracion) const {
        return tarifa * duracion; 
    }
};
