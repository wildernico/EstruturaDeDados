#include <stdio.h>
#include <stdlib.h>

//			Wilder Nico
//		  Arvore Binaria		 

typedef struct arvore{
	int info;
	struct arvore *esq;
	struct arvore *dir;
}Arvore;

Arvore *ler(FILE *arq){
	char c;
	int x;
	fscanf(arq,"%c",&c);
	fscanf(arq,"%d",&x);
	if(x==-1){
		fscanf(arq,"%c",&c);
		return NULL;
	}
	else{
		Arvore *no = (Arvore*) malloc(sizeof(Arvore));
		no->info = x;
		no->esq = ler(arq);
		no->dir = ler(arq);
		fscanf(arq,"%c",&c);
		return no;
	}
}

void imprimePre(Arvore* a){
	if(a!=NULL){
		printf("%d\t",a->info);
		imprimePre(a->esq);
		imprimePre(a->dir);
	}
}

void imprimeOrd(Arvore* a){
	if(a!=NULL){
		imprimeOrd(a->esq);
		printf("%d\t",a->info);
		imprimeOrd(a->dir);
	}
}

void imprimePos(Arvore* a){
	if(a!=NULL){
		imprimePos(a->esq);
		imprimePos(a->dir);
		printf("%d\t",a->info);
	}
}

int altura(Arvore *a){
	int alt1,alt2;

	if(a==NULL)
		return 0;
	else{
		alt1 = altura(a->esq) + 1;
		alt2 = altura(a->dir) + 1;
		if(alt1>alt2)
			return alt1;
		return alt2;
	}
}

int existe(Arvore *a, int elem){
	if(a==NULL)
		return 0;
	else{
		if(a->info == elem)
			return 1;
		else{
			if(existe(a->esq,elem)==1 || existe(a->dir,elem)==1)
				return 1;
			else
				return 0;
		}
	}
}

int quantNos(Arvore *a){
	if(a==NULL)
		return 0;
	else
		return 1 + quantNos(a->esq) + quantNos(a->dir);
}

Arvore* alteraNo(Arvore *a, int ant, int atual){
	if(!existe(a,ant))
		return a;
	else{
		if(a->info==ant){
			a->info=atual;
			printf("Elemento alterado com sucesso\n");
			return a;
		}
		else{
			alteraNo(a->esq,ant,atual);
			alteraNo(a->dir,ant,atual);
		}
	}
	return a;
}

Arvore *sair(Arvore *a){
	if(a==NULL)
		return a;
	else{
		Arvore *aux;
		aux->esq = a->esq;
		aux->dir = a->dir;
		free(a);
		a = aux->esq;
		sair(a);
		a = aux->dir;
		sair(a);
	}
}

int main(){
	int op,op2,elem,ant,atual;
	Arvore *a;
	FILE *arq;
	
	do{
		printf("\n1 - Ler uma arvore de um arquivo\n");
		printf("2 - Imprimir uma arvore\n");
		printf("3 - Calcular a altura da arvore\n");
		printf("4 - Verificar se um elemento existe na arvore\n");
		printf("5 - Conta o numero de nos da arvore\n");
		printf("6 - Alterar um conteudo do no da arvore\n");
		printf("7 - Sair\n");
	
		scanf("%d",&op);

		switch(op){
			case 1:
				arq = fopen("arquivo.txt","rt");
				if(arq!=NULL)
					a = ler(arq);
				else
					printf("Erro ao abrir o arquivo\n");
				fclose(arq);
				break;
			
			case 2:
				printf("1 - Imprimir Pre-Ordem\n");
				printf("2 - Imprimir Ordem\n");
				printf("3 - Imprimir Pos-Ordem\n");
				scanf("%d",&op2);
				if(op2==1)
					imprimePre(a);
				else
					if(op2==2)
						imprimeOrd(a);
				else
					if(op2==3)
						imprimePos(a);
				else
					printf("Opcao errada!\n");
				break;

			case 3:
				printf("%d\n",altura(a));
				break;

			case 4:
				printf("Informe o elemento\n");
				scanf("%d",&elem);
				printf("%d\n",existe(a,elem));
				break;

			case 5:
				printf("Numero de nos da arvore: %d\n",quantNos(a));
				break;

			case 6:
				printf("Informe o no antigo:  ");
				scanf("%d",&ant);
				printf("Informeo  no atual:  ");
				scanf("%d",&atual);
				if(!existe(a,ant))
					printf("Elemento nao encontrado\n");
				a = alteraNo(a,ant,atual);
				break;

			case 7:
				a = sair(a);
				break;
		}
	}while(op!=7);		
}
