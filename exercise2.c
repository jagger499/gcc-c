#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int fd_origen, fd_destino;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_leidos, bytes_escritos;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <archivo_origen> <archivo_destino>\n", argv[0]);
        return 1;
    }

    fd_origen = open(argv[1], O_RDONLY);
    if (fd_origen == -1) {
        perror("Error al abrir el archivo de origen");
        return 1;
    }

    fd_destino = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_destino == -1) {
        perror("Error al crear el archivo de destino");
        close(fd_origen);
        return 1;
    }

    while ((bytes_leidos = read(fd_origen, buffer, BUFFER_SIZE)) > 0) {
        bytes_escritos = write(fd_destino, buffer, bytes_leidos);
        if (bytes_escritos == -1) {
            perror("Error al escribir en el archivo de destino");
            close(fd_origen);
            close(fd_destino);
            return 1;
        }
    }

    if (bytes_leidos == -1) {
        perror("Error al leer del archivo de origen");
    }

    close(fd_origen);
    close(fd_destino);

    printf("Copia completada: '%s' -> '%s'\n", argv[1], argv[2]);
    return 0;
}
