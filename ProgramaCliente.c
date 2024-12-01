// Proyecto de Sistemas Operativos
//Emily Valarezo Plaza

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define path "Chisme Pipe"

void enviar(int ID_usuario, const char *TIPO_usuario, const char *TEXTO_usuario) {
    int pipe;
    char buffer[200];

    pipe = open(path, O_WRONLY);
    if (pipe < 0) {
        perror("Error en el envío...");
        exit(1);
    }

    sprintf(buffer, "%d %s %s\n", ID_usuario, TIPO_usuario, TEXTO_usuario);
    write(pipe, buffer, strlen(buffer) + 1);
    close(pipe);
    printf("El usuario %d (%s) envió el mensaje: %s\n", ID_usuario, TIPO_usuario, TEXTO_usuario);
}

int main() {
    srand(time(NULL));
    int ID_usuario = rand() % 1000;

    for (int i = 0; i < 5; i++) {
        char TEXTO_usuario[100];
        const char *TIPO_usuario = (rand() % 2 == 0) ? "pre-pago" : "pos-pago";

        sprintf(TEXTO_usuario, "Mensaje %d del usuario %d", i + 1, ID_usuario);
        enviar(ID_usuario, TIPO_usuario, TEXTO_usuario);

        sleep(rand() % 3 + 1);
    }

    return 0;
}
