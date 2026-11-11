#include <stdio.h>
#include <stdlib.h>

#include <time.h>


#include <pdcurses.h>

#include "game.h"

int checar_vitoria(Pilha fundacoes[]){
    for (int i = 0; i < 4; i++){
        if (fundacoes[i].contagem < 13){
            return 0;
        }
    }
    return 1;
}

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

        if (tecla >= '1' && tecla <= '7'){
            int coluna_escolhida = tecla - '1';

            if (descarte.topo != NULL){
                Carta *carta_descarte = descarte.topo;
                if (mover_para_tableau(carta_descarte, &tableau[coluna_escolhida]) == 1){
                    pop_carta(&descarte);
                }
            }
        }

        if (tecla == 'm' || tecla == 'M'){
            mvprintw(22, 2, "[MOVER]: Digite a coluna de ORIGEM (1-7): ");
            refresh();
            int tecla_origem = getch();

            if (tecla_origem >= '1' && tecla_origem <= '7'){
                int origem_idx = tecla_origem - '1';

                mvprintw(22, 2, "[MOVER]: Digite a coluna de DESTINO (1-7): ");
                refresh();
                int tecla_destino = getch();

                if (tecla_destino >= '1' && tecla_destino <= '7'){
                    int destino_idx = tecla_destino - '1';
                    mover_tableau_para_tableau(&tableau[origem_idx], &tableau[destino_idx]);
                }
            }
            move(22, 2);
            clrtoeol();
        }

        if (checar_vitoria(fundacoes)){
            clear();
            mvprintw(10, 10, "========================================");
            mvprintw(11, 10, "   PARABENS! VOCE VENCEU O SOLITAIRE!   ");
            mvprintw(12, 10, "========================================");
            mvprintw(14, 10, "Pressione 'q' para sair do jogo... :D");
            refresh();

            while (1){
                int fim_tecla = getch();
                if (fim_tecla == 'q' || fim_tecla == 'Q'){
                    rodando = 0;
                    break;
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