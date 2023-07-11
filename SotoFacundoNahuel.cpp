#include <stdio.h>
#include <string.h>

#define MAX_MEDICAMENTOS 10
#define MAX_FARMACIAS 10

//Asigno las variables 
struct Medicamento {
    int codigo;
    float precio;
};

struct Farmacia {
    char nombre[50];
    int cantidad;
    float valor;
};

int main() {
    struct Medicamento medicamentos[MAX_MEDICAMENTOS];
    struct Farmacia farmacias[MAX_FARMACIAS];

    //Con este codigo cargo los datos de medicamentos y sus precios a vectores
    int i;
    for (i = 0; i < MAX_MEDICAMENTOS; i++) {
        printf("Ingrese el código del medicamento %d: ", i+1);
        scanf("%d", &medicamentos[i].codigo);

        printf("Ingrese el precio del medicamento %d: ", i+1);
        scanf("%f", &medicamentos[i].precio);
    }

    // Inicio los datos de las farmacias
    for (i = 0; i < MAX_FARMACIAS; i++) {
        strcpy(farmacias[i].nombre, "");
        farmacias[i].cantidad = 0;
        farmacias[i].valor = 0.0;
    }

    int codigoMedicamento;
    int cantidad;
    char nombreFarmacia[50];

    //Con este codigo ingreso los datos de asignacion a las farmacias
    while (1) {
        printf("\nIngrese el código de medicamento (0 para finalizar): ");
        scanf("%d", &codigoMedicamento);

        if (codigoMedicamento == 0) {
            break;
        }

        printf("Ingrese la cantidad asignada: ");
        scanf("%d", &cantidad);

        printf("Ingrese el nombre de la farmacia: ");
        scanf("%s", nombreFarmacia);

        // Busco el medicamento en el vector
        int indiceMedicamento = -1;
        for (i = 0; i < MAX_MEDICAMENTOS; i++) {
            if (medicamentos[i].codigo == codigoMedicamento) {
                indiceMedicamento = i;
                break;
            }
        }

        if (indiceMedicamento == -1) {
            printf("Medicamento Inexistente\n");
            continue;
        }

        // Busco la farmacia en el vector
        int indiceFarmacia = -1;
        for (i = 0; i < MAX_FARMACIAS; i++) {
            if (strcmp(farmacias[i].nombre, nombreFarmacia) == 0) {
                indiceFarmacia = i;
                break;
            }
        }

        //Si nuestra farmacia no existe, busco una posicion vacia en el vector
        if (indiceFarmacia == -1) {
            for (i = 0; i < MAX_FARMACIAS; i++) {
                if (strlen(farmacias[i].nombre) == 0) {
                    indiceFarmacia = i;
                    strcpy(farmacias[i].nombre, nombreFarmacia);
                    break;
                }
            }
        }

        // Actualizo los datos de la farmacia y el medicamento
        farmacias[indiceFarmacia].cantidad += cantidad;
        farmacias[indiceFarmacia].valor += medicamentos[indiceMedicamento].precio * cantidad;
    }

    //Con el siguiente codigo encuentro el medicamento con menor asignacion
    int menorAsignacion = farmacias[0].cantidad;
    int indiceMenorAsignacion = 0;
    for (i = 1; i < MAX_FARMACIAS; i++) {
        if (farmacias[i].cantidad < menorAsignacion) {
            menorAsignacion = farmacias[i].cantidad;
            indiceMenorAsignacion = i;
        }
    }

    // Muestro los resultados
    printf("\Resultados\n");

    printf("Medicamentos no asignados a ninguna farmacia:\n");
    for (i = 0; i < MAX_MEDICAMENTOS; i++) {
        int asignado = 0;
        for (int j = 0; j < MAX_FARMACIAS; j++) {
            if (farmacias[j].cantidad > 0 && medicamentos[i].codigo == medicamentos[j].codigo) {
                asignado = 1;
                break;
            }
        }
        if (!asignado) {
            printf("%d\n", medicamentos[i].codigo);
        }
    }

    printf("\nMedicamento con menor asignación:\n");
    printf("Código: %d\n", medicamentos[indiceMenorAsignacion].codigo);
    printf("Cantidad total asignada: %d\n", menorAsignacion);
    printf("Valor total a percibir: %.2f\n", farmacias[indiceMenorAsignacion].valor);

    printf("\nCantidad asignada a cada farmacia:\n");
    for (i = 0; i < MAX_FARMACIAS; i++) {
        if (farmacias[i].cantidad > 0) {
            printf("Farmacia: %s\n", farmacias[i].nombre);
            printf("Cantidad: %d\n", farmacias[i].cantidad);
            printf("Valor a percibir: %.2f\n", farmacias[i].valor);
        }
    }

    return 0;
}

