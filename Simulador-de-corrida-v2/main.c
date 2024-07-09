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


// Função principal que inicia o programa
int main() {
    printBanner(); // Imprime o banner inicial
    LISTA_TXT listaResultados;
    inicializarListaTxt(&listaResultados); // Inicializa a lista de resultados
    menuPrincipal(&listaResultados); // Chama o menu principal
    return 0;
}
