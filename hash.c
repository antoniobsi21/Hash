#include "hash.h"

int chaveDivisao(int chave, int TABLE_SIZE){
    return chave % TABLE_SIZE;
}

Hash *criaHash(int TABLE_SIZE){
    Hash *hash = (Hash*) malloc(sizeof(hash));

    if(!hash){
        printf("Erro ao alocar memória para a tabela hash.\nSAINDO...");
        exit(1);
    }
    hash->TABLE_SIZE = TABLE_SIZE;
    hash->entradas = (Entrada**) malloc(TABLE_SIZE * sizeof(Entrada*));
    if(hash->entradas == NULL){
        printf("Erro ao alocar memoria para a tabela hash.\n");
        free(hash);
        return NULL;
    }

    hash->qtd = 0;
    
    int i = 0;
    for(; i < hash->TABLE_SIZE; i++){
        hash->entradas[i] = NULL;
    }
    
    return hash;
}

void liberaHash(Hash *hash){

    if(hash != NULL){
        int i;
        for(i = 0; i < hash->TABLE_SIZE; i++){

            if(hash->entradas[i] != NULL){
                Entrada *entrada = hash->entradas[i];
                for(; entrada != NULL; entrada = entrada->prox){
                    free(entrada);
                }
                free(hash->entradas[i]);
            }
        }
        free(hash->entradas);
        free(hash);
    }
}


int insereHash(Hash *hash, int chave, Data data){

    if(hash == NULL){
        return -1;
    }
    int pos = chaveDivisao(chave, hash->TABLE_SIZE);

    Entrada *entrada = hash->entradas[pos];

    Entrada *novo = (Entrada*) malloc(sizeof(Entrada));
    if(novo == NULL){
        return -1;
    }

    novo->data = data;
    novo->chave = chave;
    novo->prox = NULL;

    if(entrada != NULL){
        novo->prox = entrada;
        hash->entradas[pos] = novo;
    } else {
        hash->entradas[pos] = novo;
        hash->qtd++;
    }
    return pos;
}

void mostra_tabela_com_enfase(Hash *hash, int chave){
    if(hash == NULL){
        return;
    }
    Entrada **entradas = hash->entradas;
    int i = 0;
    printf("\n");
    while(i < hash->TABLE_SIZE){
        printf("| %d | -> ", i);
        if(entradas[i] != NULL){
            Entrada *ent = entradas[i];
            for(; ent != NULL; ent = ent->prox){
                if(chave == ent->chave){
                    printf("|||%d||| ->", ent->chave);
                } else{
                    printf("|%d| ->", ent->chave);
                }
            }
        }
        printf("\b\b\b   \n");
        i++;
    }
}

void mostra_tabelahash(Hash *hash){
    if(hash == NULL){
        return;
    }
    Entrada **entradas = hash->entradas;
    int i = 0;
    printf("\n");
    while(i < hash->TABLE_SIZE){
        printf("| %d | -> ", i);
        if(entradas[i] != NULL){
            Entrada *ent = entradas[i];
            for(; ent != NULL; ent = ent->prox){
                printf("|%d| ->", ent->chave);
            }
        }
        printf("\b\b\b   \n");
        i++;
    }
}

int buscaHash2(Hash *hash, int chave){
    // Famoso chaveDivisao2.0()
    if(hash == NULL){
        return -1;
    }
    int pos = chaveDivisao(chave, hash->TABLE_SIZE);

    return pos;
}

int removerHash(Hash *hash, int chave){
    int pos;

    if((pos = buscaHash2(hash, chave)) == -1){
        return 0;
    } else {
        Entrada *entrada = hash->entradas[pos], *ant = entrada, *temp;

        if(entrada == NULL){
            return 0;
        }

        for(; entrada != NULL && entrada->chave != chave; entrada = entrada->prox){

            ant = entrada;
        }

        if(entrada == NULL || chave != entrada->chave){
            return 0;
        }
        if(ant == entrada){
            if(entrada->prox != NULL){
                hash->entradas[pos] = ant->prox;
                free(entrada);
            } else {
                hash->qtd--;
                hash->entradas[pos] = NULL;
                free(entrada);
            }
        } else {
            temp = entrada;
            ant->prox = entrada->prox;
            free(temp);
        }
    }
    return 1;
}

float load_factor(Hash *hash){
    return (float)hash->qtd / (float)hash->TABLE_SIZE;
}