#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 5

int main() {
    pid_t pid;
    int i;

    for (i = 0; i < NUM_CHILDREN; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Error al crear un proceso hijo");
            return 1;
        } else if (pid == 0) {
            printf("Proceso hijo %d ejecutándose. PID: %d\n", i + 1, getpid());
            for (int j = 0; j < 5; j++) {
                printf("Proceso hijo %d (PID: %d) - Iteración %d\n", i + 1, getpid(), j + 1);
                sleep(1);
            }
            printf("Proceso hijo %d (PID: %d) finalizado.\n", i + 1, getpid());
            exit(0);
        }
    }

    for (i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    printf("Proceso padre (PID: %d) finalizado después de que todos los hijos terminaron.\n", getpid());
    return 0;
}
