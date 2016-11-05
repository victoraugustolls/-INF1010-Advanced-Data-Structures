
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "mapa.h"

enum minhaposicao {
	ESQ,
	MEIO,
	DIR
};

typedef enum minhaposicao tpos;

enum resultadoretirada {
	OK,
	RETIRA_MENOR,
	RETIRA_MAIOR
};

typedef enum resultadoretirada tresultret;

struct smapa {
	int  kp, kg;   /* chaves: kp<kg, se kg existir. Se kg=-1, significa que ele não existe. */
	Mapa  *pai;
	Mapa  *esq;
	Mapa  *meio;
	Mapa  *dir;
};

Mapa* cria (void) {
	return NULL;
}

Mapa* novoNo (int chave) {
	Mapa *m = (Mapa*) malloc(sizeof(struct smapa));
	if (m == NULL) {
		printf ("erro no malloc! \n");
		exit(1);
	}
	m->pai = NULL;
	m->kp = chave; 
	m->kg = -1;
	m->esq = m->meio = m->dir = NULL;
	return m;
}

Mapa* overflowQuebra (Mapa *m, int *valorainserir, Mapa* novofilho) {
/* quebra o nó m em dois, cada um com uma chave                    */
/* entrada:                                                        */
/* m é nó com 2 chaves                                             */
/* *valorainserir é a nova chave                                   */
/* novofilho é subárvore que deve entrar à esquerda da nova chave  */
/* saída:                                                          */
/* retorno é o novo nó criado                                      */
/* *valorainserir é a mediana que tem que "subir"                  */

    Mapa* novo;
    
    novo = (Mapa*) malloc(sizeof(struct smapa));
    if (novo == NULL) {
        printf ("erro no malloc! \n");
        exit(1);
    }
    
    if (*valorainserir < m->kp) {
        // printf("valorainserir é menor\n");
    	novo->kp = *valorainserir;
        novo->esq = novofilho;
        novo->meio = m->esq;
        *valorainserir = m->kp;
        m->kp = m->kg;
        m->esq = m->meio;
        m->meio = m->dir;
    }
    else if ((*valorainserir > m->kp && *valorainserir < m->kg) || m->kg == -1) {
        // printf("valorainserir é médio\n");
        novo->kp = m->kp;
        novo->esq = m->esq;
        novo->meio = novofilho;
        m->esq = m->meio;
        m->kp = m->kg;
    }
    else {
        // printf("valorainserir é maior\n");
        novo->kp = m->kp;
        novo->esq = m->esq;
        novo->meio = m->meio;
        m->kp = *valorainserir;
        *valorainserir = m->kg;
        m->esq = novofilho;
        m->meio = m->dir;
    }
    
    novo->kg = -1;
    novo->dir = NULL;

    m->kg = -1;
    m->dir = NULL;

    if (novo->esq != NULL) {
        novo->esq->pai = novo->meio->pai = novo;
    }
    if (m->esq != NULL) {
        m->esq->pai = m->meio->pai = m;
    }
    novo->pai = m->pai;
    
    return novo;
}

int insere2 (Mapa* m, int chave, int* valorainserir, Mapa** novofilho) {

	// printf("Chave: %d\n", chave);

	int inseriraqui = 0; /* indica se deve inserir neste nó */

	if (m == NULL) {
		printf("erro! subárvore nula!\n");
		exit(1);
	}

	if (m->esq != NULL) { /* não é folha, só insere neste nó se chamada recursiva retornar mediana  */
		if (chave < m->kp) {
			// printf("Chave %d é menor\n", chave);
			inseriraqui = insere2(m->esq, chave, valorainserir, novofilho); 
		}
		else if (((m->kg != -1) && (chave < m->kg)) || (m->kg == -1)) {
			// printf("Chave %d é media\n", chave);
			/* ou está entre as duas chaves ou só tem uma chave no nó */
			inseriraqui = insere2(m->meio, chave, valorainserir, novofilho);
		}
		else {
			/* chave > m->kg */
			// printf("Chave %d é maior\n", chave);
			inseriraqui = insere2(m->dir, chave, valorainserir, novofilho);
		}
	}
	else { 
		/* este nó é folha, tem que inserir nele de qq jeito */
		// printf("m->esq é NULL, chave: %d\n", chave);
		*valorainserir = chave;
		inseriraqui = 1;
		*novofilho = NULL; /* neste caso novo item não tem uma subarvore associada */
	}

	if (!inseriraqui) {
		// printf("Insercao completa\n");
		return 0; /* inserção já está completa */
	}

	if (m->kg == -1) {
	  	if (*valorainserir < m->kp) {
	  		m->kg = m->kp;
	  		m->kp = *valorainserir;
	  		if (m->esq != NULL) {
	  			m->dir = m->meio;
	  			m->meio = m->esq;
	  			m->esq = *novofilho;
	  		}
	  	}
	  	else {
	  		m->kg = *valorainserir;
	  		if (*novofilho != NULL) {
	  			m->dir = m->meio;
	  			m->meio = *novofilho;
	  		}
	  	}
		return 0; /* como havia espaço, não sobem valores a serem inseridos */
	}

	*novofilho = overflowQuebra(m, valorainserir, *novofilho);

	return 1; /* quando há quebra sempre sobe a mediana para nova inserção */ 
}

