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

// Variável global para controlar o ID das peças
int proximoId = 0;

// Função para gerar uma peça aleatoriamente
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    // Seleciona um tipo aleatório
    novaPeca.nome = tipos[rand() % 4];
    novaPeca.id = proximoId++;
    
    return novaPeca;
}

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
        printf("\nErro: A fila está cheia! Não é possível inserir mais peças.\n");
        return 0;
    }
    
    // Calcula a próxima posição (circular)
    fila->tras = (fila->tras + 1) % fila->capacidade;
    fila->pecas[fila->tras] = peca;
    fila->tamanho++;
    
    printf("\nPeça [%c %d] inserida com sucesso!\n", peca.nome, peca.id);
    return 1;
}

// Função para remover uma peça da frente da fila (dequeue)
Peca dequeue(FilaPecas *fila) {
    Peca pecaVazia = {' ', -1};
    
    if (filaVazia(fila)) {
        printf("\nErro: A fila está vazia! Não há peças para jogar.\n");
        return pecaVazia;
    }
    
    Peca pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    
    printf("\nPeça [%c %d] jogada com sucesso!\n", pecaRemovida.nome, pecaRemovida.id);
    return pecaRemovida;
}

// Função para exibir o estado atual da fila
void exibirFila(FilaPecas *fila) {
    printf("\n========================================\n");
    printf("       FILA DE PEÇAS\n");
    printf("========================================\n");
    
    if (filaVazia(fila)) {
        printf("[Fila vazia]\n");
    } else {
        int i, index;
        for (i = 0; i < fila->tamanho; i++) {
            // Calcula o índice circular
            index = (fila->frente + i) % fila->capacidade;
            printf("[%c %d] ", fila->pecas[index].nome, fila->pecas[index].id);
        }
        printf("\n");
    }
    
    printf("========================================\n");
    printf("Tamanho: %d/%d\n", fila->tamanho, fila->capacidade);
    printf("========================================\n");
}

// Função para exibir o menu de opções
void exibirMenu() {
    printf("\n+--------------------------------------+\n");
    printf("|        OPÇÕES DE AÇÃO               |\n");
    printf("+--------------------------------------+\n");
    printf("| 1 - Jogar peça (dequeue)            |\n");
    printf("| 2 - Inserir nova peça (enqueue)     |\n");
    printf("| 0 - Sair                            |\n");
    printf("+--------------------------------------+\n");
    printf("Escolha uma opção: ");
}

// Função para liberar a memória da fila
void liberarFila(FilaPecas *fila) {
    free(fila->pecas);
    free(fila);
}

// Função principal
int main() {
    int opcao;
    int capacidadeFila = 5;  // Capacidade fixa da fila
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Cria a fila de peças
    FilaPecas *fila = criarFila(capacidadeFila);
    
    // Inicializa a fila com 5 peças
    printf("========================================\n");
    printf("    TETRIS STACK - Sistema de Fila    \n");
    printf("========================================\n");
    printf("\nInicializando a fila com %d peças...\n", capacidadeFila);
    
    for (int i = 0; i < capacidadeFila; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(fila, novaPeca);
    }
    
    // Loop principal do programa
    do {
        exibirFila(fila);
        exibirMenu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:  // Jogar peça (dequeue)
                dequeue(fila);
                break;
                
            case 2:  // Inserir nova peça (enqueue)
                {
                    Peca novaPeca = gerarPeca();
                    enqueue(fila, novaPeca);
                }
                break;
                
            case 0:  // Sair
                printf("\n========================================\n");
                printf("  Encerrando o Tetris Stack...\n");
                printf("  Obrigado por jogar!\n");
                printf("========================================\n");
                break;
                
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
        
    } while(opcao != 0);
    
    // Libera a memória alocada
    liberarFila(fila);
    
    return 0;
}
