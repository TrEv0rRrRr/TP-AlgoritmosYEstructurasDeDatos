#pragma once
#include "Librerias.h"

class Cliente
{
private:
	string nombre, apellido, correo, DNI;

public:
	Cliente() : nombre(""), apellido(""), correo(""), DNI("") {}
	~Cliente();

	string getNombre() { return this->nombre; }
	string getApellido() { return this->apellido; }
	string getCorreo() { return this->correo; }
	string getDNI() { return this->DNI; }

	void setNombre(string nombre) { this->nombre = nombre; }
	void setApellido(string apellido) { this->apellido = apellido; }
	void setCorreo(string correo) { this->correo = correo; }
	void setDNI(string DNI) { this->DNI = DNI; }
};

Cliente::~Cliente(){}