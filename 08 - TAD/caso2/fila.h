typedef struct fila *Fila;
Fila inicializaFila(void);
int eCheia(Fila f);
int eVazia(Fila f);
void insereFila(Fila f, int x);
int removeDaFila(Fila f);
void imprimeFila(Fila f);
void destruirFila(Fila f);
