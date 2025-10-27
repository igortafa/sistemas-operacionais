#include <stdio.h>

// Definindo os Niveis da Hierarquia (Abstrato)
#define TEMPO_REGISTRADORES 1 
#define TEMPO_CACHE 10      
#define TEMPO_RAM 100       

// Base de dados simulada na Memoria Principal (RAM)
int MemoriaPrincipal[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

// Simulação da Memória Cache (menor e mais rápida)
struct Cache {
    int endereco;
    int valor;
};

// Cache de apenas 4 "linhas"
struct Cache CacheL1[4] = {{-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}};

// Variáveis de Registradores (Mais Rápido)
int Registrador_A = 0;
long long tempo_total_acesso = 0;

// Função que simula o acesso em toda a Hierarquia
int acessar_memoria(int endereco) {
    int valor_lido = -1;
    int cache_hit = 0; // 0 = Falso, 1 = Verdadeiro
    int i;

    // 1. Tentar Cache (L1)
    for (i = 0; i < 4; i++) {
        if (CacheL1[i].endereco == endereco) {
            // CACHE HIT! O dado está na Cache
            valor_lido = CacheL1[i].valor;
            tempo_total_acesso += TEMPO_CACHE;
            printf("Acessando Endereco %d:\n  [Cache HIT] Tempo: %d. Valor: %d\n", endereco, TEMPO_CACHE, valor_lido);
            cache_hit = 1;
            break;
        }
    }

    // 2. Se Cache MISS, ir para RAM
    if (!cache_hit) {
        // CACHE MISS! Precisa buscar na RAM
        if (endereco >= 0 && endereco < 10) {
            valor_lido = MemoriaPrincipal[endereco];
            tempo_total_acesso += TEMPO_RAM;
            printf("Acessando Endereco %d:\n  [Cache MISS] Indo para RAM. Tempo: %d. Valor: %d\n", endereco, TEMPO_RAM, valor_lido);

            // Tatica didatica: Carregar para a Cache (Substituicao simples - Mapeamento direto)
            int linha_cache = endereco % 4; 
            CacheL1[linha_cache].endereco = endereco;
            CacheL1[linha_cache].valor = valor_lido;
            printf("  [Cache] Carregando Endereco %d na Linha %d da Cache.\n", endereco, linha_cache);
        } else {
            printf("Endereco de Memoria Invalido.\n");
        }
    }

    // 3. (Simulacao de uso de Registrador)
    if (valor_lido != -1) {
        Registrador_A = valor_lido; // Coloca o dado mais rapido de todos
        tempo_total_acesso += TEMPO_REGISTRADORES;
        printf("  [Registrador] Dado transferido para o Registrador A. Tempo extra: %d\n", TEMPO_REGISTRADORES);
    }

    return valor_lido;
}

int main() {
    printf("### Demonstracao de Hierarquia de Memoria ###\n");
    printf("Tempos de Acesso (Simulado): Reg: %d, Cache: %d, RAM: %d\n\n", TEMPO_REGISTRADORES, TEMPO_CACHE, TEMPO_RAM);

    // Primeira Leitura: Endereco 5 (MISS)
    acessar_memoria(5);
    printf("Tempo Total Acumulado: %lld\n\n", tempo_total_acesso);

    // Segunda Leitura: Endereco 5 (HIT)
    acessar_memoria(5);
    printf("Tempo Total Acumulado: %lld\n\n", tempo_total_acesso);

    // Terceira Leitura: Endereco 1 (MISS)
    acessar_memoria(1);
    printf("Tempo Total Acumulado: %lld\n\n", tempo_total_acesso);

    // Quarta Leitura: Endereco 5 (HIT)
    acessar_memoria(5);
    printf("Tempo Total Acumulado: %lld\n\n", tempo_total_acesso);

    return 0;
}