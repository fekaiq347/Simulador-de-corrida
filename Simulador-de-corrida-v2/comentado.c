#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "lista.h" // Header file que contém a definição e funções relacionadas à lista

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

// Estrutura que representa um corredor
typedef struct {
    char nome[100];
    float tempo;
} Corredor;

// Declaração das funções utilizadas no programa
void simularCorrida(Corredor corredores[], LISTA_TXT* listaResultados, int* qtdCorredores);
void ordenarCorredores(Corredor corredores[], int qtdCorredores);
void exibirResultados(Corredor corredores[], int qtdCorredores);
void salvarResultados(Corredor corredores[], int qtdCorredores, LISTA_TXT* listaResultados);
void menuPrincipal(LISTA_TXT* listaResultados);
void limparTela();
void printBanner();
int refazerCorrida();
void novoMenu(Corredor corredores[], LISTA_TXT* listaResultados, int* qtdCorredores);

// Função principal que inicia o programa
int main() {
    printBanner(); // Imprime o banner inicial
    LISTA_TXT listaResultados;
    inicializarListaTxt(&listaResultados); // Inicializa a lista de resultados
    menuPrincipal(&listaResultados); // Chama o menu principal
    return 0;
}

// Função que exibe um menu para operações após a simulação da corrida
void novoMenu(Corredor corredores[], LISTA_TXT* listaResultados, int* qtdCorredores) {
    int opcao;
    while (opcao != 4) {
        printBanner();
        printf("\n");
        printf("%sMenu da Corrida%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
        printf("%s[1]%s Exibir:\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
        printf("%s[2]%s Salvar\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
        printf("%s[3]%s Refazer corrida\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
        printf("%s[4]%s Sair\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        printf("\n");
        scanf("%d", &opcao);
        switch (opcao) {                                                                              
            case 1:
                exibirResultados(corredores, *qtdCorredores); // Exibe os resultados da corrida
                break;
            case 2:
                salvarResultados(corredores, *qtdCorredores, listaResultados); // Salva os resultados da corrida
                break;
            case 3:
                if (refazerCorrida()) {
                    // Refaz a corrida com os mesmos dados
                    for (int i = 0; i < *qtdCorredores; i++) {
                        corredores[i].tempo = (float)rand() / RAND_MAX * 100;
                    ordenarCorredores(corredores, *qtdCorredores);
                    }
                } else {
                    simularCorrida(corredores, listaResultados, qtdCorredores); // Simula uma nova corrida
                    return; // Sai da função atual para evitar loop infinito
                }
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

// Função que simula a corrida
void simularCorrida(Corredor corredores[], LISTA_TXT* listaResultados, int* qtdCorredores) {
    srand(time(NULL));
    for (int i = 0; i < *qtdCorredores; i++) {
        printf("Nome do corredor %d: ", i + 1);
        scanf("%99s", corredores[i].nome);
        corredores[i].tempo = (float)rand() / RAND_MAX * 100; // Simula o tempo do corredor
    }

    ordenarCorredores(corredores, *qtdCorredores); // Ordena os corredores por tempo
    novoMenu(corredores, listaResultados, qtdCorredores); // Exibe o menu de opções pós-corrida
}

// Função que ordena os corredores por tempo
void ordenarCorredores(Corredor corredores[], int qtdCorredores) {
    for (int i = 0; i < qtdCorredores - 1; i++) { // Bubble Sort que organiza os corredores por tempo
        for (int j = 0; j < qtdCorredores - i - 1; j++) {
            if (corredores[j].tempo > corredores[j + 1].tempo) {
                Corredor temp = corredores[j];
                corredores[j] = corredores[j + 1];
                corredores[j + 1] = temp;
            }
        }
    }
}

// Função que exibe os resultados da corrida
void exibirResultados(Corredor corredores[], int qtdCorredores) {
    for (int i = 0; i < qtdCorredores; i++) {
        printf("%d. %s - %.2f\n", i + 1, corredores[i].nome, corredores[i].tempo);
    }
}

// Função que salva os resultados da corrida em um arquivo
void salvarResultados(Corredor corredores[], int qtdCorredores, LISTA_TXT* listaResultados) {
    char nomeArquivo[100];
    printf("Nome do arquivo para salvar os resultados: ");
    scanf("%99s", nomeArquivo);
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    for (int i = 0; i < qtdCorredores; i++) {
        fprintf(arquivo, "%d. %s - %.2f\n", i + 1, corredores[i].nome, corredores[i].tempo);
    }
    fclose(arquivo);
    // Adiciona o nome do arquivo à lista de resultados
    inserirElementoLista(listaResultados, nomeArquivo);
}

// Função que pergunta ao usuário se deseja refazer a corrida com os mesmos dados
int refazerCorrida() {
    char escolha;
    printf("Deseja refazer a corrida com os mesmos dados? (S/N): ");
    scanf(" %c", &escolha);
    return (escolha == 'S' || escolha == 's') ? 1 : 0;
}

// Função que procura o tempo mais próximo ao fornecido pelo usuário
void procuraResultado(float tempo, int qtd_corredores, char nome_arquivo[]){
    float anterior = 0, atual = 100;
    int lixo_1, i = 0, index;
    Corredor corredores[qtd_corredores];
    char linha[100];
    
    FILE *file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        exit(EXIT_FAILURE);
    }
    
    while (i < qtd_corredores && fgets(linha, sizeof(linha), file) != NULL) { // Guarda os corredores em um vetor
        sscanf(linha, "%d. %s - %f",&lixo_1, corredores[i].nome, &corredores[i].tempo);
        i++;
    }
    
    for(i = 0; i<qtd_corredores; i++){ // Busca sequencial por módulo
        anterior = fabs(corredores[i].tempo-tempo);
        if(anterior<=atual){
            atual = anterior;
            index = i;
        }
    }
    printf("O corredor com o tempo mais proximo:%s%s%s\nDiferenca de:%s%.2f%s\n\n\n\n", ANSI_COLOR_GREEN, corredores[index].nome, ANSI_COLOR_RESET, ANSI_COLOR_RED, atual, ANSI_COLOR_RESET);
}

// Função que limpa a tela
void limparTela() {
    system("clear||cls");
}

// Função que imprime o banner do programa
void printBanner() {
    char banner[] = 
    "███████╗██╗███╗   ███╗██╗   ██╗██╗      █████╗ ██████╗  ██████╗ ██████╗\n"    
    "██╔════╝██║████╗ ████║██║   ██║██║     ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗\n"    
    "███████╗██║██╔████╔██║██║   ██║██║     ███████║██║  ██║██║   ██║██████╔╝\n"    
    "╚════██║██║██║╚██╔╝██║██║   ██║██║     ██╔══██║██║  ██║██║   ██║██╔══██╗\n"    
    "███████║██║██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║██████╔╝╚██████╔╝██║  ██║\n"    
    "╚══════╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝     \n"
    
}