#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Función para simular envío de mensajes
void send_message(int user_id, const char *type, const char *content) {
    printf("[CLIENTE] Usuario %d (%s) envió mensaje: %s\n", user_id, type, content);

    // Aquí puedes usar IPC, sockets, o archivos compartidos para enviar el mensaje al core.
}

int main() {
    int user_id = rand() % 1000; // ID único del usuario
    char *types[] = {"pre-pago", "pos-pago"};
    int type_index = rand() % 2;

    for (int i = 0; i < 10; i++) {
        char content[100];
        sprintf(content, "Mensaje %d del usuario %d", i + 1, user_id);

        send_message(user_id, types[type_index], content);
        sleep(rand() % 3 + 1); // Espera entre envíos
    }

    return 0;
}
