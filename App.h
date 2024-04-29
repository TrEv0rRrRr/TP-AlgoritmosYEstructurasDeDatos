#pragma once
#include "Cliente.h"
#include "Habitacion.h"
#include "Tarifas.h"
#include "ListaClientes.h"
#include "ListaTarifas.h"
#include "ListaHabitaciones.h"
#include "ListaReservas.h"

class App
{
private:
    ListaClientes* listaClientes;
    ListaTarifas* listaTarifas;

public:
	App();
	~App();

    void mostrarMenu() {
        cout << "Bienvenido al sistema de gestión de reservas de hotel" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Ver disponibilidad de habitaciones" << endl;
        cout << "2. Realizar una nueva reserva" << endl;
        cout << "3. Ver información de una reserva existente" << endl;
        cout << "4. Modificar una reserva" << endl;
        cout << "5. Cancelar una reserva" << endl;
	    cout << "6. Ver Tarifas" << endl;
        cout << "7. Salir" << endl;
        cout << "--------------------------------------------------" << endl;
    }

    void registroCliente() {
        string nombre, apellido, correo, telefono;

        cout << "Por favor, ingrese su nombre: ";
        cin >> nombre;
        cout << "Por favor, ingrese su apellido: ";
        cin >> apellido;
        cout << "Por favor, ingrese su correo electrónico: ";
        cin >> correo;
        cout << "Por favor, ingrese su número de teléfono: ";
        cin >> telefono;

        Cliente nuevoCliente(nombre, apellido, correo, telefono);
        nuevoCliente.setRegistrado(true);
        nuevoCliente.guardarCliente();
    }

    void run() {
        int opcion;

        registroCliente();

        do {

            mostrarMenu();
            cout << "Ingrese el número de la opción que desea realizar: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                cout << "Habitaciones disponibles:" << endl;
                break;
            case 2:
                // Lógica para realizar una nueva reserva
                cout << "Función para realizar una nueva reserva" << endl;
                break;
            case 3:
                // Lógica para ver información de una reserva existente
                cout << "Función para ver información de una reserva existente" << endl;
                break;
            case 4:
                // Lógica para modificar una reserva
                cout << "Función para modificar una reserva" << endl;
                break;
            case 5:
                // Lógica para cancelar una reserva
                cout << "Función para cancelar una reserva" << endl;
                break;
            case 6:
                // Lógica para ver las tarifas
                cout << "Función para ver las tarifas" << endl;
                break;
	        case 7:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, ingrese un número del 1 al 7." << endl;
                break;
            }

        } while (opcion != 7);

        cout << "Saliendo del sistema..." << endl;
    }
};


App::App() {}


App::~App() {}
