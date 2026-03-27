#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[50];
    float promedio;
} Estudiante;

// Crear estudiante
Estudiante crearEstudiante(int id, const char* nombre, float promedio) {
    Estudiante e;
    e.id = id;
    strncpy(e.nombre, nombre, sizeof(e.nombre)-1);
    e.nombre[sizeof(e.nombre)-1] = '\0';
    e.promedio = promedio;
    return e;
}

// Mostrar estudiante
void mostrarEstudiante(Estudiante e) {
    printf("ID: %d | Nombre: %s | Promedio: %.2f\n", e.id, e.nombre, e.promedio);
}

// Agregar estudiante
void agregarEstudiante(Estudiante** lista, int* n) {
    int id;
    char nombre[50];
    float promedio;

    printf("ID: ");
    scanf("%d", &id);

    printf("Nombre: ");
    scanf(" %49[^\n]", nombre);

    printf("Promedio: ");
    scanf("%f", &promedio);

    *lista = realloc(*lista, (*n + 1) * sizeof(Estudiante));
    if (*lista == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }

    (*lista)[*n] = crearEstudiante(id, nombre, promedio);
    (*n)++;
}

// Mostrar todos
void mostrarLista(Estudiante* lista, int n) {
    for (int i = 0; i < n; i++) {
        mostrarEstudiante(lista[i]);
    }
}

// Buscar por ID
void buscarPorID(Estudiante* lista, int n) {
    int id;
    printf("Ingrese ID a buscar: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (lista[i].id == id) {
            printf("Encontrado:\n");
            mostrarEstudiante(lista[i]);
            return;
        }
    }
    printf("No encontrado\n");
}

// Ordenar por promedio (burbuja)
void ordenarPorPromedio(Estudiante* lista, int n) {
    Estudiante temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (lista[j].promedio < lista[j+1].promedio) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
    printf("Lista ordenada por promedio (descendente)\n");
}

// Guardar en archivo
void guardarArchivo(Estudiante* lista, int n) {
    FILE* f = fopen("estudiantes.txt", "w");
    if (!f) {
        printf("Error al abrir archivo\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%.2f\n", lista[i].id, lista[i].nombre, lista[i].promedio);
    }

    fclose(f);
    printf("Datos guardados\n");
}

// Cargar desde archivo
void cargarArchivo(Estudiante** lista, int* n) {
    FILE* f = fopen("estudiantes.txt", "r");
    if (!f) {
        printf("No hay archivo\n");
        return;
    }

    Estudiante temp;
    char linea[100];

    *n = 0;
    free(*lista);
    *lista = NULL;

    while (fgets(linea, sizeof(linea), f)) {
        sscanf(linea, "%d;%49[^;];%f", &temp.id, temp.nombre, &temp.promedio);

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

        switch(opcion) {
            case 1: agregarEstudiante(&lista, &n); break;
            case 2: mostrarLista(lista, n); break;
            case 3: buscarPorID(lista, n); break;
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
