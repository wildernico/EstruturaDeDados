#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
	int mat;
	char nome[40];
}Aluno;

typedef struct professor{
	int mat;
	char nome[40];
	char tit[50];
	int pend;
}Prof;

typedef struct generico{
	char tipo;
	void *info;
}Generico;

Generico *inicia(int n){
	Generico *vet = (Generico *) malloc(n*sizeof(Generico));
	int i;
	
	for(i=0;i<n;i++){
		vet[i].tipo = 'v';
		vet[i].info = NULL;
	}
	return vet;
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
Generico *insereAluno(Generico *vet, void *x, int pos){

	if(vet[pos].tipo == 'v'){
		vet[pos].tipo = 'a';
		vet[pos].info = x;
		return vet; 
	}
	else if(vet[pos].tipo == 'a' || vet[pos].tipo == 'p'){
		vet[pos].tipo = 'v';
		free (vet[pos].info);
		insereAluno(vet,x,pos);
	}
}

Generico *insereProf(Generico *vet, void *x, int pos){

	if(vet[pos].tipo == 'v'){
		vet[pos].tipo = 'p';
		vet[pos].info = x;
		return vet; 
	}
	else if(vet[pos].tipo == 'a' || vet[pos].tipo == 'p'){
		vet[pos].tipo = 'v';
		free (vet[pos].info);
		insereAluno(vet,x,pos);
	}
}
		
void imprime(Generico *vet, int n, char op){
	int i;
	if(op=='a'){
		for(i=0; i<n; i++){
			if(vet[i].tipo == 'a'){
				Aluno *a = (Aluno *) vet[i].info;
				printf("\nAluno\n");
				printf("Matricula:  %d\n", a->mat);
				printf("Nome:  %s\n", a->nome);
			}
		}
	}
	else if(op=='p'){
		for(i=0; i<n; i++){
			if(vet[i].tipo == 'p'){
				Prof *p = (Prof *) vet[i].info; 
				printf("\nProfessor\n");
				printf("Matricula:  %d\n", p->mat);
				printf("Nome:  %s\n", p->nome);
				printf("Titulacao:  %s\n", p->tit);
				printf("Pendentes:  %d\n", p->pend);
			}
		}
	}
	else{
		for(i=0; i<n; i++){
			if(vet[i].tipo == 'a'){
				Aluno *a = (Aluno *) vet[i].info;
				printf("\nAluno\n");
				printf("Matricula:  %d\n", a->mat);
				printf("Nome:  %s\n", a->nome);
			}
			else if(vet[i].tipo == 'p'){
				Prof *p = (Prof *) vet[i].info;
				printf("\nProfessor\n");
				printf("Matricula:  %d\n",p->mat);
				printf("Nome:  %s\n", p->nome);
				printf("Titulacao:  %s\n", p->tit);
				printf("Pendentes:  %d\n", p->pend);
			}
		}
	}
}

int contaAluno(Generico *vet, int n){
	int i,cont=0;
	for(i=0; i<n; i++)
		if(vet[i].tipo == 'a')
			cont++;
	return cont;
}

int contaProf(Generico *vet, int n){
	int i,cont=0;
	for(i=0; i<n; i++)
		if(vet[i].tipo == 'p')
			cont++;
	return cont;
}

Generico *excluiProf(Generico *vet, int n, int mat){
	int i;
	for(i=0; i<n; i++){
		if(vet[i].tipo == 'p'){
			Prof *p = (Prof *) vet[i].info;
			if(p->mat == mat){
				vet[i].tipo = 'v';
				vet[i].info = NULL;	
			}
		}
	}
	return vet;
}

Generico *sair(Generico *vet, int n){
	int i;
	for(i=0; i<n; i++){
		vet[i].tipo = 'v';
		free(vet[i].info);
	}
	return vet;
}

int main(){
	Generico *vet;
	int n,op,pos,mat;
	char op2;

	printf("Informe a quantidade de elementos do vetor:  ");
	scanf("%d",&n);
	vet = inicia(n);


	do{
		printf("\n\n1 - Insere um aluno em uma determinada posicao do vetor\n");
		printf("2 - Insere um professor em uma determinada posicao do vetor\n");
		printf("3 - Imprimir Aluno ou Professor ou Todos\n");
		printf("4 - Conta a quantidade de alunos e professores inseridos\n");
		printf("5 - Exclui um professor pela matricula\n");
		printf("6 - Sair\n");

		scanf("%d",&op);
	
		switch(op){
			case 1:
				printf("Informe a posicao para inserir o aluno:  ");
				scanf("%d",&pos);
				if(pos>(n-1))
					printf("\nPosicao informada e maior que a posicao do vetor\n");
				else{
					Aluno *a = dadosAluno();
					vet = insereAluno(vet,a,pos);
				}
				break;

			case 2:
				printf("Informe a posicao para inserir o professor:  ");
				scanf("%d",&pos);
				if(pos>(n-1))
					printf("\nPosicao informada e maior que a posicao do vetor\n");
				else{
					Prof *p = dadosProf();
					vet = insereProf(vet,p,pos);
				}
				break;

			case 3:
				printf("'a' para aluno\n'p' para professor\n't' para todos\n");
				scanf("%c",&op2);
				scanf("%c",&op2);
				imprime(vet,n,op2);
				break;

			case 4:
				printf("Alunos:  %d\n",contaAluno(vet,n));
				printf("Professores:  %d\n",contaProf(vet,n));
				break;

			case 5:
				printf("Informe a matricula  ");
				scanf("%d",&mat);
				vet = excluiProf(vet,n,mat);
				break;

			case 6:
				vet = sair(vet,n);
				break;
		}		
	}while(op!=6);
	return 0;
}
