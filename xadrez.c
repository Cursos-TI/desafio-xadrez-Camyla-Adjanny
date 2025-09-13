#include <stdio.h>
#include <unistd.h>

#define TAM 8

typedef struct {
    int linha;
    int coluna;
    int ativo;
} Peca;

// Posicionamento inicial (exemplo)
Peca torre = {7, 0, 1};     // ♖
Peca bispo = {7, 2, 1};     // ♗
Peca rainha = {7, 4, 1};    // ♕
Peca cavalo = {7, 6, 1};    // ♘
Peca peao = {6, 1, 1};      // ♙
Peca rei = {7, 3, 1};       // 👑

// Passos dados (controle dos movimentos)
int passosTorre = 0;
int passosBispo = 0;
int passosRainha = 0;
int passosCavalo = 0;
int passosPeao = 0;
int passosRei = 0;

const int MAX_TORRE = 5;
const int MAX_BISPO = 5;
const int MAX_RAINHA = 8;
const int MAX_CAVALO = 1;
const int MAX_PEAO = 2;
const int MAX_REI = 8;

void limparTela() {
    printf("\033[2J\033[H");
}

void capturarPeca(int linha, int coluna) {
    if (torre.ativo && torre.linha == linha && torre.coluna == coluna) {
        torre.ativo = 0;
        printf("♖ Torre capturada!\n");
    } else if (bispo.ativo && bispo.linha == linha && bispo.coluna == coluna) {
        bispo.ativo = 0;
        printf("♗ Bispo capturado!\n");
    } else if (rainha.ativo && rainha.linha == linha && rainha.coluna == coluna) {
        rainha.ativo = 0;
        printf("♕ Rainha capturada!\n");
    } else if (cavalo.ativo && cavalo.linha == linha && cavalo.coluna == coluna) {
        cavalo.ativo = 0;
        printf("♘ Cavalo capturado!\n");
    } else if (peao.ativo && peao.linha == linha && peao.coluna == coluna) {
        peao.ativo = 0;
        printf("♙ Peão capturado!\n");
    } else if (rei.ativo && rei.linha == linha && rei.coluna == coluna) {
        rei.ativo = 0;
        printf("👑 Rei capturado!\n");
    }
}

void imprimirTabuleiro() {
    printf("   ");
    for (int c = 0; c < TAM; c++) printf(" %d ", c);
    printf("\n");
    for (int l = 0; l < TAM; l++) {
        printf(" %d ", l);
        for (int c = 0; c < TAM; c++) {
            if (torre.ativo && torre.linha == l && torre.coluna == c) printf("♖  ");
            else if (bispo.ativo && bispo.linha == l && bispo.coluna == c) printf("♗  ");
            else if (rainha.ativo && rainha.linha == l && rainha.coluna == c) printf("♕  ");
            else if (cavalo.ativo && cavalo.linha == l && cavalo.coluna == c) printf("♘  ");
            else if (peao.ativo && peao.linha == l && peao.coluna == c) printf("♙  ");
            else if (rei.ativo && rei.linha == l && rei.coluna == c) printf("👑  ");
            else printf("·  ");
        }
        printf("\n");
    }
    printf("\n");
}

// Torre: move 1 passo para a direita (for)
int moverTorre() {
    if (!torre.ativo || passosTorre >= MAX_TORRE) return 0;
    int novaColuna = torre.coluna + 1;
    if (novaColuna < TAM) {
        capturarPeca(torre.linha, novaColuna);
        torre.coluna = novaColuna;
        passosTorre++;
        limparTela();
        printf("♖ Torre move para (%d, %d)\n\n", torre.linha, torre.coluna);
        imprimirTabuleiro();
        usleep(400000);
        return 1;
    }
    return 0;
}

// Bispo: move 1 passo diagonal cima-direita (while)
int moverBispo() {
    if (!bispo.ativo || passosBispo >= MAX_BISPO) return 0;
    int novaLinha = bispo.linha - 1;
    int novaColuna = bispo.coluna + 1;
    if (novaLinha >= 0 && novaColuna < TAM) {
        capturarPeca(novaLinha, novaColuna);
        bispo.linha = novaLinha;
        bispo.coluna = novaColuna;
        passosBispo++;
        limparTela();
        printf("♗ Bispo move para (%d, %d)\n\n", bispo.linha, bispo.coluna);
        imprimirTabuleiro();
        usleep(400000);
        return 1;
    }
    return 0;
}

