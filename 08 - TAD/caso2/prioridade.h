typedef struct filaPrioridade* FilaP;
FilaP inicializaFP(void);
void insereFP(FilaP fp, int x, char aux);
int removeFP(FilaP fp);
void imprimeFP(FilaP fp);
void sairFP(FilaP fp);
