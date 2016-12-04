typedef struct _grafo Grafo;

Grafo* grafoLe( char* filename );
Grafo* grafoLibera(Grafo* grafo);
void grafoMostra(Grafo* grafo);
void grafoPercorreProfundidade(Grafo * grafo, int no_inicial);
Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial);
void grafoPercorreLargura(Grafo * grafo, int no_inicial);
Grafo* arvoreCustoMinimo (char *filename);

int tem_ciclo (char *filename);
/* retorna 1 se existe algum ciclo no grafo não orientado no arquivo dado, 0 em caso contrário */

int num_componentes (char *filename);
/* retorna o número de componentes conexos do grafo não orientado no arquivo dado */

int nv_maior_componente (char *filename);
/* retorna o número de nós no maior componente conexo do grafo não orientado no arquivo dado */

/* formato do arquivo de teste.  grafo  
6       ! numero de nos 
5       ! numero de arestas 
0 1 20  ! aresta:  noi noj peso 
1 2 30  
1 3 25
3 4 15
4 5 10
*/