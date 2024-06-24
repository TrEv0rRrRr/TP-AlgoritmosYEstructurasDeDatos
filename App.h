#pragma once
#include "Cliente.h"
#include "ListaClientes.h"
#include "Habitacion.h"
#include "ListaHabitaciones.h"
#include "Reserva.h"
#include "ColaReservas.h"
#include "Factura.h"

class App
{
private:
    ListaClientes<Cliente*>* listaClientes = new ListaClientes<Cliente*>();
    ListaHabitaciones<Habitacion*>* listaHabitaciones = new ListaHabitaciones<Habitacion*>();
    ColaReservas<Reserva*>* colaReservas = new ColaReservas<Reserva*>();
    bool habitacionesCargadas = false;
    Factura* facturaPendiente = new Factura();

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
                    << cliente->getDNI() << endl;
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
                string nombre, apellido, correo, dni;
                getline(ss, nombre, ',');
                getline(ss, apellido, ',');
                getline(ss, correo, ',');
                getline(ss, dni, ',');
                Cliente* cliente = new Cliente();
                cliente->setNombre(nombre);
                cliente->setApellido(apellido);
                cliente->setCorreo(correo);
                cliente->setDNI(dni);
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

        string nombre, apellido, correo, dni;

        cout << "Ingrese su nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingrese su apellido: ";
        getline(cin, apellido);
        cout << "Ingrese su correo: ";
        getline(cin, correo);
        cout << "Ingrese su DNI: ";
        getline(cin, dni);

        c->setNombre(nombre);
        c->setApellido(apellido);
        c->setCorreo(correo);
        c->setDNI(dni);

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
                    << habitacion->getPrecio() << ","
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
                    string numHab, numPiso, tipo, precio;
                    int disponible;
                    getline(ss, numPiso, ',');
                    getline(ss, numHab, ',');
                    getline(ss, tipo, ',');
                    getline(ss, precio, ',');
                    ss >> disponible;

                    int numPisoInt = stoi(numPiso);
                    int numHabInt = stoi(numHab);
                    int precioInt = stoi(precio);
                    bool disponibilidad = (disponible == 1);

