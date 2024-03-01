#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

struct fila{
	int ini;
	int fim;
	int vet[20];
};

Fila inicializaFila(void){
	Fila f = (Fila) malloc(sizeof(Fila));
	f->ini = 0;
	f->fim = 0;
	return f;
}

int eCheia(Fila f){
	if(f->fim == 20)
		return 1;
	else
		return 0;
}

int eVazia(Fila f){
	if(f->fim == 0)
		return 1;
	else
		return 0;
}

void insereFila(Fila f, int x){
	if(eCheia(f)){
		printf("A fila esta cheia!!!\n");
		return;
	}
	else{
		f->vet[f->fim] = x;
		f->fim++;
	}
}

int removeDaFila(Fila f){
	if(f->fim == 0){
		printf("A fila esta vazia!\n");
		return -1;
	}
	else{
		int x = f->vet[f->ini];
		int i;
		for(i=0; i<(f->fim-1); i++)
			f->vet[i] = f->vet[i+1];
		f->fim--;
		return x;
	}
}

void imprimeFila(Fila f){
	if(f->fim==0)
		return;
	else{
		int i;
		for(i=f->ini; i<f->fim; i++)
			printf("%d\t",f->vet[i]);
	}
	printf("\n");
}

void destruirFila(Fila f){
	free(f);
}
