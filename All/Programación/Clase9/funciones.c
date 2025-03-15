#include "stdlib.h"
#include "stdio.h"



int inDevolverAleatorio(int inDesde,int inHasta)
{
	int num=0;
	num = (rand()%(inHasta-inDesde+1))+inDesde;
	return num;
}

int devolverAleatorioSinRepetir(int desde, int hasta, int *vector, int* size){

	int found = 0;
	int numero = 0;
	int i = 0;
	
	do{
		
		found = 0;		
		numero = inDevolverAleatorio(desde,hasta);
		for(i = 0; i < *size; i++){
			
			if( vector[i] == numero){
				found = 1;
			}
			
		}	
		
	} while(found);

	vector[*size]= numero;
	(*size)++;
	return numero;


}

int funcionPrimos(int n){

	int c=0,c2=0,res=0,nc=0, total=0;
	for(c=1;c<=n;c++)
	{
		for(c2=1;c2<=c;c2++)
		{
			res=c%c2;
			if(res==0)
				nc=nc+1;
		}
		if(nc==2)
			total+=c;
		nc=0;
	}
	return total;	
}

