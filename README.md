# **Sistema de Mercado \- README**

## **1\. Descrição do Projeto**

Este projeto é um sistema de mercado, desenvolvido em linguagem C. O sistema permite que o usuário cadastre produtos, adicione-os ao carrinho, visualize o carrinho, remova itens, feche o pedido e gere uma nota fiscal em formato de texto. A implementação foi realizada com o uso de estruturas (`struct`) para organizar os produtos e o carrinho de compras, além de manipulação de arquivos para geração da nota fiscal..

### **Estruturas Utilizadas:**

* **Produto**: Armazena os dados de um produto (código, nome e preço).  
* **Carrinho**: Armazena os produtos selecionados pelo usuário para compra e a quantidade de cada item.

  ## **2\. Funcionalidades Implementadas:**

1. **Cadastro de Produtos**: Permite ao usuário cadastrar novos produtos com nome e preço. Cada produto recebe um código gerado automaticamente.  
2. **Listagem de Produtos**: Exibe todos os produtos cadastrados com seu código, nome e preço.  
3. **Compra de Produtos**: Permite ao usuário escolher produtos pelo código e adicioná-los ao carrinho. Caso o produto já esteja no carrinho, sua quantidade é incrementada. Cada produto possui um código único, gerado com base no número total de produtos cadastrados. O carrinho é um **array de structs** que armazena os produtos selecionados para compra.  
4. **Visualização do Carrinho**: Exibe os produtos que estão no carrinho, junto com suas quantidades.  
5. **Remoção de Produtos do Carrinho**: O usuário pode remover produtos do carrinho, seja diminuindo a quantidade ou removendo completamente.  
6. **Fechamento de Pedido**: Exibe o resumo da compra com o total a ser pago e gera uma nota fiscal (`nota_fiscal.txt`) que contém todos os produtos comprados, suas quantidades e o valor total.  
7. **Geração de Nota Fiscal**: Ao fechar o pedido, o sistema cria um arquivo de texto com o resumo da compra, armazenando os produtos, preços e quantidades, além do valor total.

   ## **3\. Como o Sistema foi Desenvolvido**

O sistema foi desenvolvido utilizando o Visual Studio Code como ambiente principal de desenvolvimento. Além disso, o ChatGPT foi utilizado como ferramenta de correção e resolução de dúvidas pontuais, todas elas previamente sinalizadas por meio de comentários no código.

Durante o desenvolvimento, o foco foi seguir uma abordagem de aprendizado guiado. Utilizei o ChatGPT no prompt, deixando claro que não queria a geração automática de código, mas sim uma orientação passo a passo. A partir de cada etapa do pensamento, fui desenvolvendo o código de forma gradual, construindo e entendendo a lógica do sistema desde a sua concepção até a implementação final.

Essa abordagem permitiu que o código fosse arquitetado de forma personalizada, com correções pontuais baseadas nas minhas próprias ideias e soluções, garantindo um aprendizado mais profundo..

## **4\. Instruções para Compilar e Executar**

### **Passo 1: Configurar o Ambiente de Desenvolvimento**

Para compilar e executar o código, você precisará de um compilador C, como o **GCC**. No Windows, você pode instalá-lo via **MinGW**. Alternativamente, você pode usar uma IDE como **Visual Studio Code** ou **Code::Blocks**, que já possuem integração com compiladores.

### **Passo 2: Compilar o Código**

1. Abra o **Prompt de Comando** ou **PowerShell**.  
2. Navegue até o diretório onde o arquivo `Mercado.c` está salvo. No seu caso, use o comando:  
     
* `cd C:\Users\Fabiano\Desktop\Tiago\Tiago\C`  
    
3. Compile o código utilizando o seguinte comando:  
     
* `gcc -o mercado Mercado.c`


Este comando gera o executável chamado `mercado.exe`.

### **Passo 3: Executar o Programa**

1. Para rodar o programa, no mesmo terminal, execute:  
     
* `mercado.exe`  
    
2. O programa exibirá um menu com opções. Você pode navegar pelas opções digitando o número correspondente à operação desejada.

