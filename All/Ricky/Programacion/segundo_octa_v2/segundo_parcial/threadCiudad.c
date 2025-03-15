#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/ipc.h"
#include "sys/sem.h"
#include "def.h"
#include "unistd.h"
#include "time.h"
#include "memoria.h"
#include "sys/shm.h"
#include "sys/time.h"
#include "pthread.h"
#include "tiempos.h"
#include "funciones.h"
#include "global.h"
#include "cola_mensajes.h"


void *threadCiudad(void *parametro){
	
	int nro_ciudad;
	int id_colamensaje;
	char *nombre_ciudad;
	int velocidad_viento;
	int temperatura;
	int proba_lluvia;
	int id_cola_mensajes;
	int i;
	int done;
	char cadena[50];
	mensaje mensaje;
	tciudad *datos_thread;

	done=0;
	
	/*"Desarmo" el dato*/
	datos_thread=(tciudad*) parametro;
	nro_ciudad = datos_thread->nro_ciudad;
	id_cola_mensajes = datos_thread ->id_colamensaje;
	nombre_ciudad = datos_thread ->nombre_ciudad;
	strcpy(nombre_ciudad, datos_thread -> nombre_ciudad);
	velocidad_viento = datos_thread -> velocidad_viento;
	temperatura = datos_thread -> temperatura;
	proba_lluvia = datos_thread -> proba_lluvia;
	
	srand(time(NULL));
	borrar_mensajes(id_cola_mensajes);

	while(done==0){
		pthread_mutex_lock(&mutex);
		recibir_mensaje(id_cola_mensajes, MSG_CIUDAD+nro_ciudad, &mensaje);

		switch(mensaje.evento){
			case EVT_INIT:
				velocidad_viento = inDevolverAleatorio(3,25);
				temperatura = inDevolverAleatorio(2,25);
				proba_lluvia = inDevolverAleatorio(0,100);
				
				printf("************************\n");
				printf("Nombre ciudad: %s\n",nombre_ciudad);
				printf("nro_ciudad: %d\n",MSG_CIUDAD+nro_ciudad);
				printf("Velocidad viento: %d\n",velocidad_viento);
				printf("Temperatura: %d\n",temperatura);
				printf("Probabilidad de lluvia: %d\n",proba_lluvia);
				printf("************************\n");
				sleep(1);
				sprintf(cadena,"ciudad: %s,viento: %d, temp: %d, lluvia: %d",nombre_ciudad,velocidad_viento,temperatura,proba_lluvia);
				
				enviar_mensaje(id_cola_mensajes,MSG_PANEL,MSG_CIUDAD+nro_ciudad,EVT_INFO,cadena);
				break;
			
			case EVT_FINALIZAR:
				printf("\nCiudad %d finalizo\n",nro_ciudad);
				done=1;
				break;
			default:
				printf("\nCiudad %d Evento sin definir\n",nro_ciudad);
			break;
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	};
	pthread_exit((void *)"Listo");

}
