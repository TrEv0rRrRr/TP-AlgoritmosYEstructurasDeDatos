#include "Habitacion.h"

bool registrado = false;

void mostrarMenu() {
    cout << "Bienvenido al sistema de gestión de reservas de hotel" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1. Ver disponibilidad de habitaciones" << endl;
    cout << "2. Realizar una nueva reserva" << endl;
    cout << "3. Ver información de una reserva existente" << endl;
    cout << "4. Modificar una reserva" << endl;
    cout << "5. Cancelar una reserva" << endl;
    cout << "6. Ver detalles del hotel" << endl;
    cout << "7. Salir" << endl;
    cout << "--------------------------------------------------" << endl;
}

void registrarse() {
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
    nuevoCliente.guardarSesion();

    cout << "Registro exitoso. ¡Bienvenido, " << nombre << "!" << "\n\n";
    registrado = true;
}

int main() {
	setlocale(LC_ALL, "");

    int opcion;

    do {

        if (!registrado) {
            cout << "Bienvenido al sistema de gestión de reservas de hotel" << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Por favor, registre su cuenta antes de continuar." << endl;
            cout << "--------------------------------------------------" << endl;
            registrarse();
            registrado = true;
        }

        mostrarMenu();
        cout << "Ingrese el número de la opción que desea realizar: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            // Lógica para ver disponibilidad de habitaciones
            cout << "Función para ver disponibilidad de habitaciones" << endl;
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
            // Lógica para ver detalles del hotel
            cout << "Función para ver detalles del hotel" << endl;
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

	_getch();
}