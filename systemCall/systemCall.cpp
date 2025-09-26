
/*#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> // Necessário para a função atoi

const std::string ARQUIVO_ESTOQUE = "estoque.txt";
const int ESTOQUE_MINIMO = 10;

// Classe para representar um Produto
class Produto {
public:
    std::string nome;
    int quantidade;

    // Construtor
    Produto(const std::string& n = "", int q = 0) : nome(n), quantidade(q) {}
};

// Protótipos das funções
void inicializar_sistema();
void adicionar_produto(const std::string& nome, int quantidade);
void remover_produto(const std::string& nome, int quantidade);
void verificar_disponibilidade(const std::string& nome);
void gerar_relatorio_estoque_baixo();

int main() {
    inicializar_sistema();
    
    // 1. Adicionar produtos
    adicionar_produto("Camiseta", 50);
    adicionar_produto("Calca Jeans", 25);
    adicionar_produto("Sapato", 8);
    
    // 2. Verificar a disponibilidade
    verificar_disponibilidade("Camiseta");
    verificar_disponibilidade("Sapato");
    
    // 3. Remover produtos (saida)
    remover_produto("Camiseta", 15);
    remover_produto("Sapato", 5);
    
    // 4. Verificar novamente a disponibilidade
    verificar_disponibilidade("Camiseta");
    verificar_disponibilidade("Sapato");
    
    // 5. Gerar o relatorio de estoque baixo
    gerar_relatorio_estoque_baixo();

    return 0;
}

// ------------------- Funções do Sistema de Controle de Estoque -------------------

void inicializar_sistema() {
    // Abertura com .c_str() para compatibilidade
    std::ofstream arquivo(ARQUIVO_ESTOQUE.c_str(), std::ios::app);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao inicializar o sistema." << std::endl;
        exit(1);
    }
    arquivo.close();
}

void adicionar_produto(const std::string& nome, int quantidade) {
    std::vector<Produto> estoque;
    // Abertura com .c_str() para compatibilidade
    std::ifstream arq_leitura(ARQUIVO_ESTOQUE.c_str());
    
    // 1. Ler todos os produtos para a memória
    std::string linha_str;
    while (std::getline(arq_leitura, linha_str)) {
        size_t pos = linha_str.find('|');
        if (pos != std::string::npos) {
            std::string nome_lido = linha_str.substr(0, pos);
            // Uso de atoi para converter string para int
            int quantidade_lida = atoi(linha_str.substr(pos + 1).c_str());
            estoque.push_back(Produto(nome_lido, quantidade_lida));
        }
    }
    arq_leitura.close();

    // 2. Atualizar o produto se já existir
    bool encontrado = false;
    for (auto& produto : estoque) {
        if (produto.nome == nome) {
            produto.quantidade += quantidade;
            encontrado = true;
            std::cout << "Produto '" << produto.nome << "' atualizado. Nova quantidade: " << produto.quantidade << std::endl;
            break;
        }
    }

    // 3. Adicionar o novo produto se não for encontrado
    if (!encontrado) {
        estoque.push_back(Produto(nome, quantidade));
        std::cout << "Novo produto '" << nome << "' adicionado com a quantidade: " << quantidade << std::endl;
    }

    // 4. Reescrever todo o estoque no arquivo
    std::ofstream arq_escrita(ARQUIVO_ESTOQUE.c_str());
    if (!arq_escrita.is_open()) {
        std::cerr << "Erro ao reescrever o arquivo de estoque." << std::endl;
        return;
    }
    for (const auto& produto : estoque) {
        arq_escrita << produto.nome << "|" << produto.quantidade << std::endl;
    }
    arq_escrita.close();
}

void remover_produto(const std::string& nome, int quantidade) {
    std::vector<Produto> estoque;
    // Abertura com .c_str() para compatibilidade
    std::ifstream arq_leitura(ARQUIVO_ESTOQUE.c_str());
    
    // 1. Ler todos os produtos
    std::string linha_str;
    while (std::getline(arq_leitura, linha_str)) {
        size_t pos = linha_str.find('|');
        if (pos != std::string::npos) {
            std::string nome_lido = linha_str.substr(0, pos);
            // Uso de atoi para converter string para int
            int quantidade_lida = atoi(linha_str.substr(pos + 1).c_str());
            estoque.push_back(Produto(nome_lido, quantidade_lida));
        }
    }
    arq_leitura.close();

    // 2. Remover a quantidade
    bool encontrado = false;
    for (auto& produto : estoque) {
        if (produto.nome == nome) {
            encontrado = true;
            if (produto.quantidade >= quantidade) {
                produto.quantidade -= quantidade;
                std::cout << "Saida de " << quantidade << " unidades de '" << produto.nome << "'. Quantidade restante: " << produto.quantidade << std::endl;
            } else {
                std::cout << "Estoque insuficiente para '" << produto.nome << "'. Apenas " << produto.quantidade << " unidades disponiveis." << std::endl;
            }
            break;
        }
    }

    // 3. Reescrever o arquivo
    std::ofstream arq_escrita(ARQUIVO_ESTOQUE.c_str());
    if (!arq_escrita.is_open()) {
        std::cerr << "Erro ao reescrever o arquivo de estoque." << std::endl;
        return;
    }
    for (const auto& produto : estoque) {
        arq_escrita << produto.nome << "|" << produto.quantidade << std::endl;
    }
    arq_escrita.close();

    if (!encontrado) {
        std::cout << "Produto '" << nome << "' nao encontrado no estoque." << std::endl;
    }
}

void verificar_disponibilidade(const std::string& nome) {
    // Abertura com .c_str() para compatibilidade
    std::ifstream arquivo(ARQUIVO_ESTOQUE.c_str());
    if (!arquivo.is_open()) {
        std::cerr << "Nao foi possivel verificar a disponibilidade: arquivo nao encontrado." << std::endl;
        return;
    }
    
    std::string linha_str;
    bool encontrado = false;
    while (std::getline(arquivo, linha_str)) {
        size_t pos = linha_str.find('|');
        if (pos != std::string::npos) {
            std::string nome_lido = linha_str.substr(0, pos);
            if (nome_lido == nome) {
                // Uso de atoi para converter string para int
                int quantidade_lida = atoi(linha_str.substr(pos + 1).c_str());
                std::cout << "Disponibilidade de '" << nome_lido << "': " << quantidade_lida << " unidades." << std::endl;
                encontrado = true;
                break;
            }
        }
    }
    arquivo.close();

    if (!encontrado) {
        std::cout << "Produto '" << nome << "' nao encontrado no estoque." << std::endl;
    }
}

void gerar_relatorio_estoque_baixo() {
    // Abertura com .c_str() para compatibilidade
    std::ifstream arquivo(ARQUIVO_ESTOQUE.c_str());
    if (!arquivo.is_open()) {
        std::cerr << "Nao foi possivel gerar o relatorio: arquivo de estoque nao encontrado." << std::endl;
        return;
    }
    
    std::cout << "\n--- RELATORIO DE ESTOQUE BAIXO ---\n";
    bool alguma_alerta = false;
    std::string linha_str;
    
    while (std::getline(arquivo, linha_str)) {
        size_t pos = linha_str.find('|');
        if (pos != std::string::npos) {
            std::string nome = linha_str.substr(0, pos);
            // Uso de atoi para converter string para int
            int quantidade = atoi(linha_str.substr(pos + 1).c_str());
            
            if (quantidade <= ESTOQUE_MINIMO) {
                std::cout << "Alerta: '" << nome << "' esta com estoque baixo. Apenas " << quantidade << " unidades.\n";
                alguma_alerta = true;
            }
        }
    }
    arquivo.close();
    
    if (!alguma_alerta) {
        std::cout << "Nenhum produto com estoque baixo." << std::endl;
    }
    std::cout << "------------------------------------\n";
}
*/
