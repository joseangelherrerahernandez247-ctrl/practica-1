#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[50];
    float promedio;
} Estudiante;

// Función para agregar estudiante
void agregarEstudiante(Estudiante** lista, int* n) {
    *lista = realloc(*lista, (*n + 1) * sizeof(Estudiante));
    if (*lista == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }

    printf("\nNuevo estudiante\n");
    printf("ID: ");
    scanf("%d", &(*lista)[*n].id);

    printf("Nombre: ");
    scanf(" %49[^\n]", (*lista)[*n].nombre);

    printf("Promedio: ");
    scanf("%f", &(*lista)[*n].promedio);

    (*n)++;
}

// Mostrar todos
void mostrarEstudiantes(Estudiante* lista, int n) {
    if (n == 0) {
        printf("No hay estudiantes\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\nID: %d\n", lista[i].id);
        printf("Nombre: %s\n", lista[i].nombre);
        printf("Promedio: %.2f\n", lista[i].promedio);
    }
}

// Buscar por ID
void buscarEstudiante(Estudiante* lista, int n) {
    int id;
    printf("Ingresa ID a buscar: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (lista[i].id == id) {
            printf("\nEncontrado:\n");
            printf("Nombre: %s\n", lista[i].nombre);
            printf("Promedio: %.2f\n", lista[i].promedio);
            return;
        }
    }

    printf("No encontrado\n");
}

// Ordenar por promedio (burbuja)
void ordenarPorPromedio(Estudiante* lista, int n) {
    Estudiante temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (lista[j].promedio < lista[j + 1].promedio) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    printf("Ordenados por promedio (descendente)\n");
}

// Guardar en archivo
void guardarArchivo(Estudiante* lista, int n) {
    FILE* f = fopen("estudiantes.txt", "w");
    if (f == NULL) {
        printf("Error al abrir archivo\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,%s,%.2f\n",
                lista[i].id,
                lista[i].nombre,
                lista[i].promedio);
    }

    fclose(f);
    printf("Datos guardados\n");
}

// Cargar desde archivo
void cargarArchivo(Estudiante** lista, int* n) {
    FILE* f = fopen("estudiantes.txt", "r");
    if (f == NULL) {
        printf("No hay archivo para cargar\n");
        return;
    }

    *n = 0;
    *lista = NULL;

    Estudiante temp;

    while (fscanf(f, "%d,%49[^,],%f\n",
                  &temp.id,
                  temp.nombre,
                  &temp.promedio) == 3) {
        
        *lista = realloc(*lista, (*n + 1) * sizeof(Estudiante));
        (*lista)[*n] = temp;
        (*n)++;
    }

    fclose(f);
    printf("Datos cargados\n");
}

int main() {
    Estudiante* lista = NULL;
    int n = 0;
    int opcion;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Agregar estudiante\n");
        printf("2. Mostrar estudiantes\n");
        printf("3. Buscar por ID\n");
        printf("4. Ordenar por promedio\n");
        printf("5. Guardar en archivo\n");
        printf("6. Cargar desde archivo\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarEstudiante(&lista, &n);
                break;
            case 2:
                mostrarEstudiantes(lista, n);
                break;
            case 3:
                buscarEstudiante(lista, n);
                break;
            case 4:
                ordenarPorPromedio(lista, n);
                break;
            case 5:
                guardarArchivo(lista, n);
                break;
            case 6:
                cargarArchivo(&lista, &n);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida\n");
        }

    } while (opcion != 0);

    free(lista);
    return 0;
}
