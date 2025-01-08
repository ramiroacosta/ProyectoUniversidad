# ProyectoUniversidad
TRABAJO PRÁCTICO GRUPAL
ALGORITMOS Y ESTRUCTURA DE DATOS
SISTEMA BANCARIO
Descripción General
El objetivo principal fue establecer un sistema bancario básico que controle a los
clientes y sus transacciones, permitiendo operaciones financieras básicas como
registrar ingresos y egresos, consultar el saldo y mostrar una lista de transacciones.
Tres componentes principales componen el sistema:
● Gestor de Clientes: El gestor de clientes permite que los nuevos clientes se
registren en el sistema.
● Gestor de Transacciones: Las transacciones financieras de los clientes se
pueden registrar y administrar con el Gestor de Transacciones.
● Analista de Transacciones: El analista de transacciones permite la consulta
de transacciones, la lista de ingresos y gastos y la recopilación de
estadísticas sobre las transacciones que realizaron los clientes.
Grupo:
Gestor de Clientes: Juan Pablo Gilette y Bruno DiGiovanni.
Gestor de Transacciones: Santiago Moretti Murillo y Uma Chertin Velasco.
Analista de Transacciones: Ramiro Acosta.
Estructura:
1. Gestor de Clientes
El Gestor de Clientes puede registrar nuevos usuarios, dandoles un saldo inicial de
$10.000. Los clientes se guardan en un archivo binario (clientes.dat) con su
información como nombre, DNI, username, clave y saldo.
Funciones Principales:
agregarCliente(): puede registrar un nuevo cliente, ingresando su nombre,
username, DNI y clave.
obtenerClientePorDNI(): Busca un cliente por su DNI adentro del archivo
clientes.dat.
2. Gestor de Transacciones
El Gestor de Transacciones maneja el registro de las transacciones (ingresos y
egresos) de cada cliente. Cada transacción tiene un ID único, un monto, una fecha,
y un tipo (ingreso o egreso).
Funciones Principales:
agregarTransaccion(): Registra una nueva transacción para un cliente, actualizando
su saldo en el archivo de clientes.
eliminarTransaccionPorID(): elimina una transacción en base a su ID.
mostrarTodasLasTransacciones(): Muestra una lista de todas las transacciones realizadas.
3. Analista de Transacciones
Esta parte realiza consultas sobre las transacciones de los clientes, como listar
transacciones ordenadas, calcular ingresos y egresos por mes, y obtener la transacción de
mayor monto.
Funciones Principales:
listarTransacciones(): Lista las transacciones de un cliente ordenadas por fecha, mostrando
5 transacciones.
listarIngresosEgresosPorMes(): Muestra la cantidad de ingresos y egresos que un cliente
tuvo en un mes específico.
transaccionMaxima(): Muestra la transacción con el monto más alto realizada por cualquier
cliente.
clienteConMasIngresosUltimos30Dias(): Identifica al cliente que ha tenido más ingresos en
los últimos 30 días.
Patrones y Algoritmos Utilizados
Estructura de Datos: Se usan estructuras struct para definir a los clientes y las
transacciones. Cada estructura se almacena de manera secuencial en archivos binarios
para facilitar el acceso y manipulación de los datos.
Escritura en Archivos Binarios: Todos los datos se manejan mediante archivos binarios
(clientes.dat y transacciones.dat), donde cada registro se guarda y se actualiza utilizando
funciones como fread() y fwrite().
