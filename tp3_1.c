#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

typedef struct Producto
{
    int ProductoID; //Numerado en ciclo iterativo
    int Cantidad; // entre 1 y 10
    char *TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
}Producto;

typedef struct Cliente
{
    int ClienteID; // Numerado en el ciclo iterativo
    char *NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    Producto *Productos; //El tamaño de este arreglo depende de la variable “CantidadProductosAPedir”
} Cliente;

//funciones
void cargarClientes(Cliente *arreglo, int cantidad);
void cargarProductos(Producto *arreglo, int cantidad);
void mostrarClientes(Cliente *arreglo, int cantidad);
void mostrarProductos(Producto *arreglo, int cantidad);
float costoTotal(float precio, int cantidad);


int main()
{
    srand(time(NULL));

    int cantClientes;
    Cliente *arregloClientes;

    printf("\n Ingrese la cantidad de clientes (max 5): ");
    scanf("%d", &cantClientes);

    arregloClientes = (Cliente*)malloc(sizeof(Cliente)*cantClientes);
    cargarClientes(arregloClientes, cantClientes); //cargo clientes y productos

    //muestro clientes y productos
    mostrarClientes(arregloClientes, cantClientes);

    // libero
    for(int i = 0; i < cantClientes; i++){
        free((arregloClientes + i)->NombreCliente);

        free((arregloClientes + i)->Productos);        
    }
    free(arregloClientes);

    return 0;
}


//funciones
void cargarClientes(Cliente *arreglo, int cantidad)
{
    int cantProductos;
    for (int i = 0; i < cantidad; i++)
    {
        (arreglo + i)->ClienteID = i;

        fflush(stdin);
        (arreglo + i)->NombreCliente = (char*)malloc(sizeof(char)*30);
        printf("\n Ingrese el nombre del Cliente N%d:\n", i);
        gets((arreglo + i)->NombreCliente);

        (arreglo + i)->CantidadProductosAPedir = rand()% 5 + 1;
        (arreglo + i)->Productos = (Producto*)malloc(sizeof(Producto)* (arreglo + i)->CantidadProductosAPedir);
        cargarProductos((arreglo + i)->Productos, (arreglo + i)->CantidadProductosAPedir);

    }

}

void cargarProductos(Producto *arreglo, int cantidad)
{
    int numProducto;
    for (int i = 0; i < cantidad; i++)
    {
        (arreglo + i)->ProductoID = i;
        (arreglo + i)->Cantidad = rand()% 10 + 1;

        numProducto = rand()% 5;
        (arreglo + i)->TipoProducto = TiposProductos[numProducto];

        (arreglo + i)->PrecioUnitario = 10 + rand()% 90;
    }
}

void mostrarClientes(Cliente *arreglo, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        printf("\n \n ##### CLIENTE NUMERO %d ##### \n", i+1);
        printf("\n ID: %d", (arreglo + i)->ClienteID);
        printf("\n Nombre: %s", (arreglo + i)->NombreCliente);
        printf("\n Cantidad de productos: %d", (arreglo + i)->CantidadProductosAPedir);
        
        mostrarProductos((arreglo + i)->Productos, (arreglo + i)->CantidadProductosAPedir);

    }
}

void mostrarProductos(Producto *arreglo, int cantidad)
{
    float totalpProducto=0, total=0;
    for (int i = 0; i < cantidad; i++)
    {
        printf("\n \n --- PRODUCTO NUMERO %d --- \n", i+1);

        printf("\n ID: %d", (arreglo + i)->ProductoID);
        printf("\n Cantidad: %d", (arreglo + i)->Cantidad);
        printf("\n Tipo: %s", (arreglo + i)->TipoProducto);
        printf("\n Precio unitario: $%.2f", (arreglo + i)->PrecioUnitario);

        totalpProducto = costoTotal((arreglo + i)->PrecioUnitario, (arreglo + i)->Cantidad);
        printf("\n Precio Total: $%.2f", totalpProducto);

        total= total + totalpProducto;
    }

    printf("\n ----------------------------");
    printf("\n TOTAL A PAGAR: $%.2f", total);
}

float costoTotal(float precio, int cantidad)
{
    return precio * cantidad;
}