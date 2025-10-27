#include <stdio.h>

// Macro para simular um atraso (Busy Waiting).
// O valor MAX_ITERATIONS deve ser ajustado para um atraso perceptível no seu ambiente.
#define MAX_ITERATIONS 500000000 // 500 milhões para um atraso significativo

void delay_simulado() {
    long long i;
    for (i = 0; i < MAX_ITERATIONS; i++) {
        // Nada acontece aqui, a CPU fica ocupada contando.
    }
}

// ---------------------- E/S Síncrona ----------------------
void io_sincrona() {
    printf("[Sincrona] Iniciando operacao de E/S...\n");
    printf("    [Dispositivo E/S] Processando (CPU Bloqueada / Busy Wait)...\n");
    
    // A CPU AGUARDA aqui, consumindo ciclos ativamente.
    delay_simulado(); 
    
    printf("    [Dispositivo E/S] Operacao concluida.\n");
    printf("[Sincrona] Retornando a aplicacao. CPU estava ociosa/aguardando o I/O.\n");
}

// ---------------------- E/S Assíncrona ----------------------
// Simula a solicitação e o retorno imediato
void io_assincrona_iniciar() {
    printf("[Assincrona] Iniciando operacao de E/S em background...\n");
    
    // Simula que o SO iniciou o dispositivo e retornou o controle IMEDIATAMENTE.
    printf("[Assincrona] Retorno IMEDIATO. CPU L I V R E.\n");
}

// Simula o trabalho que a CPU faz enquanto a E/S estaria em andamento
void trabalho_cpu_paralelo() {
    int i;
    printf("[CPU] Realizando trabalho util em paralelo...\n");
    for(i = 0; i < 3; i++) {
        printf("[CPU] Processando tarefa %d...\n", i + 1);
        delay_simulado(); // Pequeno atraso para demonstrar processamento
    }
    printf("[CPU] Trabalho util concluido.\n");
}

int main() {

    printf("### Demonstracao de E/S Sincrona ###\n");
    io_sincrona();
    printf("--- Fim da execucao sincrona ---\n\n");

    printf("### Demonstracao de E/S Assincrona ###\n");
    io_assincrona_iniciar(); // Inicia E/S e RETORNA
    trabalho_cpu_paralelo(); // CPU faz outro trabalho
    
    printf("[Assincrona] Presumindo que a E/S foi concluida em background e o trabalho da CPU terminou.\n");
    printf("--- Fim da execucao assincrona ---\n");

    return 0;
}