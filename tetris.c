#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 5

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // Identificador exclusivo
} Peca;

// Estrutura da Fila Circular para gerenciamento das peças futuras
typedef struct {
    Peca itens[TAMANHO];
    int frente;
    int final;
    int total;
} FilaCircular;

// Variável global para garantir que cada ID seja único e sequencial
int contadorId = 0;

// Função para gerar automaticamente uma nova peça
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorId++; // Atribui o ID atual e incrementa para a próxima
    return p;
}

// Inicializa a fila preenchendo-a com as 5 peças iniciais
void inicializarFila(FilaCircular *f) {
    f->frente = 0;
    f->final = -1;
    f->total = 0;
    
    for (int i = 0; i < TAMANHO; i++) {
        f->final = (f->final + 1) % TAMANHO;
        f->itens[f->final] = gerarPeca();
        f->total++;
    }
}

// Exibe o estado atual da fila de forma clara (Requisito de Usabilidade)
void exibirFila(FilaCircular f) {
    printf("\nFila de pecas: ");
    for (int i = 0; i < f.total; i++) {
        int indice = (f.frente + i) % TAMANHO;
        printf("[%c %d] ", f.itens[indice].nome, f.itens[indice].id);
    }
    printf("\n");
}

// Remove a peça da frente (Dequeue)
void jogarPeca(FilaCircular *f) {
    if (f->total == 0) {
        printf("\nErro: A fila esta vazia!\n");
        return;
    }
    Peca removida = f->itens[f->frente];
    printf("\n>>> Peca [%c %d] jogada com sucesso!\n", removida.nome, removida.id);
    f->frente = (f->frente + 1) % TAMANHO;
    f->total--;
}

// Adiciona uma nova peça ao final (Enqueue) se houver espaço
void inserirPeca(FilaCircular *f) {
    if (f->total >= TAMANHO) {
        printf("\nErro: A fila ja esta cheia (limite de %d pecas)!\n", TAMANHO);
        return;
    }
    f->final = (f->final + 1) % TAMANHO;
    f->itens[f->final] = gerarPeca();
    f->total++;
    printf("\n>>> Nova peca inserida no final da fila!\n");
}

int main() {
    srand(time(NULL)); // Inicializa a semente aleatória
    FilaCircular fila;
    int opcao;

    inicializarFila(&fila);

    do {
        exibirFila(fila);
        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila);
                break;
            case 0:
                printf("Saindo do sistema Tetris Stack...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}