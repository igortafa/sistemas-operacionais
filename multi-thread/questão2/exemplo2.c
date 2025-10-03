// Código conceitual de I/O sequencial
int main() {
    FILE *fp = fopen("arquivo_grande.txt", "r");
    char buffer[1024];

    // Thread 1 comecaria a ler o arquivo...
    // ...mas nao ha espaco para o Thread 2 ler ao mesmo tempo

    while (fgets(buffer, 1024, fp)) {
        // Processa linha por linha
    }
    fclose(fp);
}
