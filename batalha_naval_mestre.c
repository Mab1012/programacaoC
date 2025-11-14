#include <stdio.h>
#include <stdlib.h> // para abs()

#define TAM 10          // tamanho do tabuleiro (10x10)
#define HAB_TAM 5       // tamanho das matrizes de habilidade (5x5)

#define AGUA 0
#define NAVIO 3
#define HABIL 5         // marca área de efeito

#define NAVIO_TAM 3

// Retorna 1 se a posição do tabuleiro ainda está com água
int podeColocarNavio(int tab[TAM][TAM], int l, int c) {
    return tab[l][c] == AGUA;
}

// Aplica uma matriz de habilidade 5x5 no tabuleiro, centrada em (origL, origC)
void aplicarHabilidade(int tab[TAM][TAM], int hab[HAB_TAM][HAB_TAM],
                       int origL, int origC) {
    int meio = HAB_TAM / 2;

    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {

            // Só nos interessa onde a habilidade vale 1
            if (hab[i][j] == 1) {

                int linhaTab = origL + (i - meio);
                int colunaTab = origC + (j - meio);

                // Garante que não sai fora do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM &&
                    colunaTab >= 0 && colunaTab < TAM) {

                    // Marca a área de efeito.
                    // Aqui sobrescrevemos com 5 mesmo se tiver navio:
                    tab[linhaTab][colunaTab] = HABIL;
                }
            }
        }
    }
}

int main() {

    int tabuleiro[TAM][TAM];

    // ===============================
    // 1. INICIALIZA TABULEIRO (ÁGUA)
    // ===============================
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // ===============================
    // 2. POSICIONAR NAVIOS (como no nível anterior)
    // ===============================
    // NAVIO HORIZONTAL (↔)
    int linhaH = 1, colunaH = 1; // (1,1) (1,2) (1,3)

    if (colunaH + NAVIO_TAM > TAM) {
        printf("Erro: navio horizontal fora do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO_TAM; i++) {
        if (!podeColocarNavio(tabuleiro, linhaH, colunaH + i)) {
            printf("Erro: sobreposição de navios (horizontal).\n");
            return 1;
        }
        tabuleiro[linhaH][colunaH + i] = NAVIO;
    }

    // NAVIO VERTICAL (↕)
    int linhaV = 5, colunaV = 7; // (5,7) (6,7) (7,7)

    if (linhaV + NAVIO_TAM > TAM) {
        printf("Erro: navio vertical fora do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO_TAM; i++) {
        if (!podeColocarNavio(tabuleiro, linhaV + i, colunaV)) {
            printf("Erro: sobreposição de navios (vertical).\n");
            return 1;
        }
        tabuleiro[linhaV + i][colunaV] = NAVIO;
    }

    // NAVIO DIAGONAL DESCENDO (↘)
    int linhaD1 = 3, colunaD1 = 0; // (3,0) (4,1) (5,2)

    if (linhaD1 + NAVIO_TAM > TAM || colunaD1 + NAVIO_TAM > TAM) {
        printf("Erro: navio diagonal descendo fora do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO_TAM; i++) {
        if (!podeColocarNavio(tabuleiro, linhaD1 + i, colunaD1 + i)) {
            printf("Erro: sobreposição de navios (diagonal ↘).\n");
            return 1;
        }
        tabuleiro[linhaD1 + i][colunaD1 + i] = NAVIO;
    }

    // NAVIO DIAGONAL SUBINDO (↗)
    int linhaD2 = 9, colunaD2 = 0; // (9,0) (8,1) (7,2)

    if (linhaD2 - (NAVIO_TAM - 1) < 0 || colunaD2 + NAVIO_TAM > TAM) {
        printf("Erro: navio diagonal subindo fora do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO_TAM; i++) {
        if (!podeColocarNavio(tabuleiro, linhaD2 - i, colunaD2 + i)) {
            printf("Erro: sobreposição de navios (diagonal ↗).\n");
            return 1;
        }
        tabuleiro[linhaD2 - i][colunaD2 + i] = NAVIO;
    }

    // ===============================
    // 3. CRIAR MATRIZES DAS HABILIDADES (5x5)
    // ===============================
    int cone[HAB_TAM][HAB_TAM];
    int cruz[HAB_TAM][HAB_TAM];
    int octaedro[HAB_TAM][HAB_TAM];

    int meio = HAB_TAM / 2;

    // --- CONE (apontando para baixo) ---
    // topo no meio da primeira linha, abrindo até o meio da matriz
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            if (i <= meio && j >= meio - i && j <= meio + i) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    // --- CRUZ ---
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            if (i == meio || j == meio) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }

    // --- OCTAEDRO (losango) ---
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            int dist = abs(i - meio) + abs(j - meio);
            if (dist <= 2) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }

    // ===============================
    // 4. APLICAR HABILIDADES NO TABULEIRO
    // ===============================
    // Pontos de origem definidos direto no código (simplificação)

    int origemConeL = 2, origemConeC = 5;      // centro do cone
    int origemCruzL = 6, origemCruzC = 3;      // centro da cruz
    int origemOctL  = 4, origemOctC  = 4;      // centro do octaedro

    aplicarHabilidade(tabuleiro, cone,     origemConeL, origemConeC);
    aplicarHabilidade(tabuleiro, cruz,     origemCruzL, origemCruzC);
    aplicarHabilidade(tabuleiro, octaedro, origemOctL,  origemOctC);

    // ===============================
    // 5. IMPRIMIR TABULEIRO COM COORDENADAS
    // ===============================
    printf("\n       TABULEIRO BATALHA NAVAL - NIVEL MESTRE\n\n");

    // Cabeçalho de colunas
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

    printf("\nLegenda:\n");
    printf("0 = agua\n");
    printf("3 = navio\n");
    printf("5 = area afetada por habilidade\n");

    return 0;
}
