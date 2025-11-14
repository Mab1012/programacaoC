#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define NAVIO_TAM 3   // Tamanho fixo dos navios

int main() {

    // ================================
    // 1. CRIAR O TABULEIRO 10x10
    // ================================
    int tabuleiro[TAM][TAM];

    // Inicializar todas as posições com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // =========================================
    // 2. POSICIONAR OS NAVIOS USANDO VETORES
    // =========================================
    // Cada vetor guarda as coordenadas iniciais do navio
    // navio 1 horizontal, navio 2 vertical
    
    int navioHorizontal[2] = {2, 3};  // linha 2, coluna 3
    int navioVertical[2]   = {5, 5};  // linha 5, coluna 5

    // ================================
    // POSICIONAR NAVIO HORIZONTAL
    // ================================
    int linhaH = navioHorizontal[0];
    int colunaH = navioHorizontal[1];

    // Validar limites do navio horizontal
    if (colunaH + NAVIO_TAM <= TAM) {
        for (int i = 0; i < NAVIO_TAM; i++) {
            tabuleiro[linhaH][colunaH + i] = 3; // Marca navio com valor 3
        }
    } else {
        printf("Erro: Navio horizontal ultrapassa o limite do tabuleiro.\n");
        return 1;
    }

    // ================================
    // POSICIONAR NAVIO VERTICAL
    // ================================
    int linhaV = navioVertical[0];
    int colunaV = navioVertical[1];

    // Validar limites do navio vertical
    if (linhaV + NAVIO_TAM <= TAM) {

        // Verificar se há sobreposição
        for (int i = 0; i < NAVIO_TAM; i++) {
            if (tabuleiro[linhaV + i][colunaV] == 3) {
                printf("Erro: Navios se sobrepoem.\n");
                return 1;
            }
        }

        for (int i = 0; i < NAVIO_TAM; i++) {
            tabuleiro[linhaV + i][colunaV] = 3;
        }

    } else {
        printf("Erro: Navio vertical ultrapassa o limite do tabuleiro.\n");
        return 1;
    }

    // ================================
    // 3. EXIBIR O TABULEIRO
    // ================================
    printf("\n===== TABULEIRO BATALHA NAVAL =====\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda:\n");
    printf("0 = água\n");
    printf("3 = navio\n");

    return 0;
}
