#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

struct arvore{
	struct arvore *esq, *dir;
	void *info;
	int id;
};

struct aluno{
	char nome[50];
	int mat;
	float cr;
};

Aluno *dadosAluno(){
	Aluno *al = (Aluno *) malloc(sizeof(Aluno));
	printf("Informe o nome do aluno:  ");
	scanf("%s",al->nome);
	printf("Informe a matricula do aluno:  ");
	scanf("%d",&al->mat);
	printf("Informe o cr do aluno:  ");
	scanf("%f",&al->cr);
	return al;
}

Arvore* insereAluno(Arvore *a, void *x, int id){
	if(a==NULL){
		Arvore *no = (Arvore*) malloc(sizeof(Arvore));
		no->id = id;
		no->info = x;
		no->esq = NULL;
		no->dir = NULL;
		return no;
	}
	else{
		Aluno *al = (Aluno *) a->info;
		Aluno *al2 = (Aluno *) x;
		if(al2->mat <= al->mat)
			a->esq = insereAluno(a->esq,x,id);
		else
			a->dir = insereAluno(a->dir,x,id);
	}
	return a;
}

Arvore* removeAluno(Arvore *a, int m){
	if(a!=NULL){
		Aluno *al = (Aluno *) a->info;
		if(m < al->mat)
			a->esq = removeAluno(a->esq,m);
		else if(m > al->mat)
			a->dir = removeAluno(a->dir,m);
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
				al = (Aluno *) aux->info;
				Aluno *al2 = (Aluno *) aux->info;
				a->esq = removeAluno(a->esq,al2->mat);
				return a;
			}
		}
	}
	return a;
}

int altura(Arvore *a){
	if(a==NULL)
		return 0;
	else{
		int altE,altD;
		altE = altura(a->esq) + 1;
		altD = altura(a->dir) + 1;
		if(altE>altD)
			return altE;
		else
			return altD;
	}
}

Arvore *balancear(Arvore *a){
	if(a!=NULL){
		int he,hd;
		
		a->esq = balancear(a->esq);
		a->dir = balancear(a->dir);
		he = altura(a->esq);
		hd = altura(a->dir);

		if(he-hd>1){ // desbalanceado para esquerda
			Arvore *p = a->esq;
			Aluno  *aux1, *aux2;	
			while(p->dir!=NULL)
				p=p->dir;
			aux1 = (Aluno *) a->info;
			aux2 = (Aluno *) p->info;
			a->esq = removeAluno(a->esq,aux2->mat);
			a->dir = insereAluno(a->dir,aux1,'a');
			a->info = aux2;
			a = balancear(a);
		}
		
		else if(hd-he>1){ // desbalanceado para direita
			Arvore *p = a->dir;
			Aluno  *aux1, *aux2;
			while(p->esq!=NULL)
				p=p->esq;
			aux1 = (Aluno *) a->info;
			aux2 = (Aluno *) p->info;
			a->dir = removeAluno(a->dir,aux2->mat);
			a->esq = insereAluno(a->esq,aux1,'a');
			a->info = aux2;
			a = balancear(a);
		}
	} //if(a!=NULL)
	return a;
}

int verificaBalancear(Arvore *a){
	int altE, altD;
	if(a!=NULL){
		altE = altura(a->esq);
		altD = altura(a->dir);
		if((altE-altD > 1) || (altD-altE > 1))
			return 0;
		else{
			verificaBalancear(a->esq);
			verificaBalancear(a->dir);
		}
	}
	return 1;
}

void imprimeNivel(Arvore *a, int nivel){
	if(a!=NULL){
		if(nivel==0){
			if(a->id == 'a'){
				Aluno *al = (Aluno *) a->info;
				printf("Nome:  %s\n",al->nome);
				printf("Matricula:  %d\n",al->mat);
				printf("CR:  %.2f\n\n",al->cr);
			}
		}
		else{
			imprimeNivel(a->esq, nivel-1);
			imprimeNivel(a->dir, nivel-1);
		}
	}
}

void imprimeLarg(Arvore *a){
	int i;
	int alt = altura(a);
	for(i=0; i<alt; i++){
		printf("\n ***** ALTURA %d *****\n",i+1);
		imprimeNivel(a,i);
	}	
}

void imprimeFolhas(Arvore *a){
	if(a!=NULL){
		if(a->esq==NULL && a->dir==NULL){
			if(a->id == 'a'){
				Aluno *al = (Aluno *) a->info;
				printf("Nome:  %s\n",al->nome);
				printf("Matricula:  %d\n",al->mat);
				printf("CR:  %f\n\n",al->cr);	
			}
		}
		else{
			imprimeFolhas(a->esq);
			imprimeFolhas(a->dir);
		}
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
