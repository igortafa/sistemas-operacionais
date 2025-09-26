#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 3      // Tamanho do buffer (ajuste de 1 a 5)
#define TOTAL_ITENS 10     // Total de itens a serem produzidos/consumidos

// Variáveis globais
int buffer[BUFFER_SIZE];      // Buffer compartilhado
int count = 0;                // Quantidade atual de itens no buffer
int in = 0, out = 0;          // Índices para inserir e remover do buffer
int next_item = 1;            // Próximo item a ser produzido

pthread_mutex_t mutex;        // Mutex para exclusão mútua
pthread_cond_t cond_full;     // Variável de condição para buffer cheio
pthread_cond_t cond_empty;    // Variável de condição para buffer vazio

// Função para imprimir o estado atual do buffer
void print_buffer() {
    int j;
    printf("Estado do buffer: [");
    for (j = 0; j < count; j++) {
        int idx = (out + j) % BUFFER_SIZE;
        printf("%d", buffer[idx]);
        if (j != count - 1) printf(" ");
    }
    printf("]\n\n");
}

// Função do produtor
void* produtor(void* arg) {
    int i;
    for (i = 0; i < TOTAL_ITENS; ++i) {
        pthread_mutex_lock(&mutex);
        printf("[Produtor] Tentando produzir...\n");

        // Espera caso o buffer esteja cheio
        while (count == BUFFER_SIZE) {
            printf("[Produtor] Buffer cheio, produtor bloqueado.\n");
            pthread_cond_wait(&cond_full, &mutex);
        }

        // Produz item
        buffer[in] = next_item++;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("[Produtor] Item produzido. Buffer agora tem %d item(ns).\n", count);
        print_buffer();

        pthread_cond_signal(&cond_empty); // Avisa consumidor que há item
        pthread_mutex_unlock(&mutex);

        usleep(300000); // Simula tempo de produção (0,3s)
    }
    return NULL;
}

// Função do consumidor
void* consumidor(void* arg) {
    int i;
    for (i = 0; i < TOTAL_ITENS; ++i) {
        pthread_mutex_lock(&mutex);
        printf("[Consumidor] Tentando consumir...\n");

        // Espera caso o buffer esteja vazio
        while (count == 0) {
            printf("[Consumidor] Buffer vazio, consumidor bloqueado.\n");
            pthread_cond_wait(&cond_empty, &mutex);
        }

        // Consome item
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("[Consumidor] Item consumido (%d). Buffer agora tem %d item(ns).\n", item, count);
        print_buffer();

        pthread_cond_signal(&cond_full); // Avisa produtor que há espaço
        pthread_mutex_unlock(&mutex);

        usleep(400000); // Simula tempo de consumo (0,4s)
    }
    return NULL;
}

int main() {
    pthread_t t_prod, t_cons;

    // Inicialização das variáveis de sincronização
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_full, NULL);
    pthread_cond_init(&cond_empty, NULL);

    printf("---- Problema do Produtor-Consumidor ----\n");
    printf("Buffer com %d posições. Total de itens: %d\n\n", BUFFER_SIZE, TOTAL_ITENS);

    // Cria as threads
    pthread_create(&t_prod, NULL, produtor, NULL);
    pthread_create(&t_cons, NULL, consumidor, NULL);

    // Aguarda as threads terminarem
    pthread_join(t_prod, NULL);
    pthread_join(t_cons, NULL);

    // Libera recursos
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_full);
    pthread_cond_destroy(&cond_empty);

    printf("Execução finalizada. Todos os itens foram produzidos e consumidos.\n");
    return 0;
}
