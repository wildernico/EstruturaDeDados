#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
	int info;
	struct arvore *filho;
	struct arvore *irmao;
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
		no->filho = ler(arq);
		no->irmao = ler(arq);
		fscanf(arq,"%c",&c);
		return no;
	}
}

void imprimePre(Arvore *a){
	if(a!=NULL){
		printf("%d\t",a->info);
		imprimePre(a->filho);
		imprimePre(a->irmao);
	}
}

void imprimeNivel(Arvore *a, int nivel){
	if(a!=NULL){
		if(nivel==0){
			printf("%d\t",a->info);
			imprimeNivel(a->irmao,nivel);
		}
		else{
			imprimeNivel(a->filho, nivel-1);
			imprimeNivel(a->irmao, nivel);
		}
	}
}

void imprimeLarg(Arvore *a){
	int i;
	int alt = altura(a);
	for(i=0; i<alt; i++){
		imprimeNivel(a,i);
	}	
}

int altura(Arvore *a){
	if(a==NULL)
		return 0;
	else{
		int hf,hi;
		hf = altura(a->filho)+1;
		hi = altura(a->irmao);
		if(hi>hf)
			return hi;
		else
			return hf;
	}
}

int contNoNivel(Arvore *a, int nivel){
	if(a==NULL)
		return 0;
	else{
		if(nivel==0)
			return 1 + contNoNivel(a->irmao,nivel);
		else
			return contNoNivel(a->filho,nivel-1) + contNoNivel(a->irmao,nivel);
	}
}

void imprimeFolha(Arvore *a){
	if(a!=NULL){
		if(a->filho==NULL){
			printf("%d\t",a->info);
			imprimeFolha(a->irmao);
		}
		else{
			imprimeFolha(a->filho);
			imprimeFolha(a->irmao);
		}
	}
}

Arvore *sair(Arvore *a){
	if(a!=NULL){
		Arvore *noF = a->filho;
		Arvore *noI = a->irmao;
		free(a);
		sair(noF);
		sair(noI);
	}
	return NULL;
}

int main(){
	Arvore *a;
	FILE *arq;
	int nivel,op;
	
	do{
		printf("\n\n1 - Ler a arvore do arquivo\n");
		printf("2 - Imprime em pre-ordem\n");
		printf("3 - Imprime em largura\n");
		printf("4 - Calcula a altura da arvore\n");
		printf("5 - Conta o numero de nos de um determinado nivel da arvore\n");
		printf("6 - Imprime os nos folhas da arvore\n");
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
				imprimePre(a);
				break;

			case 3:
				imprimeLarg(a);
				break;

			case 4:
				printf("\n%d",altura(a));
				break;

			case 5:
				printf("Informe o nivel: ");
				scanf("%d",&nivel);
				printf("O numero de nos no nivel e: %d\n",contNoNivel(a,nivel));
				break;

			case 6:
				imprimeFolha(a);
				break;

			case 7:
				a = sair(a);
				break;
		}
	}while(op!=7);		
}
