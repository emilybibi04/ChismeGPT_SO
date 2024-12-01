// Proyecto de Sistemas Operativos
// Emily Valarezo Plaza

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

// Parámetros
#define numfijo_mensajes 3
#define tiempo_mili 1000
#define path "Chisme Pipe"

// Estructura para los mensajes
typedef struct {
    int ID_usuario;
    char TIPO_usuario[10];
    char TEXTO_usuario[100];
} Message;

// Variables globales
pthread_mutex_t queue_lock;
pthread_cond_t estado;

Message POS_fila[100];
Message PRE_fila[100];

int POS_contador = 0;
int PRE_contador = 0;

// Procesar mensajes
void *identificar(void *arg) {
    while (1) {
        pthread_mutex_lock(&queue_lock);

        if (POS_contador > 0) {
            Message message = POS_fila[--POS_contador];
            pthread_mutex_unlock(&queue_lock);

            printf("Se está atendiendo a un usuario pos-pago %d: %s\n", message.ID_usuario, message.TEXTO_usuario);
            usleep(tiempo_mili * 1000);
        } else if (PRE_contador > 0) {
            Message message = PRE_fila[--PRE_contador];
            pthread_mutex_unlock(&queue_lock);

            printf("Se está atendiendo a un usuario pre-pago %d: %s\n", message.ID_usuario, message.TEXTO_usuario);
            usleep(tiempo_mili * 1000);
        } else {
            pthread_cond_wait(&estado, &queue_lock);
            pthread_mutex_unlock(&queue_lock);
        }
    }
    return NULL;
}

// Agregar mensajes a las filas
void add_message(Message message) {
    pthread_mutex_lock(&queue_lock);

    if (strcmp(message.TIPO_usuario, "pos-pago") == 0) {
        POS_fila[POS_contador++] = message;
    } else {
        PRE_fila[PRE_contador++] = message;
    }

    pthread_mutex_unlock(&queue_lock);
    pthread_cond_signal(&estado);
}

int main() {
    pthread_t processor_threads[numfijo_mensajes];
    char buffer[200];
    int fifo_fd;

    unlink(path); // Eliminar FIFO existente
    mkfifo(path, 0666); // Crear FIFO

    pthread_mutex_init(&queue_lock, NULL);
    pthread_cond_init(&estado, NULL);

    for (int i = 0; i < numfijo_mensajes; i++) {
        pthread_create(&processor_threads[i], NULL, identificar, NULL);
    }

    printf("El programa Core se está ejecutando...\n");
    fifo_fd = open(path, O_RDONLY);

    while (1) {
        if (read(fifo_fd, buffer, sizeof(buffer)) > 0) {
            Message message;
            sscanf(buffer, "%d %s %[^\n]", &message.ID_usuario, message.TIPO_usuario, message.TEXTO_usuario);

            printf("Mensaje del usuario %d (%s): %s\n", message.ID_usuario, message.TIPO_usuario, message.TEXTO_usuario);
            add_message(message);
        }
    }

    close(fifo_fd);
    unlink(path);
    return 0;
}

