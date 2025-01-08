#include <iostream>
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

bool ValidarCliente(Cliente &cliente, const char username[50], const char clave[50]);
void AgregarTransaccion(Cliente &cliente);
void EliminarTransaccionPorId(int id);

int main() {
    Cliente c;
    char username[50];
    char clave[50]; 
    int opcion;

    cout << "Ingrese username: ";
    cin.getline(username, 50);
    cout << "Ingrese clave: ";
    cin.getline(clave, 50);

    if (!ValidarCliente(c, username, clave)) {
        cout << "El usuario o la clave es incorrecta" << endl;
        return 0;
    }

    cout << "Su saldo es: $" << c.saldo << endl;
     do {
        cout << "\n1. Agregar Transacción" << endl;
        cout << "2. Eliminar Transacción por ID" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1:
                AgregarTransaccion(c);
                break;
            
            case 2:
                int id;
                cout << "Ingrese el ID de la transacción a eliminar: ";
                cin >> id;
                cin.ignore();
                EliminarTransaccionPorId(id);
                break;

            case 3:
                cout << "Gracias por usar el sistema. ¡Hasta luego!" << endl;
                break;

            default:
                cout << "Opción inválida. Intente de nuevo" << endl;
        }
    } while (opcion != 3);
   

    return 0;
}

bool ValidarCliente(Cliente &cliente, const char username[50], const char clave[50]) {
    FILE* archivoClientes = fopen("clientes.dat", "rb");
    if (archivoClientes == NULL) {
        cout << "No se pudo abrir el archivo de clientes." << endl;
        return false;
    }

    Cliente temp;
    while (fread(&temp, sizeof(Cliente), 1, archivoClientes) == 1) {
        if (strcmp(temp.username, username) == 0 && strcmp(temp.clave, clave) == 0) {
            cliente = temp;
            fclose(archivoClientes);
            return true;
        }
    }

    fclose(archivoClientes);
    return false;
}
void AgregarTransaccion(Cliente &cliente) {
    FILE* archivoTransacciones = fopen("transacciones.dat", "rb+");
    if (archivoTransacciones == NULL) {
        cout << "No se pudo abrir el archivo de transacciones" << endl;
        return;
    }

    Transaccion ultimaTransaccion;
    int ultimoId = 0;

    // Buscar el ID más alto
    while (fread(&ultimaTransaccion, sizeof(Transaccion), 1, archivoTransacciones) == 1) {
        if (ultimaTransaccion.id > ultimoId) {
            ultimoId = ultimaTransaccion.id;
        }
    }

    Transaccion nuevaTransaccion;
    nuevaTransaccion.id = ultimoId + 1;
    nuevaTransaccion.cliente = cliente;

    cout << "Ingrese el monto: ";
    cin >> nuevaTransaccion.monto;
    if (nuevaTransaccion.monto <= 0) {
        cout << "El monto debe ser mayor que cero" << endl;
        fclose(archivoTransacciones);
        return;
    }
    cin.ignore();

    cout << "Ingrese la fecha (DD-MM-AAAA): ";
    cin.getline(nuevaTransaccion.fecha, 11);

    cout << "Ingrese el tipo (I para ingreso, E para egreso): ";
    cin.getline(nuevaTransaccion.tipo, 10);

    if (strcmp(nuevaTransaccion.tipo, "I") == 0) {
        cliente.saldo += nuevaTransaccion.monto;
    } else if (strcmp(nuevaTransaccion.tipo, "E") == 0) {
        if (cliente.saldo >= nuevaTransaccion.monto) {
            cliente.saldo -= nuevaTransaccion.monto;
        } else {
            cout << "Saldo insuficiente para realizar esta transacción" << endl;
            fclose(archivoTransacciones);
            return;
        }
    } else {
        cout << "Tipo de transacción inválido" << endl;
        fclose(archivoTransacciones);
        return;
    }

    fseek(archivoTransacciones, 0, SEEK_END);
    fwrite(&nuevaTransaccion, sizeof(Transaccion), 1, archivoTransacciones);
    fclose(archivoTransacciones);
}

void EliminarTransaccionPorId(int id) {
    FILE* archivoTransacciones = fopen("transacciones.dat", "rb");
    if (archivoTransacciones == NULL) {
        cout << "No se pudo abrir el archivo de transacciones." << endl;
        return;
    }
    FILE* archivoTemp = fopen("temp.dat", "a+");
    FILE* archivoTemp2 = fopen("temp2.dat", "a+");
    
    Transaccion transaccion;
    bool encontrado = false;
    while (fread(&transaccion, sizeof(Transaccion), 1, archivoTransacciones) == 1) {
        if (transaccion.id != id) {
            fwrite(&transaccion, sizeof(Transaccion), 1, archivoTemp);
        } else {
            fwrite(&transaccion, sizeof(Transaccion), 1, archivoTemp2);
            encontrado = true; // Marcamos que encontramos la transacción.
        }
    }

    fclose(archivoTransacciones);
    fclose(archivoTemp);
    fclose(archivoTemp2);

    if (encontrado) {
        FILE* archivoTransacciones = fopen("transacciones.dat", "wb");
        FILE* archivoTemp = fopen("temp.dat", "rb");

        if (archivoTemp == NULL) {
            cout << "No se pudo sobrescribir el archivo de transacciones." << endl;
            return;
        }

        while (fread(&transaccion, sizeof(Transaccion), 1, archivoTemp) == 1) {
            fwrite(&transaccion, sizeof(Transaccion), 1, archivoTransacciones);
        }

        fclose(archivoTransacciones);
        fclose(archivoTemp);
        cout << "Transacción eliminada con éxito." << endl;
    } else {
        cout << "No se encontró una transacción con el ID especificado." << endl;
    }
}