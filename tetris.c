#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da Fila Circular (Peças Futuras)
typedef struct {
    Peca itens[TAM_FILA];
    int frente, final, total;
} FilaCircular;

// Estrutura da Pilha Linear (Reserva)
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} PilhaReserva;

int contadorId = 0;

Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorId++;
    return p;
}

// Funções da Fila
void inicializarFila(FilaCircular *f) {
    f->frente = 0; f->final = -1; f->total = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        f->final = (f->final + 1) % TAM_FILA;
        f->itens[f->final] = gerarPeca();
        f->total++;
    }
}

void exibirEstado(FilaCircular f, PilhaReserva p) {
    printf("\n--- 🟦 FILA (PROXIMAS) ---\n");
    for (int i = 0; i < f.total; i++) {
        int idx = (f.frente + i) % TAM_FILA;
        printf("[%c %d] ", f.itens[idx].nome, f.itens[idx].id);
    }
    
    printf("\n\n--- 🎒 PILHA (RESERVA) ---\n");
    if (p.topo == -1) printf("(Vazia)");
    for (int i = p.topo; i >= 0; i--) {
        printf("[%c %d]\n", p.itens[i].nome, p.itens[i].id);
    }
    printf("--------------------------\n");
}

// Lógica de Jogo
void jogarFila(FilaCircular *f) {
    Peca p = f->itens[f->frente];
    printf("\n🕹️ JOGOU: [%c %d]\n", p.nome, p.id);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->itens[(f->final + 1) % TAM_FILA] = gerarPeca(); // Mantém a fila cheia
    f->final = (f->final + 1) % TAM_FILA;
}

void reservarPeca(FilaCircular *f, PilhaReserva *p) {
    if (p->topo >= TAM_PILHA - 1) {
        printf("\n⚠️ Reserva cheia!\n");
        return;
    }
    // Tira da fila
    Peca paraReserva = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    
    // Coloca na pilha (Push)
    p->topo++;
    p->itens[p->topo] = paraReserva;
    
    // Repõe a fila
    f->final = (f->final + 1) % TAM_FILA;
    f->itens[f->final] = gerarPeca();
    printf("\n📥 Peca [%c %d] movida para reserva.\n", paraReserva.nome, paraReserva.id);
}

void usarReserva(PilhaReserva *p) {
    if (p->topo == -1) {
        printf("\n⚠️ Nao ha pecas na reserva!\n");
        return;
    }
    Peca tirada = p->itens[p->topo];
    p->topo--; // Pop
    printf("\n📤 USOU DA RESERVA: [%c %d]\n", tirada.nome, tirada.id);
}

int main() {
    srand(time(NULL));
    FilaCircular fila;
    PilhaReserva pilha;
    pilha.topo = -1;
    int opcao;

    inicializarFila(&fila);

    do {
        exibirEstado(fila, pilha);
        printf("\n1 - Jogar peca\n2 - Reservar peca (Push)\n3 - Usar reserva (Pop)\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: jogarFila(&fila); break;
            case 2: reservarPeca(&fila, &pilha); break;
            case 3: usarReserva(&pilha); break;
        }
    } while (opcao != 0);

    return 0;
}