#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
	int mat;
	char nome[50];
}Aluno;

typedef struct professor{
	int mat;
	char nome[40];
	char tit[50];
	int pend;
}Prof;

typedef struct lista{
	int ID;
	void *info;
	struct lista *prox;
}Lista;

Lista* criaLista(){
	return NULL;
}

Lista *insereInicio(Lista *l, void *x, int id){
	Lista *no = (Lista *) malloc(sizeof(Lista));
	no->ID = id;
	no->info = x;
	no->prox = l;
	return no;
}

Aluno *dadosAluno(){
	Aluno *a = (Aluno *) malloc(sizeof(Aluno));
	printf("Informe a matricula do aluno:  ");
	scanf("%d",&a->mat);
	printf("Informe o nome do aluno:  ");
	scanf("%s",a->nome);
	return a;
}

Prof *dadosProf(){
	Prof *p = (Prof *) malloc(sizeof(Prof));
	printf("Informe a matricula do professor:  ");	
	scanf("%d",&p->mat);
	printf("Informe o nome do professor:  ");
	scanf("%s",p->nome);
	printf("Informe a titulacao:  ");
	scanf("%s",p->tit);
	printf("Informe o numero de pendentes  ");
	scanf("%d",&p->pend);
	return p;
}

Lista *insereFim(Lista *l, void *x, int id){
	if(l==NULL){
		Lista *no = (Lista *) malloc(sizeof(Lista));
		no->ID = id;
		no->info = x;
		no->prox = l;
		return no;
	}
	else
		l->prox = insereFim(l->prox,x,id);
	return l;
}

Lista *removeAluno(Lista *l, int m){
	if(l==NULL){
		return NULL;
	}
	else{ 
		if(l->ID=='a'){
			Aluno *no = (Aluno *) l->info;
			if(no->mat == m){
				Lista* aux = l->prox;
				free(l);
				return aux;
			}
			else
				l->prox = removeAluno(l->prox,m);
		}
		else
			l->prox = removeAluno(l->prox,m);
	}
	return l;
}

Lista *removeNo(Lista *l, int pos, int cont){
	if(l==NULL)
		return NULL;
	else{
		if(cont==pos){
			Lista* aux = l->prox;
			free(l);
			return aux;
		}
		else
			l->prox = removeNo(l->prox,pos,cont+1);
	}
	return l;
}

void imprime(Lista *l){
	if(l!=NULL){
		if(l->ID == 'a'){
			Aluno *a = (Aluno *) l->info;
			printf("Aluno\n");
			printf("Matricula: %d\n",a->mat);
			printf("Nome: %s\n\n",a->nome);
			imprime(l->prox);
		}
		else{
			Prof *p = (Prof *) l->info;
			printf("Professor\n");
			printf("Matricula: %d\n",p->mat);
			printf("Nome: %s\n",p->nome);
			printf("Titulacao: %s\n",p->tit);
			printf("Numero de pendentes: %d\n\n",p->pend);
			imprime(l->prox);
		}
	}
}

int conta(Lista *l){
	int cont=0;
	while(l!=NULL){
		cont++;
		l = l->prox;
	}
	return cont;
}

int existe(Lista *l, int m){
	if(l==NULL)
		return 0;

	else{
		Lista *aux = l;
		if(aux->ID == 'a'){
			Aluno *a = (Aluno *) aux->info;
			if(a->mat == m)
				return 1;
		}
		else{
			Prof *p = (Prof *) aux->info;
			if(p->mat == m)
				return 1;
		}
		existe(l->prox,m);
	}
}

Lista *sair(Lista *l){
	if(l==NULL)
		return l;
	else{
		Lista *aux = l->prox;
		free(l);
		sair(aux);
	}
}

int main(){
	int op,mat;
	char op2;
	Lista *l;
	l = criaLista();

	do{
		printf("\n\n1 - Inserir no inicio da lista\n");
		printf("2 - Inserir no fim da lista\n");
		printf("3 - Remover um determinado aluno da lista\n");
		printf("4 - Remover um no da lista\n");
		printf("5 - Imprimir a lista\n");
		printf("6 - Contar o numero de elementos da lista\n");
		printf("7 - Verificar se o elemento existe na lista\n");
		printf("8 - Sair\n");

		scanf("%d",&op);

		switch(op){
			case 1:
				printf("Digite 'a' para inserir Aluno ou 'p' para inserir Professor:\n");
				scanf("%c",&op2);
				scanf("%c",&op2);
				if(op2=='a'){
					Aluno *a = dadosAluno();
					l = insereInicio(l,a,'a');
				}
				else if(op2=='p'){
					Prof *p = dadosProf();
					l = insereInicio(l,p,'p');
				}
				else
					printf("\nDigito nao confere\n");
				break;

			case 2:
				printf("Digite 'a para inserir Aluno ou 'p' para inserir Professor\n");
				scanf("%c",&op2);
				scanf("%c",&op2);
				if(op2=='a'){
					Aluno *a = dadosAluno();
					l = insereFim(l,a,'a');
				}
				else if(op2=='p'){
					Prof *p = dadosProf();
					l = insereFim(l,p,'p');
				}
				else
					printf("\nDigito nao confere\n");
				break;

			case 3:
				printf("Informe a matricula: ");
				scanf("%d",&mat);
				l = removeAluno(l,mat);
				break;

			case 4:
				printf("Informe a posicao que deseja remover:  ");
				scanf("%d",&mat); //mat para nao criar outra variavel
				l = removeNo(l,mat,0);
				break;

			case 5:
				imprime(l);
				break;

			case 6:
				printf("%d\n",conta(l));
				break;

			case 7:
				printf("Informe a matricula:  ");
				scanf("%d",&mat);
				printf("%d\n",existe(l,mat));
				break;

			case 8:
				l = sair(l);
				break;
		}

	}while(op!=8);
	return 0;
}
