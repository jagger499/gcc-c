#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void manejador_senal(int sig) {
    printf("Hijo: Recibida la señal %d, finalizando el proceso.\n", sig);
    exit(0);
}

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    } else if (pid == 0) {
        signal(SIGTERM, manejador_senal);

        printf("Hijo: Esperando la señal del padre...\n");
        while (1) {
            printf("Hijo: Trabajando...\n");
            sleep(1);
        }
    } else {
        printf("Padre: Esperando 10 segundos antes de enviar la señal al hijo.\n");
        sleep(10);

        printf("Padre: Enviando señal al hijo (PID: %d).\n", pid);
        if (kill(pid, SIGTERM) == -1) {
            perror("Error al enviar la señal");
            return 1;
        }

        wait(NULL);
        printf("Padre: Proceso hijo finalizado.\n");
    }

    return 0;
}
