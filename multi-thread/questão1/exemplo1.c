// Código conceitual que simula um servidor web com threads
void *processar_requisicao(void *cliente_data) {
    // Lógica para lidar com a requisição do cliente
    printf("Processando requisicao do cliente...\n");
    // ...envia a resposta
    pthread_exit(NULL);
}

int main() {
    // Servidor escutando por conexões
    while (1) {
        // Nova conexao de cliente
        // pthread_create(&novo_thread, NULL, processar_requisicao, &dados_cliente);
        // O novo thread cuida da requisicao, e o servidor volta a escutar
    }
}
