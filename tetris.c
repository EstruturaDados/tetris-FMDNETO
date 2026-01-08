#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura de uma peça
typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único da peça
} Peca;

// Definição da estrutura da fila circular
typedef struct {
    Peca *pecas;      // Array de peças
    int frente;       // Índice da frente da fila
    int tras;         // Índice do final da fila
    int tamanho;      // Número de elementos na fila
    int capacidade;   // Capacidade máxima da fila
} FilaPecas;

// Definição da estrutura da pilha de reserva
typedef struct {
    Peca *pecas;      // Array de peças
    int topo;         // Índice do topo da pilha (-1 quando vazia)
    int capacidade;   // Capacidade máxima da pilha
} PilhaReserva;

// Variável global para controlar o ID das peças
int proximoId = 0;

// ========================================
// FUNÇÕES PARA GERAÇÃO DE PEÇAS
// ========================================

// Função para gerar uma peça aleatoriamente
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    // Seleciona um tipo aleatório
    novaPeca.nome = tipos[rand() % 4];
    novaPeca.id = proximoId++;
    
    return novaPeca;
}

// ========================================
// FUNÇÕES DA FILA CIRCULAR
// ========================================

// Função para criar e inicializar a fila
FilaPecas* criarFila(int capacidade) {
    FilaPecas *fila = (FilaPecas*)malloc(sizeof(FilaPecas));
    
    fila->pecas = (Peca*)malloc(capacidade * sizeof(Peca));
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
    fila->capacidade = capacidade;
    
    return fila;
}

// Função para verificar se a fila está vazia
int filaVazia(FilaPecas *fila) {
    return fila->tamanho == 0;
}

// Função para verificar se a fila está cheia
int filaCheia(FilaPecas *fila) {
    return fila->tamanho == fila->capacidade;
}

// Função para inserir uma peça no final da fila (enqueue)
int enqueue(FilaPecas *fila, Peca peca) {
    if (filaCheia(fila)) {
        return 0;  // Falha ao inserir
    }
    
    // Calcula a próxima posição (circular)
    fila->tras = (fila->tras + 1) % fila->capacidade;
    fila->pecas[fila->tras] = peca;
    fila->tamanho++;
    
    return 1;  // Sucesso
}

// Função para remover uma peça da frente da fila (dequeue)
Peca dequeue(FilaPecas *fila) {
    Peca pecaVazia = {' ', -1};
    
    if (filaVazia(fila)) {
        return pecaVazia;  // Retorna peça vazia se a fila estiver vazia
    }
    
    Peca pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    
    return pecaRemovida;
}

// Função para liberar a memória da fila
void liberarFila(FilaPecas *fila) {
    free(fila->pecas);
    free(fila);
}

// ========================================
// FUNÇÕES DA PILHA DE RESERVA
// ========================================

// Função para criar e inicializar a pilha
PilhaReserva* criarPilha(int capacidade) {
    PilhaReserva *pilha = (PilhaReserva*)malloc(sizeof(PilhaReserva));
    
    pilha->pecas = (Peca*)malloc(capacidade * sizeof(Peca));
    pilha->topo = -1;  // Pilha inicia vazia
    pilha->capacidade = capacidade;
    
    return pilha;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(PilhaReserva *pilha) {
    return pilha->topo == -1;
}

// Função para verificar se a pilha está cheia
int pilhaCheia(PilhaReserva *pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

// Função para inserir uma peça no topo da pilha (push)
int push(PilhaReserva *pilha, Peca peca) {
    if (pilhaCheia(pilha)) {
        return 0;  // Falha ao inserir
    }
    
    pilha->topo++;
    pilha->pecas[pilha->topo] = peca;
    
    return 1;  // Sucesso
}

// Função para remover uma peça do topo da pilha (pop)
Peca pop(PilhaReserva *pilha) {
    Peca pecaVazia = {' ', -1};
    
    if (pilhaVazia(pilha)) {
        return pecaVazia;  // Retorna peça vazia se a pilha estiver vazia
    }
    
    Peca pecaRemovida = pilha->pecas[pilha->topo];
    pilha->topo--;
    
    return pecaRemovida;
}

// Função para liberar a memória da pilha
void liberarPilha(PilhaReserva *pilha) {
    free(pilha->pecas);
    free(pilha);
}

// ========================================
// FUNÇÕES DE EXIBIÇÃO
// ========================================

// Função para exibir o estado atual (fila e pilha)
void exibirEstadoAtual(FilaPecas *fila, PilhaReserva *pilha) {
    printf("\n========================================\n");
    printf("         ESTADO ATUAL\n");
    printf("========================================\n");
    
    // Exibir fila de peças
    printf("\nFila de pecas: ");
    if (filaVazia(fila)) {
        printf("[Vazia]");
    } else {
        int i, index;
        for (i = 0; i < fila->tamanho; i++) {
            index = (fila->frente + i) % fila->capacidade;
            printf("[%c %d] ", fila->pecas[index].nome, fila->pecas[index].id);
        }
    }
    printf("\n");
    
    // Exibir pilha de reserva
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(pilha)) {
        printf("[Vazia]");
    } else {
        int i;
        for (i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->pecas[i].nome, pilha->pecas[i].id);
        }
    }
    printf("\n");
    
    printf("========================================\n");
}

