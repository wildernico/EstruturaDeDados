#include <stdio.h>
#include <stdlib.h>

//           WILDER NICO
//    LISTA ENCADEADA COM RECURSAO


typedef struct lista{
	int info;
	struct lista* prox;
}Lista;

Lista* criaLista(){
	return NULL;
}

Lista* insereInicio(Lista* l, int elem){
	Lista* p;
	p = (Lista*) malloc(sizeof(Lista));
	p->info = elem;
	p->prox = l;
	return p;
}

Lista* insereFinal(Lista* l, int elem){
	if(l==NULL){
		Lista* p = (Lista*) malloc(sizeof(Lista));
		p->info = elem;
		p->prox = l;
		l = p;
		return l;
	}
	else
		l->prox = insereFinal(l->prox,elem);
	return l;
}

Lista* removeElem(Lista* l, int elem){
	if(l==NULL){
		return NULL;
	}
	else{
		if(l->info == elem){
			Lista* aux = l->prox;
			free(l);
			l=aux;
			return removeElem(l,elem);
		}
		else
			l->prox = removeElem(l->prox,elem);
	}
	return l;
}

Lista* alteraElem(Lista* l, int antElem, int novoElem){
	if(l==NULL)
		return NULL;
	else{
		if(l->info==antElem){
			l->info = novoElem;
			alteraElem(l->prox,antElem,novoElem);
		}
		else
			alteraElem(l->prox,antElem,novoElem);
	}
	return l;
}
					
void imprime(Lista* l){
	if(l==NULL)
		return;
	else{
		printf("%d\n",l->info);
		imprime(l->prox);
	}
}

int existeElem(Lista* l,int elem){
	if(l==NULL)
		return 0;
	else
		if(l->info==elem)
			return 1;
	existeElem(l->prox,elem);
}


int contaPares(Lista* l){
	if(l==NULL)
		return 0;
	else{ 
		if(l->info%2==0){
			return l->info + contaPares(l->prox);
		}
		else
			contaPares(l->prox);		
	}
}

Lista* sair(Lista* l){
	if(l==NULL){
		return l;
	}
	else{
		Lista* p = l->prox;
		free(l);
		l=p;
		sair(l);
	}
}

int main(){
	Lista* l;
	l = criaLista();
	int op,elem,novoElem;

	do{
		printf("1 - Inserir no inicio da lista\n");
		printf("2 - Inserir no final da lista\n");
		printf("3 - Remover um elemento da lista\n");
		printf("4 - Alterar um elemento da lista\n");
		printf("5 - Imprimir a lista\n");
		printf("6 - Verifica se um elemento existe na lista\n");
		printf("7 - Contar os elementos pares da lista\n");
		printf("8 - Sair\n");
		scanf("%d",&op);

		switch (op){
			
			case 1:
				printf("Informe o elemento: ");
				scanf("%d",&elem);
				l = insereInicio(l,elem);
				break;
			
			case 2:
				printf("Informe o elemento: ");
				scanf("%d",&elem);
				l = insereFinal(l,elem);
				break;

			case 3:
				printf("Informe o elemento: ");
				scanf("%d",&elem);
				l = removeElem(l,elem);
				break;


			case 4:
				printf("Informe o elemento da lista: ");
				scanf("%d",&elem);
				printf("Informe o novo elemento: ");
				scanf("%d",&novoElem);
				l = alteraElem(l,elem,novoElem);
				break;

			case 5:
				printf("\n\n");
				imprime(l);
				printf("\n\n");
				break;

			case 6:
				printf("Informe o elemento: ");
				scanf("%d",&elem);
				if(existeElem(l,elem))
					printf("\nO elemento existe na lista\n\n");
				else
					printf("\nO elemento nao existe na lista\n\n");
				break;

			case 7:
				printf("\nO numero de pares na lista e %d\n\n",contaPares(l));
				break;

			case 8:
				l = sair(l); 
		} //switch

	}while(op!=8);

	return 0;
} //main




























