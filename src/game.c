#include <stdlib.h>
#include "game.h"

Carta* criar_carta(int valor, Naipe naipe){
    Carta* nova_carta = (Carta*) malloc(sizeof(Carta));
    if (nova_carta != NULL){
        nova_carta->valor = valor;
        nova_carta->naipe = naipe;
        
        if (naipe == NAIPE_CORACOES || naipe == NAIPE_OUROS){
            nova_carta->cor = COR_VERMELHO;
        } else {
            nova_carta->cor = COR_PRETO;
        }

        nova_carta->aberta = false;
        nova_carta->proxima = NULL;
    }
    
    return nova_carta;
}

void push_carta(Pilha* pilha, Carta* carta){
    if (pilha == NULL || carta == NULL) return;

    carta->proxima = pilha->topo;
    pilha->topo = carta;
    pilha->contagem++;
}

Carta* pop_carta(Pilha* pilha){
    if (pilha == NULL || pilha->topo == NULL) return NULL;

    Carta* carta = pilha->topo;
    pilha->topo = carta->proxima;
    carta->proxima = NULL;
    pilha->contagem--;

    return carta;
}

void liberar_pilha(Pilha* pilha){
    if (pilha == NULL) return;

    while (pilha->topo != NULL){
        Carta* temp = pop_carta(pilha);
        free(temp);
    }
}

void init_deck(Pilha* estoque){
    if (estoque == NULL) return;

    Naipe naipe[] = { NAIPE_PAUS, NAIPE_ESPADAS, NAIPE_CORACOES, NAIPE_OUROS};

    // Percorre os Naipes
    for (int s = 0; s < 4; s++){
        // Percorre os Valores de 1 (Ás) a 13 (Rei)
        for (int v = 1; v <= 13; v++){
            Carta* carta = criar_carta(v, naipe[s]);
            push_carta(estoque, carta);
        }
    }
}

void embaralhar_deck(Pilha* estoque){
    if (estoque == NULL || estoque->contagem == 0) return;

    int total_cartas = estoque->contagem;

    Carta** array_cartas = (Carta**) malloc(total_cartas * sizeof(Carta*));
    if (array_cartas == NULL) return;

    for (int i = 0; i < total_cartas; i++){
        array_cartas[i] = pop_cartas(estoque);
    }

    for (int i = total_cartas- 1; i > 0; i--){
        int j = rand() % (i + 1);
        Carta* temp = array_cartas[j];
        array_cartas[i] = array_cartas[j];
        array_cartas[j] = temp;
    }

    for (int i = 0; i < total_cartas; i++){
        push_cartas(estoque, array_cartas[i]);
    }

    free(array_cartas);
}