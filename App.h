#pragma once
#include "Cliente.h"
#include "ListaClientes.h"
#include "Habitacion.h"
#include "ListaHabitaciones.h"
#include "Reserva.h"
#include "ColaReservas.h"

class App
{
private:
    ListaClientes<Cliente*>* listaClientes = new ListaClientes<Cliente*>();
    ListaHabitaciones<Habitacion*>* listaHabitaciones = new ListaHabitaciones<Habitacion*>();
    ColaReservas<Reserva*>* colaReservas = new ColaReservas<Reserva*>();
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
        return make_pair(nombreRegistrado, apellidoRegistrado);
    }

    void registrarCliente(ListaClientes<Cliente*>* lista) {
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
                    getline(ss, numPiso, ',');
                    getline(ss, numHab, ',');
                    getline(ss, tipo, ',');
                    ss >> disponible;

                    int numPisoInt = stoi(numPiso);
                    int numHabInt = stoi(numHab);
                    bool disponibilidad = (disponible == 1);

                    Habitacion* habitacion = new Habitacion();
                    habitacion->setNumPiso(numPisoInt);
                    habitacion->setNumHab(numHabInt);
                    habitacion->setTipo(tipo);
                    habitacion->setDisponibilidad(disponibilidad);
                    lista->agregarHabitacion(habitacion);
                }
                archivo.close();
                habitacionesCargadas = true;
            }
        }
    }

    void imprimirHabitacionesPaginadas(ListaHabitaciones<Habitacion*>* lista, uint indice, uint pagina, uint elementosPorPagina) {
        system("cls");
        uint totalPaginas = (lista->getLongitud() + elementosPorPagina - 1) / elementosPorPagina;
     
        if (indice < lista->getLongitud()) {
            cout << "Lista de habitaciones:\n";
            cout << "I: Individual\tS: Suite:\tD: Doble\n\n";
            cout << "Num. Piso\tNum. Habitacion\t\tTipo de habitacion\t\tDisponibilidad\n";
            for (uint i = indice; i < lista->getLongitud() && i < indice + elementosPorPagina; ++i) {
                Habitacion* habitacion = lista->obtenerPos(i);
                cout << "    " << habitacion->getNumPiso() << "\t\t      " << habitacion->getNumHab() << "\t\t\t" << habitacion->getTipo() << "\t\t\t      " << (habitacion->getDisponibilidad() ? "Si" : "No") << "\n\n";
            }
        }

        cout << "\nPagina " << pagina << " de " << totalPaginas << "\n";
        cout << "Presione 'N' para la siguiente pagina, 'P' para la pagina anterior, 'M' para el menu principal.\n";

        char tecla = _getch();
        if (tecla == 'N' || tecla == 'n') {
            if (pagina < totalPaginas) imprimirHabitacionesPaginadas(lista, indice + elementosPorPagina, pagina + 1, elementosPorPagina);
            else imprimirHabitacionesPaginadas(lista, indice, pagina, elementosPorPagina);
        }
        else if (tecla == 'P' || tecla == 'p') {
            if (pagina > 1) imprimirHabitacionesPaginadas(lista, indice - elementosPorPagina, pagina - 1, elementosPorPagina);
            else imprimirHabitacionesPaginadas(lista, indice, pagina, elementosPorPagina);
        }
        else if (tecla == 'M' || tecla == 'm') return;
        else imprimirHabitacionesPaginadas(lista, indice, pagina, elementosPorPagina);
    }

    void mostrarHabitaciones(ListaHabitaciones<Habitacion*>* lista) {
        if (lista->isEmpty()) {
            setConsoleColor(4, 15); // Red background, white text
            cout << "No hay habitaciones.\n\n";
            resetConsoleColor();
        }
        else {
            imprimirHabitacionesPaginadas(lista, 0, 1, 10);
        }
    }

    void crearHabitaciones(ListaHabitaciones<Habitacion*>* lista) {
        const int NUM_PISOS = 2;
        const int HABITACIONES_POR_PISO = 10;

        string tipos[] = { "I", "D", "S" };

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

    // -------------- ORDENAMIENTO PARA HABITACIONES --------------

    void quicksort(ListaHabitaciones<Habitacion*>* lista, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(lista, low, high);
            quicksort(lista, low, pivotIndex - 1);
            quicksort(lista, pivotIndex + 1, high);
        }
    }

    int partition(ListaHabitaciones<Habitacion*>* lista, int low, int high) {
        Habitacion* pivot = lista->obtenerPos(high);
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (lista->obtenerPos(j)->getNumHab() < pivot->getNumHab()) {
                ++i;
                lista->intercambiar(i, j);
            }
        }
        lista->intercambiar(i + 1, high);
        return i + 1;
    }

    void ordenarHabitaciones(ListaHabitaciones<Habitacion*>* lista) {
        int longitud = lista->getLongitud();
        if (longitud > 1) {
            quicksort(lista, 0, longitud - 1);
        }
    }

    // -------------- FUNCIONES PARA RESERVAS --------------

    void guardarReservas(ColaReservas<Reserva*>* cola, const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            for (uint i = 0; i < cola->obtenerLongitud(); ++i) {
                Reserva* reserva = cola->obtenerPos(i);
                archivo << reserva->getId() << "," << reserva->getNombreCliente() << "," << reserva->getApellidoCliente() << "," << reserva->getNumHabitacion() << "," << reserva->getFechaInicio() << "," << reserva->getFechaFin() << endl;
            }
            archivo.close();
        }
    }

    void cargarReservas(ColaReservas<Reserva*>* cola, const string& nombreArchivo) {
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
                cola->encolar(reserva);
            }
            archivo.close();
        }
    }

    void reservarHabitacion(ColaReservas<Reserva*>* colaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones, string& nombreCliente, string& apellidoCliente) {
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

                colaReservas->encolar(reserva);

                habitacion->setDisponibilidad(false);

                cout << "Reserva realizada con exito.\n\n";
            }
            else cout << "La habitacion no esta disponible para reservar.\n\n";
        }
        else cout << "La habitacion no se encontro.\n\n";
    }

    void modificarReserva(ColaReservas<Reserva*>* colaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones) {
        if (colaReservas->estaVacia()) return;
        else {
            int idReserva;
            cout << "Ingrese el ID de la reserva: ";
            cin >> idReserva;
            Reserva* reserva = colaReservas->buscarReserva(idReserva);

            if (reserva != nullptr) {
                int opt;
                cout << "Reserva encontrada! Que desea modificar?" << endl;
                cout << "1: Numero de habitacion" << endl;
                cout << "2: Fecha de inicio" << endl;
                cout << "3: Fecha de salida" << endl;
                cout << "4: Ambas fechas" << endl;
                cout << "5: Todos los datos" << endl;
                cout << "6: No modificar nada" << endl;
                cout << "Ingrese una opcion: ";
                cin >> opt;

                switch (opt) {
                case 1:
                {
                    int numH;
                    cout << "Ingrese el numero de la nueva habitacion: ";
                    cin >> numH;

                    Habitacion* habitacionActual = listaHabitaciones->buscarHabitacion(reserva->getNumHabitacion());
                    if (habitacionActual != nullptr) {
                        habitacionActual->setDisponibilidad(true);
                    }

                    Habitacion* nuevaHabitacion = listaHabitaciones->buscarHabitacion(numH);
                    if (nuevaHabitacion != nullptr && nuevaHabitacion->getDisponibilidad()) {
                        nuevaHabitacion->setDisponibilidad(false);
                        reserva->setNumHabitacion(numH);
                        cout << "Numero de habitacion actualizado.\n" << "Reserva modificada correctamente!\n";
                    }
                    else cout << "La nueva habitacion no esta disponible." << endl;
                    break;
                }
                case 2:
                {
                    string fechaInicio;
                    cout << "Ingrese la nueva fecha de inicio (dd/mm/aaaa): ";
                    cin.ignore();
                    getline(cin, fechaInicio);
                    reserva->setFechaInicio(fechaInicio);
                    cout << "Reserva modificada correctamente!\n";
                    break;
                }
                case 3:
                {
                    string fechaFinal;
                    cout << "Ingrese la nueva fecha de salida (dd/mm/aaaa): ";
                    cin.ignore();
                    getline(cin, fechaFinal);
                    reserva->setFechaFin(fechaFinal);
                    cout << "Reserva modificada correctamente!\n";
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
                    cout << "Reserva modificada correctamente!\n";
                    break;
                }
                case 5:
                {
                    int numH;
                    string fechaInicio, fechaFinal;

                    cout << "Ingrese el numero de la nueva habitacion: ";
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
                        cout << "Numero de habitacion actualizado." << endl;
                    }
                    else cout << "La nueva habitacion no esta disponible." << endl;

                    cout << "Ingrese la nueva fecha de inicio (dd/mm/aaaa): ";
                    getline(cin, fechaInicio);
                    cout << "Ingrese la nueva fecha de salida (dd/mm/aaaa): ";
                    getline(cin, fechaFinal);

                    reserva->setFechaInicio(fechaInicio);
                    reserva->setFechaFin(fechaFinal);
                    cout << "Reserva modificada correctamente!\n";
                    break;
                }
                case 6:
                    return;
                default:
                    cout << "Opcion no valida." << endl;
                    break;
                }

                guardarReservas(colaReservas, "reservas.txt");
                guardarHabitaciones(listaHabitaciones, "habitaciones.txt");
            }
            else cout << "Reserva no encontrada." << endl;
        }
    }

    void cancelarReserva(ColaReservas<Reserva*>* colaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones) {
        if (colaReservas->estaVacia()) return;
        else {
            int idReserva;
            cout << "Ingrese el ID de la reserva que desea cancelar: ";
            cin >> idReserva;

            Reserva* reserva = colaReservas->buscarReserva(idReserva);

            if (reserva != nullptr) {
                int numHabitacion = reserva->getNumHabitacion();

                Habitacion* habitacion = listaHabitaciones->buscarHabitacion(numHabitacion);
                if (habitacion != nullptr) {
                    habitacion->setDisponibilidad(true);
                    colaReservas->eliminarReserva(idReserva);
                    cout << "Reserva cancelada con exito!\n\n";
                }
                else cout << "No se encontro la habitacion asociada a la reserva.\n\n";
            }
            else cout << "No se encontro ninguna reserva con el ID proporcionado.\n\n";
        }
    }

    void mostrarReservas(ColaReservas<Reserva*>* cola, bool paginacion = true) {
        if (cola->estaVacia()) {
            setConsoleColor(4, 15); // Red background, white text
            cout << "No hay reservas.\n\n";
            resetConsoleColor();
        }
        else cola->imprimirCola(1, paginacion);
    }

    // -------------- FUNCIONES PRINCIPALES --------------

    void cargarDatos(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ColaReservas<Reserva*>* colaR) {
        cargarHabitaciones(listaH, "habitaciones.txt");
        cargarReservas(colaR, "reservas.txt");
        cargarClientes(listaC, "clientes.txt");
    }

    void guardarDatos(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ColaReservas<Reserva*>* colaR) {
        guardarHabitaciones(listaH, "habitaciones.txt");
        guardarReservas(colaR, "reservas.txt");
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

    bool manejarMenuRegistro(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ColaReservas<Reserva*>* colaR) {
        int opt;
        cin >> opt;
        switch (opt) {
        case 1: // REGISTRARSE
            registrarCliente(listaC);
            return true;
            break;
        case 2: // SALIR DEL PROGRAMA
            guardarDatos(listaC, listaH, colaR);
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

    void manejarMenuPrincipal(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ColaReservas<Reserva*>* colaR) {

        pair<string, string> datosCliente = cargarClientes(listaC, "clientes.txt");
        string nombreCliente = datosCliente.first;
        string apellidoCliente = datosCliente.second;

        int opt;
        cin >> opt;
        switch (opt) {
        case 1: // HABITACIONES DISPONIBLES - HECHA
            system("cls");
            ordenarHabitaciones(listaH);
            mostrarHabitaciones(listaH);
            limpiarConsola();
            break;
        case 2: // AGREGAR RESERVAS - HECHA
            system("cls");
            reservarHabitacion(colaR, listaH, nombreCliente, apellidoCliente);
            limpiarConsola();
            break;
        case 3: // VER RESERVAS - HECHA
            system("cls");
            mostrarReservas(colaR);
            limpiarConsola();
            break;
        case 4: // MODIFICAR RESERVA - HECHA
            system("cls");
            mostrarReservas(colaR, false);
            cout << "\n\n";
            modificarReserva(colaR, listaH);
            limpiarConsola();
            break;
        case 5: // ELIMINAR RESERVA - HECHA
            system("cls");
            mostrarReservas(colaR, false);
            cout << "\n\n";
            cancelarReserva(colaR, listaH);
            limpiarConsola();
            break;
        case 6: // SALIR DEL PROGRAMA
            guardarDatos(listaC, listaH, colaR);
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

    void setConsoleColor(int background, int foreground) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (background << 4) | foreground);
    }

    void resetConsoleColor() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15); // White text on black background
    }

    void run() {
        cargarHabitaciones(listaHabitaciones, "habitaciones.txt");
        cargarReservas(colaReservas, "reservas.txt");
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
                clientesRegistrados = manejarMenuRegistro(listaClientes, listaHabitaciones, colaReservas);
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
            manejarMenuPrincipal(listaClientes, listaHabitaciones, colaReservas);
        }
    }
};

App::App() {}

App::~App() { delete listaClientes; delete listaHabitaciones; }
