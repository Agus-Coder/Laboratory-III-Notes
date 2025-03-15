#include "pthread.h"

#ifndef _GLOBAL
#define _GLOBAL

pthread_mutex_t mutex;

typedef enum{
	EVT_NINGUNO,
	EVT_INIT,
	EVT_INFO,
	EVT_FINALIZAR
}Eventos;

typedef enum{
	MSG_NADIE,
	MSG_PANEL,
	MSG_CIUDAD
}Destinos;

struct tipo_dato{
	int empezar;
};

typedef struct tipo_dato dato;

struct tipo_ciudad{
	int nro_ciudad;
	int id_colamensaje;
	char nombre_ciudad[100];
	int velocidad_viento;
	int temperatura;
	int proba_lluvia;	
};

typedef struct tipo_ciudad tciudad;

#endif

