#include <stdio.h>

// Variáveis de Estado Simulado
int interrupcao_pendente = 0; // 0 = Falso, 1 = Verdadeiro
int contador_principal = 0;
int valor_salvo_cpu = 0;

// Rotina do Manipulador de Interrupção (ISR - Interrupt Service Routine)
void manipulador_interrupcao() {
    printf("\n--- INTERRUPCAO DETECTADA ---\n");
    
    // 1. Salvar Contexto (Simulado)
    valor_salvo_cpu = contador_principal;
    printf("  [CPU] Salvando Contexto: Valor de contador_principal (%d) salvo.\n", valor_salvo_cpu);

    // 2. Executar Manipulador (Acao da Interrupcao)
    printf("  [ISR] Executando rotina: Respondendo ao evento externo.\n");
    printf("  [ISR] Evento Processado.\n");
    
    // 3. Restaurar Contexto (Simulado)
    contador_principal = valor_salvo_cpu;
    printf("  [CPU] Restaurando Contexto: contador_principal retomado em %d.\n", contador_principal);

    // 4. Limpar Flag de Interrupcao
    interrupcao_pendente = 0; // Define como Falso
    printf("--- INTERRUPCAO CONCLUIDA ---\n\n");
}

// Tarefa Principal (Simula o Loop de Execucao da CPU)
void tarefa_principal() {
    int i;
    for (i = 0; i < 10; i++) {
        // Verifica Interrupcao a Cada Passo 
        if (interrupcao_pendente) {
            manipulador_interrupcao();
        }

        contador_principal++;
        printf("[Principal] Executando... Contador = %d\n", contador_principal);

        // A interrupcao e simulada em um ponto especifico para demonstracao
        if (contador_principal == 5) {
            printf("\n--- DISPOSITIVO ATIVA INTERRUPCAO (Hardware) ---\n");
            interrupcao_pendente = 1; // Define a flag de interrupcao como Verdadeiro
        }
    }
}

int main() {
    printf("Iniciando Simulacao de Interrupcao:\n");
    tarefa_principal();
    printf("Simulacao de Interrupcao Concluida.\n");
    return 0;
}