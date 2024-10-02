#include <stdio.h>
#include <stdlib.h>

#define PRODS 50
#define NOME 30

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

void gerarNotaFiscal(Carrinho carrinho[PRODS], int contCarrinho, float total) // minha cereja do bolo, foi mais facil do eu imaginei fazer isso aqui, so  precisei ver uns 2 videos e uma ajudinha do chat
{
    FILE *arquivo = fopen("nota_fiscal.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo da nota fiscal.\n");
        return;
    }
    fprintf(arquivo, "******************************\n");
    fprintf(arquivo, "*         Nota Fiscal        *\n");
    fprintf(arquivo, "******************************\n");
    fprintf(arquivo, "Produtos:\n");
    for (int i = 0; i < contCarrinho; i++)
    {
        fprintf(arquivo, "Produto: %s | Quantidade: %d | Preço: R$ %.2f\n", carrinho[i].produtos.nome, carrinho[i].quantidade, carrinho[i].produtos.preco);
    }
    fprintf(arquivo, "Total: R$ %.2f\n", total);
    fprintf(arquivo, "******************************\n");
    fclose(arquivo);
    printf("Nota fiscal gerada com sucesso! abra a pasta output de onde esta o arquivo do codigo\n");
}

// Funcao para exibir o cabecalho
void cabecalho()
{
    printf("******************************\n");
    printf("*  Bem vindo ao mercado  *\n");
    printf("******************************\n");
}

// Funcao para cadastrar produtos
void cadastrarProduto(Produto produtos[PRODS], int *contador)
{
    char continuar = 's';

    while (continuar == 's' && *contador < PRODS)
    { // prods é 50 !nao esquecer!
        printf("******************************\n");
        printf("*  Cadastro de produto  *\n");
        printf("******************************\n");

        Produto novoProduto;
        novoProduto.codigo = *contador + 1; // linha baseada no contador, aumenta a cada novo

        printf("Digite o nome do produto (max 50 caracteres):\n");
        getchar();                            // Limpa o enter anterior
        fgets(novoProduto.nome, NOME, stdin); // Lê o nome do produto, stdin entrada padrao -> me compliquei pra entender

        printf("Digite o preco do produto: ");
        scanf("%f", &novoProduto.preco);

        // Armazena o produto no array
        produtos[*contador] = novoProduto; // o array produtos na posição do contador é armazenado, no caso da primeira rodada armazena em produtos[0] e incremente em 1 depois armazrnda na posição produtos [1]/ pq ponteiro é tao chato
        (*contador)++;                     // Incrementa o contador de produtos

        // Perguntar se o usuario quer cadastrar outro produto
        if (*contador < PRODS)
        { // if contador menor que 50
            printf("Deseja cadastrar outro produto? (s/n): ");
            scanf(" %c", &continuar);
        }
        else
        {
            printf("Limite de produtos atingido!\n");
        }
    }
}

// Funcao para listar produtos
void listarProdutos(Produto produtos[PRODS], int contador)
{ // pega o array pridutos, e o valor atual do contador
    if (contador == 0)
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
            printf("Codigo: %d | Produto: %s | Preco: R$ %.2f\n",
                   produtos[i].codigo, produtos[i].nome, produtos[i].preco);
        }
    }
}

// Funcao para comprar produtos
void comprarProdutos(Produto produtos[PRODS], int contador, Carrinho carrinho[PRODS], int *contCarrinho)
{
    if (contador == 0)
    {
        printf("Nenhum produto disponível para compra.\n");
        return;
    }

    int codigo; // nova variavel codigo para comparar com a do contador
    printf("Digite o codigo do produto que deseja adicionar ao carrinho: ");
    scanf("%d", &codigo);

    // Verifica se o codigo digitado é valido
    for (int i = 0; i < contador; i++)
    {
        if (produtos[i].codigo == codigo)
        {
            int existe = 0; // começa em falso para ver c o produto ja existe no carrin
            for (int j = 0; j < *contCarrinho; j++)
            {
                if (carrinho[j].produtos.codigo == codigo)
                {
                    carrinho[j].quantidade++;
                    printf("A quantidade do produto foi incrementada.");
                    existe = 1;
                }
            }
            if (!existe)
            { // se for de existe o produto entra como novo produto no carrinho
                carrinho[*contCarrinho].produtos = produtos[i];
                carrinho[*contCarrinho].quantidade = 1; // dizer que tem 1 agor
                (*contCarrinho)++;                      // para mudar a posicao do vet
                printf("O produto %s foi colocado no carrinho", produtos[i].nome);
            }

            return;
        }
    }

    printf("Produto com codigo %d nao encontrado.\n", codigo);
}

// Funcao para ver o carrinho
void verCarrinho(Carrinho carrinho[PRODS], int contCarrinho)
{
    if (contCarrinho == 0)
    {
        printf("O carrinho esta vazio.\n");
        return;
    }

    printf("******************************\n");
    printf("* Carrinho de Compras *\n");
    printf("******************************\n");

    for (int i = 0; i < contCarrinho; i++)
    {
        printf("Produto: %s | Quantidade: %d\n", carrinho[i].produtos.nome, carrinho[i].quantidade);
    }
}

// Funcao para fechar pedido
void fecharPedido(Carrinho carrinho[PRODS], int *contCarrinho)
{
    float total = 0.0;

    if (*contCarrinho == 0)
    {
        printf("O carrinho esta vazio");
        return;
    }

    printf("******************************\n");
    printf("* Resumo do Pedido *\n");
    printf("******************************\n");

    for (int i = 0; i < *contCarrinho; i++)
    {
        float subt = carrinho[i].produtos.preco * carrinho[i].quantidade;
        printf("Produto: %s | Quantidade: %d | Subtotal: %.2f\n",
               carrinho[i].produtos.nome, carrinho[i].quantidade, subt);

        total += subt;
    }

    printf("Total Final da Compra: %.2f\n", total);

    gerarNotaFiscal(carrinho, *contCarrinho, total); // isso aqui foi genial

    *contCarrinho = 0; // Zera o carrinho
}

// Funcao para remover produto do carrinho
void removerProdutoCarrinho(Carrinho carrinho[PRODS], int *contCarrinho)
{
    if (*contCarrinho == 0)
    {
        printf("O carrinho está vazio.\n");
        return;
    }

    int codigo;
    printf("Digite o codigo do produto que deseja remover do carrinho: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *contCarrinho; i++)
    {
        if (carrinho[i].produtos.codigo == codigo)
        {
            carrinho[i].quantidade--;

            if (carrinho[i].quantidade == 0)
            {
                for (int j = i; j < *contCarrinho - 1; j++) // isso aqui foi chat gpt, nao estava conseguindo
                {
                    carrinho[j] = carrinho[j + 1];
                }
                (*contCarrinho)--; // Decrementa o contador de produtos no carrinho
            }
            printf("Produto removido do carrinho.\n");
            return;
        }
    }

    printf("Produto com codigo %d nao encontrado no carrinho.\n", codigo);
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