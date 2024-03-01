#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int op,m;
	Arvore *a = NULL;
	Aluno *al;
	
	do{
		printf("\n1 - Inserir um no da arvore\n");
		printf("2 - Remover um no da arvore\n");
		printf("3 - Balanceia\n");
		printf("4 - Verifica se esta balanceada\n");
		printf("5 - Altura da arvore\n");
		printf("6 - Imprime em largura\n");
		printf("7 - Imprime folhas\n");
		printf("8 - Sair\n");
	
		scanf("%d",&op);

		switch(op){
			case 1:
				al = dadosAluno();
				a = insereAluno(a,al,'a');
				break;

			case 2:
				printf("Informe a matricula:  ");
				scanf("%d",&m);
				a = removeAluno(a,m);
				break;

			case 3:
				a = balancear(a);
				break;

			case 4:
				printf("%d\n",verificaBalancear(a));
				break;

			case 5:
				printf("Altura:  %d\n",altura(a));
				break;

			case 6:
				imprimeLarg(a);
				break;

			case 7:
				imprimeFolhas(a);
				break;

			case 8:
				a = sair(a);
				break;
		}
	}while(op!=8);		
}
