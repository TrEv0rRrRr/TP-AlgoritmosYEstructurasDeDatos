#pragma once
#include "Cliente.h"
#include "ListaClientes.h"
#include "Habitacion.h"
#include "ListaHabitaciones.h"
#include "Reserva.h"
#include "ListaReservas.h"

class App
{
private:
    ListaClientes<Cliente*>* listaClientes = new ListaClientes<Cliente*>();
    ListaHabitaciones<Habitacion*>* listaHabitaciones = new ListaHabitaciones<Habitacion*>();
    ListaReservas<Reserva*>* listaReservas = new ListaReservas<Reserva*>();
    bool habitacionesCargadas = false;

public:
	App();
	~App();

    // -------------- FUNCIONES PARA CLIENTES --------------

    void guardarClientes(ListaClientes<Cliente*>* lista, const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            for (uint i = 0; i < lista->getLongitud(); ++i) {
                Cliente* cliente = lista->obtenerPos(i);
                archivo << cliente->getNombre() << ","
                    << cliente->getApellido() << ","
                    << cliente->getCorreo() << ","
                    << cliente->getTelefono() << endl;
            }
            archivo.close();
        }
        else {
            cout << "Error al abrir el archivo " << nombreArchivo << " para escritura." << endl;
        }
    }

    pair<string, string> cargarClientes(ListaClientes<Cliente*>* lista, const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        string nombreRegistrado, apellidoRegistrado;

        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                stringstream ss(linea);
                string nombre, apellido, correo, telefono;
                getline(ss, nombre, ',');
                getline(ss, apellido, ',');
                getline(ss, correo, ',');
                getline(ss, telefono, ',');
                Cliente* cliente = new Cliente();
                cliente->setNombre(nombre);
                cliente->setApellido(apellido);
                cliente->setCorreo(correo);
                cliente->setTelefono(telefono);
                lista->agregaClienteAlFinal(cliente);

                nombreRegistrado = nombre;
                apellidoRegistrado = apellido;
            }
            archivo.close();
        }
        else {
            cout << "El archivo " << nombreArchivo << " no existe. Se creará uno nuevo al guardar usuarios." << endl;
        }

        return make_pair(nombreRegistrado, apellidoRegistrado);
    }

    void registrarCliente(ListaClientes<Cliente*>* lista) {
        system("cls");

        Cliente* c = new Cliente();

        string nombre, apellido, correo, telefono;

        cout << "Ingrese su nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingrese su apellido: ";
        getline(cin, apellido);
        cout << "Ingrese su correo: ";
        getline(cin, correo);
        cout << "Ingrese su telefono: ";
        getline(cin, telefono);

        c->setNombre(nombre);
        c->setApellido(apellido);
        c->setCorreo(correo);
        c->setTelefono(telefono);

        lista->agregaClienteAlFinal(c);
    }

    // -------------- FUNCIONES PARA HABITACIONES --------------

    void guardarHabitaciones(ListaHabitaciones<Habitacion*>* lista, const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            for (uint i = 0; i < lista->getLongitud(); ++i) {
                Habitacion* habitacion = lista->obtenerPos(i);
                archivo << habitacion->getNumPiso() << ","
                    << habitacion->getNumHab() << ","
                    << habitacion->getTipo() << ","
                    << habitacion->getDisponibilidad() << endl;
            }
            archivo.close();
        }
        else {
            cout << "Error al abrir el archivo " << nombreArchivo << " para escritura." << endl;
        }
    }

    void cargarHabitaciones(ListaHabitaciones<Habitacion*>* lista, const string& nombreArchivo) {
        if (!habitacionesCargadas) {
            ifstream archivo(nombreArchivo);
            if (archivo.is_open()) {
                string linea;
                while (getline(archivo, linea)) {
                    stringstream ss(linea);
                    string numHab, numPiso, tipo;
                    int disponible;
                    getline(ss, numHab, ',');
                    getline(ss, numPiso, ',');
                    getline(ss, tipo, ',');
                    ss >> disponible;

                    int numHabInt = stoi(numHab);
                    int numPisoInt = stoi(numPiso);
                    bool disponibilidad = (disponible == 1);

                    Habitacion* habitacion = new Habitacion();
                    habitacion->setNumHab(numHabInt);
                    habitacion->setNumPiso(numPisoInt);
                    habitacion->setTipo(tipo);
                    habitacion->setDisponibilidad(disponibilidad);
                    lista->agregarHabitacion(habitacion);
                }
                archivo.close();
                habitacionesCargadas = true;
            }
            else {
                cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
            }
        }
    }

    void imprimirHabitaciones(ListaHabitaciones<Habitacion*>* lista, uint indice) {
        if (indice < lista->getLongitud()) {
            Habitacion* habitacion = lista->obtenerPos(indice);
            cout << "\t" << habitacion->getNumHab() << "\t\t" << habitacion->getNumPiso() << "\t\t\t" << habitacion->getTipo() << "\t\t\t" << (habitacion->getDisponibilidad() ? "Si" : "No") << endl;
            cout << "________________________________________________________________________________________\n";
            imprimirHabitaciones(lista, indice + 1);
        }
    }

    void mostrarHabitaciones(ListaHabitaciones<Habitacion*>* lista) {
        if (lista->isEmpty()) {
            cout << "No hay habitaciones.\n\n";
        }
        else {
            cout << "Lista de habitaciones:\n";
            cout << "Num. Piso\tNum. Habitacion\t\tTipo de habitacion\t\tDisponibilidad\n";
            imprimirHabitaciones(lista, 0);
        }
    }

    void crearHabitaciones(ListaHabitaciones<Habitacion*>* lista) {
        const int NUM_PISOS = 2;
        const int HABITACIONES_POR_PISO = 10;

        string tipos[] = { "Individual", "Doble", "Suite" };

        for (int piso = 1; piso <= NUM_PISOS; ++piso) {
            int numHabInicio = (piso == 1) ? 101 : 201;

            for (int numHab = numHabInicio; numHab < numHabInicio + HABITACIONES_POR_PISO; ++numHab) {
                Habitacion* habitacion = new Habitacion();
                habitacion->setNumPiso(piso);
                habitacion->setNumHab(numHab);
                habitacion->setDisponibilidad(true);
                habitacion->setTipo(tipos[rand() % (sizeof(tipos) / sizeof(tipos[0]))]);
                lista->agregarHabitacion(habitacion);
            }
        }

        guardarHabitaciones(lista, "habitaciones.txt");
    }

    // -------------- FUNCIONES PARA RESERVAS --------------

    void guardarReservas(ListaReservas<Reserva*>* lista, const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            for (uint i = 0; i < lista->getLongitud(); ++i) {
                Reserva* reserva = lista->obtenerPos(i);
                archivo << reserva->getId() << "," << reserva->getNombreCliente() << "," << reserva->getApellidoCliente() << "," << reserva->getNumHabitacion() << "," << reserva->getFechaInicio() << "," << reserva->getFechaFin() << endl;
            }
            archivo.close();
        }
        else {
            cout << "Error al abrir el archivo " << nombreArchivo << " para escritura." << endl;
        }
    }

    void cargarReservas(ListaReservas<Reserva*>* lista, const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                stringstream ss(linea);
                string nombreCliente, apellidoCliente, fechaInicio, fechaFin, id, numHabitacion;
                getline(ss, id, ',');
                getline(ss, nombreCliente, ',');
                getline(ss, apellidoCliente, ',');
                getline(ss, numHabitacion, ',');
                getline(ss, fechaInicio, ',');
                getline(ss, fechaFin, ',');

                // Convertir cadenas numericas a enteros
                int numHabInt = stoi(numHabitacion);
                int idInt = stoi(id);

                // Crear objeto Habitacion y agregarlo a la lista
                Reserva* reserva = new Reserva();
                reserva->setId(idInt);
                reserva->setNombreCliente(nombreCliente);
                reserva->setApellidoCliente(apellidoCliente);
                reserva->setNumHabitacion(numHabInt);
                reserva->setFechaInicio(fechaInicio);
                reserva->setFechaFin(fechaFin);
                lista->agregarReserva(reserva);
            }
            archivo.close();
        }
        else {
            cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        }
    }

    void reservarHabitacion(ListaReservas<Reserva*>* listaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones, string& nombreCliente, string& apellidoCliente) {
        system("cls");
        string fInicio, fFinal;
        int numH;
        cout << "Ingrese el numero de habitacion que quiere reservar: ";
        cin >> numH;

        Habitacion* habitacion = listaHabitaciones->buscarHabitacion(numH);
        if (habitacion != nullptr) {
            if (habitacion->getDisponibilidad()) {
                cout << "Habitacion disponible para reservar." << endl;

                cout << "Ingrese la fecha de inicio (dd/mm/aaaa): ";
                cin.ignore();
                getline(cin, fInicio);
                cout << "Ingrese la fecha de salida (dd/mm/aaaa): ";
                getline(cin, fFinal);

                int idReserva = generarIdReserva();
                cout << "ID generada: " << idReserva << endl;

                Reserva* reserva = new Reserva();
                reserva->setNombreCliente(nombreCliente);
                reserva->setApellidoCliente(apellidoCliente);
                reserva->setNumHabitacion(numH);
                reserva->setFechaInicio(fInicio);
                reserva->setFechaFin(fFinal);
                reserva->setId(idReserva);

                listaReservas->agregarReserva(reserva);

                habitacion->setDisponibilidad(false);

                cout << "Reserva realizada con exito.\n\n";
                menuPrincipal();
            }
            else {
                cout << "La habitacion no esta disponible para reservar.\n\n";
                menuPrincipal();
            }
        }
        else {
            cout << "La habitacion no se encontró.\n\n";
            menuPrincipal();
        }
    }

    void modificarReserva(ListaReservas<Reserva*>* listaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones) {
        int idReserva;
        cout << "Ingrese el ID de la reserva: ";
        cin >> idReserva;
        Reserva* reserva = listaReservas->buscarReserva(idReserva);

        if (reserva != nullptr) {
            int opt;
            cout << "Reserva encontrada. ¿Qué desea modificar?" << endl;
            cout << "1: Número de habitación" << endl;
            cout << "2: Fecha de inicio" << endl;
            cout << "3: Fecha de salida" << endl;
            cout << "4: Ambas fechas" << endl;
            cout << "5: Todos los datos" << endl;
            cout << "6: No modificar nada" << endl;
            cout << "Ingrese una opción: ";
            cin >> opt;

            switch (opt) {
            case 1:
            {
                int numH;
                cout << "Ingrese el número de la nueva habitación: ";
                cin >> numH;

                Habitacion* habitacionActual = listaHabitaciones->buscarHabitacion(reserva->getNumHabitacion());
                if (habitacionActual != nullptr) {
                    habitacionActual->setDisponibilidad(true);
                }

                Habitacion* nuevaHabitacion = listaHabitaciones->buscarHabitacion(numH);
                if (nuevaHabitacion != nullptr && nuevaHabitacion->getDisponibilidad()) {
                    nuevaHabitacion->setDisponibilidad(false);
                    reserva->setNumHabitacion(numH);
                    cout << "Número de habitación actualizado." << endl;
                }
                else {
                    cout << "La nueva habitación no está disponible." << endl;
                }
                break;
            }
            case 2:
            {
                string fechaInicio;
                cout << "Ingrese la nueva fecha de inicio (dd/mm/aaaa): ";
                cin.ignore();
                getline(cin, fechaInicio);
                reserva->setFechaInicio(fechaInicio);
                break;
            }
            case 3:
            {
                string fechaFinal;
                cout << "Ingrese la nueva fecha de salida (dd/mm/aaaa): ";
                cin.ignore();
                getline(cin, fechaFinal);
                reserva->setFechaFin(fechaFinal);
                break;
            }
            case 4:
            {
                string fechaFinal, fechaInicio;
                cout << "Ingrese la nueva fecha de inicio (dd/mm/aaaa): ";
                getline(cin, fechaInicio);
                cout << "Ingrese la nueva fecha de salida (dd/mm/aaaa): ";
                getline(cin, fechaFinal);

                reserva->setFechaInicio(fechaInicio);
                reserva->setFechaFin(fechaFinal);
                break;
            }
            case 5:
            {
                int numH;
                string fechaInicio, fechaFinal;

                cout << "Ingrese el número de la nueva habitación: ";
                cin >> numH;
                cin.ignore();
                Habitacion* habitacionActual = listaHabitaciones->buscarHabitacion(reserva->getNumHabitacion());
                if (habitacionActual != nullptr) {
                    habitacionActual->setDisponibilidad(true);
                }

                Habitacion* nuevaHabitacion = listaHabitaciones->buscarHabitacion(numH);
                if (nuevaHabitacion != nullptr && nuevaHabitacion->getDisponibilidad()) {
                    nuevaHabitacion->setDisponibilidad(false);
                    reserva->setNumHabitacion(numH);
                    cout << "Número de habitación actualizado." << endl;
                }
                else {
                    cout << "La nueva habitación no está disponible." << endl;
                }

                cout << "Ingrese la nueva fecha de inicio (dd/mm/aaaa): ";
                getline(cin, fechaInicio);
                cout << "Ingrese la nueva fecha de salida (dd/mm/aaaa): ";
                getline(cin, fechaFinal);

                reserva->setFechaInicio(fechaInicio);
                reserva->setFechaFin(fechaFinal);
                break;
            }
            case 6:
                system("cls");
                menuPrincipal();
                return;
            default:
                cout << "Opción no válida." << endl;
                break;
            }

            guardarReservas(listaReservas, "reservas.txt");
            guardarHabitaciones(listaHabitaciones, "habitaciones.txt");

            cout << "Reserva modificada correctamente." << endl;
        }
        else cout << "Reserva no encontrada." << endl;
    }

    void cancelarReserva(ListaReservas<Reserva*>* listaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones) {
        int idReserva;
        cout << "Ingrese el ID de la reserva que desea cancelar: ";
        cin >> idReserva;

        Reserva* reserva = listaReservas->buscarReserva(idReserva);

        if (reserva != nullptr) {
            int numHabitacion = reserva->getNumHabitacion();

            Habitacion* habitacion = listaHabitaciones->buscarHabitacion(numHabitacion);
            if (habitacion != nullptr) {
                habitacion->setDisponibilidad(true);
                listaReservas->eliminarReserva(idReserva);
                cout << "Reserva cancelada con exito.\n\n";
                menuPrincipal();
            }
            else { 
                cout << "No se encontro la habitacion asociada a la reserva.\n\n";
                menuPrincipal();
            }
        }
        else { 
            cout << "No se encontro ninguna reserva con el ID proporcionado.\n\n";
            menuPrincipal();
        }
    }

    void imprimirReservas(ListaReservas<Reserva*>* lista, uint indice) {
        if (indice < lista->getLongitud()) {
            Reserva* reserva = lista->obtenerPos(indice);
            cout << reserva->getId() << "\t"
                << reserva->getNombreCliente() << ", " << reserva->getApellidoCliente() << "\t"
                << reserva->getNumHabitacion() << "\t\t"
                << reserva->getFechaInicio() << " - " << reserva->getFechaFin() << endl;
            cout << "_______________________________________________________________________________\n";
            imprimirReservas(lista, indice + 1);
        }
    }

    void mostrarReservas(ListaReservas<Reserva*>* listaReservas) {
        system("cls");
        if (listaReservas->isEmpty()) {
            cout << "No hay reservas.\n\n";
        }
        else {
            cout << "Lista de reservas:\n";
            cout << "ID\tCliente\t\tHabitacion\tFechas de reserva\n";
            imprimirReservas(listaReservas, 0);
        }
    }

    // -------------- FUNCIONES PRINCIPALES --------------

    void cargarDatos(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ListaReservas<Reserva*>* listaR) {
        cargarHabitaciones(listaH, "habitaciones.txt");
        cargarReservas(listaR, "reservas.txt");
        cargarClientes(listaC, "clientes.txt");
    }

    void guardarDatos(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ListaReservas<Reserva*>* listaR) {
        guardarHabitaciones(listaH, "habitaciones.txt");
        guardarReservas(listaR, "reservas.txt");
        guardarClientes(listaC, "clientes.txt");
    }

    void menuRegistro() {
        cout << "Bienvenido al sistema de gestion de reservas de hotel" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Registrarse" << endl;
        cout << "2. Salir" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
    }

    bool manejarMenuRegistro(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ListaReservas<Reserva*>* listaR) {
        int opt;
        cin >> opt;
        switch (opt) {
        case 1: // REGISTRARSE
            registrarCliente(listaC);
            return true;
            break;
        case 2: // SALIR DEL PROGRAMA
            guardarDatos(listaC, listaH, listaR);
            exit(0);
            break;
        default:
            cout << "Opcion no valida. Por favor, ingrese un numero del 1 al 2." << endl;
            break;
        }
        return false;
    }

    void menuPrincipal() {
        cout << "Bienvenido al sistema de gestion de reservas de hotel" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Ver disponibilidad de habitaciones" << endl;
        cout << "2. Realizar una nueva reserva" << endl;
        cout << "3. Ver reservas" << endl;
        cout << "4. Modificar una reserva" << endl;
        cout << "5. Cancelar una reserva" << endl;
        cout << "6. Salir" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
    }

    void manejarMenuPrincipal(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ListaReservas<Reserva*>* listaR) {

        pair<string, string> datosCliente = cargarClientes(listaC, "clientes.txt");
        string nombreCliente = datosCliente.first;
        string apellidoCliente = datosCliente.second;

        int opt;
        cin >> opt;
        switch (opt) {
        case 1: // HABITACIONES DISPONIBLES - HECHA
            system("cls");
            mostrarHabitaciones(listaH);
            break;
        case 2: // AGREGAR RESERVAS - HECHA
            reservarHabitacion(listaR, listaH, nombreCliente, apellidoCliente);
            break;
        case 3: // VER RESERVAS - HECHA
            system("cls");
            mostrarReservas(listaR);
            break;
        case 4: // MODIFICAR RESERVA - HECHA
            modificarReserva(listaR, listaH);
            break;
        case 5: // ELIMINAR RESERVA - HECHA
            cancelarReserva(listaR, listaH);
            break;
        case 6: // SALIR DEL PROGRAMA
            guardarDatos(listaC, listaH, listaR);
            exit(0);
            break;
        default:
            cout << "Opcion no valida. Por favor, ingrese un numero del 1 al 7." << endl;
            break;
        }
    }

    bool archivoExiste(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        archivo.close();
        return archivo.good();
    }

    void limpiarConsola() {
        system("pause");
        system("cls");
    }

    void run() {
        cargarHabitaciones(listaHabitaciones, "habitaciones.txt");
        cargarReservas(listaReservas, "reservas.txt");
        // Verificar si el archivo de clientes existe y cargarlos si es asi
        bool clientesRegistrados = archivoExiste("clientes.txt");

        // Verificar si el archivo de habitaciones existe y cargarlas si es asi
        bool habitacionesCreadas = archivoExiste("habitaciones.txt");

        // Verificar si el archivo de reservas existe y cargarlas si es asi
        bool reservasCargadas = archivoExiste("reservas.txt");

        // Si el archivo de clientes no existe, se mostrara el menu de registro
        if (!clientesRegistrados) {
            while (true) {
                menuRegistro();
                clientesRegistrados = manejarMenuRegistro(listaClientes, listaHabitaciones, listaReservas);
                if (clientesRegistrados) break;
            }
        }

        // Si el archivo de habitaciones no existe, se crearan las habitaciones
        if (!habitacionesCreadas) crearHabitaciones(listaHabitaciones);

        // Si el archivo de reservas no existe, se inicializara vacio
        if (!reservasCargadas) {
            ofstream archivoReservas("reservas.txt");
            archivoReservas.close();
        }

        // Logica principal del programa
        while (true) {
            menuPrincipal();
            manejarMenuPrincipal(listaClientes, listaHabitaciones, listaReservas);
        }
    }
};

App::App() {}

App::~App() { delete listaClientes; delete listaHabitaciones; delete listaReservas; }
