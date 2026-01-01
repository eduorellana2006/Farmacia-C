#include <stdio.h>
#include <string.h>

void agregarProducto();
void realizarCompra();
void limpiarBuffer();

int main() {
    char opcion;

    do {
        printf("\n--- SISTEMA DE FARMACIA v1.1 ---");
        printf("\n1. Agregar producto");
        printf("\n2. Realizar compra");
        printf("\n3. Salir");
        printf("\nSeleccione una operacion: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case '1': agregarProducto(); break;
            case '2': realizarCompra(); break;
            case '3': printf("Saliendo del sistema...\n"); break;
            default:  printf("Opcion no valida.\n");
        }
    } while (opcion != '3');

    return 0;
}

void agregarProducto() {
    int id;
    char nombre[50];
    FILE *archivo = fopen("productos.txt", "a");

    if (archivo == NULL) {
        printf(">> Error al abrir la base de datos.\n");
        return;
    }

    printf("\n--- REGISTRO DE PRODUCTO ---");
    printf("\nID numerico: ");
    scanf(" %d", &id);
    printf("Nombre (sin espacios): ");
    scanf(" %s", nombre);

    fprintf(archivo, "%d %s\n", id, nombre);
    fclose(archivo);
    printf(">> Producto guardado correctamente.\n");
}

void realizarCompra() {
    char buscar[20], idArchivo[20], nombreArchivo[50], seguir;
    double precio, subtotal, totalVenta = 0;
    int cantidad, descuento, encontrado;

    do {
        encontrado = 0;
        printf("\nIngrese ID del producto a comprar: ");
        scanf("%s", buscar);

        FILE *leer = fopen("productos.txt", "r");
        if (leer == NULL) {
            printf("Error: No existe el archivo de productos.\n");
            return;
        }

        while (fscanf(leer, "%s %s", idArchivo, nombreArchivo) != EOF) {
            if (strcmp(buscar, idArchivo) == 0) {
                encontrado = 1;
                break;
            }
        }
        fclose(leer);

        if (encontrado) {
            printf("Producto: %s\n", nombreArchivo);
            printf("Precio unitario: ");
            scanf(" %lf", &precio);
            printf("Cantidad: ");
            scanf(" %d", &cantidad);
            printf("Descuento (%%): ");
            scanf(" %d", &descuento);

            subtotal = cantidad * (precio * (1.0 - (descuento / 100.0)));
            totalVenta += subtotal;
            printf("Subtotal: $%.2lf\n", subtotal);
        } else {
            printf("ID [%s] no encontrado.\n", buscar);
        }

        printf("\n¿Desea agregar otro producto a esta compra? (s/n): ");
        scanf(" %c", &seguir);

    } while (seguir == 's' || seguir == 'S');

    printf("\n=================================");
    printf("\nTOTAL FINAL DE COMPRA: $%.2lf", totalVenta);
    printf("\n=================================\n");
}