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

typedef struct {
    Peca itens[TAM_FILA];
    int frente, final, total;
} FilaCircular;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} PilhaReserva;

int contadorId = 0;

// Funções Auxiliares
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorId++;
    return p;
}

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
    printf("\n--- 🎒 PILHA (RESERVA) ---\n");
    if (p.topo == -1) printf("(Vazia)\n");
    for (int i = p.topo; i >= 0; i--) {
        printf("[%c %d]\n", p.itens[i].nome, p.itens[i].id);
    }
    printf("--------------------------\n");
}

// OPERAÇÕES MESTRE

// Troca o topo da pilha com a frente da fila
void trocarPeca(FilaCircular *f, PilhaReserva *p) {
    if (p->topo == -1 || f->total == 0) {
        printf("\n⚠️ Operacao impossivel: estruturas vazias!\n");
        return;
    }
    Peca temp = f->itens[f->frente];
    f->itens[f->frente] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    printf("\n🔄 TROCA REALIZADA: Fila e Pilha sincronizadas!\n");
}

// Inverte a Fila usando a Pilha como auxílio
void inverterFila(FilaCircular *f) {
    if (f->total == 0) return;
    
    Peca temp[TAM_FILA];
    int n = f->total;
    
    // Transfere para um array temporário de forma reversa
    for (int i = 0; i < n; i++) {
        int idx = (f->frente + (n - 1 - i)) % TAM_FILA;
        temp[i] = f->itens[idx];
    }
    
    // Devolve para a fila na nova ordem
    for (int i = 0; i < n; i++) {
        int idx = (f->frente + i) % TAM_FILA;
        f->itens[idx] = temp[i];
    }
    printf("\n🔃 FILA INVERTIDA! Estratégia alterada.\n");
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
        printf("\n1 - Jogar peca\n2 - Reservar peca (Push)\n3 - Usar reserva (Pop)");
        printf("\n4 - Trocar Topo com Frente\n5 - Inverter Fila\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("\n🕹️ JOGOU: [%c %d]\n", fila.itens[fila.frente].nome, fila.itens[fila.frente].id);
                fila.frente = (fila.frente + 1) % TAM_FILA;
                fila.final = (fila.final + 1) % TAM_FILA;
                fila.itens[fila.final] = gerarPeca();
                break;
            case 2:
                if (pilha.topo < TAM_PILHA - 1) {
                    pilha.itens[++pilha.topo] = fila.itens[fila.frente];
                    fila.frente = (fila.frente + 1) % TAM_FILA;
                    fila.final = (fila.final + 1) % TAM_FILA;
                    fila.itens[fila.final] = gerarPeca();
                } else printf("\n⚠️ Pilha cheia!\n");
                break;
            case 3:
                if (pilha.topo != -1) printf("\n📤 USOU RESERVA: [%c %d]\n", pilha.itens[pilha.topo--].nome, pilha.itens[pilha.topo + 1].id);
                else printf("\n⚠️ Reserva vazia!\n");
                break;
            case 4: trocarPeca(&fila, &pilha); break;
            case 5: inverterFila(&fila); break;
        }
    } while (opcao != 0);

    return 0;
}