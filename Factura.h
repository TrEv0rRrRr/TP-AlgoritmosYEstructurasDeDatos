#pragma once
#include "Librerias.h"

class Factura
{
private:
	int idFactura, total;
	string nombreCliente, apellidoCliente;
	time_t fechaEmision;
	bool pagada;

public:
	Factura() : idFactura(0), total(0), nombreCliente(""), apellidoCliente(""), fechaEmision(time(nullptr)), pagada(true) {}
	~Factura();

	int getIdFactura() const { return idFactura; }
	string getNombreCliente() const { return nombreCliente; }
	string getApellidoCliente() const { return apellidoCliente; }
	double getTotal() const { return total; }
	bool getPagada() const { return this->pagada; }
	time_t getFecha() const { return this->fechaEmision; }

	void setIdFactura(int idFactura) { this->idFactura = idFactura; }
	void setNombreCliente(string nombreCliente) { this->nombreCliente = nombreCliente; }
	void setApellidoCliente(string apellidoClient) { this->apellidoCliente = apellidoCliente; }
	void setTotal(int total) { this->total = total; }
	void setPagada(bool pagada) { this->pagada = pagada; }
	void setFecha(time_t fechaEmision) { this->fechaEmision = fechaEmision; }

	void mostrarFactura() const {
		cout << " -------------------------------------------" << endl;
		cout << "    Factura ID: " << idFactura << endl;
		cout << "    Cliente: " << nombreCliente << " " << apellidoCliente << endl;
		cout << "    Fecha de Emision: " << put_time(localtime(&fechaEmision), "%Y-%m-%d %H:%M:%S") << endl;
		cout << " -------------------------------------------" << endl;
		cout << "    Total: $" << total << endl;
		cout << "    Estado: " << (pagada ? "Pagada" : "Pendiente") << endl;
		cout << " -------------------------------------------" << endl;
	}
};

Factura::~Factura() {}