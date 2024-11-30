#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define MAX_CONCURRENT_MESSAGES 3
#define PROCESSING_TIME 1000  // Milisegundos
#define MAX_PREPAID_MESSAGES 10

// Estructura para mensajes
typedef struct {
    int user_id;
    char type[10]; // "pre-pago" o "pos-pago"
    char content[100];
} Message;

// Colas de mensajes
Message postpaid_queue[100];
Message prepaid_queue[100];
int postpaid_count = 0;
int prepaid_count = 0;

// Sincronización
pthread_mutex_t queue_lock;
pthread_cond_t process_condition;

// Función para procesar mensajes
void *process_messages(void *arg) {
    while (1) {
        pthread_mutex_lock(&queue_lock);

        if (postpaid_count > 0) {
            // Procesar mensaje pos-pago
            Message message = postpaid_queue[--postpaid_count];
            pthread_mutex_unlock(&queue_lock);

            printf("[CORE] Procesando mensaje pos-pago de usuario %d: %s\n", message.user_id, message.content);
            usleep(PROCESSING_TIME * 1000);
        } else if (prepaid_count > 0) {
            // Procesar mensaje pre-pago
            Message message = prepaid_queue[--prepaid_count];
            pthread_mutex_unlock(&queue_lock);

            printf("[CORE] Procesando mensaje pre-pago de usuario %d: %s\n", message.user_id, message.content);
            usleep(PROCESSING_TIME * 1000);
        } else {
            // Esperar si no hay mensajes
            pthread_cond_wait(&process_condition, &queue_lock);
            pthread_mutex_unlock(&queue_lock);
        }
    }
    return NULL;
}

// Función para recibir mensajes del cliente
void add_message(int user_id, const char *type, const char *content) {
    pthread_mutex_lock(&queue_lock);

    if (strcmp(type, "pos-pago") == 0) {
        postpaid_queue[postpaid_count++] = (Message){user_id, "pos-pago", ""};
        strcpy(postpaid_queue[postpaid_count - 1].content, content);
    } else {
        prepaid_queue[prepaid_count++] = (Message){user_id, "pre-pago", ""};
        strcpy(prepaid_queue[prepaid_count - 1].content, content);
    }

    printf("[CORE] Mensaje recibido de usuario %d (%s): %s\n", user_id, type, content);
    pthread_mutex_unlock(&queue_lock);
    pthread_cond_signal(&process_condition);
}

int main() {
    pthread_t processor_threads[MAX_CONCURRENT_MESSAGES];

    // Inicializar sincronización
    pthread_mutex_init(&queue_lock, NULL);
    pthread_cond_init(&process_condition, NULL);

    // Crear hilos de procesamiento
    for (int i = 0; i < MAX_CONCURRENT_MESSAGES; i++) {
        pthread_create(&processor_threads[i], NULL, process_messages, NULL);
    }

    // Simular recepción de mensajes desde cliente (puedes usar IPC o archivos compartidos aquí)
    printf("[CORE] Core en ejecución. Esperando mensajes...\n");
    while (1) {
        // Simula
