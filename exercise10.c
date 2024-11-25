#include <stdio.h>
#include <stdlib.h>

void mostrar_memoria_disponible() {
    printf("\n=== Memoria disponible ===\n");
    system("cat /proc/meminfo | grep MemAvailable");
}

void mostrar_procesos_ejecucion() {
    printf("\n=== Procesos en ejecución ===\n");
    system("ps -e --format pid,comm,state --sort=pid");
}

void mostrar_carga_sistema() {
    printf("\n=== Carga del sistema ===\n");
    system("uptime");
}

int main() {
    printf("Monitor de sistema básico\n");

    mostrar_memoria_disponible();

    mostrar_procesos_ejecucion();

    mostrar_carga_sistema();

    printf("\nMonitor de sistema finalizado.\n");
    return 0;
}
