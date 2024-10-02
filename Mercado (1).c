#include <stdio.h>
#include <stdlib.h>

#define PRODS 50 // Define o número máximo de produtos
#define NOME 30  // Define o tamanho máximo para o nome do produto

// Estrutura para armazenar um produto
typedef struct
{
    int codigo;              // Código identificador do produto
    char nome[NOME];         // Nome do produto com tamanho limitado
    float preco;             // Preço do produto
} Produto;

// Estrutura para armazenar um produto no carrinho
typedef struct
{
    Produto produtos;        // Produto que será adicionado ao carrinho
    int quantidade;          // Quantidade desse produto no carrinho
} Carrinho;

// Função para gerar a nota fiscal
void gerarNotaFiscal(Carrinho carrinho[PRODS], int contCarrinho, float total) //isso foi lendario
{
    FILE *arquivo = fopen("nota_fiscal.txt", "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) // Verifica se o arquivo foi aberto corretamente
    {
        printf("Erro ao criar o arquivo da nota fiscal.\n"); // Caso dê erro, informa o usuário
        return; // Encerra a função
    }

    // Cabeçalho da nota fiscal
    fprintf(arquivo, "******************************\n");
    fprintf(arquivo, "*         Nota Fiscal        *\n");
    fprintf(arquivo, "******************************\n");
    fprintf(arquivo, "Produtos:\n");

    // Itera sobre o carrinho e escreve cada produto no arquivo
    for (int i = 0; i < contCarrinho; i++)
    {
        fprintf(arquivo, "Produto: %s | Quantidade: %d | Preço: R$ %.2f\n", carrinho[i].produtos.nome, carrinho[i].quantidade, carrinho[i].produtos.preco);
    }

    // Escreve o valor total da compra
    fprintf(arquivo, "Total: R$ %.2f\n", total);
    fprintf(arquivo, "******************************\n");
    fclose(arquivo); // Fecha o arquivo

    // Informa o usuário sobre a geração da nota fiscal
    printf("Nota fiscal gerada com sucesso! abra a pasta output de onde esta o arquivo do codigo\n");
}

// Função para exibir o cabeçalho do sistema
void cabecalho()
{
    printf("******************************\n");
    printf("*  Bem vindo ao mercado  *\n");
    printf("******************************\n");
}

// Função para cadastrar produtos no sistema
void cadastrarProduto(Produto produtos[PRODS], int *contador)
{
    char continuar = 's'; // Variável de controle para o loop

    while (continuar == 's' && *contador < PRODS)
    {
        printf("******************************\n");
        printf("*  Cadastro de produto  *\n");
        printf("******************************\n");

        Produto novoProduto; // Cria uma nova instância de Produto
        novoProduto.codigo = *contador + 1; // Atribui o código automaticamente baseado no contador

        printf("Digite o nome do produto (max 30 caracteres):\n");
        getchar(); // Limpa o buffer do teclado para evitar erros
        fgets(novoProduto.nome, NOME, stdin); // Lê o nome do produto

        printf("Digite o preco do produto: ");
        scanf("%f", &novoProduto.preco); // Lê o preço do produto

        produtos[*contador] = novoProduto; // Armazena o novo produto no array
        (*contador)++; // Aumnta o contador de produtos

        // Pergunta se o usuário deseja continuar cadastrando produtos
        if (*contador < PRODS)
        {
            printf("Deseja cadastrar outro produto? (s/n): ");
            scanf(" %c", &continuar);
        }
        else
        {
            printf("Limite de produtos atingido!\n");
        }
    }
}

// Função para listar todos os produtos cadastrados
void listarProdutos(Produto produtos[PRODS], int contador)
{
    if (contador == 0) // Verifica se há produtos cadastrados
    {
        printf("Nenhum produto cadastrado.\n");
    }
    else
    {
        printf("******************************\n");
        printf("*   Lista de Produtos  *\n");
        printf("******************************\n");
        for (int i = 0; i < contador; i++)
        {
            // Exibe o código, nome e preço de cada produto
            printf("Codigo: %d | Produto: %s | Preco: R$ %.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
        }
    }
}

// Função para adicionar produtos ao carrinho
void comprarProdutos(Produto produtos[PRODS], int contador, Carrinho carrinho[PRODS], int *contCarrinho)
{
    if (contador == 0)
    {
        printf("Nenhum produto disponível para compra.\n");
        return;
    }

    int codigo; // Variável para armazenar o código do produto escolhido
    printf("Digite o codigo do produto que deseja adicionar ao carrinho: ");
    scanf("%d", &codigo);

    for (int i = 0; i < contador; i++) // Procura o produto pelo código
    {
        if (produtos[i].codigo == codigo)
        {
            int existe = 0; // Verifica se o produto já está no carrinho
            for (int j = 0; j < *contCarrinho; j++)
            {
                if (carrinho[j].produtos.codigo == codigo)
                {
                    carrinho[j].quantidade++; // aumenta a quantidade se o produto já estiver no carrinho
                    printf("A quantidade do produto foi aumentada.");
                    existe = 1;
                }
            }
            if (!existe) // Se o produto não estiver no carrinho, ele é adicionado
            {
                carrinho[*contCarrinho].produtos = produtos[i]; // Adiciona o produto ao carrinho
                carrinho[*contCarrinho].quantidade = 1; // Define a quantidade como 1
                (*contCarrinho)++; // aumenta o contador do carrinho
                printf("O produto %s foi colocado no carrinho", produtos[i].nome);
            }

            return;
        }
    }

    printf("Produto com codigo %d nao encontrado.\n", codigo); // Caso o código do produto não seja encontrado
}

// Função para visualizar o carrinho de compras
void verCarrinho(Carrinho carrinho[PRODS], int contCarrinho)
{
    if (contCarrinho == 0) // Verifica se há produtos no carrinho
    {
        printf("O carrinho esta vazio.\n");
        return;
    }

    printf("******************************\n");
    printf("* Carrinho de Compras *\n");
    printf("******************************\n");

    // loop com contador para imprimimr carrinho
    for (int i = 0; i < contCarrinho; i++)
    {
        printf("Produto: %s | Quantidade: %d\n", carrinho[i].produtos.nome, carrinho[i].quantidade);
    }
}

// Função para fechar o pedido e gerar a nota fiscal
void fecharPedido(Carrinho carrinho[PRODS], int *contCarrinho)
{
    float total = 0.0; // Inicializa o total da compra

    if (*contCarrinho == 0)
    {
        printf("O carrinho esta vazio");
        return;
    }

    printf("******************************\n");
    printf("* Resumo do Pedido *\n");
    printf("******************************\n");

    // Calcula o final do pedido
    for (int i = 0; i < *contCarrinho; i++)
    {
        float subt = carrinho[i].produtos.preco * carrinho[i].quantidade;
        printf("Produto: %s | Quantidade: %d | Subtotal: %.2f\n", carrinho[i].produtos.nome, carrinho[i].quantidade, subt);
        total += subt;
    }

    printf("Total Final da Compra: %.2f\n", total);

    gerarNotaFiscal(carrinho, *contCarrinho, total); // Gera a nota fiscal

    *contCarrinho = 0; // Zera o carrinho após o fechamento do pedido
}

// Função para remover um produto do carrinho
void removerProdutoCarrinho(Carrinho carrinho[PRODS], int *contCarrinho)
{
    if (*contCarrinho == 0) // Verifica se o carrinho está vazio
    {
        printf("O carrinho está vazio.\n");
        return;
    }

    int codigo; // Variável para armazenar o código do produto a ser removido
    printf("Digite o codigo do produto que deseja remover do carrinho: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *contCarrinho; i++) // Procura o produto no carrinho pelo código
    {
        if (carrinho[i].produtos.codigo == codigo)
        {
            carrinho[i].quantidade--; // Decrementa a quantidade do produto

            if (carrinho[i].quantidade == 0) // Se a quantidade for zero, o produto é removido do carrinho
            {
                for (int j = i; j < *contCarrinho - 1; j++)
                {
                    carrinho[j] = carrinho[j + 1]; // Reorganiza o array removendo o produto
                }
                (*contCarrinho)--; // Decrementa itens no carrinho
            }

            printf("O produto foi removido do carrinho.\n");
            return;
        }
    }

    printf("Produto com codigo %d nao encontrado no carrinho.\n", codigo); // Caso o produto não seja encontrado
}
// Funcao de menu
int menu(Produto produtos[PRODS], int *contador, Carrinho carrinho[PRODS], int *contCarrinho)
{
    int escolha;

    do
    {
        printf("\nO que deseja fazer?\n");
        printf("[1] Cadastrar produto\n");
        printf("[2] Listar Produtos\n");
        printf("[3] Comprar produtos\n");
        printf("[4] Ver carrinho\n");
        printf("[5] Fechar pedido\n");
        printf("[6] Remover produto do carrinho\n");
        printf("[0] Sair\n");

        // Ler a escolha
        scanf("%d", &escolha);

        // Verificar qual foi a escolha e chamar a funcao
        switch (escolha)
        {
        case 1:
            cadastrarProduto(produtos, contador);
            break;
        case 2:
            listarProdutos(produtos, *contador);
            break;
        case 3:
            comprarProdutos(produtos, *contador, carrinho, contCarrinho);
            break;
        case 4:
            verCarrinho(carrinho, *contCarrinho);
            break;
        case 5:
            fecharPedido(carrinho, contCarrinho);
            break;
        case 6:
            removerProdutoCarrinho(carrinho, contCarrinho);
            break;
        case 0:
            printf("aTe logo\n");
            break;
        default:
            printf("Opcao invalida, tente novamente.\n");
        }
    } while (escolha != 0);

    return escolha;
}

int main()
{
    cabecalho();

    Produto produtos[PRODS];
    int contador = 0;
    Carrinho carrinho[PRODS];
    int contCarrinho = 0;

    menu(produtos, &contador, carrinho, &contCarrinho);
    /*01/10/2024 finalizei isso depois de 1 semana, foi terrivel, me senti um jegue, usei ajuda de IA... POREM pra corrijir erros, o codigo foi todo arquitetado por mim 👍
    vou colocar isso no meu github -> @tiagosdbastos.  OBRIGADO WELDES ME SENTI UM BURRO FAZENDO ISSO KKKKKKKKKKKKKK*/
    return 0;
}