Mapa* insere(Mapa* m, int chave) {
	int valorquesubiu;
	Mapa* novofilho;
	Mapa* novaraiz;

	// printf("Chave recebida: %d\n", chave);

	if (m == NULL) {
		m = novoNo(chave);
		m->pai = novoNo(-1);
	}
	else {
		if (insere2(m, chave, &valorquesubiu, &novofilho)) {
	  		/* cria nova raiz */
			novaraiz = novoNo(valorquesubiu);
		    novaraiz->pai = m->pai;
		    novaraiz->esq = novofilho;
		    novaraiz->esq->pai = novaraiz;
		    novaraiz->meio = m;
		    novaraiz->meio->pai = novaraiz;
		    m = novaraiz;
		} 
	}

	return m;
}


int busca (Mapa *m, int chave) {

	if (m == NULL){
		return INT_MAX;
	}

	if (m->kp == chave || m->kg == chave) {
		return chave;
	}
	else {
		if (chave < m->kp) {
			return busca(m->esq, chave);
		}
		else if (m->kg == -1 || chave < m->kg) {
			return busca(m->meio, chave);
		}
		else {
			return busca(m->dir, chave);
		}
	}

	return 0;
}

tpos minhaposnopai (Mapa* pai, Mapa* filho) {
	if (filho == pai->esq) {
		return ESQ;
	}
	else if (filho == pai->meio) {
		return MEIO;
	}
	else if (filho == pai->dir) {
		return DIR;
	}
	else {
		return -1;
	}
}

void preenche (Mapa *m, Mapa *nesq, int nkp, Mapa *nmeio, int nkg, Mapa *ndir) {
	m->esq = nesq;
	m->kp = nkp;
	m->meio = nmeio;
	m->kg = nkg;
	m->dir = ndir;
}

int maisaesquerda (Mapa *m) {
	while (m->esq != NULL) {
		m = m->esq;
	}
	return m->kp;
}

