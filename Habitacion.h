#pragma once
#include "Librerias.h"
class Habitacion
{
private:
	int numHab, numPiso;
	bool disponible;
	string tipo;

public:
	Habitacion() : numHab(0), numPiso(0), tipo(""), disponible(false) {}
	~Habitacion();

	bool getDisponibilidad() const { return this->disponible; }
	int getNumPiso() const { return this->numPiso; } 
	int getNumHab() const { return this->numHab; }
	string getTipo() const { return this->tipo; }

	void setDisponibilidad(bool disponible) { this->disponible = disponible; }
	void setNumPiso(int numPiso) { this->numPiso = numPiso; }
	void setNumHab(int numHab) { this->numHab = numHab; }
	void setTipo(string tipo) { this->tipo = tipo; }
};

Habitacion::~Habitacion() {}
