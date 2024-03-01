#include "fila.h"
#include "prioridade.h"
#include <stdio.h>
#include <stdlib.h>

struct filaPrioridade{
	Fila comum;
 	Fila prioritaria;
};

FilaP inicializaFP(){
	FilaP fp = (FilaP) malloc(sizeof(FilaP));
	fp->prioritaria = inicializaFila();
	fp->comum = inicializaFila();
	return fp;
}

void insereFP(FilaP fp, int x, char aux){
	if(aux=='p'){
		if(eCheia(fp->prioritaria))
			printf("Fila prioritaria esta cheia!\n");
		else
			insereFila(fp->prioritaria, x);
	}
	else{ 
		if(aux=='c'){	
			if(eCheia(fp->comum))
				printf("Fila comum esta cheia!");
			else
				insereFila(fp->comum, x);
		}
	}
}

int removeFP(FilaP fp){
	if(!(eVazia(fp->prioritaria)))
		return removeDaFila(fp->prioritaria);
	else{
		if(eVazia(fp->comum))
			printf("Fila prioritaria e comum estao vazias!\n");
		else
			return removeDaFila(fp->comum);
	}
}

void imprimeFP(FilaP fp){
	printf("\nFila de Prioridade\n");
	imprimeFila(fp->prioritaria);
	printf("\nFila comum\n");
	imprimeFila(fp->comum);
}

void sairFP(FilaP fp){
	destruirFila(fp->comum);
	destruirFila(fp->prioritaria);
}
