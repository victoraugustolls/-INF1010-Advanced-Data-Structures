#ifndef _MAPA_H
#define _MAPA_H

typedef struct smapa Mapa;

Mapa* cria (void);
Mapa* insere (Mapa* m, int chave, int novodado);
int busca (Mapa *m, int chave);
Mapa* remove2 (Mapa *m, int chave);
void destroi (Mapa *m);
void imprimeOrdenado (Mapa *m);
void imprime (Mapa *m);
int compara (Mapa* m1, Mapa* m2);

#endif
