#pragma once
#include "Librerias.h"


class Cliente
{
private:
	string nombre, apellido, correo, telefono;
	bool registrado;

public:
	Cliente(string nombre= "", string apellido= "", string correo= "", string telefono= "");
	~Cliente();

	string getNombre() { return this->nombre; }
	string getApellido() { return this->apellido; }
	string getCorreo() { return this->correo; }
	string getTelefono() { return this->telefono; }
	bool getRegistrado() const { return registrado; }

	void setNombre(string nombre) { this->nombre = nombre; }
	void setApellido(string apellido) { this->apellido = apellido; }
	void setCorreo(string correo) { this->correo = correo; }
	void setTelefono(string telefono) { this->telefono = telefono; }
	void setRegistrado(bool registrado) { this->registrado = registrado; }

	void guardarCliente() const {
		ofstream archivo("Clientes.txt", ios::app); // Abrir el archivo en modo de apendizaje
		if (archivo.is_open()) {
			archivo << "Nombre: " << nombre << endl;
			archivo << "Apellido: " << apellido << endl;
			archivo << "Correo: " << correo << endl;
			archivo << "Teléfono: " << telefono << endl;
			archivo << "Registrado: " << (registrado ? "SI" : "NO") << endl;
			archivo << "-----------------------------------" << endl;
			archivo.close();
			cout << "Cliente registrado correctamente." << endl;
		}
		else {
			cout << "Error al abrir el archivo para guardar el cliente." << endl;
		}
	}
};

Cliente::Cliente(string nombre, string apellido, string correo, string telefono) {
	this->nombre = nombre;
	this->apellido = apellido;
	this->correo = correo;
	this->telefono = telefono;
}

Cliente::~Cliente(){}