#include <stdio.h>
#include <stdlib.h>

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

Arvore* insere(Arvore *a, int x){
	if(a==NULL){
		Arvore *no = (Arvore*) malloc(sizeof(Arvore));
		no->info = x;
		no->esq = NULL;
		no->dir = NULL;
		return no;
	}
	else{
		if(x <= a->info)
			a->esq = insere(a->esq,x);
		else
			a->dir = insere(a->dir,x);
	}
	return a;
}

Arvore* remover(Arvore *a, int x){
	if(a!=NULL){
		if(x < a->info)
			a->esq = remover(a->esq,x);
		else if(x > a->info)
			a->dir = remover(a->dir,x);
		else{ // x == a->info
			if(a->esq==NULL && a->dir==NULL){ // Situacao 1: no folha
				free(a);
				return NULL;
			}
			else if(a->esq==NULL || a->dir==NULL){ // Situacao 2: um filho != NULL
				Arvore *aux;
				if(a->esq==NULL)
					aux = a->dir;
				else
					aux = a->esq;
				free(a);
				return aux;
			}
			else{ // Situacao 3: dois filhos != NULL
				Arvore *aux = a->esq;
				while(aux->dir!=NULL)
					aux = aux->dir;
				a->info = aux->info;
				a->esq = remover(a->esq,aux->info);
				return a;
			}
		}
	}
	return a;
}

int busca(Arvore *a, int x){
	if(a==NULL)
		return 0;
	else{
		if(x==a->info)
			return 1;
		else{
			if(x < a->info)
				return busca(a->esq,x);
			else
				return busca(a->dir,x);
		}
	}
}

void imprimeMaiorIgual(Arvore *a, int x){ // imprime os maiores ou iguais a x
	if(a!=NULL){
		if(a->info==x){
			printf("%d\t",a->info);
			imprimeOrd(a->dir);
		}
		else if(a->info < x)
			imprimeMaiorIgual(a->dir,x);
		else{
			imprimeMaiorIgual(a->esq,x);
			printf("%d\t",a->info);
			imprimeOrd(a->dir);
		}
	}
}

void imprimeEntre(Arvore *a, int x, int y){
	if(a!=NULL){
		if(a->info==x || a->info>x){
			if(a->info<y){
				if(a->info==x)
					imprimeEntre(a->dir,x,y);
				else{
					imprimeEntre(a->esq,x,y);
					printf("%d\t",a->info);
					imprimeEntre(a->dir,x,y);
				}	
			}
			else
				imprimeEntre(a->esq,x,y);
		}
		else
			imprimeEntre(a->dir,x,y);
	}
}

Arvore *sair(Arvore *a){
	if(a==NULL)
		return a;
	else{
		sair(a->esq);
		sair(a->dir);
		free(a);
	}
}

int main(){
	int elem,maior,op,op2;
	Arvore *a;
	FILE *arq;
	
	do{
		printf("\n\n1 - Ler uma arvore binaria de busca\n");
		printf("2 - Imprimir a arvore\n");
		printf("3 - Inserir um no da arvore\n");
		printf("4 - Remover um no da arvore\n");
		printf("5 - Verifica se um no existe na arvore\n");
		printf("6 - Imprime nos da arvore maiores ou iguals a x\n");
		printf("7 - Imprime todos os valores da arvore entre x e y\n"); //y sempre maior que x
		printf("8 - Sair\n");
	
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
				printf("Informe o elemento:  ");
				scanf("%d",&elem);
				a = insere(a,elem);
				break;

			case 4:
				printf("Informe o elemento:  ");
				scanf("%d",&elem);
				a = remover(a,elem);
				break;

			case 5:
				printf("Informe o elemento:  ");
				scanf("%d",&elem);
				printf("\n%d",busca(a,elem));
				break;

			case 6:
				printf("Informe o elemento:  ");
				scanf("%d",&elem);
				printf("\n");
				imprimeMaiorIgual(a,elem);
				break;

			case 7:
				printf("Informe o elemento menor:  ");
				scanf("%d",&elem);
				printf("Informe o elemento maior:  ");
				scanf("%d",&maior);
				printf("\n");
				imprimeEntre(a,elem,maior);
				break;

			case 8:
				a = sair(a);
				break;
		}
	}while(op!=8);		
}
