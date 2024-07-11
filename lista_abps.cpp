#include "lista_abps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListaDeABPs* inicializaListaDeABPs() {
    ListaDeABPs *lista = (ListaDeABPs*) malloc(sizeof(ListaDeABPs));
    if (lista) {
        for (int i = 0; i < 26; i++) {
            lista->abp[i] = NULL;
        }
    }
    return lista;
}

int obterIndice(char letra) {
    if ('A' <= letra && letra <= 'Z') {
        return letra - 'A';
    } else if ('a' <= letra && letra <= 'z') {
        return letra - 'a';
    } else {
        //trata se der erro
        return -1;
    }
}

NodoABP* insereProduto(NodoABP *raiz, const char *nome, int quantidade) {
    if (raiz == NULL) {
        NodoABP *novo = (NodoABP*) malloc(sizeof(NodoABP));
        if (novo) {
            strcpy(novo->produto.nome, nome);
            novo->produto.quantidade = quantidade;
            novo->esquerda = NULL;
            novo->direita = NULL;
            return novo;
        }
    } else {
        int comparacao = strcmp(nome, raiz->produto.nome);
        if (comparacao < 0) {
            raiz->esquerda = insereProduto(raiz->esquerda, nome, quantidade);
        } else if (comparacao > 0) {
            raiz->direita = insereProduto(raiz->direita, nome, quantidade);
        } else {
            printf("Produto ja existe.\n");
        }
    }
    return raiz;
}

Produto* consultaProduto(NodoABP *raiz, const char *nome) {
    while (raiz) {
        int comparacao = strcmp(nome, raiz->produto.nome);
        if (comparacao == 0) {
            return &raiz->produto;
        } else if (comparacao < 0) {
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }
    return NULL;
}

NodoABP* removeProduto(NodoABP *raiz, const char *nome) {
    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = strcmp(nome, raiz->produto.nome);
    if (comparacao < 0) {
        raiz->esquerda = removeProduto(raiz->esquerda, nome);
    } else if (comparacao > 0) {
        raiz->direita = removeProduto(raiz->direita, nome);
    } else {
        // sem filhos ou só 1
        if (raiz->esquerda == NULL) {
            NodoABP *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NodoABP *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

		// c/ filho
        NodoABP *temp = raiz->direita;
        while (temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        strcpy(raiz->produto.nome, temp->produto.nome);
        raiz->produto.quantidade = temp->produto.quantidade;
        raiz->direita = removeProduto(raiz->direita, temp->produto.nome);
    }
    return raiz;
}

void exibeEmOrdem(NodoABP *raiz) {
    if (raiz) {
        exibeEmOrdem(raiz->esquerda);
        printf("%s (%d)\n", raiz->produto.nome, raiz->produto.quantidade);
        exibeEmOrdem(raiz->direita);
    }
}

void exibeProdutosTotal(ListaDeABPs *lista) {
    for (int i = 0; i < 26; i++) {
        if (lista->abp[i] != NULL) {
            exibeEmOrdem(lista->abp[i]);
        }
    }
}

void exibeProdutosLetra(ListaDeABPs *lista, char letra) {
    int indice = obterIndice(letra);
    if (indice >= 0 && lista->abp[indice] != NULL) {
        exibeEmOrdem(lista->abp[indice]);
    } else {
        printf("Nenhum produto encontrado para a letra '%c'.\n", letra);
    }
}

void exibeProdutosPorQuantidadeAcimaAux(NodoABP *raiz, int quantidade) {
    if (raiz) {
        exibeProdutosPorQuantidadeAcimaAux(raiz->esquerda, quantidade);
        if (raiz->produto.quantidade >= quantidade) {
            printf("%s (%d)\n", raiz->produto.nome, raiz->produto.quantidade);
        }
        exibeProdutosPorQuantidadeAcimaAux(raiz->direita, quantidade);
    }
}

void exibeProdutosPorQuantidadeAcima(ListaDeABPs *lista, int quantidade) {
    for (int i = 0; i < 26; i++) {
        if (lista->abp[i] != NULL) {
            exibeProdutosPorQuantidadeAcimaAux(lista->abp[i], quantidade);
        }
    }
}

void exibeProdutosPorQuantidadeAbaixoAux(NodoABP *raiz, int quantidade) {
    if (raiz) {
        exibeProdutosPorQuantidadeAbaixoAux(raiz->esquerda, quantidade);
        if (raiz->produto.quantidade <= quantidade) {
            printf("%s (%d)\n", raiz->produto.nome, raiz->produto.quantidade);
        }
        exibeProdutosPorQuantidadeAbaixoAux(raiz->direita, quantidade);
    }
}

void exibeProdutosPorQuantidadeAbaixo(ListaDeABPs *lista, int quantidade) {
    for (int i = 0; i < 26; i++) {
        if (lista->abp[i] != NULL) {
            exibeProdutosPorQuantidadeAbaixoAux(lista->abp[i], quantidade);
        }
    }
}

int contarProdutos(NodoABP *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarProdutos(raiz->esquerda) + contarProdutos(raiz->direita);
}

int totalProdutos(ListaDeABPs *lista) {
    int total = 0;
    for (int i = 0; i < 26; i++) {
        total += contarProdutos(lista->abp[i]);
    }
    return total;
}

int somarQuantidades(NodoABP *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return raiz->produto.quantidade + somarQuantidades(raiz->esquerda) + somarQuantidades(raiz->direita);
}

int totalQuantidadesProdutos(ListaDeABPs *lista) {
    int total = 0;
    for (int i = 0; i < 26; i++) {
        total += somarQuantidades(lista->abp[i]);
    }
    return total;
}

