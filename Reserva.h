#pragma once

class Reserva
{
private:
    string nombreCliente, apellidoCliente;
    string fechaInicio, fechaFin;
    int id, numHabitacion;

public:
    Reserva::Reserva(): nombreCliente(""), apellidoCliente(""), numHabitacion(0), fechaInicio(""), fechaFin(""), id(0) {}

    Reserva::~Reserva();

    // Getters
    string getNombreCliente() { return this->nombreCliente; }
    string getApellidoCliente() { return this->apellidoCliente; }
    string getFechaInicio() { return this->fechaInicio; }
    string getFechaFin() { return this->fechaFin; }
    int getNumHabitacion() { return this->numHabitacion; }
    int getId() { return this->id; }

    // Setters
    void setNombreCliente(string nombreCliente) { this->nombreCliente = nombreCliente; }
    void setApellidoCliente(string apellidoCliente) { this->apellidoCliente = apellidoCliente; }
    void setNumHabitacion(int numHabitacion) { this->numHabitacion = numHabitacion; }
    void setFechaInicio(string fechaInicio) { this->fechaInicio = fechaInicio; }
    void setFechaFin(string fechaFin) { this->fechaFin = fechaFin; }
    void setId(int id) { this->id = id; }
    string toString() const {
        return to_string(id) + "\t" + apellidoCliente + ", " + nombreCliente + "\t" +
               to_string(numHabitacion) + "\t\t\t" + fechaInicio + " - " + fechaFin;
    }
};

Reserva::~Reserva() {}