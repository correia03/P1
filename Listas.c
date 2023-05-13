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
    char identificador[1];
    printf("Insira o nome da categoria: ");
    scanf("%s", nome);
    printf("Insira o identificador da categoria: ");
    scanf("%s", identificador);
    strcpy(categorias[*num_categorias].nome, nome);
    strcpy(categorias[*num_categorias].identificador, identificador);
    *num_categorias = *num_categorias + 1;
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
    printf("insira o sku do produto: \n");
    scanf("%s", &produto.sku);
    fflush(stdin);
    printf("insira o preço do produto: \n");
    scanf("%f", &produto.preco);
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


