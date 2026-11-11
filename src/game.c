#include <stdlib.h>
#include <pdcurses.h>
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
        array_cartas[i] = pop_carta(estoque);
    }

    for (int i = total_cartas- 1; i > 0; i--){
        int j = rand() % (i + 1);
        Carta* temp = array_cartas[i];
        array_cartas[i] = array_cartas[j];
        array_cartas[j] = temp;
    }

    for (int i = 0; i < total_cartas; i++){
        push_carta(estoque, array_cartas[i]);
    }

    free(array_cartas);
}

void comprar_carta(Pilha *estoque, Pilha *descarte){

    if (estoque->topo == NULL) {
        if (descarte->topo == NULL) {
            return; 
        }

        while (descarte->topo != NULL) {
            Carta *c = pop_carta(descarte);
            if (c != NULL) {
                c->aberta = false;      
                push_carta(estoque, c);
            }
        }
    }

    Carta *c = pop_carta(estoque);
    if (c != NULL) {
        c->aberta = true;
        push_carta(descarte, c);
    }
}

void distribuir_tableau(Pilha *estoque, Pilha tableau[7]){
    
    for (int i = 0; i < 7; i++){
        tableau[i].topo = NULL;
        tableau[i].contagem = 0;
    }

    for (int i = 0; i < 7; i++){
        for (int j = 0; j <= i; j++){
            Carta *c = pop_carta(estoque);
            if (c != NULL){
                
                if (j == i){
                    c->aberta = true;
                } else {
                    c->aberta = false;
                }
                
                push_carta(&tableau[i], c);
            }
        }
    }
}

int mover_para_fundacao(Carta *c, Pilha *fundacao){
    if (c == NULL) return 0;

    //Se a fundação estiver vazia, só aceita Ás (valor 1)
    if (fundacao->topo == NULL){
        if (c->valor == 1){
            push_carta(fundacao, c);
            return 1; //Sucesso
        }
        return 0; //Inválido (não é Ás)
    }

    // Se a fundação já tem cartas, deve ser do mesmo naipe e valor consecutivo (valor + 1)
    Carta *topo_atual = fundacao->topo;
    if (c->naipe == topo_atual->naipe && c->valor == topo_atual->valor + 1){
        push_carta(fundacao, c);
        return 1;
    }

    return 0;
}

void renderizar_jogo(Pilha *estoque, Pilha *descarte, Pilha fundacoes[], Pilha tableau[]){
    clear();

    mvprintw(1, 2, "=== KLONDIKE SOLITAIRE ===");

    move(3, 2);
    clrtoeol();
    mvprintw(3, 2, "Estoque: [ %d cartas ]", estoque->contagem);
    
    move(4, 2);
    clrtoeol();
    if (descarte->topo != NULL){
        mvprintw(4, 2, "Descarte: Topo -> [%d, Naipe: %d]", descarte->topo->valor, descarte->topo->naipe);
    } else {
        mvprintw(4, 2, "Descarte: [ Vazio ]");
    }

    mvprintw(3, 40, "Fundações:");
    for (int i = 0; i < 4; i++){
        int qtd = fundacoes[i].contagem;
        mvprintw(4, 40 + (i * 8), "[ F%d: %d]", i + 1, qtd);
    }

    mvprintw(7, 2, "Tableau:");
    for (int i = 0; i < 7; i++){
        
        int x = 2 + (i * 14);
        
        mvprintw(8, x, "Col %d", i + 1);
        mvprintw(9, x, "(Ct: %d)", tableau[i].contagem);

        move(10, x);
        clrtoeol();

    
        if (tableau[i].topo != NULL){
            mvprintw(10, x, "[%2d, N:%d]", tableau[i].topo->valor, tableau[i].topo->naipe);
        } else {
            mvprintw(10, x, "[Vazia]");
        }
    }

    mvprintw(20, 2, "Pressione 'q' para sair do jogo... :(");
    refresh();
}