// Rainha: move 1 passo para a esquerda (recursão controlada externamente)
int moverRainhaRec(int passosFeitos) {
    if (!rainha.ativo || passosFeitos >= MAX_RAINHA) return 0;
    int novaColuna = rainha.coluna - 1;
    if (novaColuna >= 0) {
        capturarPeca(rainha.linha, novaColuna);
        rainha.coluna = novaColuna;
        limparTela();
        printf("♕ Rainha move para (%d, %d)\n\n", rainha.linha, rainha.coluna);
        imprimirTabuleiro();
        usleep(400000);
        return 1;
    }
    return 0;
}
int moverRainha() {
    if (passosRainha >= MAX_RAINHA) return 0;
    if (moverRainhaRec(passosRainha)) {
        passosRainha++;
        return 1;
    }
    return 0;
}

// Cavalo: move 1 movimento em L (2 cima, 1 direita) (loops aninhados controlados no main)
int moverCavalo() {
    if (!cavalo.ativo || passosCavalo >= MAX_CAVALO) return 0;
    int novaLinha = cavalo.linha - 2;
    int novaColuna = cavalo.coluna + 1;
    if (novaLinha >= 0 && novaColuna < TAM) {
        capturarPeca(novaLinha, novaColuna);
        cavalo.linha = novaLinha;
        cavalo.coluna = novaColuna;
        passosCavalo++;
        limparTela();
        printf("♘ Cavalo move em L para (%d, %d)\n\n", cavalo.linha, cavalo.coluna);
        imprimirTabuleiro();
        usleep(400000);
        return 1;
    }
    return 0;
}

// Peão: move 1 passo para cima
int moverPeao() {
    if (!peao.ativo || passosPeao >= MAX_PEAO) return 0;
    int novaLinha = peao.linha - 1;
    if (novaLinha >= 0) {
        capturarPeca(novaLinha, peao.coluna);
        peao.linha = novaLinha;
        passosPeao++;
        limparTela();
        printf("♙ Peão move para (%d, %d)\n\n", peao.linha, peao.coluna);
        imprimirTabuleiro();
        usleep(400000);
        return 1;
    }
    return 0;
}

// Rei: move 1 passo em uma direção (8 direções possíveis)
int moverRei() {
    if (!rei.ativo || passosRei >= MAX_REI) return 0;
    int direcoes[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };
    int d = passosRei;
    int novaLinha = rei.linha + direcoes[d][0];
    int novaColuna = rei.coluna + direcoes[d][1];
    if (novaLinha >= 0 && novaLinha < TAM && novaColuna >= 0 && novaColuna < TAM) {
        capturarPeca(novaLinha, novaColuna);
        rei.linha = novaLinha;
        rei.coluna = novaColuna;
        limparTela();
        printf("👑 Rei move para (%d, %d)\n\n", rei.linha, rei.coluna);
        imprimirTabuleiro();
        usleep(400000);
    }
    passosRei++;
    return 1;
}

// Roque: só troca posições (simples)
void roque() {
    if (!rei.ativo || !torre.ativo) return;
    limparTela();
    printf("🔄 Roque realizado: Rei e Torre trocam de posição\n\n");
    int tempLinha = rei.linha;
    int tempColuna = rei.coluna;
    rei.linha = torre.linha;
    rei.coluna = torre.coluna;
    torre.linha = tempLinha;
    torre.coluna = tempColuna;
    imprimirTabuleiro();
    usleep(1000000);
}

int main() {
    limparTela();
    printf("Tabuleiro inicial:\n\n");
    imprimirTabuleiro();
    usleep(1000000);

    int turno = 0;
    int maxTurnos = MAX_TORRE + MAX_BISPO + MAX_RAINHA + MAX_CAVALO + MAX_PEAO + MAX_REI + 1; // +1 roque

    while (turno < maxTurnos) {
        switch(turno % 7) {
            case 0: moverTorre(); break;
            case 1: moverBispo(); break;
            case 2: moverRainha(); break;
            case 3: moverCavalo(); break;
            case 4: moverPeao(); break;
            case 5: moverRei(); break;
            case 6: roque(); break;
        }
        turno++;
    }

    printf("✅ Todos os movimentos foram executados em turnos!\n");
    return 0;
}
