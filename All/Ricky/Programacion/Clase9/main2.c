#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <def.h>
#include <funciones.h>
#include <sys/time.h>
#include <archivo.h>
#include <memoria.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <semaforo.h>
#include <thread.h>
#include <pthread.h>
#include <cronometro.h>
#include <global.h>



int main(int argc,char *argv[]){
	
	char con_thread = 's';
	int i, total=0;
	int cantidad = argc -1;
	int* num = (int*) malloc(sizeof(int)*(argc-1));
	

	
	pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad);
	pthread_attr_t 	atributos;
	
	
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	printf("PPAL: Cantidad = %d\n", cantidad);
	
	printf("PPAL: Con thread (s/n)");
	scanf(" %c", &con_thread);

	if (con_thread=='s')
		printf("\nPPAL: CON THREAD\n");
	else
		printf("\nPPAL: SIN THREAD\n");
	gettimeofday(&t_inicio, 0);


	for(i=0; i<cantidad; i++)
	{
		num[i]=atoi(argv[i+1]);	
		if (con_thread=='s')
			pthread_create (&idHilo[i], &atributos, funcionPrimosThread, &num[i]);
		else
			total +=funcionPrimos(num[i]); 
	}
	
	if (con_thread=='s')
	{
		for(i=0; i<cantidad; i++)
		{
			printf("PPAL: Voy a esperar al thread %d\n", i);
			pthread_join (idHilo[i], NULL);
			printf("PPAL: Recibi: %d\n", num[i]);
			total +=num[i];
		}
	}
	
	printf("PPAL: El total es %d\n", total);
	
	gettimeofday(&t_final, 0);

	printf("PPAL: Tiemplo empleado %dms\n", difMilli(t_inicio, t_final));
	free(idHilo);
    	return 0;

}
