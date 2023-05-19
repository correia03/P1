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
// funçao para adicionar categorias 
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
void adicionar_produto(lista **iniciolista, lista **fimlista, int *num_produtos, categoria *categorias, int *num_categorias)
{
    lista *novo = NULL;
    novo = calloc(1, sizeof(lista));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    produto novo_produto ;

    
    novo_produto.categoria = malloc(sizeof(categoria));
    if (novo_produto.categoria == NULL)
    {
        printf("Erro ao alocar memória!\n");
        free(novo);
        return;
    }
    printf("Insira o nome do produto: ");
    scanf("%s", novo_produto.nome);
    fflush(stdin);
    printf("Insira o preco do produto: ");
    scanf("%f", &(novo_produto.preco));
    fflush(stdin);
    printf("Insira o SKU do produto: ");
    scanf("%s", novo_produto.sku);
    fflush(stdin);
    printf("Insira a quantidade em stock: ");
    scanf("%d", &(novo_produto.quantidade));
    fflush(stdin);
    printf("Insira a categoria do produto: ");
    scanf("%s", novo_produto.categoria->nome);
    fflush(stdin);
    printf("Insira o identificador da categoria do produto: ");
    scanf("%s", novo_produto.categoria->identificador);
    fflush(stdin);
    // verificar se a categoria existe
    int existe = 0;
    for (int i = 0; i < *num_categorias; i++)
    {
        if (stricmp(categorias[i].nome, novo_produto.categoria->nome) == 0 && strcmp(categorias[i].identificador, novo_produto.categoria->identificador) == 0)
        {
            existe = 1;
        }
    }
    // se a categoria não existir, adicionar
    if (existe == 0)
    {
        printf("nao existe essa categoria");
        free(novo);
        return;
    }
    // incrementar o total de produtos
    (*num_produtos)++;
    novo_produto.produto_numero = (*num_produtos);
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
        printf("Nome: %s\n", atual->produto.nome);
        printf("Preco: %.2f\n", atual->produto.preco);
        printf("SKU: %s\n", atual->produto.sku);
        printf("Quantidade em stock: %d\n", atual->produto.quantidade);
        printf("Categoria: %s\n", atual->produto.categoria->nome);
        printf("Identificador da categoria: %s\n", atual->produto.categoria->identificador);
        printf("Numero do produto: %d\n", atual->produto.produto_numero);
        printf("----------------------------------------------------------------------------\n");
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
        if (atual->produto.produto_numero == numero)
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
            free(atual->produto.categoria);
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
            produto p1 = atual->produto;
            produto p2 = atual->proximo->produto;
            
            if (stricmp(p1.nome, p2.nome) > 0)
            {
                // Trocar os produtos
                produto temp = atual->produto;
                atual->produto = atual->proximo->produto;
                atual->proximo->produto = temp;
                trocou = 1;
            }
            
            atual = atual->proximo;
        }
        
        ultimo = atual;
    } while (trocou);
}
// guardar num ficheiro de texto as categorias
void guardar_categorias(categoria *categorias, int num_categorias)
{
    FILE *ficheiro = fopen("categorias.txt", "w");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }
    
    for (int i = 0; i < num_categorias; i++)
    {
        fprintf(ficheiro, "nome da categoria:%s identificador da categoria:%s\n", categorias[i].nome, categorias[i].identificador);
    }
    
    fclose(ficheiro);
}
// ler as categorias do ficheiro de texto
void ler_categorias(categoria *categorias, int *num_categorias)
{
    FILE *ficheiro = fopen("categorias.txt", "r");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }
    
    while (fscanf(ficheiro, "nome da categoria:%s identificador da categoria:%s\n", categorias[*num_categorias].nome, categorias[*num_categorias].identificador) == 2)
    {
        (*num_categorias)++;
    }
    
    fclose(ficheiro);
}
// guardar num ficheiro de texto os produtos
void guardar_produtos(lista *iniciolista)
{
    FILE *ficheiro = fopen("produtos.txt", "w");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }
    
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        fprintf(ficheiro, "marca/nome:%s preco do produto:%.2f sku:%s quantidade em stock:%d categoria:%s identificador da categoria:%s id do produto:%d\n", atual->produto.nome, atual->produto.preco, atual->produto.sku, atual->produto.quantidade, atual->produto.categoria->nome, atual->produto.categoria->identificador, atual->produto.produto_numero);
        atual = atual->proximo;
    }
    
    fclose(ficheiro);
}
// ler os produtos do ficheiro de texto
void ler_produtos(lista **iniciolista, lista **fimlista, int *num_produtos, categoria *categorias, int *num_categorias)
{
    FILE *ficheiro = fopen("produtos.txt", "r");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }
    while (1)
    {
        produto p;
        p.categoria = calloc(1,sizeof(categoria));
        if (p.categoria == NULL)
        {
            printf("Erro ao alocar memória!\n");
            fclose(ficheiro);
            return;
        }
        lista *novo = calloc(1, sizeof(lista));
        if (novo == NULL)
        {
            printf("Erro ao alocar memória!\n");
            fclose(ficheiro);
            return;
        }
        printf("4");
        if (fscanf(ficheiro, "marca/nome:%s preco do produto:%f sku:%s quantidade em stock:%d categoria:%s identificador da categoria:%s id do produto:%d\n",
                   p.nome, &(p.preco), p.sku, &(p.quantidade),
                   p.categoria->nome, p.categoria->identificador, &(p.produto_numero)) != 7)
        {
            free(p.categoria);
            free(novo);
            break;  // Exit the loop if fscanf fails to read all values
        }
        novo->produto = p;

        (*num_produtos)++;
        novo->anterior = NULL;
        novo->proximo = NULL;

        // Add the new product to the list
        if (*iniciolista == NULL)
        {
            *iniciolista = novo;
            *fimlista = novo;
        }
        else
        {
            novo->anterior = *fimlista;
            (*fimlista)->proximo = novo;
            *fimlista = novo;
        }
    }

    fclose(ficheiro);
}
// VENDA
/*
typedef struct vendas
{
    char nome[100];
    int Nif;
    char morada[100];
    char email[100];
    char telefone[100];
    Data data;
    int quantidade_total;
    float preco_total;
    int id;
} vendas;
LISTA DE Vendas
typedef struct lista_vendas
{
    vendas vendas;
    struct lista_vendas *proximo;
    struct lista_vendas *anterior;
} lista_vendas;
*/
// função para adicionar vendas e ler o input
void adicionar_venda(lista_vendas *iniciolista, lista_vendas *fimlista, int *num_vendas, FILE *ficheiro)
{
    //adicionar uma venda de um produto ja existente
    // listar produtos
    listar_produtos(iniciolista);
    int numero;
    printf("Insira o número do produto a vender: ");
    scanf("%d", &numero);
    // adicionar a lista das vendas as informaçoes do vendas
    lista_vendas *novo = NULL;
    novo = calloc(1, sizeof(lista_vendas));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }
    vendas novo_vendas;
    printf("Insira o nome do cliente: ");
    scanf("%s", novo_vendas.nome);
    fflush(stdin);
    printf("Insira o NIF do cliente: ");
    scanf("%d", &(novo_vendas.Nif));
    fflush(stdin);
    printf("Insira a morada do cliente: ");
    scanf("%s", novo_vendas.morada);
    fflush(stdin);
    printf("Insira o email do cliente: ");
    scanf("%s", novo_vendas.email);
    fflush(stdin);
    printf("Insira o telefone do cliente: ");
    scanf("%s", novo_vendas.telefone);
    fflush(stdin);
    printf("Insira a data da venda: ");
    scanf("%d/%d/%d", &(novo_vendas.data.dia), &(novo_vendas.data.mes), &(novo_vendas.data.ano));
    fflush(stdin);
    printf("Insira a quantidade a vender: ");
    scanf("%d", &(novo_vendas.quantidade_total));
    fflush(stdin);
    printf("Insira o preco total: ");
    scanf("%f", &(novo_vendas.preco_total));
    fflush(stdin);
    printf("Insira o id da venda: ");
    scanf("%d", &(novo_vendas.id));
    fflush(stdin);
    // adicionar a lista das vendas as informaçoes do vendas
    novo->vendas = novo_vendas;
    novo->anterior = NULL;
    novo->proximo = NULL;
    // adicionar o novo vendas na lista das vendas
    if (iniciolista == NULL)
    {
        iniciolista = novo;
        fimlista = novo;
    }
    else
    {
        novo->anterior = fimlista;
        fimlista->proximo = novo;
        fimlista = novo;
    }
    // decrementar a quantidade do produto
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.produto_numero == numero)
        {
            atual->produto.quantidade = atual->produto.quantidade - novo_vendas.quantidade_total;
        }
        atual = atual->proximo;
    }
    // guardar no ficheiro de texto
    fprintf(ficheiro, "nome do cliente:%s NIF do cliente:%d morada do cliente:%s email do cliente:%s telefone do cliente:%s data da venda:%d/%d/%d quantidade total:%d preco total:%.2f id da venda:%d\n", novo_vendas.nome, novo_vendas.Nif, novo_vendas.morada, novo_vendas.email, novo_vendas.telefone, novo_vendas.data.dia, novo_vendas.data.mes, novo_vendas.data.ano, novo_vendas.quantidade_total, novo_vendas.preco_total, novo_vendas.id);
}
// função para listar vendas
void listar_vendas(lista_vendas *iniciolista)
{
    lista_vendas *atual = iniciolista;
    while (atual != NULL)
    {
        printf("Nome do cliente: %s\n", atual->vendas.nome);
        printf("NIF do cliente: %d\n", atual->vendas.Nif);
        printf("Morada do cliente: %s\n", atual->vendas.morada);
        printf("Email do cliente: %s\n", atual->vendas.email);
        printf("Telefone do cliente: %s\n", atual->vendas.telefone);
        printf("Data da venda: %d/%d/%d\n", atual->vendas.data.dia, atual->vendas.data.mes, atual->vendas.data.ano);
        printf("Quantidade total: %d\n", atual->vendas.quantidade_total);
        printf("Preco total: %.2f\n", atual->vendas.preco_total);
        printf("Id da venda: %d\n", atual->vendas.id);
        printf("----------------------------------------------------------------------------\n");
        atual = atual->proximo;
    }
}
// função para anomnimizar os dados das pessoa
void anomnimizar_dados(lista_vendas *iniciolista)
{
    lista_vendas *atual = iniciolista;
    while (atual != NULL)
    {
        atual->vendas.Nif = 0;
        atual->vendas.data.dia = 0;
        atual->vendas.data.mes = 0;
        atual->vendas.data.ano = 0;
        atual->vendas.id = 0;
        atual = atual->proximo;
    }
}



