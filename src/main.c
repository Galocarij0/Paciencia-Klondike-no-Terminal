#include <stdio.h>
#include <stdlib.h>

#include <time.h>


#include <pdcurses.h>

#include "game.h"

int main(void){
    srand(time(NULL));
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    Pilha estoque = { .topo = NULL, .contagem = 0};
    Pilha descarte = {.topo = NULL, .contagem = 0};
    Pilha tableau[7];
    Pilha fundacoes[4];

    for (int i = 0; i < 4; i++){
        fundacoes[i].topo = NULL;
        fundacoes[i].contagem = 0;
    }

    init_deck(&estoque);
    embaralhar_deck(&estoque);
    distribuir_tableau(&estoque, tableau);

    int rodando = 1;
    while (rodando){
        renderizar_jogo(&estoque, &descarte, fundacoes, tableau);
        int tecla = getch();
        

        if (tecla == 'q' || tecla == 'Q'){
            rodando = 0;
        } 

        if (tecla == 'e' || tecla == 'E' || tecla == ' '){
            comprar_carta(&estoque, &descarte);
        }

        if (tecla == 'f' || tecla == 'F'){
            if (descarte.topo != NULL){
                Carta *carta_descarte = descarte.topo;

                for (int i = 0; i < 4; i++){
                    if (mover_para_fundacao(carta_descarte, &fundacoes[i]) == 1){
                        pop_carta(&descarte);
                        break;
                    }
                }
            }
        }

        renderizar_jogo(&estoque, &descarte, fundacoes, tableau);
    }

    endwin();

    liberar_pilha(&estoque);
    liberar_pilha(&descarte);
    for (int i = 0; i < 7; i++){
        liberar_pilha(&tableau[i]);
    }
    for (int i = 0; i < 4; i++){
        liberar_pilha(&fundacoes[i]);
    }
    

    return 0;
}