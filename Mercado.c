#include <stdio.h>

#define PRODS 50
#define NOME 50

// Estrutura para armazenar um produto
typedef struct
{
    int codigo;
    char nome[NOME];
    float preco;
} Produto;

// Estrutura para armazenar um produto
typedef struct
{
    Produto produtos;
    int quantidade;
} Carrinho;

// Função para exibir o cabeçalho
void cabecalho()
{
    printf("******************************\n");
    printf("*     Bem vindo ao mercado   *\n");
    printf("******************************\n");
}

// Função para cadastrar produtos
void cadastrarProduto(Produto produtos[PRODS], int *contador)
{
    char continuar = 's'; // Para controle do loop

    while (continuar == 's' && *contador < PRODS)
    {
        printf("******************************\n");
        printf("*     Cadastro de produto    *\n");
        printf("******************************\n");

        Produto novoProduto;
        novoProduto.codigo = *contador + 1; // Código único baseado no contador

        printf("Digite o nome do produto (máx 50 caracteres):\n");
        getchar();                            // Limpa o enter anterior
        fgets(novoProduto.nome, NOME, stdin); // Lê o nome do produto

        printf("Digite o preço do produto: ");
        scanf("%f", &novoProduto.preco);

        // Armazena o produto no array
        produtos[*contador] = novoProduto;
        (*contador)++; // Incrementa o contador de produtos

        // Perguntar se o usuário quer cadastrar outro produto
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

// Função para listar produtos
void listarProdutos(Produto produtos[PRODS], int contador)
{
    if (contador == 0)
    {
        printf("Nenhum produto cadastrado.\n");
    }
    else
    {
        printf("******************************\n");
        printf("*       Lista de Produtos     *\n");
        printf("******************************\n");
        for (int i = 0; i < contador; i++)
        {
            printf("Código: %d | Produto: %s | Preço: R$ %.2f\n",
                   produtos[i].codigo, produtos[i].nome, produtos[i].preco);
        }
    }
}

// Função para comprar produtos
void comprarProdutos(Produto produtos[PRODS], int contador)
{
    if (contador == 0)
    {
        printf("Nenhum produto disponível para compra.\n");
        return;
    }

    int codigo;
    printf("Digite o código do produto que deseja adicionar ao carrinho: ");
    scanf("%d", &codigo);

    // Verifica se o código digitado é válido
    for (int i = 0; i < contador; i++)
    {
        if (produtos[i].codigo == codigo)
        {
            printf("Produto %s adicionado ao carrinho.\n", produtos[i].nome);
            return;
        }
    }

    printf("Produto com código %d não encontrado.\n", codigo);
}

// Função para ver o carrinho
void verCarrinho()
{
    printf("Função de ver carrinho\n");

    // travei aqui que saco.
}

// Função para fechar pedido
void fecharPedido()
{
    printf("Função de fechar pedido\n");
}

// Função de menu
int menu(Produto produtos[PRODS], int *contador)
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
        printf("[0] Sair\n");

        // Ler a escolha do usuário
        scanf("%d", &escolha);

        // Verificar qual foi a escolha e chamar a função correspondente
        switch (escolha)
        {
        case 1:
            cadastrarProduto(produtos, contador);
            break;
        case 2:
            listarProdutos(produtos, *contador);
            break;
        case 3:
            comprarProdutos(produtos, *contador);
            break;
        case 4:
            verCarrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 0:
            printf("Até logo!\n");
            break;
        default:
            printf("Opção inválida, tente novamente.\n");
        }
    } while (escolha != 0);

    return escolha;
}

int main()
{
    cabecalho();

    Produto produtos[PRODS]; // Array para armazenar produtos
    int contador = 0;        // Contador de produtos cadastrados

    menu(produtos, &contador); // Chama o menu passando o array de produtos e contador

    return 0;
} 