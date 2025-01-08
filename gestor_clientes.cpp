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




bool obtenerClientePorUser (char username[50]){
    FILE *archivoClientes = fopen("clientes.dat", "rb");
    if (archivoClientes == NULL) {
        cout << "No se pudo abrir el archivo de clientes." << endl;
        return false;
    }

    Cliente cliente;
    bool encontrado = false;

    while (fread(&cliente, sizeof(Cliente), 1, archivoClientes) == 1) {
        if (strcmp(username, cliente.username)==0) {
            encontrado = true;
            break;
        }
    }
    fclose(archivoClientes);
    return encontrado;
}

bool obtenerClientePorDNI(int dni) {
    FILE *archivoClientes = fopen("clientes.dat", "rb");
    if (archivoClientes == NULL) {
        cout << "No se pudo abrir el archivo de clientes." << endl;
        return false;
    }

    Cliente cliente;
    bool encontrado = false;

    while (fread(&cliente, sizeof(Cliente), 1, archivoClientes) == 1) {
        if (cliente.dni == dni) {
            encontrado = true;
            break;
        }
    }

    fclose(archivoClientes);
    return encontrado;
}

// Función para agregar un nuevo cliente
void agregarCliente() {
    FILE *archivo = fopen("clientes.dat", "ab"); //Abre el archivo y si no existe lo crea.
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo de clientes." << endl;
        return;
    }

    Cliente nuevoCliente;
    cout << "Ingrese el DNI del cliente: ";
    cin >> nuevoCliente.dni;
    if (!(obtenerClientePorDNI(nuevoCliente.dni))){
        cout << "Ingrese un nombre de usuario: " << endl;
        cin.ignore();  //limpiar el buffer de la terminal
        cin.getline(nuevoCliente.username, 50);
        while (obtenerClientePorUser(nuevoCliente.username)){
            cout << "Ese nombre de usuario ya esta en uso, por favor prueba con otro" << endl;
            cin.getline(nuevoCliente.username, 50);
        }
        cout << "Ingrese el nombre del cliente: " << endl;
        cin.ignore();  // Limpiar el buffer de entrada
        cin.getline(nuevoCliente.nombre, 50);
        cout << "Ingrese la clave del cliente: ";
        cin >> nuevoCliente.clave;
        nuevoCliente.saldo = 10000.0;  // El saldo inicial es 10000

        fwrite(&nuevoCliente, sizeof(Cliente), 1, archivo);
        fclose(archivo);

        cout << "Cliente agregado exitosamente." << endl;
    }else{
        cout << "Ese dni ya esta en uso. Por favor revise si es correcto." <<endl;
    }
}


int main(){
    int opcion;
    int dni;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Agregar cliente\n";
        cout << "2. Salir  \n"; 
        cin >> opcion;
        switch(opcion) {
            case 1:
                agregarCliente();
                break;
             case 2:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opción no valida, intente nuevamente." << endl;
                break;

          }
    } while (opcion != 2);

    return 0;
}