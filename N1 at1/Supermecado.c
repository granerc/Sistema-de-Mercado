#include <stdio.h>        
#include <string.h>       
#include <locale.h>       
#include <stdlib.h>       

#define MAX_PRODUTOS 50  
#define MAX_CARRINHO 50   

typedef struct {
    int codigo;           
    char nome[30];        
    float preco;          
    int estoque;          
} Produto;

typedef struct {
    Produto produto;      
    int quantidade;       
} Carrinho;


Produto produtos[MAX_PRODUTOS];  
Carrinho carrinho[MAX_CARRINHO]; 

int numProdutos = 0;      
int numCarrinho = 0;      

void limparBuffer() {
    while (getchar() != '\n'); 
}

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

void infoProduto(Produto prod) {
    printf("Código: %d | Nome: %s | Preço: R$%.2f | Estoque: %d unidades\n", prod.codigo, prod.nome, prod.preco, prod.estoque);
}

void cadastrarProduto() {
    if (numProdutos < MAX_PRODUTOS) { 
        Produto novoProduto;          
        int sucesso = 0;              

        do {
            printf("Digite o código do produto: ");
            sucesso = scanf("%d", &novoProduto.codigo);
            limparBuffer();
            if (!sucesso) {
                printf("Entrada inválida! Por favor, insira um número válido para o código.\n");
            }
        } while (!sucesso);

        printf("Digite o nome do produto: ");
        scanf(" %[^\n]s", novoProduto.nome); 
        limparBuffer();

        do {
            printf("Digite o preço do produto: ");
            sucesso = scanf("%f", &novoProduto.preco);
            limparBuffer();
            if (!sucesso) {
                printf("Entrada inválida! Por favor, insira um valor numérico para o preço.\n");
            }
        } while (!sucesso);

        do {
            printf("Digite a quantidade em estoque: ");
            sucesso = scanf("%d", &novoProduto.estoque);
            limparBuffer();
            if (!sucesso || novoProduto.estoque < 0) { 
                printf("Entrada inválida! Por favor, insira uma quantidade válida.\n");
            }
        } while (!sucesso || novoProduto.estoque < 0);

        produtos[numProdutos++] = novoProduto;
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Limite de produtos cadastrados atingido!\n");
    }
}

void listarProdutos() {
    if (numProdutos == 0) {  
        printf("Nenhum produto cadastrado!\n");
    } else {
        printf("\n=== Produtos Cadastrados ===\n");
        for (int i = 0; i < numProdutos; i++) {  
            infoProduto(produtos[i]);            
        }
    }
}

int temNoCarrinho(int codigo) {
    for (int i = 0; i < numCarrinho; i++) {    
        if (carrinho[i].produto.codigo == codigo) {
            return i;  
        }
    }
    return -1;  
}


void comprarProduto() {
    int codigo, quantidade;
    
    if (numProdutos == 0) {  
        printf("Nenhum produto disponível para compra.\n");
        return;
    }

    int sucesso = 0;

    do {
        printf("Digite o código do produto que deseja comprar: ");
        sucesso = scanf("%d", &codigo);
        limparBuffer();
        if (!sucesso) {
            printf("Entrada inválida! Por favor, insira um número válido para o código.\n");
        }
    } while (!sucesso);

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

    int carrinhoIndex = temNoCarrinho(codigo);  
    if (carrinhoIndex != -1) {

        do {
            printf("Digite a quantidade adicional: ");
            sucesso = scanf("%d", &quantidade);
            limparBuffer();
            if (!sucesso || quantidade <= 0 || (carrinho[carrinhoIndex].quantidade + quantidade > produtos[encontrado].estoque)) {
                printf("Entrada inválida! Quantidade insuficiente em estoque ou valor inválido.\n");
            }
        } while (!sucesso || quantidade <= 0 || (carrinho[carrinhoIndex].quantidade + quantidade > produtos[encontrado].estoque));
        
        carrinho[carrinhoIndex].quantidade += quantidade;  
        printf("Quantidade atualizada no carrinho!\n");
    } else {

        do {
            printf("Digite a quantidade: ");
            sucesso = scanf("%d", &quantidade);
            limparBuffer();
            if (!sucesso || quantidade <= 0 || quantidade > produtos[encontrado].estoque) {
                printf("Entrada inválida! Quantidade insuficiente em estoque ou valor inválido.\n");
            }
        } while (!sucesso || quantidade <= 0 || quantidade > produtos[encontrado].estoque);
        
        if (numCarrinho < MAX_CARRINHO) {  
            carrinho[numCarrinho].produto = produtos[encontrado];  
            carrinho[numCarrinho].quantidade = quantidade;  
            numCarrinho++;
            printf("Produto adicionado ao carrinho!\n");
        } else {
            printf("Carrinho cheio!\n");
        }
    }
}

void visualizarCarrinho() {
    if (numCarrinho == 0) {  
        printf("Carrinho vazio!\n");
    } else {
        printf("\n=== Carrinho de Compras ===\n");
        for (int i = 0; i < numCarrinho; i++) {  
            Produto prod = carrinho[i].produto; 
            printf("Código: %d | Nome: %s | Preço: R$%.2f | Quantidade: %d\n",
                   prod.codigo, prod.nome, prod.preco, carrinho[i].quantidade); 
        }
    }
}

void buscarProduto() {
    char nome[30];
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]s", nome); 
    limparBuffer();
    
    int encontrado = 0;  
    printf("\n=== Resultados da Busca ===\n");
    for (int i = 0; i < numProdutos; i++) {  
        if (strstr(produtos[i].nome, nome)) {  
            infoProduto(produtos[i]);  
            encontrado = 1;
        }
    }
    
    if (!encontrado) {
        printf("Nenhum produto encontrado!\n");  
    }
}

void fecharPedido() {
    if (numCarrinho == 0) {  
        printf("Carrinho vazio! Não é possível fechar o pedido.\n");
    } else {
        float total = 0;  
        printf("\n=== Resumo do Pedido ===\n");
        for (int i = 0; i < numCarrinho; i++) {  
            Produto prod = carrinho[i].produto;  
            total += carrinho[i].quantidade * prod.preco;  
            produtos[i].estoque -= carrinho[i].quantidade;  
            printf("Produto: %s | Quantidade: %d | Preço: R$%.2f\n", prod.nome, carrinho[i].quantidade, carrinho[i].quantidade * prod.preco);
        }
        printf("Total do pedido: R$%.2f\n", total);  
        numCarrinho = 0;  
        printf("Pedido fechado com sucesso!\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese"); 
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
    } while (opcao != 7); 

    return 0;
}

