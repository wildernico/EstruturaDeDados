#include <stdio.h>
#include <stdlib.h>

void combSemRep(char *v1, char *v2, int pos, int tam){
	int i,j,aux=0;

	if(pos==tam){
		for(i=0;i<tam-1;i++){
			for(j=i+1;j<tam;j++){
				if(v1[i]==v1[j]){
					aux++;
					break;
				}
			}
			if(aux>0)
				break;
		}
		if(aux==0){
			printf("\n");
			for(i=0;i<tam;i++)
				printf("%c\t",v1[i]);
		}
	}
	else{
		for(i=0;i<5;i++){
			v1[pos]=v2[i];
			combSemRep(v1,v2,pos+1,tam);	
		}
	}	
}

void combDif(char *v1, char *v2, int pos, int tam){
	int i,j,aux=0;

	if(pos==tam){
		for(i=0;i<tam-1;i++){
			for(j=i+1;j<tam;j++){
				if(v1[i]>v1[j]){
					aux++;
					break;
				}
			}
		}
		if(aux==0){
			printf("\n");
			for(i=0;i<tam;i++)
				printf("%c\t",v1[i]);
		}
	}
	else{
		for(i=0;i<=4;i++){
			v1[pos]=v2[i];
			combDif(v1,v2,pos+1,tam);
		}
	}	
}

void quantMoedas(float *vetMoedas, int *vTotal, float x, int pos){
	int i,j,aux=0;
	float soma=0.0;

	if(pos==4){
		soma = vTotal[0] + vTotal[1]*0.50 + vTotal[2]*0.10 + vTotal[3]*0.01;
		if(soma == x){
			for(i=0;i<4;i++)
				printf("%d\t",vTotal[i]);
			printf("\n");
		}
	}
	else{
		int y = x/vetMoedas[pos];
		for(i=0;i<=y;i++){
			vTotal[pos] = i;
			quantMoedas(vetMoedas,vTotal,x,pos+1);
		}
	}	
}

int main(){
	int op,tam;
	char *v1,*v2;
	v2 = (char *) malloc(5*sizeof(char));
	v2[0] = 'a'; 
	v2[1] = 'e'; 
	v2[2] = 'i'; 
	v2[3] = 'o'; 
	v2[4] = 'u';
	float *vetMoedas,x;
	

	do{
		printf("\n1 - Todas as combinacoes de tamanho n de {a,e,i,o,u} sem repeticao de elementos\n");
		printf("2 - Todas as combinacoes diferentes de tamanho n de {a,e,i,o,u}\n");
		printf("3 - Maneiras de reunir moedas para totalizar o valor X lido\n");
		printf("4 - Sair\n");
	
		scanf("%d",&op);

		switch(op){
			case 1:
				printf("Informe o tamanho para combinacao: ");
				scanf("%d",&tam);
				if(tam>5)
					printf("Impossivel fazer combinacao sem repeticao de tamanho maior que 5\n");
				else{
					v1 = (char *) malloc(tam*sizeof(char));
					combSemRep(v1,v2,0,tam);
				}
				printf("\n");
				break;
		
			case 2:
				printf("Informe o tamanho da combinacao:  ");
				scanf("%d",&tam);
				v1 = (char *) malloc(tam*sizeof(char));
				combDif(v1,v2,0,tam);
				printf("\n");
				break;

			case 3:
				vetMoedas = (float *) malloc(4*sizeof(float));
				vetMoedas[0] = 1.0;
				vetMoedas[1] = 0.50;
				vetMoedas[2] = 0.10;
				vetMoedas[3] = 0.01;
				int *vTotal = (int *) malloc(4*sizeof(int));
				printf("Informe o valor:  ");
				scanf("%f",&x);
				printf("\nR$1,00\tR$0,50\tR$0,10\tR$0,01\n\n");
				quantMoedas(vetMoedas,vTotal,x,0);
				break;

			case 4:
				break;				
		}
	}while(op!=4);		
}

