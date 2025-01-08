#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Cliente {                      
    char nombre[50];
    char username[50];
    int dni; 
    char clave[50]; 
    float saldo;
};

struct Transaccion {
    int id;
    Cliente cliente;  
    float monto;
    char fecha[11];  // DD-MM-AAAA
    char tipo[10];   // "I" para ingreso, "E" para egreso
};


// funciones analista de transacciones
void listarTransacciones(int dni) {
    FILE* archivo = fopen("transacciones.dat", "rb");
    if (archivo != NULL) {
        Transaccion transaccion;
        int contador = 0;
        while (fread(&transaccion, sizeof(Transaccion), 1, archivo) == 1) {
            if (transaccion.cliente.dni == dni) {
                cout << "ID: " << transaccion.id << ", Fecha: " << transaccion.fecha 
                     << ", Monto: " << transaccion.monto << ", Tipo: " << transaccion.tipo << endl;
                contador++;
                if (contador % 5 == 0) {
                    cout << "Enter para continuar";
                    cin.ignore();
                    cin.get();
                }
            }
        }
        fclose(archivo);
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}
void listarIngresosEgresosPorMes(int dni, const char* mesAnio) {
    FILE* archivo = fopen("transacciones.dat", "rb");
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    Transaccion transaccion;
    float ingresos = 0, egresos = 0;

    while (fread(&transaccion, sizeof(Transaccion), 1, archivo)) {
        if (transaccion.cliente.dni == dni && strncmp(transaccion.fecha + 3, mesAnio, 7) == 0) {
            if (transaccion.tipo[0] == 'I') ingresos += transaccion.monto;
            else if (transaccion.tipo[0] == 'E') egresos += transaccion.monto;
        }
    }

    fclose(archivo);
    cout << "Ingresos en " << mesAnio << ": " << ingresos << endl;
    cout << "Egresos en " << mesAnio << ": " << egresos << endl;
}
void transaccionMaxima() {
    FILE* archivo = fopen("transacciones.dat", "rb");
    if (archivo != NULL) {
        Transaccion transaccion;
        Transaccion maxTransaccion;
        maxTransaccion.monto = 0;
        while (fread(&transaccion, sizeof(Transaccion), 1, archivo) == 1) {
            if (transaccion.monto > maxTransaccion.monto) {
                maxTransaccion = transaccion;
            }
        }
        fclose(archivo);
        if (maxTransaccion.monto > 0) {
            cout << "Transaccion de mayor monto:\n";
            cout << "Cliente DNI: " << maxTransaccion.cliente.dni << ", Fecha: " 
                 << maxTransaccion.fecha << ", Monto: " << maxTransaccion.monto << endl;
        } else {
            cout << "No se encontraron transacciones.\n";
        }
    } else {
        cout << "Error al abrir el archivo de transacciones.\n";
    }
}
void clienteConMasIngresosUltimos30Dias() {
    FILE* archivo = fopen("transacciones.dat", "rb");
    if (archivo != NULL) {
        char mesAnio[] = "10-2021";  // Fecha para los últimos 30 días
        int maxIngresos = 0;         
        int dniMaxIngresos = 0;      

        Transaccion transaccion;
        while (fread(&transaccion, sizeof(Transaccion), 1, archivo) == 1) {
            if (strncmp(transaccion.fecha + 3, mesAnio, 7) == 0 && transaccion.tipo[0] == 'I') {
                int ingresos = transaccion.monto; // sumar ingresos
                int dniActual = transaccion.cliente.dni;

                // volver a recorrer el archivo para sumar ingresos del mismo cliente
                FILE* archivoTemporal = fopen("transacciones.dat", "rb");
                if (archivoTemporal != NULL) {
                    Transaccion tempTransaccion;
                    while (fread(&tempTransaccion, sizeof(Transaccion), 1, archivoTemporal) == 1) {
                        if (tempTransaccion.cliente.dni == dniActual && strncmp(tempTransaccion.fecha + 3, mesAnio, 7) == 0 && tempTransaccion.tipo[0] == 'I') {
                            ingresos += tempTransaccion.monto;
                        }
                    }
                    fclose(archivoTemporal);
                }

                // Actualizar cliente
                if (ingresos > maxIngresos) {
                    maxIngresos = ingresos;
                    dniMaxIngresos = dniActual;
                }
            }
        }
        fclose(archivo);

        // Mostrar el cliente
        if (dniMaxIngresos > 0) {
            cout << "Cliente con mas ingresos en los ultimos 30 dias (DNI): " 
                 << dniMaxIngresos << ", Ingresos: " << maxIngresos << endl;
        } else {
            cout << "No se encontraron ingresos.\n";
        }
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}
// Función principal (main)
int main() {
    int opcion;
    int idTransaccion;
    int dni;
    char mesAnio[8];

    do {
        cout << "\n--- Menu ---\n";
         cout <<"1. Listar transacciones de un cliente\n";
        cout << "2. Listar ingresos y egresos por mes de un cliente\n";
        cout << "3. Mostrar transaccion de mayor monto\n";
        cout << "4. Mostrar cliente con mas ingresos en los ultimos 30 dias\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingrese el DNI del cliente: ";
                cin >> dni;
                listarTransacciones(dni);
                break;
            case 2:
                cout << "Ingrese el DNI del cliente: ";
                cin >> dni;
                cout << "Ingrese el mes y año (DD-MM-AAAA): ";
                cin >> mesAnio;
                listarIngresosEgresosPorMes(dni, mesAnio);
                break;

            case 3:
                transaccionMaxima();
                break;

            case 4:
                clienteConMasIngresosUltimos30Dias();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no valida, intente nuevamente." << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}