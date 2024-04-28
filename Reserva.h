#pragma once
#include "Habitacion.h"
#include "Cliente.h"

template<typename T1, typename T2>
class Reserva
{
private:
    Cliente* cliente;
    Habitacion<T1, T2>* habitacion;
    string fechaInicio;
    string fechaFin;
    int duracion;

public:
    Reserva(Cliente* cliente, Habitacion<T1, T2>* habitacion, string fechaInicio, string fechaFin, int duracion);
    ~Reserva();

    // Getters
    Cliente* getCliente() const { return cliente; }
    Habitacion<T1, T2>* getHabitacion() const { return habitacion; }
    string getFechaInicio() const { return fechaInicio; }
    string getFechaFin() const { return fechaFin; }
    int getDuracion() const { return duracion; }

    // Setters
    void setCliente(Cliente* cliente) { this->cliente = cliente; }
    void setHabitacion(Habitacion<T1, T2>* habitacion) { this->habitacion = habitacion; }
    void setFechaInicio(string fechaInicio) { this->fechaInicio = fechaInicio; }
    void setFechaFin(string fechaFin) { this->fechaFin = fechaFin; }

    void mostrarReserva();

};

template<typename T1, typename T2>
Reserva<T1, T2>::Reserva(Cliente* cliente, Habitacion<T1, T2>* habitacion, string fechaInicio, string fechaFin, int duracion) {
    this->cliente = cliente;
    this->habitacion = habitacion;
    this->fechaInicio = fechaInicio;
    this->fechaFin = fechaFin;
    this->duracion = duracion;
}

template<typename T1, typename T2>
Reserva<T1, T2>::~Reserva() {}

template<typename T1, typename T2>
void Reserva<T1, T2>::mostrarReserva() {
    cout << "Cliente: " << cliente->getNombre() << " " << cliente->getApellido() << endl;
    cout << "Habitación: " << habitacion->getNumHab() << endl;
    cout << "Fechas de reserva -> Fecha de inicio (dd/mm/aaaa) - Fecha de salida (dd/mm/aaaa): " << fechaInicio << " - " << fechaFin << endl;
    cout << "Duración: " << duracion << " días" << endl;
}