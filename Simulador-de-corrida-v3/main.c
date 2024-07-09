#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "lista.h" // Header file que contém a definição e funções relacionadas à lista
#include "fcoes.h" // Header file que contém a definição e funções relacionadas à implementação 

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

void menuPrincipal(LISTA_TXT* listaResultados) {
    int opcao, qtdCorredores;
    Corredor corredores[100]; // Limite de 100 corredores para simplificação
    char nomearq[100];
    float tempo;
    limparTela();
    do {
        printBanner();
        printf("\nMenu Principal\n");
        printf("%s[1]%s Simular corrida\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
        printf("%s[2]%s Listar corridas\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
        printf("%s[3]%s Exibir corrida\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
        printf("%s[4]%s Excluir corrida\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
        printf("%s[5]%s Procurar tempo\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
        printf("%s[6]%s Sair\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        printf("\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe a quantidade de corredores: ");
                scanf("%d", &qtdCorredores);
                simularCorrida(corredores, listaResultados, &qtdCorredores);
                break;
            case 2:
                exibirElementosLista(listaResultados);
                break;
            case 3:
            printf("Digite o nome do arquivo para exibir a corrida: ");
            scanf("%99s", nomearq);

            FILE* arquivo = fopen(nomearq, "r");
            if (arquivo == NULL){
                printf("Erro ao abrir o arquivo.\n");
                break;
            }

            char linha[150];
            while (fgets(linha, sizeof(linha), arquivo) != NULL){
            printf("%s", linha);
            }

            fclose(arquivo);
            break;
            case 4:
            printf("Digite o nome do arquivo para exibir a corrida: ");
            scanf("%99s", nomearq);

            if(excluirElementoLista(listaResultados, nomearq)){
                printf("Arquivo excluido com sucesso\n");
                break;
            }
            else{
                printf("Erro ao excluir arquivo\n");
            }
                break;
            case 5:
                printf("Informe tempo a ser buscado: ");
                scanf("%f", &tempo);
                printf("Digite o nome do arquivo: ");
                scanf("%99s", nomearq);
                procuraResultado(tempo, qtdCorredores, nomearq);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 6);
    
    return;
}

// Função principal que inicia o programa
int main() {
    printBanner(); // Imprime o banner inicial
    LISTA_TXT listaResultados;
    inicializarListaTxt(&listaResultados); // Inicializa a lista de resultados

    menuPrincipal(&listaResultados); // Chama o menu principal
    return 0;
}
