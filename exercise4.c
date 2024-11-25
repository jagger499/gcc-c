#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define NUM_COUNT 10

int main() {
    int pipe_fd[2];
    pid_t pid;

    if (pipe(pipe_fd) == -1) {
        perror("Error al crear la tubería");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    } else if (pid == 0) {
        close(pipe_fd[1]);

        int numero;
        printf("Consumidor: Leyendo números...\n");
        while (read(pipe_fd[0], &numero, sizeof(int)) > 0) {
            printf("Consumidor: Número recibido: %d\n", numero);
        }

        close(pipe_fd[0]);
        printf("Consumidor: Finalizado.\n");
    } else {
        close(pipe_fd[0]);

        srand(time(NULL));
        printf("Productor: Generando números...\n");
        for (int i = 0; i < NUM_COUNT; i++) {
            int numero = rand() % 100;
            write(pipe_fd[1], &numero, sizeof(int));
            printf("Productor: Número enviado: %d\n", numero);
        }

        close(pipe_fd[1]);
        printf("Productor: Finalizado.\n");

        wait(NULL);
    }

    return 0;
}
