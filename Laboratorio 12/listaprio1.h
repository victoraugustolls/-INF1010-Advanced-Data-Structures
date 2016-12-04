typedef struct _listaprio ListaP;

/* cria nova lista de prioridades, opcionalmente passando uma lista inicial de prios */
ListaP *listap_cria (int max, int qtos, int* iniciais);

/* insere uma nova prioridade na lista */
void listap_insere (ListaP *lp, int prioridade); 

/* remove e retorna a maior prioridade */
int listap_remove(ListaP *lp);

/* libera a lista de prioridades */
void listap_libera(ListaP *lp);

/* sÃ³ para debug: enxerga representaÃ§Ã£o interna! */
void debug_listap_show (ListaP *hp, char* title);

int *cria_listaordenada (ListaP *lp, int* tam);