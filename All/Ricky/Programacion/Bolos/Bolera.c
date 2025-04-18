#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include "time.h"
#include "pthread.h"
#include "clave.h"
#include "def.h"
#include "global.h"
#include "memoria.h"
#include "cola.h"
#include "funciones.h"
#include "hilos.h"
#include "semaforo.h"

int main(int arg, char *argv[]){
/* variables */
	int *memoria=NULL;
	int id_memoria;
	int id_semaforo;
	int done;
    int fin;
	int i;
    int rondas;
    int nro_jugador;
    int nro_mensaje;
    char cadena[50];
    int suceso;
    int puntos;
    int pinos[Cantidad_Jugadores];
    hilo_jugadores datos_jugadores[Cantidad_Jugadores];
	mensaje msg;
	int id_cola_mensajes;
    
    /* inicializacion */
    nro_mensaje = 0;
    puntos = 0;
    suceso = 0;
    nro_jugador = 0;
	done=0;
	i=0;
    fin = 0;
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	id_semaforo = creo_semaforo();
   	memoria[0] = 0;
   	inicio_semaforo(id_semaforo,VERDE);

   	espera_semaforo(id_semaforo);
   	memoria[0] = 1;
   	levanta_semaforo(id_semaforo);
    for ( i = 0; i < Cantidad_Jugadores; i++)
    {
        
        datos_jugadores[i].puntos=0;
        pinos[i]=10;
        
    }
    srand(time(NULL));

  	while (TRUE)
  	{
      		espera_semaforo(id_semaforo);
     	if (memoria[1] == 1)
     	{
         	levanta_semaforo(id_semaforo);
         	break;
     	}
      	else
      	{
         	levanta_semaforo(id_semaforo);
      	}
      	usleep(TIEMPO_ESPERA);
   	}

    for ( i = 0; i < Cantidad_Jugadores; i++)
    {
        enviar_mensaje(id_cola_mensajes,MSG_JUGADOR+i,MSG_BOLERA,EVT_INICIO,"");
    }
    
    while (done == 0)
    {
        
        recibir_mensaje(id_cola_mensajes,MSG_BOLERA,&msg);
        nro_jugador = msg.rte -2 ;
        if (nro_jugador < 0 || nro_jugador >= Cantidad_Jugadores) {
        printf("Error: índice de jugador fuera de rango: %d\n", nro_jugador);
        continue; 
        }
        nro_mensaje = msg.rte;
        rondas++;
        switch (msg.evento)
        {
            case EVT_TIRO:
                suceso = inDevolverNumeroAleatorio(1, pinos[nro_jugador]);
                if (rondas == 1)
                {
                    if (suceso == 10)
                    {
                        datos_jugadores[nro_jugador].puntos = 20;
                        pinos[nro_jugador] = 0;
                        printf("Jugador  %d hizo un tiro perfecto\n", nro_jugador);
                        printf("Chuzaaaa!\n");
                        sprintf(cadena, "%d", datos_jugadores[nro_jugador].puntos);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_JUGADOR + nro_jugador, EVT_FIN, cadena);
                    }
                    else
                    {   
                        printf("Jugador  %d tiró\n", nro_jugador);
                        printf("Tiró %d pinos \n", suceso);
                        datos_jugadores[nro_jugador].puntos = suceso;
                        pinos[nro_jugador] = pinos[nro_jugador] - suceso;
                        sprintf(cadena, "%d", datos_jugadores[nro_jugador].puntos);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_JUGADOR + nro_jugador, EVT_RESULTADO, cadena);
                    }
                }
                if (rondas == 2)
                {
                    if (suceso == pinos[nro_jugador])
                    {
                        datos_jugadores[nro_jugador].puntos += suceso;
                        pinos[nro_jugador] = 0;
                        printf("Jugador  %d hizo un tiro casi perfecto\n", nro_jugador);
                        printf("spare!\n");
                        sprintf(cadena, "%d", datos_jugadores[nro_jugador].puntos);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_JUGADOR + nro_jugador, EVT_FIN, cadena);
                    }
                    else
                    {   
                        printf("Jugador  %d tiró\n", nro_jugador);
                        printf("Tiró %d pinos \n", suceso);
                        datos_jugadores[nro_jugador].puntos += suceso;
                        pinos[nro_jugador] = pinos[nro_jugador] - suceso;
                        sprintf(cadena, "%d", datos_jugadores[nro_jugador].puntos);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_JUGADOR + nro_jugador, EVT_RESULTADO, cadena);
                    }
                }
                if (rondas == 3)
                {
                    if (suceso == pinos[nro_jugador])
                    {
                        datos_jugadores[nro_jugador].puntos += suceso;
                        pinos[nro_jugador] = 0;
                        printf("Jugador  %d hizo un tiro casi perfecto\n", nro_jugador);
                        printf("spare!\n");
                        sprintf(cadena, "%d", datos_jugadores[nro_jugador].puntos);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_JUGADOR + nro_jugador, EVT_FIN, cadena);
                    }
                    else
                    {   
                        printf("Jugador  %d tiró\n", nro_jugador);
                        printf("Tiró %d pinos \n", suceso);
                        datos_jugadores[nro_jugador].puntos += suceso;
                        pinos[nro_jugador] = pinos[nro_jugador] - suceso;
                        sprintf(cadena, "%d", datos_jugadores[nro_jugador].puntos);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_JUGADOR + nro_jugador, EVT_RESULTADO, cadena);
                    }
                    done = 1;
                    
                }
                

            break; 
        }
        
                
    }
    
    

    
    voLiberar_memoria(memoria, id_memoria);
    eliminar_semaforo(id_semaforo);
	borrar_mensajes(id_cola_mensajes);
    eliminar_cola_mensajes(id_cola_mensajes);
	

    return 0;

}
