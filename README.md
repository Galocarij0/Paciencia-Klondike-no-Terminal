# 🃏 Solitaire Klondike (Terminal / TUI)

> Implementação clássica do jogo **klondike solitaire** desenvolvido em **c** puro, utilizando a biblioteca de interface de terminal **ncurses** (compatível com Windows via PDCurses e Linux/WSL).

> Desenvolvido como projeto acadêmico de Estruturas de Dados para exercitar manipulação de ponteiros, estruturas de pilhas (`Pilha`), alocação dinâmica e lógica de jogos baseada em TUI (Text User Interface).

---

## ♦️ Funcionalidades
* **Embaralhamento Algorítmico:** Implementação rigorosa do algoritmo Fisher-Yates para distribuição correta das cartas.
* **Estoque e Descarte:** Sistema de compra de cartas do monte e reciclagem dinâmica.
* **Fundações (Aces ➔ Reis):** Validação automática para envio de cartas direto para as 4 fundações (`'f'`).
* **Tableau Completo:**
  * Envio de cartas do descarte para as colunas (`'1'-'7'`).
  * Movimentação de cartas entre as colunas do Tableau (`'m'`).
  * Revelação automática (`aberta = true`) de cartas viradas para baixo ao liberar o topo.
* **Detecção de Vitória:** Verificação automática se todas as fundações atingiram 13 cartas.

---

## ♠️ Pré-requisitos e Dependências
Para compilar e rodar o projeto, você precisará de:
* Um compilador C (como `gcc`)
* A biblioteca **ncurses** (ou **PDCurses** se estiver a compilar no ambiente Windows/MSYS2/UCRT64)
* Ferramenta de build `make`

---

## ❤️ Como Compilar e Executar
1. Clone o repositório e navegue até a pasta do projeto.
2. Certifique-se de limpar objetos antigos e compilar com o Makefile:
   ```bash
   rm -f src/*.o solitaire.exe
   make