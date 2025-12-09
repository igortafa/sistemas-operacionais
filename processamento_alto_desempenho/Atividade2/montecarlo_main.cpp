#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <iomanip>

int main() {
    long long N = 100000000; 
    int repeticoes = 10;
    
    std::cout << "=== PROBLEMA 2: MONTE CARLO ===" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Threads | Tempo Medio (s) | Speedup" << std::endl;

    std::vector<int> num_threads = {1, 2, 4, 8, 16};
    double tempo_seq = 0.0;

    for (int t : num_threads) {
        omp_set_num_threads(t);
        double tempo_total = 0.0;

        for (int r = 0; r < repeticoes; r++) {
            long long count = 0;
            double inicio = omp_get_wtime();

            if (t == 1) {
                unsigned int seed = 42; 
                for (long long i = 0; i < N; i++) {
                    double x = (double)rand_r(&seed) / RAND_MAX;
                    double y = (double)rand_r(&seed) / RAND_MAX;
                    if (x * x + y * y <= 1.0) count++;
                }
            } else {
                #pragma omp parallel reduction(+:count)
                {
                    unsigned int seed = 42 + omp_get_thread_num();
                    #pragma omp for
                    for (long long i = 0; i < N; i++) {
                        double x = (double)rand_r(&seed) / RAND_MAX;
                        double y = (double)rand_r(&seed) / RAND_MAX;
                        if (x * x + y * y <= 1.0) count++;
                    }
                }
            }

            double fim = omp_get_wtime();
            tempo_total += (fim - inicio);
        }

        double tempo_medio = tempo_total / repeticoes;
        
        if (t == 1) tempo_seq = tempo_medio;
        
        double speedup = tempo_seq / tempo_medio;

        std::cout << "   " << t << "    |    " << tempo_medio 
                  << "     |  " << speedup << std::endl;
    }
    return 0;
}
