#include "pthread.h"
#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0
#define DESDE 29
#define HASTA 54
#define CANTIDAD 10
#define LARGO 100

#define ROJO 0
#define VERDE 1
#define CLAVE_BASE 34

#define TIEMPO_ESPERA 500000

pthread_mutex_t mutex;

struct avion{

	int nro_avion;
    char ciudad[100];

};

#endif

