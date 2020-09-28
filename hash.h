#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    /* Defina aqui a estrutura de dado a ser usado na tabela hash */
    int i;
} Data;

typedef struct entrada {
    int chave;
    Data data;
    struct entrada *prox;
} Entrada;

typedef struct hash {
    Entrada **entradas;
    int TABLE_SIZE;
    int qtd;
} Hash;

Hash *criaHash(int TABLE_SIZE);

void liberaHash(Hash *hash);

int insereHash(Hash *hash, int chave, Data data);

void mostra_tabelahash(Hash *hash);

void mostra_tabela_com_enfase(Hash *hash, int chave);

int buscaHash(Hash *hash, int chave, Data *result);

int removerHash(Hash *hash, int chave);

float load_factor(Hash *hash);