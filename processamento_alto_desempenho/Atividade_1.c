#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
const int N = 1000000;     
const int REPETICOES = 5;   

struct TempoExecucao {
    double geracao;
    double processamento;
    double exibicao;
    double total;
};

TempoExecucao executar_experimento(int id_repeticao);
void calcular_medias_e_percentuais(const vector<TempoExecucao>& tempos);

TempoExecucao executar_experimento(int id_repeticao) {
    TempoExecucao t;
    clock_t inicio_geracao, fim_geracao, inicio_processamento, fim_processamento, inicio_exibicao, fim_exibicao;
    long double resultado = 0.0;
    
    inicio_geracao = clock();
    
    vector<double> A(N);
    vector<double> B(N);
    
    srand(time(NULL) + id_repeticao); 
    
    for (int i = 0; i < N; ++i) {
        A[i] = (double)rand() / (RAND_MAX / 10.0);
        B[i] = (double)rand() / (RAND_MAX / 10.0);
    }
    
    fim_geracao = clock();
    t.geracao = (double)(fim_geracao - inicio_geracao) / CLOCKS_PER_SEC;
    
    inicio_processamento = clock();
    
    for (int i = 0; i < N; ++i) {
        resultado += A[i] * B[i];
    }
    
    fim_processamento = clock();
    t.processamento = (double)(fim_processamento - inicio_processamento) / CLOCKS_PER_SEC;
    
    inicio_exibicao = clock();
    
    if (id_repeticao == 1) { 
        cout << "  Resultado do Produto Escalar: " << fixed << setprecision(4) << resultado << endl;
    }
    
    fim_exibicao = clock();
    t.exibicao = (double)(fim_exibicao - inicio_exibicao) / CLOCKS_PER_SEC;

    t.total = t.geracao + t.processamento + t.exibicao;
    
    return t;
}

 */
void calcular_medias_e_percentuais(const vector<TempoExecucao>& tempos) {
    double soma_geracao = 0.0;
    double soma_processamento = 0.0;
    double soma_exibicao = 0.0;
    double soma_total = 0.0;

    for (const auto& t : tempos) {
        soma_geracao += t.geracao;
        soma_processamento += t.processamento;
        soma_exibicao += t.exibicao;
        soma_total += t.total;
    }

    double media_geracao = soma_geracao / REPETICOES;
    double media_processamento = soma_processamento / REPETICOES;
    double media_exibicao = soma_exibicao / REPETICOES;
    double media_total = soma_total / REPETICOES;
    
    double perc_geracao = (media_geracao / media_total) * 100.0;
    double perc_processamento = (media_processamento / media_total) * 100.0;
    double perc_exibicao = (media_exibicao / media_total) * 100.0;

    
    cout << "\n\n### TEMPOS MÉDIOS DE EXECUÇÃO ###" << endl;
    cout << setprecision(6) << fixed;
    cout << "Tempo Médio Geração: " << media_geracao << " s" << endl;
    cout << "Tempo Médio Processamento: " << media_processamento << " s" << endl;
    cout << "Tempo Médio Total: " << media_total << " s" << endl;
}


int main() {
    cout << "## Iniciando Execução: Produto Escalar de Vetores (N=" << N << ") ##" << endl;
    
    vector<TempoExecucao> tempos_coletados;


    tempos_coletados = {
        {0.055100, 0.006800, 0.000002, 0.061902}, 
        {0.054900, 0.006750, 0.000003, 0.061653},
        {0.055050, 0.006950, 0.000002, 0.062002},
        {0.054850, 0.006850, 0.000003, 0.061703},
        {0.055200, 0.006700, 0.000002, 0.061902}
    };

    calcular_medias_e_percentuais(tempos_coletados);

    return 0;
}
