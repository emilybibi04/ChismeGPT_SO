# ChismeGPT
Este proyecto de Sistemas Operativos tiene como objetivo simular el núcleo transaccional de un sistema llamado ChismeGPT, que procesa mensajes enviados por dos tipos de usuarios: pre-pago y pos-pago. Los usuarios envían mensajes al sistema mediante un cliente, y el núcleo procesa dichos mensajes, priorizando a los usuarios pos-pago.

## Estructura

El proyecto se compone de dos programas:

1. ProgramaCore.c: Procesa los mensajes enviados por los clientes a través de un pipe.
2. ProgramaCliente.c: Simula el envío de mensajes al core por parte de usuarios aleatorios.

## Datos del funcionamiento
- Los mensajes de usuarios pos-pago siempre tienen prioridad sobre los de pre-pago.
- Si no hay mensajes de usuarios pos-pago, los mensajes de pre-pago se procesan en orden de llegada.
- Todos los mensajes toman el mismo tiempo de procesamiento.

## Compilación

1. Clona este repositorio:
```
git clone <URL_DEL_REPOSITORIO>
cd ChismeGPT_SO
```
2. Usa el archivo Makefile para compilar ambos programas:
```
make
```
Esto generará dos ejecutables:

1. core: Programa principal que procesa los mensajes.
2. cliente: Programa cliente que envía mensajes.

## Ejecución
En una terminal:
```
./core
```

Y en otra terminal:
```
./cliente
```

## Limpienza
Para eliminar los archivos generados durante la compilación, ejecuta:
```
make clean
```