                    Habitacion* habitacion = new Habitacion();
                    habitacion->setNumPiso(numPisoInt);
                    habitacion->setNumHab(numHabInt);
                    habitacion->setTipo(tipo);
                    habitacion->setPrecio(precioInt);
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
            cout << "Num. Piso\tNum. Habitacion\t\tTipo de habitacion\t\tDisponibilidad\t\tPrecio\n";
            for (uint i = indice; i < lista->getLongitud() && i < indice + elementosPorPagina; ++i) {
                Habitacion* habitacion = lista->obtenerPos(i);
                cout << "    " << habitacion->getNumPiso() << "\t\t      " << habitacion->getNumHab() << "\t\t\t" << habitacion->getTipo() << "\t\t\t      " << (habitacion->getDisponibilidad() ? "Si" : "No") << "\t\t $" << habitacion->getPrecio() << "\n\n";
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
        else imprimirHabitacionesPaginadas(lista, 0, 1, 10);
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
                if (habitacion->getTipo() == "I") habitacion->setPrecio(20);
                else if (habitacion->getTipo() == "D") habitacion->setPrecio(50);
                else habitacion->setPrecio(100);
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
                archivo << reserva->getId() << "," << reserva->getNombreCliente() << "," << reserva->getApellidoCliente() << "," << reserva->getNumHabitacion() << "," << reserva->getPrecio() << "," << reserva->getFechaInicio() << "," << reserva->getFechaFin() << endl;
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
                string nombreCliente, apellidoCliente, fechaInicio, fechaFin, id, numHabitacion, precio;
                getline(ss, id, ',');
                getline(ss, nombreCliente, ',');
                getline(ss, apellidoCliente, ',');
                getline(ss, numHabitacion, ',');
                getline(ss, precio, ',');
                getline(ss, fechaInicio, ',');
                getline(ss, fechaFin, ',');

                // Convertir cadenas numericas a enteros
                int numHabInt = stoi(numHabitacion);
                int idInt = stoi(id);
                int precioInt = stoi(precio);

                // Crear objeto Habitacion y agregarlo a la lista
                Reserva* reserva = new Reserva();
                reserva->setId(idInt);
                reserva->setNombreCliente(nombreCliente);
                reserva->setApellidoCliente(apellidoCliente);
                reserva->setNumHabitacion(numHabInt);
                reserva->setPrecio(precioInt);
                reserva->setFechaInicio(fechaInicio);
                reserva->setFechaFin(fechaFin);
                cola->encolar(reserva);
            }
            archivo.close();
        }
    }

    void reservarHabitacion(ColaReservas<Reserva*>* colaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones, string& nombreCliente, string& apellidoCliente) {
        string fInicio, fFinal;
        int numH, precio;
        if (!facturaPendiente->getPagada()) {
            cout << "No puede reservar otra habitacion hasta que pague la factura pendiente." << endl;
            return;
        }
        else {
            cout << "Ingrese el numero de habitacion que quiere reservar: ";
            cin >> numH;

            Habitacion* habitacion = listaHabitaciones->buscarHabitacion(numH);
            if (habitacion != nullptr) {
                if (habitacion->getDisponibilidad()) {
                    precio = habitacion->getPrecio();
                    cout << "Habitacion disponible para reservar." << endl;

                    cout << "Ingrese la fecha de inicio (dd/mm/aaaa): ";
                    cin.ignore();
                    getline(cin, fInicio);
                    cout << "Ingrese la fecha de salida (dd/mm/aaaa): ";
                    getline(cin, fFinal);

                    int idReserva = generarIdReserva();
                    cout << "ID generada: " << idReserva << endl;

                    cout << "Costo de la reserva: $" << precio << endl;

                    Reserva* reserva = new Reserva();
                    reserva->setNombreCliente(nombreCliente);
                    reserva->setApellidoCliente(apellidoCliente);
                    reserva->setNumHabitacion(numH);
                    reserva->setFechaInicio(fInicio);
                    reserva->setFechaFin(fFinal);
                    reserva->setId(idReserva);
                    reserva->setPrecio(precio);

                    colaReservas->encolar(reserva);

                    habitacion->setDisponibilidad(false);

                    facturaPendiente->setIdFactura(generarIdFactura());
                    facturaPendiente->setNombreCliente(nombreCliente);
                    facturaPendiente->setApellidoCliente(apellidoCliente);
                    facturaPendiente->setTotal(precio);
                    facturaPendiente->setPagada(false);
                    cout << "Reserva realizada con exito.\n\n";
                }
                else cout << "La habitacion no esta disponible para reservar.\n\n";
            }
            else cout << "La habitacion no se encontro.\n\n";
        }
    }

    void modificarReserva(ColaReservas<Reserva*>* colaReservas, ListaHabitaciones<Habitacion*>* listaHabitaciones) {
        if (colaReservas->estaVacia()) return;
        else {
            int idReserva;
            cout << "Ingrese el ID de la reserva: ";
            cin >> idReserva;
            Reserva* reserva = colaReservas->buscarReserva(idReserva);

            if (reserva == nullptr) {
                cout << "No se encontro la reserva con el ID " << idReserva << ".\n";
                return;
            }
            else {
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
            }
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

    void manejarFacturacion() {
        if (!facturaPendiente->getPagada()) {
            cout << "Tienes una factura pendiente:" << endl;
            facturaPendiente->mostrarFactura();

            char opcion;
            cout << "Desea pagar la factura ahora? (S/N): ";
            cin >> opcion;

            if (opcion == 'S' || opcion == 's') {
                cout << "Procesando pago...\n";
                facturaPendiente->setPagada(true);
                cout << "Pago realizado con exito. La factura ha sido pagada.\n";
            }
            else cout << "No se ha realizado el pago. La factura sigue pendiente." << endl;
        }
        else cout << "No tienes facturas pendientes." << endl;
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

    void menuRegistro(int opcionSeleccionada) {
        system("cls");
        resetConsoleColor();
        cout << "Bienvenido al sistema de gestion de reservas de hotel" << endl;
        cout << "--------------------------------------------------" << endl;
        setConsoleColor(0, opcionSeleccionada == 1 ? 10 : 15); // Verde si esta seleccionado, blanco si no
        cout << "1. Registrarse" << endl;
        setConsoleColor(0, opcionSeleccionada == 2 ? 10 : 15); // Verde si esta seleccionado, blanco si no
        cout << "2. Salir" << endl;
        resetConsoleColor();
    }

    bool manejarMenuRegistro(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ColaReservas<Reserva*>* colaR) {
        int opcionSeleccionada = 1;
        int key;

        while (true) {
            menuRegistro(opcionSeleccionada);
            key = _getch();

            if (key == 224) {
                switch (_getch()) {
                case 72:
                    if (opcionSeleccionada > 1) opcionSeleccionada--;
                    break;
                case 80:
                    if (opcionSeleccionada < 2) opcionSeleccionada++;
                    break;
                }
            }
            else if (key == 13) {
                switch (opcionSeleccionada) {
                case 1: // REGISTRARSE
                    system("cls");
                    registrarCliente(listaC);
                    guardarClientes(listaC, "clientes.txt");
                    limpiarConsola();
                    return true;
                case 2: // SALIR DEL PROGRAMA
                    guardarDatos(listaC, listaH, colaR);
                    exit(0);
                }
            }
        }
    }

    void menuPrincipal(int opcionSeleccionada) {
        system("cls");
        resetConsoleColor();
        cout << "Bienvenido al sistema de gestion de reservas de hotel" << endl;
        cout << "--------------------------------------------------" << endl;
        setConsoleColor(0, opcionSeleccionada == 1 ? 10 : 15);
        cout << "1. Ver disponibilidad de habitaciones" << endl;
        setConsoleColor(0, opcionSeleccionada == 2 ? 10 : 15);
        cout << "2. Realizar una nueva reserva" << endl;
        setConsoleColor(0, opcionSeleccionada == 3 ? 10 : 15);
        cout << "3. Ver reservas" << endl;
        setConsoleColor(0, opcionSeleccionada == 4 ? 10 : 15);
        cout << "4. Modificar una reserva" << endl;
        setConsoleColor(0, opcionSeleccionada == 5 ? 10 : 15);
        cout << "5. Cancelar una reserva" << endl;
        setConsoleColor(0, opcionSeleccionada == 6 ? 10 : 15);
        cout << "6. Facturacion" << endl;
        setConsoleColor(0, opcionSeleccionada == 7 ? 10 : 15);
        cout << "7. Salir" << endl;
        resetConsoleColor();
    }

    void manejarMenuPrincipal(ListaClientes<Cliente*>* listaC, ListaHabitaciones<Habitacion*>* listaH, ColaReservas<Reserva*>* colaR) {
        pair<string, string> datosCliente = cargarClientes(listaC, "clientes.txt");
        string nombreCliente = datosCliente.first;
        string apellidoCliente = datosCliente.second;

        int opcionSeleccionada = 1;
        int key;

        while (true) {
            menuPrincipal(opcionSeleccionada);
            key = _getch();

            if (key == 224) {
                switch (_getch()) {
                case 72:
                    if (opcionSeleccionada > 1) opcionSeleccionada--;
                    break;
                case 80:
                    if (opcionSeleccionada < 7) opcionSeleccionada++;
                    break;
                }
            }
            else if (key == 13) {
                switch (opcionSeleccionada) {
                case 1: // HABITACIONES DISPONIBLES
                    system("cls");
                    ordenarHabitaciones(listaH);
                    mostrarHabitaciones(listaH);
                    limpiarConsola();
                    break;
                case 2: // AGREGAR RESERVAS
                    system("cls");
                    reservarHabitacion(colaR, listaH, nombreCliente, apellidoCliente);
                    limpiarConsola();
                    break;
                case 3: // VER RESERVAS
                    system("cls");
                    mostrarReservas(colaR);
                    limpiarConsola();
                    break;
                case 4: // MODIFICAR RESERVA
                    system("cls");
                    mostrarReservas(colaR, false);
                    cout << "\n\n";
                    modificarReserva(colaR, listaH);
                    limpiarConsola();
                    break;
                case 5: // ELIMINAR RESERVA
                    system("cls");
                    mostrarReservas(colaR, false);
                    cout << "\n\n";
                    cancelarReserva(colaR, listaH);
                    limpiarConsola();
                    break;
                case 6: // MOSTRAR FACTURA
                    system("cls");
                    manejarFacturacion();
                    limpiarConsola();
                    break;
                case 7: // SALIR DEL PROGRAMA
                    guardarDatos(listaC, listaH, colaR);
                    exit(0);
                }
            }
            else if (key == 27) break;
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
                Console::CursorVisible = false;
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
            Console::CursorVisible = false;
            manejarMenuPrincipal(listaClientes, listaHabitaciones, colaReservas); 
        }
    }
};

App::App() {}

App::~App() { delete listaClientes; delete listaHabitaciones; }