// Função para exibir o menu de opções
void exibirMenu() {
    printf("\n+----------------------------------------------+\n");
    printf("|           OPCOES DE ACAO                     |\n");
    printf("+----------------------------------------------+\n");
    printf("| Codigo | Acao                                |\n");
    printf("+----------------------------------------------+\n");
    printf("|   1    | Jogar peca da frente da fila        |\n");
    printf("|   2    | Enviar peca da fila para a pilha    |\n");
    printf("|   3    | Usar peca da pilha de reserva       |\n");
    printf("|   4    | Trocar peca da fila com topo pilha  |\n");
    printf("|   5    | Trocar 3 da fila com 3 da pilha     |\n");
    printf("|   0    | Sair                                |\n");
    printf("+----------------------------------------------+\n");
    printf("\nOpcao escolhida: ");
}

// ========================================
// FUNÇÕES DE AÇÕES DO JOGO
// ========================================

// Função para jogar uma peça (remove da fila)
void jogarPeca(FilaPecas *fila) {
    if (filaVazia(fila)) {
        printf("\n[ERRO] A fila esta vazia! Nao ha pecas para jogar.\n");
        return;
    }
    
    Peca pecaJogada = dequeue(fila);
    printf("\n[ACAO] Peca [%c %d] foi jogada!\n", pecaJogada.nome, pecaJogada.id);
    
    // Adiciona uma nova peça automaticamente
    Peca novaPeca = gerarPeca();
    enqueue(fila, novaPeca);
    printf("[INFO] Nova peca [%c %d] foi adicionada a fila.\n", novaPeca.nome, novaPeca.id);
}

