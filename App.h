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

public:
	App();
	~App();

    // -------------- FUNCIONES PARA CLIENTES --------------

    void guardarClientes(ListaClientes<Cliente*>* lista, const string& nombreArchivo) {
        string nombre, apellido, correo, telefono;

        ofstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            archivo.clear(); // Limpiar el archivo antes de escribir

            for (uint i = 0; i < lista->getLongitud(); ++i) {
                Cliente* cliente = lista->obtenerPos(i);
                archivo << cliente->getNombre() << "," << cliente->getApellido() << "," << cliente->getCorreo() << "," << cliente->getTelefono() << endl;
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
            cout << "El archivo " << nombreArchivo << " no existe. Se creara uno nuevo al guardar usuarios." << endl;
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
            archivo.clear(); // Limpiar el archivo antes de escribir

            for (uint i = 0; i < lista->getLongitud(); ++i) {
                Habitacion* habitacion = lista->obtenerPos(i);
                archivo << habitacion->getNumPiso() << "," << habitacion->getNumHab() << "," << habitacion->getTipo() << "," << habitacion->getDisponibilidad() << endl;
            }
            archivo.close();
        }
        else {
            cout << "Error al abrir el archivo " << nombreArchivo << " para escritura." << endl;
        }
    }

    void cargarHabitaciones(ListaHabitaciones<Habitacion*>* lista, const string& nombreArchivo) {
        bool habitacionesCargadas = false;
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

    void mostrarHabitacionesPaginado(ListaHabitaciones<Habitacion*>* lista, int elementosPorPagina) {
        system("cls");
        if (lista->isEmpty()) {
            cout << "No hay habitaciones.\n\n";
            return;
        }

        int totalPaginas = (lista->getLongitud() + elementosPorPagina - 1) / elementosPorPagina;
        int paginaActual = 0;
        char opcion;

        do {
            system("cls");
            cout << "Lista de habitaciones - Pagina " << paginaActual + 1 << " de " << totalPaginas << ":\n";
            cout << "Num. Piso\tNum. Habitacion\t\tTipo de habitacion\t\tDisponibilidad\n";

            int inicio = paginaActual * elementosPorPagina;
            int fin = min(inicio + elementosPorPagina, (int)lista->getLongitud());

            for (int i = inicio; i < fin; ++i) {
                Habitacion* habitacion = lista->obtenerPos(i);
                cout << "\t" << habitacion->getNumHab() << "\t\t" << habitacion->getNumPiso() << "\t\t\t"
                    << habitacion->getTipo() << "\t\t\t" << (habitacion->getDisponibilidad() ? "Si" : "No") << endl;
                cout << "________________________________________________________________________________________\n";
            }

            cout << "n: Siguiente pagina, p: Pagina anterior, q: Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            if (opcion == 'n' && paginaActual < totalPaginas - 1) {
                paginaActual++;
            }
            else if (opcion == 'p' && paginaActual > 0) {
                paginaActual--;
            }
            else if (opcion != 'q') {
                cout << "Opcion no valida.\n";
            }
        } while (opcion != 'q');
    }

    void crearHabitaciones(ListaHabitaciones<Habitacion*>* lista) {
        // Cantidad de pisos y habitaciones por piso
        const int NUM_PISOS = 2;
        const int HABITACIONES_POR_PISO = 10;

        // Tipos de habitaciones
        string tipos[] = { "Individual", "Doble", "Suite" };

        // Iteramos sobre los pisos y las habitaciones por piso
        for (int piso = 1; piso <= NUM_PISOS; ++piso) {
            int numHabInicio = (piso == 1) ? 101 : 201;

            for (int numHab = numHabInicio; numHab < numHabInicio + HABITACIONES_POR_PISO; ++numHab) {
                // Creamos una nueva habitacion
                Habitacion* habitacion = new Habitacion();
                habitacion->setNumPiso(piso);
                habitacion->setNumHab(numHab);
                habitacion->setDisponibilidad(true);
                // Asignamos un tipo aleatorio
                habitacion->setTipo(tipos[rand() % (sizeof(tipos) / sizeof(tipos[0]))]);

                // Agregamos la habitacion a la lista
                lista->agregarHabitacion(habitacion);
            }
        }

        guardarHabitaciones(lista, "habitaciones.txt");
    }

    void ordenarHabitaciones(ListaHabitaciones<Habitacion*>* lista) {
        bool swapped;
        for (uint i = 0; i < lista->getLongitud() - 1; ++i) {
            swapped = false;
            for (uint j = 0; j < lista->getLongitud() - i - 1; ++j) {
                Habitacion* hab1 = lista->obtenerPos(j);
                Habitacion* hab2 = lista->obtenerPos(j + 1);

                if (hab1->getNumPiso() > hab2->getNumPiso() ||
                    (hab1->getNumPiso() == hab2->getNumPiso() && hab1->getNumHab() > hab2->getNumHab())) {
                    swap(*lista->obtenerPos(j), *lista->obtenerPos(j + 1));
                    swapped = true;
                }
            }
            // Si no se realizo ningun intercambio, la lista esta ordenada
            if (!swapped)
                break;
        }
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

                // Actualizar disponibilidad de la habitacion
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

    void modificarReserva(ListaReservas<Reserva*>* lista) {
        system("cls");
        int idReserva;
        cout << "Ingrese el ID de la reserva: ";
        cin >> idReserva;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Reserva* reserva = lista->buscarReserva(idReserva);

        if (reserva != nullptr) {
            int opt;
            cout << "Reserva encontrada! Que desea modificar?" << endl;
            cout << "1: Numero de habitacion" << endl;
            cout << "2: Fecha de inicio" << endl;
            cout << "3: Fecha de salida" << endl;
            cout << "4: Todos los datos" << endl;
            cout << "5: No modificar nada" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opt;

            switch (opt) {
            case 1:
            {
                int numH;
                cout << "Ingrese el numero de la nueva habitacion: ";
                cin >> numH;
                reserva->setNumHabitacion(numH);
                break;
            }
            case 2:
            {
                string fechaInicio;
                cout << "Ingrese la nueva fecha de inicio (dd/mm/aaaa): ";
                getline(cin, fechaInicio);
                reserva->setFechaInicio(fechaInicio);
                break;
            }
            case 3:
            {
                string fechaFinal;
                cout << "Ingrese la nueva fecha de salida (dd/mm/aaaa): ";
                getline(cin, fechaFinal);
                reserva->setFechaFin(fechaFinal);
                break;
            }
            case 4:
            {
                int numH;
                string fechaInicio, fechaFinal;

                cout << "Ingrese el numero de la nueva habitacion: ";
                cin >> numH;
                cin.ignore();

                cout << "Ingrese la nueva fecha de inicio (dd/mm/aaaa): ";
                getline(cin, fechaInicio);
                cout << "Ingrese la nueva fecha de salida (dd/mm/aaaa): ";
                getline(cin, fechaFinal);

                reserva->setNumHabitacion(numH);
                reserva->setFechaInicio(fechaInicio);
                reserva->setFechaFin(fechaFinal);
                menuPrincipal();
                break;
            }
            case 5:
            {   
                limpiarConsola();
                menuPrincipal();
                break;
            }
            default:
                cout << "Opcion no valida." << endl;
                break;
            }
            cout << "Reserva modificada correctamente.\n\n";
            menuPrincipal();
        }
        else {
            cout << "Reserva no encontrada.\n\n";
            menuPrincipal();
        }
    }

    void cancelarReserva(ListaReservas<Reserva*>* listaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones) {
        system("cls");

        int idReserva;
        cout << "Ingrese el ID de la reserva que desea cancelar: ";
        cin >> idReserva;

        // Buscar la reserva por su ID
        Reserva* reserva = listaReservas->buscarReserva(idReserva);

        if (reserva != nullptr) {
            // Obtener el numero de habitacion reservada
            int numHabitacion = reserva->getNumHabitacion();

            // Actualizar la disponibilidad de la habitacion reservada
            Habitacion* habitacion = listaHabitaciones->buscarHabitacion(numHabitacion);
            if (habitacion != nullptr) {
                habitacion->setDisponibilidad(true);
                // Eliminar la reserva de la lista
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

    void mostrarReservasPaginado(ListaReservas<Reserva*>* listaReservas, int elementosPorPagina) {
        system("cls");
        if (listaReservas->isEmpty()) {
            cout << "No hay reservas.\n\n";
            return;
        }

        int totalPaginas = (listaReservas->getLongitud() + elementosPorPagina - 1) / elementosPorPagina;
        int paginaActual = 0;
        char opcion;

        do {
            system("cls");
            cout << "Lista de reservas - Pagina " << paginaActual + 1 << " de " << totalPaginas << ":\n";
            cout << "ID\tCliente\t\tHabitacion\tFechas de reserva\n";

            int inicio = paginaActual * elementosPorPagina;
            int fin = min(inicio + elementosPorPagina, (int)listaReservas->getLongitud());

            for (int i = inicio; i < fin; ++i) {
                Reserva* reserva = listaReservas->obtenerPos(i);
                cout << reserva->getId() << "\t"
                    << reserva->getNombreCliente() << ", " << reserva->getApellidoCliente() << "\t"
                    << reserva->getNumHabitacion() << "\t\t"
                    << reserva->getFechaInicio() << " - " << reserva->getFechaFin() << endl;
                cout << "_______________________________________________________________________________\n";
            }

            cout << "n: Siguiente pagina, p: Pagina anterior, q: Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            if (opcion == 'n' && paginaActual < totalPaginas - 1) {
                paginaActual++;
            }
            else if (opcion == 'p' && paginaActual > 0) {
                paginaActual--;
            }
            else if (opcion != 'q') {
                cout << "Opcion no valida.\n";
            }
        } while (opcion != 'q');
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
        cout << "6. Ver Tarifa" << endl;
        cout << "7. Salir" << endl;
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
            //ordenarHabitaciones(listaH);
            system("cls");
            mostrarHabitacionesPaginado(listaH, 10);
            break;
        case 2: // AGREGAR RESERVAS - HECHA
            reservarHabitacion(listaR, listaH, nombreCliente, apellidoCliente);
            guardarDatos(listaC, listaH, listaR);
            break;
        case 3: // VER RESERVAS - HECHA
            system("cls");
            mostrarReservasPaginado(listaR, 10);
            break;
        case 4: // MODIFICAR RESERVA - HECHA
            modificarReserva(listaR);
            guardarDatos(listaC, listaH, listaR);
            break;
        case 5: // ELIMINAR RESERVA - HECHA
            cancelarReserva(listaR, listaH);
            guardarDatos(listaC, listaH, listaR);
            break;
        case 6: // VER TARIFA
            cout << "Funcion para ver las tarifas" << endl;
            break;
        case 7: // SALIR DEL PROGRAMA
            guardarDatos(listaC, listaH, listaR);
            exit(0);
            break;
        default:
            cout << "Opcion no valida. Por favor, ingrese un numero del 1 al 7." << endl;
            break;
        }

        limpiarConsola();
    }

    bool archivoExiste(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
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
        ifstream archivoClientes("clientes.txt");
        bool clientesRegistrados = archivoClientes.good();
        archivoClientes.close();

        // Verificar si el archivo de habitaciones existe y cargarlas si es asi
        ifstream archivoHabitaciones("habitaciones.txt");
        bool habitacionesCreadas = archivoHabitaciones.good();
        archivoHabitaciones.close();

        // Verificar si el archivo de reservas existe y cargarlas si es asi
        ifstream archivoReservas("reservas.txt");
        bool reservasCargadas = archivoReservas.good();
        archivoReservas.close();

        // Si el archivo de clientes no existe, se mostrara el menu de registro
        if (!clientesRegistrados) {
            while (true) {
                menuRegistro();
                clientesRegistrados = manejarMenuRegistro(listaClientes, listaHabitaciones, listaReservas);
                system("cls");
                if (clientesRegistrados) break;
            }
        }

        // Si el archivo de habitaciones no existe, se crearan las habitaciones
        if (!habitacionesCreadas) {
            crearHabitaciones(listaHabitaciones);
        }

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
