#pragma once
template<typename T1, typename T2>

class Habitacion
{
private:
	T1 numHab;
	bool disponible;
	T2 tipo;

public:
	Habitacion(T1 numPiso, T1 numHab, T2 tipo, bool disponible);
	~Habitacion();

	void verDisponibilidad();

	bool getDisponibilidad() { return this->disponible; }
	T1 getNumPiso() { return this->numpPiso; } T1 getNumHab() { return this->numHab; }
	T2 getTipo() { return this->tipo; }

	void getDisponibilidad(bool disponible) { this->disponible = disponible; }
	void getNumPiso(T1 numPiso) { this->numpPiso = numpPiso; }
	void getNumHab(T1 numHab) { this->numHab = numHab; }
	void getTipo(T2 tipo) { this->tipo = tipo; }
};

template<typename T1, typename T2>
Habitacion<T1, T2>::Habitacion(T1 numPiso, T1 numHab, T2 tipo, bool disponible) {
	this->tipo = tipo;
	this->disponible = disponible;
}

template<typename T1, typename T2>
Habitacion<T1, T2>::~Habitacion() {}

template<typename T1, typename T2>
void Habitacion<T1, T2>::verDisponibilidad(){
	cout << "Número de Piso: " << numPiso << " - Número de Habitación : " << numHab << " - Tipo : " << tipo << " - Disponible : " << (disponible ? "Sí" : "No") << endl;
}