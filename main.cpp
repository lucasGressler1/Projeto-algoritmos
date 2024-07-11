#include "lista_abps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu() {
    printf("|--------------------------------|\n");
    printf("| Menu:                          |\n");
    printf("| 1. Inserir produto             |\n");
    printf("| 2. Consultar produto           |\n");
    printf("| 3. Remover produto             |\n");
    printf("| 4. Exibir todos os produtos    |\n");
    printf("| 5. Exibir produtos por letra   |\n");
    printf("| 6. Exibir produtos acima       |\n");
    printf("| 7. Exibir produtos abaixo      |\n");
    printf("| 8. Total de produtos           |\n");
    printf("| 9. Total de quantidades        |\n");
    printf("| 0. Sair                        |\n");
    printf("|--------------------------------|\n");
    printf("Escolha uma opcao: ");
}

int main() {
    ListaDeABPs *lista = inicializaListaDeABPs();
    int opcao;
    char nome[100];
    int quantidade;
    Produto *resultado;
    char letra;
    int valor;

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Nome do produto: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; 
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                lista->abp[obterIndice(nome[0])] = insereProduto(lista->abp[obterIndice(nome[0])], nome, quantidade);
                break;

            case 2:
                printf("Nome do produto: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; 
                resultado = consultaProduto(lista->abp[obterIndice(nome[0])], nome);
                if (resultado) {
                    printf("Produto encontrado: %s (%d)\n", resultado->nome, resultado->quantidade);
                } else {
                    printf("Produto nao encontrado.\n");
                }
                break;

            case 3:
                printf("Nome do produto: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; 
                lista->abp[obterIndice(nome[0])] = removeProduto(lista->abp[obterIndice(nome[0])], nome);
                printf("Produto removido (se existia).\n");
                break;

            case 4:
                printf("Lista de produtos:\n");
                exibeProdutosTotal(lista);
                break;

            case 5:
                printf("Digite a letra para exibir os produtos: ");
                scanf("%c", &letra);
                getchar();
                exibeProdutosLetra(lista, letra);
                break;

            case 6:
                printf("Digite a quantidade para exibir produtos acima: ");
                scanf("%d", &valor);
                exibeProdutosPorQuantidadeAcima(lista, valor);
                break;

            case 7:
                printf("Digite a quantidade para exibir produtos abaixo: ");
                scanf("%d", &valor);
                exibeProdutosPorQuantidadeAbaixo(lista, valor);
                break;

            case 8:
                printf("Total de produtos: %d\n", totalProdutos(lista));
                break;

            case 9:
                printf("Total de quantidades: %d\n", totalQuantidadesProdutos(lista));
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

