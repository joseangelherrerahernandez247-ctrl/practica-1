#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un estudiante
typedef struct {
    int id;
    char nombre[50];
    float promedio;
} Estudiante;

// Función para crear un estudiante
Estudiante* crearEstudiante(int id, const char* nombre, float promedio) {
    Estudiante* e = (Estudiante*) malloc(sizeof(Estudiante));
    
    if (e == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    e->id = id;
    strncpy(e->nombre, nombre, sizeof(e->nombre) - 1);
    e->nombre[sizeof(e->nombre) - 1] = '\0'; // asegurar terminación
    e->promedio = promedio;

    return e;
}

// Función para mostrar un estudiante
void mostrarEstudiante(const Estudiante* e) {
    printf("ID: %d\n", e->id);
    printf("Nombre: %s\n", e->nombre);
    printf("Promedio: %.2f\n\n", e->promedio);
}

// Función para liberar memoria
void liberarEstudiante(Estudiante* e) {
    free(e);
}

int main() {
    int n;

    printf("¿Cuantos estudiantes quieres registrar? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada inválida\n");
        return 1;
    }

    // Arreglo dinámico de punteros
    Estudiante** lista = (Estudiante**) malloc(n * sizeof(Estudiante*));
    
    if (lista == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int id;
        char nombre[50];
        float promedio;

        printf("\nEstudiante %d\n", i + 1);

        printf("ID: ");
        if (scanf("%d", &id) != 1) {
            printf("Entrada inválida\n");
            return 1;
        }

        printf("Nombre: ");
        scanf(" %49[^\n]", nombre); // limita tamaño para evitar overflow

        printf("Promedio: ");
        if (scanf("%f", &promedio) != 1) {
            printf("Entrada inválida\n");
            return 1;
        }

        lista[i] = crearEstudiante(id, nombre, promedio);
    }

    printf("\n--- Lista de estudiantes ---\n\n");

    for (int i = 0; i < n; i++) {
        mostrarEstudiante(lista[i]);
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        liberarEstudiante(lista[i]);
    }
    free(lista);

    return 0;
}
