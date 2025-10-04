#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tamanho máximo da fila
#define MAX 5

// Estrutura para uma peça do Tetris
struct Peca {
    char tipo;  // Tipo da peça: I, O, T, S, Z, J, L
    int id;     // Número de identificação
};

// Variáveis globais para simplificar
struct Peca fila[MAX];
int inicio = 0;
int fim = -1;
int tamanho = 0;
int proximo_id = 1;

// Função para ver se a fila está vazia
int filaVazia() {
    return tamanho == 0;
}

// Função para ver se a fila está cheia
int filaCheia() {
    return tamanho == MAX;
}

// Função para adicionar peça na fila
void adicionarPeca(char tipo) {
    if (filaCheia()) {
        printf("ERRO: A fila esta cheia!\n");
        return;
    }
    
    // Calcula a próxima posição (fila circular)
    fim = (fim + 1) % MAX;
    
    // Cria a nova peça
    fila[fim].tipo = tipo;
    fila[fim].id = proximo_id;
    
    proximo_id++;
    tamanho++;
    
    printf("Peça %c (ID: %d) adicionada!\n", tipo, fila[fim].id);
}

// Função para remover peça da fila
void removerPeca() {
    if (filaVazia()) {
        printf("ERRO: A fila esta vazia!\n");
        return;
    }
    
    // Mostra qual peça está sendo removida
    printf("Peça removida: %c (ID: %d)\n", fila[inicio].tipo, fila[inicio].id);
    
    // Move o início para a próxima posição (fila circular)
    inicio = (inicio + 1) % MAX;
    tamanho--;
}

// Função para mostrar todas as peças na fila
void mostrarFila() {
    printf("\n=== FILA DE PECAS ===\n");
    
    if (filaVazia()) {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("Peças na fila (%d de %d):\n", tamanho, MAX);
    
    int posicao = inicio;
    for (int i = 0; i < tamanho; i++) {
        printf("%d. [ID: %d, Tipo: %c]\n", i+1, fila[posicao].id, fila[posicao].tipo);
        posicao = (posicao + 1) % MAX;  // Vai para a próxima posição circular
    }
    printf("\n");
}

// Função para gerar tipo de peça aleatório
char gerarTipoAleatorio() {
    // Os 7 tipos de peças do Tetris
    char tipos[] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
    
    // Gera número aleatório entre 0 e 6
    int numero_aleatorio = rand() % 7;
    
    return tipos[numero_aleatorio];
}

// Função para mostrar o menu
void mostrarMenu() {
    printf("\n=== MENU TETRIS ===\n");
    printf("1. Ver fila de peças\n");
    printf("2. Remover primeira peça\n");
    printf("3. Adicionar peça aleatória\n");
    printf("4. Sair\n");
    printf("Escolha: ");
}

// Programa principal
int main() {
    int opcao;
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    printf("Bem-vindo ao Simulador de Tetris!\n");
    printf("Fila criada com capacidade para %d peças.\n", MAX);
    
    // Preenche a fila inicial com peças aleatórias
    printf("\nGerando peças iniciais...\n");
    for (int i = 0; i < MAX; i++) {
        adicionarPeca(gerarTipoAleatorio());
    }
    
    // Loop do menu
    do {
        mostrarMenu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: // Mostrar fila
                mostrarFila();
                break;
                
            case 2: // Remover peça
                if (!filaVazia()) {
                    removerPeca();
                    // Adiciona automaticamente uma nova peça no final
                    adicionarPeca(gerarTipoAleatorio());
                    printf("Nova peça adicionada automaticamente!\n");
                } else {
                    printf("Não há peças para remover!\n");
                }
                break;
                
            case 3: // Adicionar peça
                if (!filaCheia()) {
                    adicionarPeca(gerarTipoAleatorio());
                } else {
                    printf("A fila já está cheia! Remova uma peça primeiro.\n");
                }
                break;
                
            case 4: // Sair
                printf("Obrigado por jogar! Até mais!\n");
                break;
                
            default:
                printf("Opção inválida! Use 1, 2, 3 ou 4.\n");
        }
        
        // Pausa antes de continuar (apenas para opções 1-3)
        if (opcao != 4) {
            printf("\nPressione Enter para continuar...");
            getchar();  // Limpa o buffer
            getchar();  // Espera o Enter
        }
        
    } while (opcao != 4);
    
    return 0;
}