#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FILE_NAME "reporte.txt"
#define FILE_CONTENT "Este es un reporte generado por el programa.\n"

int main() {
    int fd;

    fd = open(FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error al crear el archivo");
        return 1;
    }

    if (write(fd, FILE_CONTENT, sizeof(FILE_CONTENT) - 1) == -1) {
        perror("Error al escribir en el archivo");
        close(fd);
        return 1;
    }
    close(fd);

    if (chmod(FILE_NAME, S_IRUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Error al cambiar los permisos del archivo");
        return 1;
    }

    printf("El archivo '%s' ha sido creado, su contenido se ha escrito y los permisos han sido cambiados a 'solo lectura' para todos los usuarios.\n", FILE_NAME);

    return 0;
}
