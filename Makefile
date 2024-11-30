CC = gcc
CFLAGS = -pthread -Wall

all: core cliente

core: core.c
	$(CC) $(CFLAGS) -o core core.c

cliente: cliente.c
	$(CC) $(CFLAGS) -o cliente cliente.c

clean:
	rm -f core cliente
