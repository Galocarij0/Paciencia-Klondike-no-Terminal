#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include "game.h"

int main(void){
    srand(time(NULL));

    Pilha estoque = { .topo = NULL, .contagem = 0};

    init_deck(&estoque);
    printf("Baralho Criado! Total de Cartas: %d\n", estoque.contagem);

    embaralhar_deck(&estoque);
    printf("Baralho embaralhado com sucesso!\n");

    if (estoque.topo != NULL){
        printf("Carta no topo do monte: %d, Naipe %d\n", estoque.topo->valor, estoque.topo->naipe);
    }

    liberar_pilha(&estoque);
    return 0;
}