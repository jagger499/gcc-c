#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    } else if (pid == 0) {
        int suma_hijo = 0;
        for (int i = 1; i <= 50; i++) {
            suma_hijo += i;
        }
        printf("Proceso hijo (PID: %d): La suma de los números del 1 al 50 es %d\n", getpid(), suma_hijo);
    } else {
        int suma_padre = 0;
        for (int i = 51; i <= 100; i++) {
            suma_padre += i;
        }
        printf("Proceso padre (PID: %d): La suma de los números del 51 al 100 es %d\n", getpid(), suma_padre);

        wait(NULL);
    }

    return 0;
}
