#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME_PRODUTO 100
#define ARQUIVO_ESTOQUE "estoque.txt"
#define ARQUIVO_TEMP "temp_estoque.txt"
#define ESTOQUE_MINIMO 10 // Limite para alerta de estoque baixo

// Estrutura para representar um produto
typedef struct {
    char nome[MAX_NOME_PRODUTO];
    int quantidade;
} Produto;

// Protótipos das funções
void inicializar_sistema();
void adicionar_produto(const char *nome, int quantidade);
void remover_produto(const char *nome, int quantidade);
void verificar_disponibilidade(const char *nome);
void gerar_relatorio_estoque_baixo();

int main() {
    inicializar_sistema();
    
    // 1. Adicionar produtos ao estoque
    adicionar_produto("Camiseta", 50);
    adicionar_produto("Calça Jeans", 25);
    adicionar_produto("Sapato", 8);
    
    // 2. Verificar a disponibilidade de um produto
    verificar_disponibilidade("Camiseta");
    verificar_disponibilidade("Sapato");
    
    // 3. Simular a saída de mercadorias
    remover_produto("Camiseta", 15);
    remover_produto("Sapato", 5);
    
    // 4. Verificar novamente a disponibilidade
    verificar_disponibilidade("Camiseta");
    verificar_disponibilidade("Sapato");
    
    // 5. Gerar o relatório de estoque baixo
    gerar_relatorio_estoque_baixo();

    return 0;
}

// ------------------- Funções do Sistema de Controle de Estoque -------------------

void inicializar_sistema() {
    // Tenta abrir o arquivo para garantir que ele exista.
    FILE *f = fopen(ARQUIVO_ESTOQUE, "a");
    if (f == NULL) {
        printf("Erro ao inicializar o sistema.\n");
        exit(1);
    }
    fclose(f);
}

void adicionar_produto(const char *nome, int quantidade) {
    // Para atualizar a quantidade, a lógica é ler, modificar e reescrever.
    FILE *f_origem = fopen(ARQUIVO_ESTOQUE, "r");
    FILE *f_temp = fopen(ARQUIVO_TEMP, "w");
    if (f_origem == NULL || f_temp == NULL) {
        printf("Erro ao adicionar produto.\n");
        if (f_origem) fclose(f_origem);
        if (f_temp) fclose(f_temp);
        return;
    }

    Produto produto;
    int encontrado = 0;
    while (fscanf(f_origem, "%[^|]|%d\n", produto.nome, &produto.quantidade) == 2) {
        if (strcmp(produto.nome, nome) == 0) {
            produto.quantidade += quantidade;
            encontrado = 1;
            printf("Produto '%s' atualizado. Nova quantidade: %d\n", produto.nome, produto.quantidade);
        }
        fprintf(f_temp, "%s|%d\n", produto.nome, produto.quantidade);
    }
    
    if (!encontrado) {
        fprintf(f_temp, "%s|%d\n", nome, quantidade);
        printf("Novo produto '%s' adicionado com a quantidade: %d\n", nome, quantidade);
    }

    fclose(f_origem);
    fclose(f_temp);

    remove(ARQUIVO_ESTOQUE);
    rename(ARQUIVO_TEMP, ARQUIVO_ESTOQUE);
}

void remover_produto(const char *nome, int quantidade) {
    FILE *f_origem = fopen(ARQUIVO_ESTOQUE, "r");
    FILE *f_temp = fopen(ARQUIVO_TEMP, "w");
    if (f_origem == NULL || f_temp == NULL) {
        printf("Erro ao remover produto.\n");
        if (f_origem) fclose(f_origem);
        if (f_temp) fclose(f_temp);
        return;
    }

    Produto produto;
    int encontrado = 0;
    while (fscanf(f_origem, "%[^|]|%d\n", produto.nome, &produto.quantidade) == 2) {
        if (strcmp(produto.nome, nome) == 0) {
            encontrado = 1;
            if (produto.quantidade >= quantidade) {
                produto.quantidade -= quantidade;
                printf("Saida de %d unidades de '%s'. Quantidade restante: %d\n", quantidade, produto.nome, produto.quantidade);
            } else {
                printf("Estoque insuficiente para '%s'. Apenas %d unidades disponiveis.\n", produto.nome, produto.quantidade);
            }
        }
        fprintf(f_temp, "%s|%d\n", produto.nome, produto.quantidade);
    }

    fclose(f_origem);
    fclose(f_temp);

    remove(ARQUIVO_ESTOQUE);
    rename(ARQUIVO_TEMP, ARQUIVO_ESTOQUE);

    if (!encontrado) {
        printf("Produto '%s' nao encontrado.\n", nome);
    }
}

void verificar_disponibilidade(const char *nome) {
    FILE *f = fopen(ARQUIVO_ESTOQUE, "r");
    if (f == NULL) {
        printf("Nao foi possivel verificar a disponibilidade: arquivo nao encontrado.\n");
        return;
    }

    Produto produto;
    int encontrado = 0;
    while (fscanf(f, "%[^|]|%d\n", produto.nome, &produto.quantidade) == 2) {
        if (strcmp(produto.nome, nome) == 0) {
            printf("Disponibilidade de '%s': %d unidades.\n", produto.nome, produto.quantidade);
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Produto '%s' nao encontrado no estoque.\n", nome);
    }
}

void gerar_relatorio_estoque_baixo() {
    FILE *f = fopen(ARQUIVO_ESTOQUE, "r");
    if (f == NULL) {
        printf("Nao foi possivel gerar o relatorio: arquivo de estoque nao encontrado.\n");
        return;
    }
    
    Produto produto;
    printf("\n--- RELATORIO DE ESTOQUE BAIXO ---\n");
    int alguma_alerta = 0;
    
    while (fscanf(f, "%[^|]|%d\n", produto.nome, &produto.quantidade) == 2) {
        if (produto.quantidade <= ESTOQUE_MINIMO) {
            printf("Alerta: '%s' esta com estoque baixo. Apenas %d unidades.\n", produto.nome, produto.quantidade);
            alguma_alerta = 1;
        }
    }
    fclose(f);
    
    if (!alguma_alerta) {
        printf("Nenhum produto com estoque baixo.\n");
    }
    printf("------------------------------------\n");
}
