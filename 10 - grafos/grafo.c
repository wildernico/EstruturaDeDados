#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int destino;
	float custo;
	struct lista *prox;
}Lista;

Lista **inicializa(int numVert){
	int i;
	Lista **g = (Lista **) malloc((numVert+1)*sizeof(Lista *));
	for(i=0;i<=numVert;i++)
		g[i] = NULL;
	return g;
}

Lista *insereLista(Lista *l, int d, float c){
	Lista *no = (Lista *) malloc(sizeof(Lista));
	no->destino = d;
	no->custo = c;
	no->prox = l;
	l = no;
	return l;
}

Lista **insereAresta(Lista **g, int origem, int destino, float custo){
	g[origem] = insereLista(g[origem], destino, custo);
	return g;
}

Lista *removeDaLista(Lista* l, int d){
	if(l==NULL){
		return NULL;
	}
	else{
		if(l->destino == d){
			Lista* aux = l->prox;
			free(l);
			l=aux;
			return removeDaLista(l,d);
		}
		else
			l->prox = removeDaLista(l->prox,d);
	}
	return l;
}
		
Lista **removeAresta(Lista **g, int origem, int destino){
	g[origem] = removeDaLista(g[origem],destino);
	return g;
}

void imprimeLista(Lista *l){
	while(l!=NULL){
		printf("%d|%.2f\t", l->destino, l->custo);
		l = l->prox;
	}
	printf("\n");
}

void imprimeGrafo(Lista **g, int numVert){
	int i;
	for(i=1;i<numVert+1;i++){
		printf("Vertice %d\n",i);
		imprimeLista(g[i]);
		printf("\n");
	}
}

int existeLista(Lista* l,int d){
	if(l==NULL)
		return 0;
	else
		if(l->destino==d)
			return 1;
	existeLista(l->prox,d);
}

int existeGrafo(Lista **g, int origem, int d){
	return existeLista(g[origem],d);
}

int grauVert(Lista **g, int vert){
	int grau=0;
	Lista *l = g[vert];
	while(l!=NULL){
		l = l->prox;
		grau++;
	}
	return grau;
}

int verificaCompleto(Lista **g, int numVert){
	int i,soma;
	for(i=1;i<numVert+1;i++){
		soma=0;
		Lista *l = g[i];
		while(l!=NULL){
			l = l->prox;
			soma++;
		}
		if(soma != numVert-1)
			return 0;
	}
	return 1;
}

/*
void menorCusto(Lista **g, int *vet, int pos, int destino){
	if(vet[pos-1] == destino){
		int i,j;
		float soma=0.0;
		for(j=0;j<pos;j++){
			Lista *l = g[vet[j]];
			if(l->destino != vet[pos]){
				l = l->prox;
			else{
				soma = soma + l->custo;
			}
		}
		printf("\n");
		for(i=0;i<pos;i++)
			printf("%d  ",vet[i]);
	}
	else{
		Lista *p = g[vet[pos-1]];
		while(p!=NULL){
			if(existeVetor(vet,pos,p->destino)==0){
				vet[pos] = p->destino;
				imprimeCaminhos(g,vet,pos+1,destino);
			}
			p = p->prox;
		}
	}
}
*/

int existeVetor(int *vet, int pos, int destino){
	int i;
	for(i=0;i<pos;i++){
		if(vet[i] == destino)
			return 1;
	}	
	return 0;
}

void imprimeCaminhos(Lista **g, int *vet, int pos, int destino){
	if(vet[pos-1] == destino){
		int i;
		printf("\n");
		for(i=0;i<pos;i++)
			printf("%d  ",vet[i]);
	}
	else{
		Lista *p = g[vet[pos-1]];
		while(p!=NULL){
			if(existeVetor(vet,pos,p->destino)==0){
				vet[pos] = p->destino;
				imprimeCaminhos(g,vet,pos+1,destino);
			}
			p = p->prox;
		}
	}
}

Lista *destruirLista(Lista *l){
	if(l==NULL){
		return l;
	}
	else{
		Lista* p = l->prox;
		free(l);
		l=p;
		destruirLista(l);
	}
}	

void destruirGrafo(Lista **g,int numVert){
	int i;
	for(i=1;i<numVert+1;i++)
		destruirLista(g[i]);
	free(g);
}

int main(){
	int op, numVert, origem, destino, vert;
	float custo;
	Lista **g;
	int *vet;
	vet = (int *) malloc(5*sizeof(int));
	vet[0] = 1; 
	vet[1] = -999; 
	vet[2] = -999; 
	vet[3] = -999; 
	vet[4] = -999;
	
	printf("Informe o numero de vertices: ");
	scanf("%d",&numVert);
	g = inicializa(numVert);
 
	do{
		printf("\n1 - Inserir uma aresta no grafo\n");
		printf("2 - Remover uma aresta do grafo\n");
		printf("3 - Imprimir o grafo\n");
		printf("4 - Verifica se uma aresta existe\n");
		printf("5 - Calcula o grau de saida de um determinado vertice\n");
		printf("6 - Verifica se o grafo e completo\n");
		printf("7 - Menor caminho (menor custo) entre dois vertices\n");
		printf("8 - Imprime todos os caminhos entre uma origem e um destino\n");
		printf("9 - Sair\n");
	
		scanf("%d",&op);

		switch(op){
			case 1:
				printf("Informe a origem: ");
				scanf("%d",&origem);
				printf("\n");
				printf("Informe o destino: ");
				scanf("%d",&destino);
				printf("\n");
				printf("Informe o custo: ");
				scanf("%f",&custo);
				printf("\n");
				g = insereAresta(g,origem,destino,custo);
				break;

			case 2:
				printf("Informe a origem: ");
				scanf("%d",&origem);
				printf("\n");
				printf("Informe o destino: ");
				scanf("%d",&destino);
				printf("\n");
				g = removeAresta(g,origem,destino);
				break;

			case 3:
				imprimeGrafo(g,numVert);
				break;

			case 4:
				printf("Informe a origem:  ");
				scanf("%d",&origem);
				printf("\n");
				printf("Informe o destino:  ");
				scanf("%d",&destino);
				printf("\n");
				printf("Retorno: %d\n",existeGrafo(g,origem,destino));
				break;

			case 5:
				printf("Informe o vertice:  ");
				scanf("%d",&vert);
				printf("Grau:  %d\n", grauVert(g,vert));
				break;

			case 6:
				printf("Retorno: %d\n", verificaCompleto(g,numVert));
				break;

			case 7:
			//	menorCusto(g,vet,1,destino);
				break;

			case 8:
				printf("Informe o destino:  ");
				scanf("%d",&destino);
				imprimeCaminhos(g,vet,1,destino);
				printf("\n");
				break;

			case 9:
				destruirGrafo(g,numVert);
				break;
		}
	}while(op!=9);		
}












































