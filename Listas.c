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
void adicionar_produto(lista **iniciolista,lista **fimlista,int *total, categoria *categoria, int *num_categorias)
{
    lista *novo = NULL;
    novo = calloc(1, sizeof(lista));
    if (novo == NULL)
    {
        printf("erro a alocar a memoria!");
        return 0;
    }
    produto produto;
    //percorrer as categorias e adicionar a categoria ao produto
    for (int i = 0; i < *num_categorias; i++)
    {
        printf("%s\n", categoria[i].nome);
    }
    printf("insira a categoria do produto: \n");
    scanf("%s", &produto.categoria);
    fflush(stdin);
    printf("insira o nome do produto: \n");
    scanf("%s", &produto.nome);
    fflush(stdin);
    printf("insira o preço do produto: \n");
    scanf("%f", &produto.preco);
    fflush(stdin);
    printf("insira o sku do produto: \n");
    scanf("%s", &produto.sku);
    fflush(stdin);
    printf("insira a quantidade em stock: \n");
    scanf("%d",&produto.quantidade);
    (*total)++;
    produto.produto_numero=(*total);
    lista *anterior = NULL;
    lista *proximo = NULL;
    novo->produto = &produto;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (*iniciolista == NULL)
    {
     (*iniciolista) = novo;
      (*fimlista) = novo;
    }
    else
    {
        novo->anterior = (*fimlista);
        (*fimlista)->proximo = novo;
        (*fimlista) = novo;
    }
    return;
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
void listar_produtos(lista *iniciolista)
{
    lista *atual = iniciolista;

    if (atual == NULL)
    {
        printf("A lista de produtos esta vazia.\n");
        return;
    }

    printf("Lista de Produtos:\n");

    while (atual != NULL)
    {
        produto *p = atual->produto;
        printf("Produto Numero: %d\n", p->produto_numero);
        printf("Categoria: %s\n", p->categoria->nome);
        printf("Nome: %s\n", p->nome);
        printf("Preco: %.2f\n", p->preco);
        printf("SKU: %s\n", p->sku);
        printf("Quantidade em Stock: %d\n", p->quantidade);
        printf("\n");

        atual = atual->proximo;
    }
}
