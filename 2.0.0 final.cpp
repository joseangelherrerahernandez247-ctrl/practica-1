#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[50];
    float promedio;
} Estudiante;

// Limpiar buffer
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Agregar estudiante
void agregarEstudiante(Estudiante** lista, int* n) {
    Estudiante* temp = realloc(*lista, (*n + 1) * sizeof(Estudiante));
    if (temp == NULL) {
        printf("Error de memoria\n");
        return;
    }
    *lista = temp;

    printf("\nNuevo estudiante\n");

    printf("ID: ");
    if (scanf("%d", &(*lista)[*n].id) != 1) {
        printf("Entrada invalida\n");
        limpiarBuffer();
        return;
    }

    limpiarBuffer();

    printf("Nombre: ");
    fgets((*lista)[*n].nombre, 50, stdin);
    (*lista)[*n].nombre[strcspn((*lista)[*n].nombre, "\n")] = '\0';

    printf("Promedio: ");
    if (scanf("%f", &(*lista)[*n].promedio) != 1) {
        printf("Entrada invalida\n");
        limpiarBuffer();
        return;
    }

    (*n)++;
}

// Mostrar estudiantes
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

// Buscar estudiante
void buscarEstudiante(Estudiante* lista, int n) {
    int id;
    printf("Ingresa ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada invalida\n");
        limpiarBuffer();
        return;
    }

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

// Ordenar por promedio
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
    printf("Ordenado correctamente\n");
}

// Guardar archivo
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

// Cargar archivo
void cargarArchivo(Estudiante** lista, int* n) {
    FILE* f = fopen("estudiantes.txt", "r");
    if (f == NULL) {
        printf("No existe archivo\n");
        return;
    }

    Estudiante* tempLista = NULL;
    int tempN = 0;
    Estudiante temp;

    while (fscanf(f, "%d,%49[^,],%f\n",
                  &temp.id,
                  temp.nombre,
                  &temp.promedio) == 3) {

        Estudiante* nuevo = realloc(tempLista, (tempN + 1) * sizeof(Estudiante));
        if (nuevo == NULL) {
            printf("Error de memoria\n");
            free(tempLista);
            fclose(f);
            return;
        }

        tempLista = nuevo;
        tempLista[tempN] = temp;
        tempN++;
    }

    fclose(f);

    free(*lista);
    *lista = tempLista;
    *n = tempN;

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

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida\n");
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1: agregarEstudiante(&lista, &n); break;
            case 2: mostrarEstudiantes(lista, n); break;
            case 3: buscarEstudiante(lista, n); break;
            case 4: ordenarPorPromedio(lista, n); break;
            case 5: guardarArchivo(lista, n); break;
            case 6: cargarArchivo(&lista, &n); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida\n");
        }

    } while (opcion != 0);

    free(lista);
    return 0;
}
