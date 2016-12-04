typedef struct _listaprio ListaP;

/* cria nova lista de prioridades, opcionalmente passando uma lista inicial de prios */
ListaP *listap_cria (int tam);

/* insere um novo dado na lista */
void listap_insere (ListaP *lp, int prioridade, int no1, int no2); 

/* remove e retorna a maior prioridade */
int listap_remove(ListaP *lp, int* no1, int* no2);

/* libera a lista de prioridades */
void listap_libera(ListaP *lp);

/* sÃ³ para debug: enxerga representaÃ§Ã£o interna! */
void debug_listap_show (ListaP *hp, char* title);
