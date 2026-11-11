#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// Definição de Naipes 
typedef enum {
    NAIPE_PAUS,
    NAIPE_ESPADAS,
    NAIPE_CORACOES,
    NAIPE_OUROS
} Naipe;

// Definição de Cores
typedef enum {
    COR_VERMELHO,
    COR_PRETO
} Cor;

// Estrutura de uma Carta
typedef struct Carta {
    int valor; // 1 (Ás) a 13 (Rei)
    Naipe naipe; 
    Cor cor; 
    bool aberta; // Aberta/face pra cima (true), virada pra baixo (false)
    struct Carta *proxima; // Ponteiro para a próxima carta na Pilha
} Carta;

// Estrutura de uma Pilha
typedef struct {
    Carta *topo; // Ponteiro para a Carta no Topo da Pilha
    int contagem; // Quantidade de Cartas na Pilha
} Pilha;

// Protótipos das funções principais
Carta* criar_carta(int valor, Naipe naipe);
void push_carta(Pilha* pilha, Carta* carta);
Carta* pop_carta(Pilha* pilha);
void liberar_pilha(Pilha* pilha);

void comprar_carta(Pilha *estoque, Pilha *descarte);

void init_deck(Pilha* estoque);
void embaralhar_deck(Pilha* estoque);

void distribuir_tableau(Pilha *estoque, Pilha tableau[7]);

int mover_para_fundacao(Carta *c, Pilha *fundacao);

int mover_para_tableau(Carta *c, Pilha *coluna);

int mover_tableau_para_tableau(Pilha *origem, Pilha *destino);

void renderizar_jogo(Pilha *estoque, Pilha *descarte, Pilha fundacoes[], Pilha tableau[]);



void init_game(void);
void free_game(void);

#endif