tresultret retirarec (Mapa *m, int chave) {

	tresultret res;
	tpos minhapos;
	Mapa *filhoqueficou, *irmao;

	if (m == NULL) {
		printf("erro! subárvore nula! \n"); exit (1);
	}

 	if (m->esq != NULL) { /* não é folha */
		if (chave < m->kp) {
			res = retirarec(m->esq, chave);
		}
	    else if (m->kp == chave) { /* achou - troca por succ */
			m->kp = maisaesquerda(m->meio);
			res = retirarec(m->meio, m->kp);
		}
		else if (((m->kg != -1) && (chave < m->kg)) || (m->kg == -1)) {
      		/* ou está entre as duas chaves ou só tem uma chave no nó */
			res = retirarec(m->meio, chave);
		}
    	else if (m->kg == chave) { /* achou - troca por succ */
			m->kg = maisaesquerda(m->dir);
			res = retirarec(m->dir, m->kg);
		}
    	else { /* chave > m->kg */
			res = retirarec(m->dir, chave);
		}
		if (res == OK) {
			return OK;
		}
	}
  	else { /* este nó é folha, chave tem que estar nele de qq jeito */
		if (chave == m->kp) {
			res = RETIRA_MENOR;
		}
		else if (chave == m->kg) {
			res = RETIRA_MAIOR;
		}
    	else {
    		/* chave não está na árvore!!! */
			return OK;
    	}
	}
  	/* retirada */
  	/* pode ser porque estamos em uma folha ou porque "caiu" uma das chaves */

  	if (res == RETIRA_MAIOR) { /* caso mais simples */
		preenche(m, m->esq, m->kp, m->meio ? m->meio : m->dir, -1, NULL);
		return OK;
	}

  	/* RETIRAMENOR */ 
	if (m->kg != -1) {
  		/* ainda vai ficar um no nó, tb simples */
		preenche(m, m->esq ? m->esq : m->meio, m->kg, m->dir, -1, NULL);
		return OK;
	}

  	/* RETIRAMENOR: essa é a única chave! combinar ou distribuir */

	minhapos = minhaposnopai(m->pai, m);

  	/* se ainda tiver algum filho pegá-lo para reposicionar */
	filhoqueficou = m->esq ? m->esq : m->meio;

	if (minhapos == ESQ) {
    	/* sempre tem irmao no meio - pegar */
    	// printf("Esq: chave %d\n", chave);
		irmao = m->pai->meio;
    	if (irmao->kg == -1) { /* combinar */
			preenche(irmao, filhoqueficou, m->pai->kp, irmao->esq, irmao->kp, irmao->meio);
			if (irmao->esq) {
				irmao->esq->pai = irmao;
			}
			m->pai->esq = NULL;
			free(m);
			res = RETIRA_MENOR;
		}
    	else { /* irmão tem duas chaves, redistribuir  */
			preenche(m, filhoqueficou, m->pai->kp, irmao->esq, -1, NULL);      
			if (m->esq) {
				m->esq->pai = m;
			}
			if (m->meio) {
				m->meio->pai = m;
			}
			preenche(m->pai, m->pai->esq, irmao->kp, m->pai->meio, m->pai->kg, m->pai->dir);
			preenche(irmao, irmao->meio, irmao->kg, irmao->dir, -1, NULL);
			res = OK;
		}  
	}
	else if (minhapos == MEIO) {
        /* sempre tem irmao a esquerda - pegar */
        // printf("Meio: chave %d\n", chave);
        irmao = m->pai->esq;
        if (irmao->kg == -1) { /* combinar */
            preenche(irmao, irmao->esq, irmao->kp, irmao->meio, m->pai->kp, filhoqueficou);
            if (irmao->dir) {
            	irmao->dir->pai = irmao;
            }
            m->pai->meio = NULL;
            free(m);
            res = RETIRA_MENOR;
        }
        else { /* irmão tem duas chaves, redistribuir  */
            preenche(m, irmao->dir, m->pai->kp, filhoqueficou, -1, NULL);
            if (m->esq) {
            	m->esq->pai = m;
            }
            if (m->meio) {
            	m->meio->pai = m;
            }
            preenche(m->pai, m->pai->esq, irmao->kg, m->pai->meio, m->pai->kg, m->pai->dir);
            preenche(irmao, irmao->esq, irmao->kp, irmao->meio, -1, NULL);
            res = OK;
        }
    }
    else if (minhapos == DIR) {
        /* sempre tem irmao a esquerda - pegar */
        // printf("Dir: chave %d\n", chave);
        irmao = m->pai->meio;
        if (irmao->kg == -1) { /* combinar */
            preenche(irmao, irmao->esq, irmao->kp, irmao->meio, m->pai->kp, filhoqueficou);
            if (irmao->dir) {
            	irmao->dir->pai = irmao;
            }
            m->pai->meio = NULL;
            free(m);
            res = RETIRA_MAIOR;
        }
        else { /* irmão tem duas chaves, redistribuir  */
            preenche(m, irmao->dir, m->pai->kp, filhoqueficou, -1, NULL);
            if (m->esq) {
            	m->esq->pai = m;
            }
            if (m->meio) {
            	m->meio->pai = m;
            }
            preenche(m->pai, m->pai->esq, irmao->kg, m->pai->meio, m->pai->kg, m->pai->dir);
            preenche(irmao, irmao->esq, irmao->kp, irmao->meio, -1, NULL);
            res = OK;
        }
    }

	return res;
}


Mapa* retira (Mapa *m, int chave) {
	tresultret res;
	Mapa* novaraiz;

	// printf("Retira chave: %d\n", chave);

	res = retirarec(m, chave);

 	if (res == RETIRA_MAIOR) { /* caso mais simples */
		preenche(m, m->esq, m->kp, m->meio ? m->meio : m->dir, -1, NULL);
	}

	else if (res == RETIRA_MENOR) {

		if (m->kg != -1) {
    		/* ainda vai ficar um no nó, tb simples */
			preenche(m, m->esq ? m->esq : m->meio, m->kg, m->dir, -1, NULL);
		}

		else {
      		/* vai acabar com a raiz */
      		/* um dos filhos virou nulo - pegar o outro */
			novaraiz = (m->esq) ? m->esq : m->meio;
			novaraiz->pai = m->pai;
			free(m);
			m = novaraiz;
		}
	}

	return m;
}

void destroi (Mapa *m) {
	if (m!= NULL) {
		destroi (m->esq);
		destroi (m->meio);
		destroi (m->dir);
		free (m);
	}
}

void debug_mostra_mapa_int (Mapa *m) {
  printf ("[");
  if (m != NULL) {
  	if (m->pai != NULL)
  	{
  		printf ("%d:%d/%d", m->kp, m->kg, m->pai->kp);
  	}
  	else {
  		printf ("%d:%d", m->kp, m->kg);
  	}
    
    debug_mostra_mapa_int (m->esq);
    debug_mostra_mapa_int (m->meio);
    if (m->kg != -1) {
    	debug_mostra_mapa_int(m->dir);
    }
  }
  printf ("]");
}

void debug_mostra_mapa (Mapa *m) {
	debug_mostra_mapa_int (m);
	printf("\n");
}