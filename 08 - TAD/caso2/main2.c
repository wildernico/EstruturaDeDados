#include "prioridade.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
	FilaP fp;
	fp = inicializaFP();
	int num=-1,op,elem;
	char aux;

	do{
		printf("\n\n1 - Insere Fila\n");
		printf("2 - Remove Fila\n");
		printf("3 - Imprime\n");
		printf("4 - Inicializa\n");
		printf("5 - Sair\n");
	
		scanf("%d",&op);

		switch(op){
			case 1:
				printf("Informe o elemento a ser inserido:  ");
				scanf("%d",&elem);
				printf("Digite 'p' para inserir na fila prioritaria ou 'c' para inserir na comum\n");
				scanf("%c",&aux);
				scanf("%c",&aux);
				if(aux=='p' || aux=='c')
					insereFP(fp,elem,aux);
				else
					printf("Opcao errada!\n");
				break;

			case 2:
				num = removeFP(fp);
				printf("O elemento removido foi:  %d\n",num);
				break;

			case 3:
				imprimeFP(fp);				
				break;
			
			case 4:
				fp = inicializaFP();
				break;

			case 5:
				sairFP(fp);
				break;
		}
	}while(op!=5);
	return 0;
}
