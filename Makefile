# Variables
CC = gcc
CFLAGS = -pthread -Wall
TARGETS = core cliente

# Reglas principales
all: $(TARGETS)

core: ProgramaCore.c
	$(CC) $(CFLAGS) -o core ProgramaCore.c

cliente: ProgramaCliente.c
	$(CC) $(CFLAGS) -o cliente ProgramaCliente.c

# Limpieza
clean:
	rm -f $(TARGETS) *.o

