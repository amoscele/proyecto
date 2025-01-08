#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 512
#define QUEUE_KEY 1234

// Estructura del mensaje
struct mensaje {
    long tipo;
    char texto[MSG_SIZE];
};

void enviar_mensaje(int msqid, const char *texto) {
    struct mensaje msg;
    msg.tipo = 1;  // Tipo de mensaje (puede ser arbitrario)
    strncpy(msg.texto, texto, MSG_SIZE);

    // Enviar mensaje a la cola
    if (msgsnd(msqid, &msg, strlen(msg.texto) + 1, 0) == -1) {
        perror("Error al enviar mensaje");
        exit(1);
    }

    printf("Mensaje enviado: %s\n", texto);
}

int main() {
    key_t clave = QUEUE_KEY;
    int msqid;

    // Conectar o crear la cola de mensajes
    msqid = msgget(clave, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("Error al conectarse a la cola de mensajes");
        exit(1);
    }

    printf("Productor iniciado.\n");

    // Bucle para enviar mensajes
    while (1) {
        char nombre[50], materia[50];
        int edad, matricula, grado;
        char buffer[MSG_SIZE];

        printf("Ingrese los datos del alumno en el formato:\n");
        printf("Nombre, Edad, Matricula, Grado, Materia\n");
        printf("O escriba 'salir' para terminar: ");
        fgets(buffer, MSG_SIZE, stdin);

        // Eliminar el salto de línea al final
        buffer[strcspn(buffer, "\n")] = '\0';

        // Verificar si es un comando para salir
        if (strcmp(buffer, "salir") == 0) {
            enviar_mensaje(msqid, "salir");
            break;
        }

        // Obtener los datos del alumno
        sscanf(buffer, "%49[^,], %d, %d, %d, %49s", nombre, &edad, &matricula, &grado, materia);

        // Formatear el mensaje según el formato esperado
        char mensaje[MSG_SIZE];
        snprintf(mensaje, MSG_SIZE, "Nombre: %s, Edad: %d, Matricula: %d, Grado: %d, Materia: %s", nombre, edad, matricula, grado, materia);

        // Enviar el mensaje
        enviar_mensaje(msqid, mensaje);
    }

    printf("Productor finalizado.\n");

    return 0;
}
