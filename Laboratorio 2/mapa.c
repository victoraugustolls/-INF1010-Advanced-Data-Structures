#include "mapa.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct smapa {
    int chave;
    int conteudo;
    struct smapa* esq;
    struct smapa* dir;
} Mapa;

Mapa* cria() {
    return NULL;
}

Mapa* insere (Mapa* m, int chave, int novodado) {
    if (m == NULL) {
        m = (Mapa*)malloc(sizeof(Mapa));
        m->chave = chave;
        m->conteudo = novodado;
        m->esq = NULL;
        m->dir = NULL;
    }
    else if (chave < m->chave) {
        m->esq = insere(m->esq, chave, novodado);
    }
    else if (chave > m->chave) {
        m->dir = insere(m->dir, chave, novodado);
    }
    return m;
}

int busca (Mapa *m, int chave) {
    if (m == NULL) {
        return INT_MAX;
    }
    else if (m->chave == chave) {
        return m->conteudo;
    }
    else if (chave < m->chave) {
        return busca(m->esq, chave);
    }
    else if (chave > m->chave) {
        return busca(m->dir, chave);
    }
    else {
        return INT_MAX;
    }
}

Mapa* remove2 (Mapa *m, int chave) {
    if (m == NULL) {
        return NULL;
    }
    else if (chave < m->chave) {
        m->dir = remove2(m->dir, chave);
    }
    else if (chave > m->chave) {
        m->esq = remove2(m->esq, chave);
    }
    else {
        if (m->esq == NULL && m->dir == NULL) {
            free(m);
            return NULL;
        }
        else if (m->dir == NULL) {
            Mapa* aux = m;
            m = m->esq;
            free(aux);
        }
        else if (m->esq == NULL) {
            Mapa* aux = m;
            m = m->dir;
            free(aux);
        }
        else {
            Mapa* aux = m->dir;
            while (aux->esq != NULL) {
                aux = aux->esq;
            }
            m->conteudo = aux->conteudo;
            aux->chave = chave;
            m->dir = remove2(m->dir, chave);
        }
    }
    return m;
}

void destroi (Mapa *m) {
    if (m != NULL) {
        destroi(m->esq);
        destroi(m->dir);
        free(m);
    }
}

void imprimeOrdenado (Mapa* m) {
    if (m != NULL) {
        imprime(m->esq);
        printf("Chave: %d / Conteudo: %d\n", m->chave, m->conteudo);
        imprime(m->dir);
    }
}

void imprime (Mapa* m) {
    if (m != NULL) {
        printf("Chave: %d / Conteudo: %d\n", m->chave, m->conteudo);
        imprime(m->esq);
        imprime(m->dir);
    }
}
