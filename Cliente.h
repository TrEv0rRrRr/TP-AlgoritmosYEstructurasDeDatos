#pragma once
#include "Librerias.h"

class Cliente
{
private:
	string nombre, apellido, correo, telefono;

public:
	Cliente() : nombre(""), apellido(""), correo(""), telefono("") {}
	~Cliente();

	string getNombre() { return this->nombre; }
	string getApellido() { return this->apellido; }
	string getCorreo() { return this->correo; }
	string getTelefono() { return this->telefono; }

	void setNombre(string nombre) { this->nombre = nombre; }
	void setApellido(string apellido) { this->apellido = apellido; }
	void setCorreo(string correo) { this->correo = correo; }
	void setTelefono(string telefono) { this->telefono = telefono; }
};

Cliente::~Cliente(){}