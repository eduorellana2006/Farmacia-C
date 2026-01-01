#include <stdio.h>
#include <string.h>

int main() {
	char operacionRealizar, nombre[15];
    int agregarIdentificador; // Se usa como int al guardar

    int encontrado = 0;
    char identificador[15];

    char buscar[20], seguir;
    int descuento = 0, cantidadProducto = 0;
    double precioProducto, precioFinal = 0, subCompra = 0;

    printf("Bienvenido al software v1.0.0 --- Farmacia.\n");
    printf("Que operacion desea realizar Agregar o Comprar? (a/c): ");
    scanf(" %c", &operacionRealizar); // Espacio antes de %c para limpiar el buffer

    if (operacionRealizar == 'c' || operacionRealizar == 'C') {
    	do {
    		printf("\nIngrese el ID del producto: ");
    		scanf("%s", buscar);

    		FILE *leer = fopen("productos.txt", "r");
    		if (leer == NULL) {
    			printf("Error: No existe el archivo de productos.\n");
    			break;
    		} else {
    			encontrado = 0;
                // Leemos el ID y el nombre que guardamos antes
    			while (fscanf(leer, "%s %s", identificador, nombre) != EOF) {
                    // CORRECCIÓN: Comparamos 'identificador' con 'buscar'
    				if (strcmp(buscar, identificador) == 0) {
    					encontrado = 1;
    					break;
    				}
    			}
    			fclose(leer);

    			if (encontrado) {
    				printf("Producto encontrado: %s\n", nombre);
    				printf("\nIngrese el valor del producto: ");
    				scanf("%lf", &precioProducto);

    				printf("Ingrese la cantidad: ");
    				scanf("%d", &cantidadProducto);

    				printf("Descuento (0-100): ");
    				scanf("%d", &descuento);

    				subCompra = cantidadProducto * (precioProducto - (descuento * precioProducto / 100.0));
    				precioFinal += subCompra;

    				printf("\nSubtotal actual: x%d $%.2lf\n", cantidadProducto, precioFinal);
    			} else {
    				printf("\nError: ID no encontrado.\n");
    			}
    		}

    		printf("\n¿Seguir comprando? (s/n): ");
    		scanf(" %c", &seguir);

    	} while (seguir == 's' || seguir == 'S');

    	printf("\n--- RESUMEN DE COMPRA ---");
    	printf("\nTotal a pagar: $%.2lf\n", precioFinal);

    } else if(operacionRealizar == 'a' || operacionRealizar == 'A') {
    	printf("\nIndique un ID numerico: ");
    	scanf("%d", &agregarIdentificador);

    	printf("Nombre del producto: ");
    	scanf("%s", nombre);

    	FILE *archivo = fopen("productos.txt", "a");
    	if (archivo != NULL) {
            // Guardamos ID y Nombre
    		fprintf(archivo, "%d %s\n", agregarIdentificador, nombre);
    		fclose(archivo);
    		printf("Producto guardado con exito.\n");
    	}
    } else {
    	printf("\nOperacion no comprendida.\n");
    }

    return 0;
}