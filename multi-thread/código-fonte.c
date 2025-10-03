#include <stdio.h>

// Variáveis globais para armazenar os resultados
double media_global;
int minimo_global;
int maximo_global;

// Simulação da função para o "Thread 1" - Calcula a média
void thread_calcula_media(int numeros[], int tamanho) {
    long long soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += numeros[i];
    }
    media_global = (double)soma / tamanho;
    // O thread "terminaria" aqui após a conclusão da tarefa.
}

// Simulação da função para o "Thread 2" - Encontra o mínimo
void thread_encontra_minimo(int numeros[], int tamanho) {
    int min = numeros[0];
    for (int i = 1; i < tamanho; i++) {
        if (numeros[i] < min) {
            min = numeros[i];
        }
    }
    minimo_global = min;
    // O thread "terminaria" aqui após a conclusão da tarefa.
}

// Simulação da função para o "Thread 3" - Encontra o máximo
void thread_encontra_maximo(int numeros[], int tamanho) {
    int max = numeros[0];
    for (int i = 1; i < tamanho; i++) {
        if (numeros[i] > max) {
            max = numeros[i];
        }
    }
    maximo_global = max;
    // O thread "terminaria" aqui após a conclusão da tarefa.
}

int main() {
    int numeros[] = {90, 81, 78, 95, 79, 72, 85};
    int tamanho = 7;
    
    // As chamadas de função abaixo representam a "criação e execução" dos threads.
    // Em um programa real, eles rodariam em paralelo.
    
    // "Thread 1" é criado e começa a calcular a média
    thread_calcula_media(numeros, tamanho);
    
    // "Thread 2" é criado e começa a encontrar o mínimo
    thread_encontra_minimo(numeros, tamanho);
    
    // "Thread 3" é criado e começa a encontrar o máximo
    thread_encontra_maximo(numeros, tamanho);
    
    // No programa real, o "thread pai" (main) aguardaria todos os outros
    // "threads" finalizarem antes de prosseguir.
    
    // Exibição dos resultados (como se os threads já tivessem finalizado)
    printf("O valor medio e %.2f\n", media_global);
    printf("O valor minimo e %d\n", minimo_global);
    printf("O valor maximo e %d\n", maximo_global);

    return 0;
}
