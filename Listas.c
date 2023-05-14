#include "listas.h"

/*inserir categoria com esta struct typedef struct categoria
{
    char nome[100];
    char identificador[1];
} categoria;
typedef struct produto
{
    categoria *categoria;
    char nome[100];
    char identificador[1];
    float preco;
    int quantidade;

} produto;

typedef struct lista
{
    produto *produto;
    struct lista *prox;
    struct lista *ante;
} lista;*/
// funçao para adicionar categorias e ler o input do utilizador
void adicionar_categoria(categoria *categorias, int *num_categorias)
{
    char nome[100];
    char identificador[100];
    printf("Insira o nome da categoria: ");
    scanf("%s", &nome);
    printf("Insira o identificador da categoria: ");
    scanf("%s", &identificador);
    strcpy(categorias[*num_categorias].nome, nome);
    strcpy(categorias[*num_categorias].identificador, identificador);
    *num_categorias = *num_categorias + 1;
}
// funçao para listar categorias
void listar_categorias(categoria *categorias, int num_categorias)
{
    for (int i = 0; i < num_categorias; i++)
    {
        printf("Nome: %s\n", categorias[i].nome);
        printf("Identificador: %s\n", categorias[i].identificador);
    }
}
// funçao para remover categorias
void remover_categoria(categoria *categorias, int *num_categorias)
{
    // listar categorias
    listar_categorias(categorias, *num_categorias);
    char nome[100];
    printf("Insira o nome da categoria a remover: ");
    scanf("%s", nome);
    for (int i = 0; i < *num_categorias; i++)
    {
        if (strcmp(categorias[i].nome, nome) == 0)
        {
            for (int j = i; j < *num_categorias; j++)
            {
                categorias[j] = categorias[j + 1];
            }
            *num_categorias = *num_categorias - 1;
        }
    }
}
// função para adicionar produtos e ler o input
void adicionar_produto(lista **iniciolista, lista **fimlista, int *total, categoria *categorias, int *num_categorias)
{
    lista *novo = NULL;
    novo = calloc(1, sizeof(lista));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    produto *novo_produto = malloc(sizeof(produto));
    if (novo_produto == NULL)
    {
        printf("Erro ao alocar memória!\n");
        free(novo);
        return;
    }
    
    novo_produto->categoria = malloc(sizeof(categoria));
    if (novo_produto->categoria == NULL)
    {
        printf("Erro ao alocar memória!\n");
        free(novo);
        free(novo_produto);
        return;
    }
    // ler nome do produto
    printf("Insira o nome do produto: ");
    scanf("%s", novo_produto->nome);
    fflush(stdin);
    // ler preço do produto
    printf("Insira o preço do produto: ");
    scanf("%f", &(novo_produto->preco));
    fflush(stdin);
    // ler SKU do produto
    printf("Insira o SKU do produto: ");
    scanf("%s", novo_produto->sku);
    fflush(stdin);
    // ler quantidade em stock do produto
    printf("Insira a quantidade em stock: ");
    scanf("%d", &(novo_produto->quantidade));
    fflush(stdin);
    // ler categoria do produto
    printf("Insira a categoria do produto: ");
    scanf("%s", novo_produto->categoria->nome);
    fflush(stdin);
    // ler identificador da categoria do produto
    printf("Insira o identificador da categoria do produto: ");
    scanf("%s", novo_produto->categoria->identificador);
    fflush(stdin);
    // verificar se a categoria existe
    int existe = 0;
    for (int i = 0; i < *num_categorias; i++)
    {
        if (strcmp(categorias[i].nome, novo_produto->categoria->nome) == 0 && strcmp(categorias[i].identificador, novo_produto->categoria->identificador) == 0)
        {
            existe = 1;
        }
    }
    // se a categoria não existir, adicionar
    if (existe == 0)
    {
        adicionar_categoria(categorias, num_categorias);
    }
    // incrementar o total de produtos
    (*total)++;
    novo_produto->produto_numero = (*total);
    // adicionar o produto à lista
    novo->produto = novo_produto;
    novo->anterior = NULL;
    novo->proximo = NULL;
    // se a lista estiver vazia, adicionar o produto
    if (*iniciolista == NULL)
    {
        *iniciolista = novo;
        *fimlista = novo;
    }
    // se a lista não estiver vazia, adicionar o produto
    else
    {
        novo->anterior = *fimlista;
        (*fimlista)->proximo = novo;
        *fimlista = novo;
    }
}
// função para listar produtos
void listar_produtos(lista *iniciolista)
{
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        printf("Nome: %s\n", atual->produto->nome);
        printf("Preço: %.2f\n", atual->produto->preco);
        printf("SKU: %s\n", atual->produto->sku);
        printf("Quantidade em stock: %d\n", atual->produto->quantidade);
        printf("Categoria: %s\n", atual->produto->categoria->nome);
        printf("Identificador da categoria: %s\n", atual->produto->categoria->identificador);
        printf("Número do produto: %d\n", atual->produto->produto_numero);
        atual = atual->proximo;
    }
}
// função para remover produtos
void remover_produto(lista **iniciolista, lista **fimlista)
{
    // listar produtos
    listar_produtos(*iniciolista);
    int numero;
    printf("Insira o número do produto a remover: ");
    scanf("%d", &numero);
    lista *atual = *iniciolista;
    while (atual != NULL)
    {
        if (atual->produto->produto_numero == numero)
        {
            // se o produto for o primeiro da lista
            if (atual == *iniciolista)
            {
                *iniciolista = atual->proximo;
                (*iniciolista)->anterior = NULL;
            }
            // se o produto for o último da lista
            else if (atual == *fimlista)
            {
                *fimlista = atual->anterior;
                (*fimlista)->proximo = NULL;
            }
            // se o produto estiver no meio da lista
            else
            {
                atual->anterior->proximo = atual->proximo;
                atual->proximo->anterior = atual->anterior;
            }
            free(atual->produto->categoria);
            free(atual->produto);
            free(atual);
            return;
        }
        atual = atual->proximo;
    }
}

// função para listar produtos por ordem alfabética
void ordenar_produtos(lista *iniciolista)
{
    if (iniciolista == NULL || iniciolista->proximo == NULL)
    {
        // Lista vazia ou com apenas um elemento, não há necessidade de ordenação
        return;
    }
    
    int trocou;
    lista *atual;
    lista *ultimo = NULL;
    
    do
    {
        trocou = 0;
        atual = iniciolista;
        
        while (atual->proximo != ultimo)
        {
            produto *p1 = atual->produto;
            produto *p2 = atual->proximo->produto;
            
            if (strcmp(p1->nome, p2->nome) > 0)
            {
                // Trocar os produtos
                produto *temp = atual->produto;
                atual->produto = atual->proximo->produto;
                atual->proximo->produto = temp;
                trocou = 1;
            }
            
            atual = atual->proximo;
        }
        
        ultimo = atual;
    } while (trocou);
}
