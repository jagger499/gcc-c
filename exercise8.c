#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>

#define MESSAGE_QUEUE_KEY 1234
#define MESSAGE_SIZE 100

struct message {
    long message_type;
    char message_text[MESSAGE_SIZE];
};

int main() {
    pid_t pid;
    int msgid;

    msgid = msgget(MESSAGE_QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("Error al crear la cola de mensajes");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("Error al crear el proceso");
        return 1;
    } else if (pid == 0) {
        struct message received_message;

        for (int i = 0; i < 5; i++) {
            if (msgrcv(msgid, &received_message, sizeof(received_message.message_text), 1, 0) == -1) {
                perror("Error al recibir mensaje");
                exit(1);
            }
            printf("Consumidor: Mensaje recibido: %s\n", received_message.message_text);
        }

        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("Error al eliminar la cola de mensajes");
            exit(1);
        }

        printf("Consumidor: Cola de mensajes eliminada.\n");
        exit(0);
    } else {
        struct message sent_message;
        sent_message.message_type = 1;

        for (int i = 0; i < 5; i++) {
            snprintf(sent_message.message_text, MESSAGE_SIZE, "Mensaje %d desde el productor", i + 1);

            if (msgsnd(msgid, &sent_message, sizeof(sent_message.message_text), 0) == -1) {
                perror("Error al enviar mensaje");
                exit(1);
            }
            printf("Productor: Mensaje enviado: %s\n", sent_message.message_text);
            sleep(1);
        }

        wait(NULL);
        printf("Productor: Proceso terminado.\n");
    }

    return 0;
}