// Função para reservar uma peça (move da fila para pilha)
void reservarPeca(FilaPecas *fila, PilhaReserva *pilha) {
    if (filaVazia(fila)) {
        printf("\n[ERRO] A fila esta vazia! Nao ha pecas para reservar.\n");
        return;
    }
    
    if (pilhaCheia(pilha)) {
        printf("\n[ERRO] A pilha de reserva esta cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    
    Peca pecaReservada = dequeue(fila);
    push(pilha, pecaReservada);
    printf("\n[ACAO] Peca [%c %d] foi movida para a reserva!\n", pecaReservada.nome, pecaReservada.id);
    
    // Adiciona uma nova peça automaticamente
    Peca novaPeca = gerarPeca();
    enqueue(fila, novaPeca);
    printf("[INFO] Nova peca [%c %d] foi adicionada a fila.\n", novaPeca.nome, novaPeca.id);
}

// Função para usar uma peça reservada (remove da pilha)
void usarPecaReservada(PilhaReserva *pilha) {
    if (pilhaVazia(pilha)) {
        printf("\n[ERRO] A pilha de reserva esta vazia! Nao ha pecas reservadas para usar.\n");
        return;
    }
    
    Peca pecaUsada = pop(pilha);
    printf("\n[ACAO] Peca reservada [%c %d] foi usada!\n", pecaUsada.nome, pecaUsada.id);
}

// Função para trocar a peça da frente da fila com o topo da pilha
void trocarPecaAtual(FilaPecas *fila, PilhaReserva *pilha) {
    if (filaVazia(fila)) {
        printf("\n[ERRO] A fila esta vazia! Nao ha peca para trocar.\n");
        return;
    }
    
    if (pilhaVazia(pilha)) {
        printf("\n[ERRO] A pilha de reserva esta vazia! Nao ha peca para trocar.\n");
        return;
    }
    
    // Remove peça da frente da fila
    Peca pecaFila = fila->pecas[fila->frente];
    
    // Remove peça do topo da pilha
    Peca pecaPilha = pilha->pecas[pilha->topo];
    
    // Realiza a troca
    fila->pecas[fila->frente] = pecaPilha;
    pilha->pecas[pilha->topo] = pecaFila;
    
    printf("\n[ACAO] Troca realizada!\n");
    printf("  - Peca [%c %d] da fila foi para a pilha\n", pecaFila.nome, pecaFila.id);
    printf("  - Peca [%c %d] da pilha foi para a fila\n", pecaPilha.nome, pecaPilha.id);
}

// Função para trocar as 3 primeiras peças da fila com as 3 peças da pilha
void trocaMultipla(FilaPecas *fila, PilhaReserva *pilha) {
    // Verifica se a fila tem pelo menos 3 peças
    if (fila->tamanho < 3) {
        printf("\n[ERRO] A fila precisa ter pelo menos 3 pecas para realizar a troca multipla.\n");
        printf("  Pecas na fila: %d\n", fila->tamanho);
        return;
    }
    
    // Verifica se a pilha tem exatamente 3 peças
    if (pilha->topo + 1 < 3) {
        printf("\n[ERRO] A pilha precisa ter pelo menos 3 pecas para realizar a troca multipla.\n");
        printf("  Pecas na pilha: %d\n", pilha->topo + 1);
        return;
    }
    
    // Array temporário para armazenar as 3 peças da fila
    Peca tempFila[3];
    
    // Array temporário para armazenar as 3 peças da pilha
    Peca tempPilha[3];
    
    // Copia as 3 primeiras peças da fila
    printf("\n[ACAO] Iniciando troca multipla...\n");
    printf("\nPecas da fila a serem trocadas:\n");
    for (int i = 0; i < 3; i++) {
        int index = (fila->frente + i) % fila->capacidade;
        tempFila[i] = fila->pecas[index];
        printf("  [%c %d] ", tempFila[i].nome, tempFila[i].id);
    }
    
    // Copia as 3 peças do topo da pilha (do topo para a base)
    printf("\n\nPecas da pilha a serem trocadas:\n");
    for (int i = 0; i < 3; i++) {
        tempPilha[i] = pilha->pecas[pilha->topo - i];
        printf("  [%c %d] ", tempPilha[i].nome, tempPilha[i].id);
    }
    
    // Coloca as peças da pilha na fila (do topo da pilha para frente da fila)
    for (int i = 0; i < 3; i++) {
        int index = (fila->frente + i) % fila->capacidade;
        fila->pecas[index] = tempPilha[i];
    }
    
    // Coloca as peças da fila na pilha (invertendo a ordem)
    for (int i = 0; i < 3; i++) {
        pilha->pecas[pilha->topo - i] = tempFila[i];
    }
    
    printf("\n\n[SUCESSO] Troca multipla realizada entre os 3 primeiros da fila e os 3 da pilha!\n");
}

// ========================================
// FUNÇÃO PRINCIPAL
// ========================================

int main() {
    int opcao;
    int capacidadeFila = 5;     // Capacidade da fila
    int capacidadePilha = 3;    // Capacidade da pilha de reserva
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Cria a fila de peças e a pilha de reserva
    FilaPecas *fila = criarFila(capacidadeFila);
    PilhaReserva *pilha = criarPilha(capacidadePilha);
    
    // Cabeçalho do programa
    printf("========================================\n");
    printf("    TETRIS STACK - Gerenciador de Pecas\n");
    printf("========================================\n");
    printf("\nInicializando o jogo...\n");
    printf("- Fila de pecas: %d posicoes\n", capacidadeFila);
    printf("- Pilha de reserva: %d posicoes\n", capacidadePilha);
    
    // Inicializa a fila com peças
    printf("\nGerando pecas iniciais...\n");
    for (int i = 0; i < capacidadeFila; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(fila, novaPeca);
        printf("  Peca [%c %d] adicionada.\n", novaPeca.nome, novaPeca.id);
    }
    
    printf("\nJogo iniciado! Boa sorte!\n");
    
    // Loop principal do programa
    do {
        exibirEstadoAtual(fila, pilha);
        exibirMenu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:  // Jogar peça
                jogarPeca(fila);
                break;
                
            case 2:  // Reservar peça
                reservarPeca(fila, pilha);
                break;
                
            case 3:  // Usar peça reservada
                usarPecaReservada(pilha);
                break;
                
            case 4:  // Trocar peça da frente da fila com topo da pilha
                trocarPecaAtual(fila, pilha);
                break;
                
            case 5:  // Trocar 3 peças da fila com 3 da pilha
                trocaMultipla(fila, pilha);
                break;
                
            case 0:  // Sair
                printf("\n========================================\n");
                printf("  Encerrando o Tetris Stack...\n");
                printf("  Obrigado por jogar!\n");
                printf("========================================\n");
                break;
                
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
                break;
        }
        
    } while(opcao != 0);
    
    // Libera a memória alocada
    liberarFila(fila);
    liberarPilha(pilha);
    
    return 0;
}
