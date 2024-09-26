# Sistema de Carrinho de Compras em C

<p align="center">
  <img src="https://github.com/granerc/Sistema-de-Mercado/blob/main/paraUsoReadme/images.jfif" alt="Imagem Ilustrativa Supermecado" />
</p>


## Desenvolvimento do Sistema

<p align = "justify"> Este projeto foi desenvolvido em C como um exercício prático para demonstrar conceitos fundamentais de programação, como manipulação de estruturas de dados, entrada e saída, e controle de fluxo. O objetivo principal era criar um sistema que permitisse gerenciar produtos e compras de maneira simples e eficaz. O exemplo a seguir demonstra como ele é apresentado ao usuário e o exemplo do cadastramento de um produto. </p>

<p align="center">
  <img src="https://github.com/granerc/Sistema-de-Mercado/blob/main/paraUsoReadme/ExemploCadastrar.png" alt="Exemplo da Função Cadastrar" />
</p>


## Nova Funcionalidade Implementada
<p align = "justify">Durante o desenvolvimento, decidi implementar a função de **buscar produto**, onde não estava listado nos requisitos. Foi adicionado como uma das funcionalidades principais. Essa escolha foi motivada pela necessidade de facilitar a navegação no sistema, permitindo que os usuários encontrem produtos de forma rápida, especialmente em um cenário onde muitos produtos podem ser cadastrados. A busca por nome é uma funcionalidade intuitiva que melhora a experiência do usuário. Na imagem a seguir, podemos ver como essa nova parte funciona: </p>

<p align="center">
  <img src="https://github.com/granerc/Sistema-de-Mercado/blob/main/paraUsoReadme/FuncaoBusca.png" alt="Exemplo da Função Implementada Buscar Produto" />
</p>


## Funcionalidades Apresentadas

- **Cadastrar Produto:** Permite adicionar até 50 produtos ao sistema, com informações como código, nome, preço e quantidade em estoque.
- **Listar Produtos:** Exibe todos os produtos cadastrados, ajudando o usuário a visualizar o que está disponível.
- **Comprar Produto:** Adiciona produtos ao carrinho, garantindo que a quantidade desejada esteja disponível em estoque.
- **Visualizar Carrinho:** Mostra os produtos que foram adicionados ao carrinho e suas respectivas quantidades.
- **Fechar Pedido:** Finaliza a compra, exibindo um resumo dos itens no carrinho e calculando o total. Atualiza o estoque com base nas quantidades compradas.
- **Buscar Produto pelo Nome:** Permite ao usuário buscar produtos por nome, tornando a navegação mais eficiente.

## Tratamento de Erros Possíveis do Usuário na função Cadastrar Produtos:

<p align = "justify">
  
- **Erro de entrada no código do produto:** Se o usuário digitar um caractere em vez de um número para o código, uma mensagem de erro "Entrada inválida! Por favor, insira um número válido para o código." será exibida. O sistema continua pedindo até que uma entrada válida seja inserida.

- **Erro no preço do produto:** Caso o usuário digite um valor não numérico para o preço, a validação semelhante será feita, com a mensagem "Entrada inválida! Por favor, insira um valor numérico para o preço."

- **Erro na quantidade de estoque:** O estoque não pode ser negativo, então, além de validar que a entrada seja numérica, a função também verifica se o valor é maior ou igual a zero, informando o erro se necessário. </p>

## Tratamento de Erros Possíveis do Usuário na Função Listar Produtos:

- Apenas uma verificação se há produtos cadastrados. Caso não haja, uma mensagem "Nenhum produto cadastrado!" é exibida.

## Tratamento de Erros Possíveis do Usuário na Função Comprar Produtos:

<p align = "justify">
  
- **Erro ao inserir o código do produto:** Se o usuário inserir um caractere ou outro valor inválido, a mensagem "Entrada inválida! Por favor, insira um número válido para o código." será exibida.
  
- **Produto não encontrado:** Caso o código inserido não corresponda a nenhum produto, a mensagem "Produto não encontrado!" é exibida.
  
- **Erro ao inserir a quantidade:** A quantidade precisa ser um valor numérico positivo e menor ou igual ao estoque disponível. Caso contrário, a função exibirá "Entrada inválida! Quantidade insuficiente em estoque ou valor inválido." </p>

## Tratamento de Erros Possíveis do Usuário na Função Visualizar Carrinho

- Caso não haja itens no carrinho, a mensagem "Carrinho vazio!" será exibida.

## Tratamento de Erros Possíveis do Usuário na Função Fechar Pedido:
- Se o carrinho estiver vazio, o pedido não pode ser fechado, e a mensagem "Carrinho vazio! Não é possível fechar o pedido." será exibida.

## Tratamento de Erros Possíveis do Usuário na Função Buscar Produto

- A função buscarProduto não exige validação complexa de entrada, pois busca por substrings no nome do produto. Se nenhum produto for encontrado, a mensagem "Nenhum produto encontrado!" será exibida. 

## Tratamento de Erros Possíveis do Usuário no Menu Principal

- Se o usuário digitar uma opção inválida no menu, como uma letra ou um número fora das opções (1 a 7), a mensagem "Opção inválida!" será exibida, e o programa volta a exibir o menu principal. 

## Instruções de Compilação

1. Assegure se de que você possui um compilador C instalado (como o GCC).
2. Para compilar o programa, execute o seguinte comando no terminal:

   ```bash
   gcc -o programa_produtos programa_produtos.c

## Instruções para Execução

1. Após a compilação, execute o programa com o comando:
   ```bash
   ./programa_produtos
2. O menu será exibido e você poderá interagir com o programa.



