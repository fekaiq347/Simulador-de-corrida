#ifndef LISTA_TXT_H
#define LISTA_TXT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct aux {
    char nomeArquivo[256]; // Caminho do arquivo .txt
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
} LISTA_TXT;

// Inicializa a lista
void inicializarListaTxt(LISTA_TXT* l) {
    l->inicio = NULL;
}

// Exclui um elemento da lista pelo nome do arquivo
bool excluirElementoLista(LISTA_TXT* l, char* nomeArquivo) {
    PONT ant = NULL, atual = l->inicio;
    while (atual != NULL && strcmp(atual->nomeArquivo, nomeArquivo) != 0) {
        ant = atual;
        atual = atual->prox;
    }
    if (atual == NULL) return false; // Elemento não encontrado
    if (remove(atual->nomeArquivo) != 0) return false; // Falha ao tentar remover o arquivo físico
    if (ant == NULL) l->inicio = atual->prox; // Remove o primeiro elemento da lista
    else ant->prox = atual->prox;
    free(atual);
    return true;
}

// Exibe os elementos da lista (nomes dos arquivos .txt)
void exibirElementosLista(LISTA_TXT* l) {
    PONT atual = l->inicio;
    while (atual != NULL) {
        printf("%s\n", atual->nomeArquivo);
        atual = atual->prox;
    }
}

// Insere um novo elemento na lista
bool inserirElementoLista(LISTA_TXT* l, char* nomeArquivo) {
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    if (novo == NULL) return false; // Falha ao alocar memória
    strcpy(novo->nomeArquivo, nomeArquivo);
    novo->prox = l->inicio;
    l->inicio = novo;
    return true;
}

#endif // LISTA_TXT_H