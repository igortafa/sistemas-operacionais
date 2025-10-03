// Código conceitual de cálculo sequencial
int fibonacci(int n) {
    if (n <= 1) return n;
    // O resultado de cada etapa depende do anterior
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    // Nao ha como dividir esta tarefa entre threads
    int resultado = fibonacci(40);
    printf("Fibonacci de 40: %d\n", resultado);
}
