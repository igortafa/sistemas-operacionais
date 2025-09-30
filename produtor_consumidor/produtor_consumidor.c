#include <stdio.h>
#include <stdlib.h>

// Definimos o tamanho do nosso "buffer"
#define TAMANHO_BUFFER 5

int main() {
    // Nosso buffer, simulado por um array
    int buffer[TAMANHO_BUFFER];

    // Variáveis de controle do buffer
    int in = 0;   // Índice para onde o produtor vai adicionar o próximo item
    int out = 0;  // Índice de onde o consumidor vai pegar o próximo item
    int contador = 0; // Quantidade de itens no buffer

    int item_produtor = 1; // Item a ser produzido

    printf("Iniciando a simulacao do Produtor-Consumidor...\n\n");

    // Simulamos um ciclo de 15 "ações" para demonstração
    for (int i = 0; i < 15; i++) {
        // --- ACAO DO PRODUTOR ---
        // Se o buffer nao estiver cheio...
        if (contador < TAMANHO_BUFFER) {
            // Adiciona o item ao buffer
            buffer[in] = item_produtor;
            printf("Produtor: Item %d adicionado na posicao %d.\n", item_produtor, in);

            // Incrementa o indice e o contador
            in = (in + 1) % TAMANHO_BUFFER;
            contador++;

            // Incrementa o valor do proximo item a ser produzido
            item_produtor++;
        } else {
            printf("Produtor: Buffer cheio! Produtor esperando...\n");
        }
        
        // --- ACAO DO CONSUMIDOR ---
        // Se o buffer nao estiver vazio...
        if (contador > 0) {
            // Remove o item do buffer
            int item_consumido = buffer[out];
            printf("Consumidor: Item %d removido da posicao %d.\n", item_consumido, out);

            // Incrementa o indice e decrementa o contador
            out = (out + 1) % TAMANHO_BUFFER;
            contador--;
        } else {
            printf("Consumidor: Buffer vazio! Consumidor esperando...\n");
        }

        printf("--- Estado atual: %d de %d itens no buffer. ---\n\n", contador, TAMANHO_BUFFER);
    }

    printf("Simulacao encerrada.\n");

    return 0;
}
