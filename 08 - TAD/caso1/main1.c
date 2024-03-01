#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Fila f;
	f = inicializaFila();
	int op,elem;
	
	do{
		printf("\n\n1 - Insere Fila\n");
		printf("2 - Remove Fila\n");
		printf("3 - Imprime\n");
		printf("4 - inicializa\n");
		printf("5 - Sair\n");
	
		scanf("%d",&op);

		switch(op){
			case 1:
				printf("Informe o elemento a ser inserido:  ");
				scanf("%d",&elem);
				insereFila(f,elem);
				break;
			
			case 2:
				elem = removeDaFila(f);
				printf("O elemento removido foi:  %d\n",elem);
				break;

			case 3:
				imprimeFila(f);
				break;
		
			case 4:
				f = inicializaFila();
				break;

			case 5:
				destruirFila(f);
				break;
		}
	}while(op!=5);		
}
	
