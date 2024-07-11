#ifndef LISTA_ABPS_H
#define LISTA_ABPS_H
#include <stdio.h>
#include <stdlib.h>

int obterIndice(char letra);

typedef struct Produto {
    char nome[100];
    int quantidade;
} Produto;

typedef struct NodoABP {
    Produto produto;
    struct NodoABP *esquerda;
    struct NodoABP *direita;
} NodoABP;

typedef struct ListaDeABPs {
    NodoABP *abp[26]; 
} ListaDeABPs;

ListaDeABPs* inicializaListaDeABPs();
NodoABP* insereProduto(NodoABP *raiz, const char *nome, int quantidade);
Produto* consultaProduto(NodoABP *raiz, const char *nome);
NodoABP* removeProduto(NodoABP *raiz, const char *nome);
void exibeProdutosTotal(ListaDeABPs *lista);
void exibeProdutosLetra(ListaDeABPs *lista, char letra);
void exibeProdutosPorQuantidadeAcima(ListaDeABPs *lista, int quantidade);
void exibeProdutosPorQuantidadeAbaixo(ListaDeABPs *lista, int quantidade);
int totalProdutos(ListaDeABPs *lista);
int totalQuantidadesProdutos(ListaDeABPs *lista);

#endif 

