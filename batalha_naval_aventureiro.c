#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define AGUA 0
#define NAVIO_TAM 3

// Retorna 1 se a posição ainda está com água
int podeColocar(int tab[TAM][TAM], int l, int c) {
    return tab[l][c] == AGUA;
}

int main() {

    int tabuleiro[TAM][TAM];

    // 1. Inicializar tabuleiro com água (0)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // ===============================
    // NAVIO HORIZONTAL (↔)
    // ===============================
    int linhaH = 1, colunaH = 1; // (1,1) (1,2) (1,3)

    // Validação simples de limite
    if (colunaH + NAVIO_TAM > TAM) {
        printf("Erro: navio horizontal fora do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO_TAM; i++) {
        if (!podeColocar(tabuleiro, linhaH, colunaH + i)) {
            printf("Erro: sobreposição de navios (horizontal).\n");
            return 1;
        }
        tabuleiro[linhaH][colunaH + i] = NAVIO;
    }

    // ===============================
    // NAVIO VERTICAL (↕)
    // ===============================
    int linhaV = 5, colunaV = 7; // (5,7) (6,7) (7,7)

    if (linhaV + NAVIO_TAM > TAM) {
        printf("Erro: navio vertical fora do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO_TAM; i++) {
        if (!podeColocar(tabuleiro, linhaV + i, colunaV)) {
            printf("Erro: sobreposição de navios (vertical).\n");
            return 1;
        }
        tabuleiro[linhaV + i][colunaV] = NAVIO;
    }

    // ===============================
    // NAVIO DIAGONAL DESCENDO (↘)
    // ===============================
    int linhaD1 = 3, colunaD1 = 0; // (3,0) (4,1) (5,2)

    if (linhaD1 + NAVIO_TAM > TAM || colunaD1 + NAVIO_TAM > TAM) {
        printf("Erro: navio diagonal descendo fora do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO_TAM; i++) {
        if (!podeColocar(tabuleiro, linhaD1 + i, colunaD1 + i)) {
            printf("Erro: sobreposição de navios (diagonal ↘).\n");
            return 1;
        }
        tabuleiro[linhaD1 + i][colunaD1 + i] = NAVIO;
    }

    // ===============================
    // NAVIO DIAGONAL SUBINDO (↗)
    // ===============================
    int linhaD2 = 9, colunaD2 = 0; // (9,0) (8,1) (7,2)

    if (linhaD2 - (NAVIO_TAM - 1) < 0 || colunaD2 + NAVIO_TAM > TAM) {
        printf("Erro: navio diagonal subindo fora do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO_TAM; i++) {
        if (!podeColocar(tabuleiro, linhaD2 - i, colunaD2 + i)) {
            printf("Erro: sobreposição de navios (diagonal ↗).\n");
            return 1;
        }
        tabuleiro[linhaD2 - i][colunaD2 + i] = NAVIO;
    }

    // ===============================
    // IMPRIMIR TABULEIRO COM COORDENADAS
    // ===============================
    printf("\n       TABULEIRO BATALHA NAVAL\n\n");

    // Cabeçalho das colunas
    printf("    ");
    for (int c = 0; c < TAM; c++) {
        printf("%d ", c);
    }
    printf("\n");

    printf("    ");
    for (int c = 0; c < TAM; c++) printf("--");
    printf("\n");

    // Linhas com índice
    for (int l = 0; l < TAM; l++) {
        printf("%2d | ", l);
        for (int c = 0; c < TAM; c++) {
            printf("%d ", tabuleiro[l][c]);
        }
        printf("\n");
    }

    printf("\nLegenda:\n0 = água\n3 = navio\n");

    return 0;
}
