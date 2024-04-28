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
	bool estaRegistrado() const { return registrado; }

	void setNombre(string nombre) { this->nombre = nombre; }
	void setApellido(string apellido) { this->apellido = apellido; }
	void setCorreo(string correo) { this->correo = correo; }
	void setTelefono(string telefono) { this->telefono = telefono; }
	void setRegistrado(bool estado) { registrado = estado; }

	void guardarSesion() const {
		ofstream archivo("sesion.txt");
		if (archivo.is_open()) {
			archivo << "Nombre: " << nombre << endl;
			archivo << "Apellido: " << apellido << endl;
			archivo << "Correo: " << correo << endl;
			archivo << "Teléfono: " << telefono << endl;
			archivo << "Registrado: " << (registrado ? "SI" : "NO") << endl;
			archivo.close();
			cout << "Inicio de sesión exitoso. Bienvenido, " << nombre << "!" << endl;
		}
		else {
			cout << "Error al abrir el archivo para guardar la sesión." << endl;
		}
	}

	void cargarSesion() {
		ifstream archivo("sesion.txt");
		if (archivo.is_open()) {
			string line;
			while (getline(archivo, line)) {
				// Parsear la línea para obtener el nombre de la variable y su valor
				stringstream ss(line);
				string key, value;
				getline(ss, key, ':');
				getline(ss, value);
				// Asignar el valor correspondiente a cada atributo
				if (key == "Nombre") {
					nombre = value;
				}
				else if (key == "Apellido") {
					apellido = value;
				}
				else if (key == "Correo") {
					correo = value;
				}
				else if (key == "Teléfono") {
					telefono = value;
				}
				else if (key == "Registrado") {
					registrado = (value == "SI");
				}
			}
			archivo.close();
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