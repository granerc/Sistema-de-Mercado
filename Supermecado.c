#include <stdio.h>        // Biblioteca entrada e saída de dados
#include <string.h>       // Biblioteca manipulação de strings 
#include <locale.h>       // Biblioteca configurar a localidade 
#include <stdlib.h>       // Biblioteca funções utilitárias

#define MAX_PRODUTOS 50   // nº máximo de produtos que podem ser cadastrados
#define MAX_CARRINHO 50   // nº máximo de produtos diferentes no carrinho

// Struct para armazenar dados de um produto
typedef struct {
    int codigo;           
    char nome[30];        // Nome do produto, até 30 caracteres
    float preco;          
    int estoque;          
} Produto;

// Struct para armazenar dados de um item no carrinho
typedef struct {
    Produto produto;      // Produto adicionado ao carrinho
    int quantidade;       
} Carrinho;

// Arrays globais para armazenar produtos e itens do carrinho

Produto produtos[MAX_PRODUTOS];  
Carrinho carrinho[MAX_CARRINHO]; 

// Variáveis globais para contar quantos produtos e itens estão cadastrados e no carrinho

int numProdutos = 0;      
int numCarrinho = 0;      

// Função para limpar o buffer de entrada
void limparBuffer() {
    while (getchar() != '\n');  // Limpa qualquer caractere no buffer do teclado
}

// Função para exibir o menu 
void menu() {
    printf("\n=== Menu Principal ===\n");
    printf("1. Cadastrar produto\n");
    printf("2. Listar produtos\n");
    printf("3. Comprar produto\n");
    printf("4. Visualizar carrinho\n");
    printf("5. Fechar pedido\n");
    printf("6. Buscar produto pelo nome\n");
    printf("7. Sair\n");
    printf("======================\n");
    printf("Escolha uma opção: ");
}

// Função que exibe informações detalhadas de um produto
void infoProduto(Produto prod) {
    printf("Código: %d | Nome: %s | Preço: R$%.2f | Estoque: %d unidades\n", prod.codigo, prod.nome, prod.preco, prod.estoque);
}

// Função para cadastrar um novo produto
void cadastrarProduto() {
    if (numProdutos < MAX_PRODUTOS) { // Verifica se ainda é possível cadastrar mais produtos
        Produto novoProduto;          // Cria uma nova instância da struct Produto
        int sucesso = 0;              // Variável para controlar o sucesso da entrada de dados

        
        // Entrada e validação do código
        do {
            printf("Digite o código do produto: ");
            sucesso = scanf("%d", &novoProduto.codigo);
            limparBuffer();
            if (!sucesso) {
                printf("Entrada inválida! Por favor, insira um número válido para o código.\n");
            }
        } while (!sucesso);

        // Entrada do nome do produto

        printf("Digite o nome do produto: ");
        scanf(" %[^\n]s", novoProduto.nome);  // Lê uma string com espaços
        limparBuffer();

        // Entrada e validação do preço
        do {
            printf("Digite o preço do produto: ");
            sucesso = scanf("%f", &novoProduto.preco);
            limparBuffer();
            if (!sucesso) {
                printf("Entrada inválida! Por favor, insira um valor numérico para o preço.\n");
            }
        } while (!sucesso);

        // Entrada e validação da quantidade em estoque
        do {
            printf("Digite a quantidade em estoque: ");
            sucesso = scanf("%d", &novoProduto.estoque);
            limparBuffer();
            if (!sucesso || novoProduto.estoque < 0) {  // Estoque não pode ser negativo
                printf("Entrada inválida! Por favor, insira uma quantidade válida.\n");
            }
        } while (!sucesso || novoProduto.estoque < 0);

        // Adiciona o produto no array de produtos
        produtos[numProdutos++] = novoProduto;
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Limite de produtos cadastrados atingido!\n");
    }
}

// Função para listar todos os produtos cadastrados
void listarProdutos() {
    if (numProdutos == 0) {  // Verifica se há produtos cadastrados
        printf("Nenhum produto cadastrado!\n");
    } else {
        printf("\n=== Produtos Cadastrados ===\n");
        for (int i = 0; i < numProdutos; i++) {  // Percorre o array de produtos
            infoProduto(produtos[i]);            // Exibe informações de cada produto
        }
    }
}

// Função para verificar se um produto já está no carrinho
int temNoCarrinho(int codigo) {
    for (int i = 0; i < numCarrinho; i++) {    // Percorre o array de itens do carrinho
        if (carrinho[i].produto.codigo == codigo) {
            return i;  // Retorna o índice do produto no carrinho, se encontrado
        }
    }
    return -1;  // Retorna -1 se o produto não estiver no carrinho
}

// Função para adicionar um produto ao carrinho com verificação de estoque

