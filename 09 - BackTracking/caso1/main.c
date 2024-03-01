#include <stdio.h>
#include <stdlib.h>

void combinacao567(int *vet, int pos, int n){
	int i;
	
	if(pos==n){
		printf("\n");
		for(i=0;i<pos;i++)
			printf("%d\t",vet[i]);
	}
	else{
		for(i=5;i<=7;i++){
			vet[pos]=i;
			combinacao567(vet,pos+1,n);
		}
	}	
}

void combNaoRepetidos(int *vet, int pos, int n){
	int i,j,aux=0;

	if(pos==n){
		for(i=0;i<n-1;i++){
			if(vet[i]==vet[i+1])
				aux++;
		}
		if(aux==0){
			printf("\n");
			for(i=0;i<n;i++)
				printf("%d\t",vet[i]);
		}
	}
	else{
		for(i=5;i<=9;i++){
			vet[pos]=i;
				combNaoRepetidos(vet,pos+1,n);	
		}
	}	
}

void combinacaoA9Z(char *vet, char *vet2, int pos, int n ){
	int i;
	
	if(pos==n){
		printf("\n");
		for(i=0;i<pos;i++)
			printf("%c\t",vet[i]);
	}
	else{
		for(i=0;i<3;i++){
			vet[pos]=vet2[i];
			combinacaoA9Z(vet,vet2,pos+1,n);
		}
	}	 
}

int main(){
	int *vet,n,op;
	char *v,*v2;

	do{
		printf("\n\n1 - Imprime combinacoes de tamanho n de 5,6 e 7\n");
		printf("2 - Imprime combinacoes de tamanho n de 5,6,7,8,9 sem elementos repetidos\n");
		printf("3 - Imprime todas as combinacoes de n elementos de a,9,z\n");
		printf("4 - Sair\n");
		scanf("%d",&op);
		
		switch(op){
			case 1:
				vet = (int *) malloc(3*sizeof(int));
				printf("Informe o tamanho da combinacao:  ");
				scanf("%d",&n);
				combinacao567(vet,0,n);
				printf("\n\n");
				break;

			case 2:
				vet = (int *) malloc(5*sizeof(int));
				printf("Informe o tamanho da combinacao:  ");
				scanf("%d",&n);
				combNaoRepetidos(vet,0,n);
				printf("\n\n");
				break;

			case 3:
				v = (char *) malloc(3*sizeof(char));
				v2 = (char *) malloc(3*sizeof(char));
				v2[0] = 'a';
				v2[1] = '9';
				v2[2] = 'z';
				printf("Informe o tamanho da combinacao:  ");
				scanf("%d",&n);
				combinacaoA9Z(v,v2,0,n);
				printf("\n\n");
				break;

			case 4:
				break;
		}
	}while(op!=4);
	return 0;
}
