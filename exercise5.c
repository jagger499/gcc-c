#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define NUM_COUNT 100
#define FILE_NAME "numeros.bin"

int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int numeros[NUM_COUNT];
    int fd;

    srand(time(NULL));
    for (int i = 0; i < NUM_COUNT; i++) {
        numeros[i] = rand() % 1000;
    }

    fd = open(FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error al crear el archivo");
        return 1;
    }

    if (write(fd, numeros, sizeof(numeros)) == -1) {
        perror("Error al escribir en el archivo");
        close(fd);
        return 1;
    }
    close(fd);

    fd = open(FILE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo para lectura");
        return 1;
    }

    if (read(fd, numeros, sizeof(numeros)) == -1) {
        perror("Error al leer del archivo");
        close(fd);
        return 1;
    }
    close(fd);

    qsort(numeros, NUM_COUNT, sizeof(int), comparar);

    fd = open(FILE_NAME, O_WRONLY | O_TRUNC);
    if (fd == -1) {
        perror("Error al abrir el archivo para escritura");
        return 1;
    }

    if (write(fd, numeros, sizeof(numeros)) == -1) {
        perror("Error al escribir en el archivo");
        close(fd);
        return 1;
    }
    close(fd);

    printf("Los números han sido generados, ordenados y guardados en '%s'.\n", FILE_NAME);
    return 0;
}