void comprarProduto() {
    int codigo, quantidade;
    
    if (numProdutos == 0) {  // Verifica se há produtos disponíveis para compra
        printf("Nenhum produto disponível para compra.\n");
        return;
    }

    int sucesso = 0;

    // Validação da entrada do código do produto
    do {
        printf("Digite o código do produto que deseja comprar: ");
        sucesso = scanf("%d", &codigo);
        limparBuffer();
        if (!sucesso) {
            printf("Entrada inválida! Por favor, insira um número válido para o código.\n");
        }
    } while (!sucesso);

    // Procura o produto pelo código no array de produtos
    int encontrado = -1;
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) { 
        printf("Produto não encontrado!\n");
        return;
    }

    int carrinhoIndex = temNoCarrinho(codigo);  // Verifica se o produto já está no carrinho
    if (carrinhoIndex != -1) {
        // Se o produto já está no carrinho, pede quantidade adicional
        do {
            printf("Digite a quantidade adicional: ");
            sucesso = scanf("%d", &quantidade);
            limparBuffer();
            if (!sucesso || quantidade <= 0 || (carrinho[carrinhoIndex].quantidade + quantidade > produtos[encontrado].estoque)) {
                printf("Entrada inválida! Quantidade insuficiente em estoque ou valor inválido.\n");
            }
        } while (!sucesso || quantidade <= 0 || (carrinho[carrinhoIndex].quantidade + quantidade > produtos[encontrado].estoque));
        
        carrinho[carrinhoIndex].quantidade += quantidade;  // Atualiza a quantidade no carrinho
        printf("Quantidade atualizada no carrinho!\n");
    } else {
        // Se o produto não está no carrinho, pede a quantidade inicial
        do {
            printf("Digite a quantidade: ");
            sucesso = scanf("%d", &quantidade);
            limparBuffer();
            if (!sucesso || quantidade <= 0 || quantidade > produtos[encontrado].estoque) {
                printf("Entrada inválida! Quantidade insuficiente em estoque ou valor inválido.\n");
            }
        } while (!sucesso || quantidade <= 0 || quantidade > produtos[encontrado].estoque);
        
        if (numCarrinho < MAX_CARRINHO) {  // Verifica se o carrinho não está cheio
            carrinho[numCarrinho].produto = produtos[encontrado];  // Adiciona o produto ao carrinho
            carrinho[numCarrinho].quantidade = quantidade;  // Define a quantidade comprada
            numCarrinho++;
            printf("Produto adicionado ao carrinho!\n");
        } else {
            printf("Carrinho cheio!\n");
        }
    }
}

// Função para visualizar os itens no carrinho
void visualizarCarrinho() {
    if (numCarrinho == 0) {  // Verifica se há itens no carrinho
        printf("Carrinho vazio!\n");
    } else {
        printf("\n=== Carrinho de Compras ===\n");
        for (int i = 0; i < numCarrinho; i++) {  // Percorre o array de itens do carrinho
            Produto prod = carrinho[i].produto;  // Acessa o produto no carrinho
            printf("Código: %d | Nome: %s | Preço: R$%.2f | Quantidade: %d\n",
                   prod.codigo, prod.nome, prod.preco, carrinho[i].quantidade); 
        }
    }
}


// Função para buscar um produto pelo nome
void buscarProduto() {
    char nome[30];
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]s", nome);  // Lê o nome com espaços
    limparBuffer();
    
    int encontrado = 0;  // Variável para verificar se algum produto foi encontrado
    printf("\n=== Resultados da Busca ===\n");
    for (int i = 0; i < numProdutos; i++) {  
        if (strstr(produtos[i].nome, nome)) {  // Verifica se o nome buscado faz parte do nome do produto
            infoProduto(produtos[i]);  // Exibe informações do produto encontrado
            encontrado = 1;
        }
    }
    
    if (!encontrado) {
        printf("Nenhum produto encontrado!\n");  // Caso nenhum produto for encontrado
    }
}

// Função para finalizar a compra e exibir o valor total
void fecharPedido() {
    if (numCarrinho == 0) {  // Verifica se há itens no carrinho
        printf("Carrinho vazio! Não é possível fechar o pedido.\n");
    } else {
        float total = 0;  // Variável para calcular o valor total da compra
        printf("\n=== Resumo do Pedido ===\n");
        for (int i = 0; i < numCarrinho; i++) {  
            Produto prod = carrinho[i].produto;  // Acessa o produto no carrinho
            total += carrinho[i].quantidade * prod.preco;  // Calcula o valor total do item (preço * quantidade)
            produtos[i].estoque -= carrinho[i].quantidade;  // Atualiza o estoque do produto
            printf("Produto: %s | Quantidade: %d | Preço: R$%.2f\n", prod.nome, carrinho[i].quantidade, carrinho[i].quantidade * prod.preco);
        }
        printf("Total do pedido: R$%.2f\n", total);  
        numCarrinho = 0;  // Limpa o carrinho após o fechamento do pedido
        printf("Pedido fechado com sucesso!\n");
    }
}

// Função principal do programa
int main() {
    setlocale(LC_ALL, "Portuguese");  // Define a localidade para permitir acentuação
    int opcao;

    do {
        menu();  
        scanf("%d", &opcao); 
        limparBuffer();

        switch (opcao) {
            case 1: 
            cadastrarProduto(); 
            break;       

            case 2: 
            listarProdutos(); 
            break;          

            case 3: 
            comprarProduto(); 
            break;          

            case 4: 
            visualizarCarrinho(); 
            break;      

            case 5: 
            fecharPedido(); 
            break;            

            case 6: 
            buscarProduto(); 
            break;           

            case 7: 
            printf("Saindo...\n"); 
            break;     

            default: 
            printf("Opção inválida!\n");  
        }
    } while (opcao != 7);  // Continua executando o menu até o usuário escolher sair

    return 0;
}

