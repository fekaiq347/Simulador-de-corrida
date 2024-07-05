#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "lista.h" 

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

typedef struct {
    char nome[100];
    float tempo;
} Corredor;

void simularCorrida(Corredor corredores[], LISTA_TXT* listaResultados, int* qtdCorredores);
void ordenarCorredores(Corredor corredores[], int qtdCorredores);
void exibirResultados(Corredor corredores[], int qtdCorredores);
void salvarResultados(Corredor corredores[], int qtdCorredores, LISTA_TXT* listaResultados);
void menuPrincipal(LISTA_TXT* listaResultados);
void limparTela();
void printBanner();
int refazerCorrida();
void novoMenu(Corredor corredores[], LISTA_TXT* listaResultados, int* qtdCorredores);

int main() {
    printBanner();                                                                 
    LISTA_TXT listaResultados;
    inicializarListaTxt(&listaResultados);
    menuPrincipal(&listaResultados);
    return 0;
}

void novoMenu(Corredor corredores[], LISTA_TXT* listaResultados, int* qtdCorredores) {
    int opcao;
    while (opcao != 4){

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
            exibirResultados(corredores, *qtdCorredores); 
            break;
        case 2:
            salvarResultados(corredores, *qtdCorredores, listaResultados); 
            break;
        case 3:
            if (refazerCorrida()) {
                for (int i = 0; i < *qtdCorredores; i++) {
                    corredores[i].tempo = (float)rand() / RAND_MAX * 100; // Refaz a corrida com os mesmos dados
                ordenarCorredores(corredores, *qtdCorredores);
                }
            } else {
                simularCorrida(corredores, listaResultados, qtdCorredores);
                return; 
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

void simularCorrida(Corredor corredores[], LISTA_TXT* listaResultados, int* qtdCorredores) {
    srand(time(NULL));
    for (int i = 0; i < *qtdCorredores; i++) {
        printf("Nome do corredor %d: ", i + 1);
        scanf("%99s", corredores[i].nome);
        corredores[i].tempo = (float)rand() / RAND_MAX * 100; // Simula o tempo
    }

    ordenarCorredores(corredores, *qtdCorredores); 
    novoMenu(corredores, listaResultados, qtdCorredores);
}

void ordenarCorredores(Corredor corredores[], int qtdCorredores) {
    for (int i = 0; i < qtdCorredores - 1; i++) {
        for (int j = 0; j < qtdCorredores - i - 1; j++) {
            if (corredores[j].tempo > corredores[j + 1].tempo) {
                Corredor temp = corredores[j];
                corredores[j] = corredores[j + 1];
                corredores[j + 1] = temp;
            }
        }
    }
}

void exibirResultados(Corredor corredores[], int qtdCorredores) {
    for (int i = 0; i < qtdCorredores; i++) {
        printf("%d. %s - %.2f\n", i + 1, corredores[i].nome, corredores[i].tempo);
    }
}

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

    inserirElementoLista(listaResultados, nomeArquivo); 
}

int refazerCorrida() {
    char escolha;
    printf("Deseja refazer a corrida com os mesmos dados? (S/N): ");
    scanf(" %c", &escolha);
    return (escolha == 'S' || escolha == 's') ? 1 : 0;
}

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
    
    while (i < qtd_corredores && fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "%d. %s - %f",&lixo_1, corredores[i].nome, &corredores[i].tempo);
        i++;
    }
    
    for(i = 0; i<qtd_corredores; i++){
        
        anterior = fabs(corredores[i].tempo-tempo);

        if(anterior<=atual){

            atual = anterior;
            index = i;
        }
    }
    printf("O corredor com o tempo mais proximo:%s%s%s\nDiferenca de:%s%.2f%s\n\n\n\n", ANSI_COLOR_GREEN, corredores[index].nome, ANSI_COLOR_RESET, ANSI_COLOR_RED, atual, ANSI_COLOR_RESET);
}

void limparTela() {
    system("clear||cls");
}

void printBanner() {
    char banner[] = 
    "███████╗██╗███╗   ███╗██╗   ██╗██╗      █████╗ ██████╗  ██████╗ ██████╗\n"    
    "██╔════╝██║████╗ ████║██║   ██║██║     ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗\n"    
    "███████╗██║██╔████╔██║██║   ██║██║     ███████║██║  ██║██║   ██║██████╔╝\n"    
    "╚════██║██║██║╚██╔╝██║██║   ██║██║     ██╔══██║██║  ██║██║   ██║██╔══██╗\n"    
    "███████║██║██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║██████╔╝╚██████╔╝██║  ██║\n"    
    "╚══════╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═╝\n"    
    "\n"                                                                            
    "██████╗ ███████╗     ██████╗ ██████╗ ██████╗ ██████╗ ██╗██████╗  █████╗\n"
    "██╔══██╗██╔════╝    ██╔════╝██╔═══██╗██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗\n"    
    "██║  ██║█████╗      ██║     ██║   ██║██████╔╝██████╔╝██║██║  ██║███████║\n"    
    "██║  ██║██╔══╝      ██║     ██║   ██║██╔══██╗██╔══██╗██║██║  ██║██╔══██║\n"    
    "██████╔╝███████╗    ╚██████╗╚██████╔╝██║  ██║██║  ██║██║██████╔╝██║  ██║\n"    
    "╚═════╝ ╚══════╝     ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═════╝ ╚═╝  ╚═╝\n";    
    printf("\n");
    printf("%s", banner); // Imprime o banner na tela.
    printf("\n"); 
}

void menuPrincipal(LISTA_TXT* listaResultados) {
    int opcao, qtdCorredores;
    Corredor corredores[100]; 
    char nomearq[100];
    float tempo;
    limparTela();
    printBanner();
    do {
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