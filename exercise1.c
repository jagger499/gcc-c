#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define NUM_COUNT 20
#define FILE_NAME "datos.bin"

int main() {
    int numbers[NUM_COUNT];
    int i, fd;

    srand(time(NULL));
    for (i = 0; i < NUM_COUNT; i++) {
        numbers[i] = rand() % 51 + 50;
    }

    fd = open(FILE_NAME, O_CREAT | O_WRONLY, 0600);
    if (fd == -1) {
        perror("Error al crear el archivo");
        return 1;
    }

    if (write(fd, numbers, sizeof(numbers)) == -1) {
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

    int read_numbers[NUM_COUNT];
    if (read(fd, read_numbers, sizeof(read_numbers)) == -1) {
        perror("Error al leer del archivo");
        close(fd);
        return 1;
    }
    close(fd);

    printf("Números leídos del archivo '%s':\n", FILE_NAME);
    for (i = 0; i < NUM_COUNT; i++) {
        printf("%d ", read_numbers[i]);
    }
    printf("\n");

    return 0;
}
