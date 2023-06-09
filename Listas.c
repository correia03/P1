#include "listas.h"
/*####################################################################################################################################
#######################################################categorias#####################################################################
######################################################################################################################################*/
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
        printf("\t-----------------------------------------------------------\n");
        printf("Nome: %s\n", categorias[i].nome);
        printf("Identificador: %s\n", categorias[i].identificador);
        printf("\t-----------------------------------------------------------\n");
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
        if (stricmp(categorias[i].nome, nome) == 0)
        {
            for (int j = i; j < *num_categorias; j++)
            {
                categorias[j] = categorias[j + 1];
            }
            *num_categorias = *num_categorias - 1;
        }
    }
}
// atualizar uma categoria e verificar que nenhum produto tem essa categoria
void atualizar_categoria(categoria *categorias, int *num_categorias, lista *iniciolista)
{
    // listar categorias
    listar_categorias(categorias, *num_categorias);
    char nome[100];
    printf("Insira o nome da categoria a atualizar: ");
    scanf("%s", nome);
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (stricmp(atual->produto.categoria->nome, nome) == 0)
        {
            printf("Nao pode atualizar uma categoria que tem produtos associados!\n");
            return;
        }
        atual = atual->proximo;
    }
    for (int i = 0; i < *num_categorias; i++)
    {
        if (stricmp(categorias[i].nome, nome) == 0)
        {
            char novo_nome[100];
            char novo_identificador[100];
            printf("Insira o novo nome da categoria: ");
            scanf("%s", novo_nome);
            printf("Insira o novo identificador da categoria: ");
            scanf("%s", novo_identificador);
            strcpy(categorias[i].nome, novo_nome);
            strcpy(categorias[i].identificador, novo_identificador);
        }
    }
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
/*####################################################################################################################################
#######################################################produtos#####################################################################
######################################################################################################################################*/
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

    produto novo_produto;
    novo_produto.categoria = NULL;
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
        if (stricmp(categorias[i].nome, novo_produto.categoria->nome) == 0 && stricmp(categorias[i].identificador, novo_produto.categoria->identificador) == 0)
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
    novo_produto.produto_numero = (*num_produtos);
    (*num_produtos)++;

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
        printf("\t-----------------------------------------------------------\n");
        printf("Nome: %s\n", atual->produto.nome);
        printf("Preco: %.2f\n", atual->produto.preco);
        printf("SKU: %s\n", atual->produto.sku);
        printf("Quantidade em stock: %d\n", atual->produto.quantidade);
        printf("Categoria: %s\n", atual->produto.categoria->nome);
        printf("Identificador da categoria: %s\n", atual->produto.categoria->identificador);
        printf("Numero do produto: %d\n", atual->produto.produto_numero);
        printf("\t-----------------------------------------------------------\n");
        atual = atual->proximo;
    }
}
// listar produtos com stock
void listar_produtos_com_stock(lista *iniciolista)
{
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.quantidade > 0)
        {
            printf("\t-----------------------------------------------------------\n");
            printf("Nome: %s\n", atual->produto.nome);
            printf("Preco: %.2f\n", atual->produto.preco);
            printf("SKU: %s\n", atual->produto.sku);
            printf("Quantidade em stock: %d\n", atual->produto.quantidade);
            printf("Categoria: %s\n", atual->produto.categoria->nome);
            printf("Identificador da categoria: %s\n", atual->produto.categoria->identificador);
            printf("Numero do produto: %d\n", atual->produto.produto_numero);
            printf("\t-----------------------------------------------------------\n");
        }
        atual = atual->proximo;
    }
}
// função para remover produtos
void remover_produto(lista **iniciolista, lista **fimlista, int *num_produtos)
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
// funçao para retirar o stock de um produto
void retirar_stock(lista *iniciolista)
{
    // listar produtos
    listar_produtos(iniciolista);
    int numero;
    printf("Insira o número do produto a retirar stock: ");
    scanf("%d", &numero);
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.produto_numero == numero)
        {
            atual->produto.quantidade = 0;
            return;
        }
        atual = atual->proximo;
    }
}
// funçao para adicionar o stock de um produto
void adicionar_stock(lista *iniciolista)
{
    // listar produtos
    listar_produtos_com_stock(iniciolista);
    int numero;
    printf("Insira o número do produto a adicionar stock: ");
    scanf("%d", &numero);
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.produto_numero == numero)
        {
            int quantidade;
            printf("Insira a quantidade a adicionar: ");
            scanf("%d", &quantidade);
            atual->produto.quantidade += quantidade;
            return;
        }
        atual = atual->proximo;
    }
}
// funçao para atualizar o produto
void atualizar_produto(lista *iniciolista, categoria *categorias, int *num_categorias)
{
    // listar produtos
    listar_produtos(iniciolista);
    int numero;
    printf("Insira o número do produto a atualizar: ");
    scanf("%d", &numero);
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.produto_numero == numero)
        {
            printf("Insira o nome do produto: ");
            scanf("%s", atual->produto.nome);
            fflush(stdin);
            printf("Insira o preço do produto: ");
            scanf("%f", &(atual->produto.preco));
            fflush(stdin);
            printf("Insira o SKU do produto: ");
            scanf("%s", atual->produto.sku);
            fflush(stdin);
            printf("Insira a quantidade em stock: ");
            scanf("%d", &(atual->produto.quantidade));
            fflush(stdin);
            printf("Insira a categoria do produto: ");
            scanf("%s", atual->produto.categoria->nome);
            fflush(stdin);
            printf("Insira o identificador da categoria do produto: ");
            scanf("%s", atual->produto.categoria->identificador);
            fflush(stdin);
            // verificar se a categoria existe
            int existe = 0;
            for (int i = 0; i < *num_categorias; i++)
            {
                if (stricmp(categorias[i].nome, atual->produto.categoria->nome) == 0 && stricmp(categorias[i].identificador, atual->produto.categoria->identificador) == 0)
                {
                    existe = 1;
                }
            }
            // se a categoria não existir, adicionar
            if (existe == 0)
            {
                printf("nao existe essa categoria");
                return;
            }
            return;
        }
        atual = atual->proximo;
    }
}
// encontrar id do produto
int encontrar_id_produto(lista *iniciolista)
{
    int numero;
    listar_produtos(iniciolista);
    printf("Insira o número do produto a encontrar: ");
    scanf("%d", &numero);
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.produto_numero == numero)
        {
            return atual->produto.produto_numero;
        }
        atual = atual->proximo;
    }
    return -1;
}
// verificicar quantidade
int verificar_quantidade(lista *iniciolista, int quantidade, int idproduto)
{
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.produto_numero == idproduto)
        {
            if (atual->produto.quantidade >= quantidade)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        atual = atual->proximo;
    }
    return 0;
}
// funçao para retirar a quantidade depois da venda
void retirar_quantidade(lista *iniciolista, int quantidade, int idproduto)
{
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.produto_numero == idproduto)
        {
            atual->produto.quantidade -= quantidade;
            return;
        }
        atual = atual->proximo;
    }
}
// funçao para enontrar o preço do produto
float encontrar_preco_produto(lista *iniciolista, int idproduto)
{
    lista *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->produto.produto_numero == idproduto)
        {
            return atual->produto.preco;
        }
        atual = atual->proximo;
    }
    return -1;
}

// ordem descencente de preço
void ordenar_preco_desc(lista **iniciolista, lista **fimlista)
{
    if (*iniciolista == NULL || (*iniciolista)->proximo == NULL)
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
        atual = *iniciolista;

        while (atual->proximo != ultimo)
        {
            produto p1 = atual->produto;
            produto p2 = atual->proximo->produto;

            if (p1.preco < p2.preco)
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

    (*fimlista)->proximo = NULL;
}
// ordenar por ordem alfabetica
void ordenar_produtos_alfabetica(lista **iniciolista, lista **fimlista)
{
    if (*iniciolista == NULL || (*iniciolista)->proximo == NULL)
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
        atual = *iniciolista;

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

    *fimlista = ultimo;
}

// listar produtos pelas categorias existentes
void listar_produtos_categoria(lista *iniciolista, categoria *categorias, int num_categorias)
{
    for (int i = 0; i < num_categorias; i++)
    {
        printf("Categoria: %s", categorias[i].nome);
        lista *atual = iniciolista;
        while (atual != NULL)
        {
            if (stricmp(categorias[i].identificador, atual->produto.categoria->identificador) == 0)
            {
                printf("\t-----------------------------------------------------------\n");
                printf("Nome: %s\n", atual->produto.nome);
                printf("Preco: %.2f\n", atual->produto.preco);
                printf("SKU: %s\n", atual->produto.sku);
                printf("Quantidade em stock: %d\n", atual->produto.quantidade);
                printf("Numero do produto: %d\n", atual->produto.produto_numero);
                printf("\t-----------------------------------------------------------\n");
            }
            atual = atual->proximo;
        }
    }
}

// gerar relatorio produtos
void gerar_relatorio_produtos_categoria(lista *iniciolista, categoria *categorias, int num_categorias)
{
    FILE *ficheiro = fopen("relatorio.txt", "w");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }

    for (int i = 0; i < num_categorias; i++)
    {
        fprintf(ficheiro, "Categoria: %s\n", categorias[i].nome);
        fprintf(ficheiro, "Produtos associados:\n");
        lista *atual = iniciolista;
        while (atual != NULL)
        {
            if (stricmp(categorias[i].identificador, atual->produto.categoria->identificador) == 0)
            {
                fprintf(ficheiro, "\t-----------------------------------------------------------\n");
                fprintf(ficheiro, "Nome: %s\n", atual->produto.nome);
                fprintf(ficheiro, "Preco: %.2f\n", atual->produto.preco);
                fprintf(ficheiro, "SKU: %s\n", atual->produto.sku);
                fprintf(ficheiro, "Quantidade em stock: %d\n", atual->produto.quantidade);
                fprintf(ficheiro, "Numero do produto: %d\n", atual->produto.produto_numero);
                fprintf(ficheiro, "\t-----------------------------------------------------------\n");
            }
            atual = atual->proximo;
        }
    }
    fclose(ficheiro);
}
// ordenar produtos por ids
void ordenar_produtos_ids(lista **iniciolista, lista **fimlista)
{
    if (*iniciolista == NULL || (*iniciolista)->proximo == NULL)
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
        atual = *iniciolista;

        while (atual->proximo != ultimo)
        {
            produto p1 = atual->produto;
            produto p2 = atual->proximo->produto;

            if (p1.produto_numero > p2.produto_numero)
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

    *fimlista = ultimo;
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
        fprintf(ficheiro, "marca/nome:%s preco do produto:%.2f sku:%s quantidade em stock:%d categoria:%s identificador da categoria:%s id do produto:%d\n",
                atual->produto.nome, atual->produto.preco, atual->produto.sku, atual->produto.quantidade,
                atual->produto.categoria->nome, atual->produto.categoria->identificador, atual->produto.produto_numero);

        lista *temp = atual;
        categoria *tempc = atual->produto.categoria;

        atual = atual->proximo;

        free(temp);
        free(tempc);
    }

    fclose(ficheiro);
}

// ler os produtos do ficheiro de texto
void ler_produtos(lista **iniciolista, lista **fimlista, int *num_produtos, categoria *categorias)
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
        p.categoria = calloc(1, sizeof(categoria));
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
            break; // Exit the loop if fscanf fails to read all values
        }
        novo->produto = p;
        printf("\n%i \n", novo->produto.produto_numero);
        (*num_produtos) = novo->produto.produto_numero;
        printf("numero produtos %d\n", *num_produtos);
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
/*
typedef struct clientes
{
    char nome[100];
    int nif;
    char endereco[100];
    int telefone;
    int cliente_numero;

}clientes;
typedef struct lista_clientes
{
    clientes clientes;
    struct lista_clientes *proximo;
    struct lista_clientes *anterior;
} lista_clientes;
*/
// adicionar cliente
/*####################################################################################################################################
#######################################################clientes#######################################################################
######################################################################################################################################*/
void adicionar_cliente(lista_clientes **iniciolistaclientes, lista_clientes **fimlistaclientes, int *numclientes)
{
    char nome[100];
    int nif;
    char endereco[100];
    int telefone;
    lista_clientes *novo = NULL;
    novo = calloc(1, sizeof(lista_clientes));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }
    printf("Nome do cliente: ");
    scanf("%s", nome);
    fflush(stdin);
    printf("NIF do cliente: ");
    scanf("%d", &nif);
    fflush(stdin);
    printf("Endereco do cliente: (neste formato: rua_nomerua) ");
    scanf("%s", endereco);
    fflush(stdin);
    printf("Telefone do cliente: ");
    scanf("%d", &telefone);
    // anonamizar dados caso pedido pelo utilizador
    printf("pretende anonamizar os seus dados? (s/n)");
    char anon;
    fflush(stdin);
    scanf("%c", &anon);
    printf("%c", anon);
    if (anon == 's')
    {
        strcpy(nome, "anonimo");
        nif = 999999999;
        strcpy(endereco, "anonimo");
        telefone = 911111111;
        strcpy(novo->clientes.nome, nome);
        novo->clientes.nif = nif;
        strcpy(novo->clientes.endereco, endereco);
        novo->clientes.telefone = telefone;
    }
    else
    {
        strcpy(novo->clientes.nome, nome);
        novo->clientes.nif = nif;
        strcpy(novo->clientes.endereco, endereco);
        novo->clientes.telefone = telefone;
    }
    novo->clientes.cliente_numero = *numclientes;
    novo->anterior = NULL;
    novo->proximo = NULL;
    if (*iniciolistaclientes == NULL)
    {
        *iniciolistaclientes = novo;
        *fimlistaclientes = novo;
    }
    else
    {
        novo->anterior = *fimlistaclientes;
        (*fimlistaclientes)->proximo = novo;
        *fimlistaclientes = novo;
    }
    numclientes++;
}
// listar clientes
void listar_clientes(lista_clientes *iniciolistaclientes)
{
    lista_clientes *atual = iniciolistaclientes;
    while (atual != NULL)
    {
        printf("Nome do cliente: %s\n", atual->clientes.nome);
        printf("NIF do cliente: %d\n", atual->clientes.nif);
        printf("Endereco do cliente: %s\n", atual->clientes.endereco);
        printf("Telefone do cliente: %d\n", atual->clientes.telefone);
        printf("Numero do cliente: %d\n", atual->clientes.cliente_numero);
        atual = atual->proximo;
    }
}
// funçao para ordenar a lista por ordem afabetica de  nome
void ordenar_clientes_alfabetica(lista_clientes **iniciolistaclientes, lista_clientes **fimlistaclientes)
{
    lista_clientes *atual = *iniciolistaclientes;
    lista_clientes *seguinte = NULL;
    lista_clientes *anterior = NULL;
    lista_clientes *aux = NULL;
    int troca = 0;
    do
    {
        troca = 0;
        atual = *iniciolistaclientes;
        while (atual->proximo != NULL)
        {
            seguinte = atual->proximo;
            if (strcmp(atual->clientes.nome, seguinte->clientes.nome) > 0)
            {
                troca = 1;
                if (anterior != NULL)
                {
                    anterior->proximo = seguinte;
                }
                else
                {
                    *iniciolistaclientes = seguinte;
                }
                atual->proximo = seguinte->proximo;
                seguinte->proximo = atual;
                aux = atual;
                atual = seguinte;
                seguinte = aux;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    } while (troca);
    *fimlistaclientes = atual;
}
// encontrar id do cliente
int encontrar_id_cliente(lista_clientes *iniciolistaclientes)
{
    listar_clientes(iniciolistaclientes);
    int id;
    printf("qual cliente quer comprar: ");
    scanf("%d", &id);
    lista_clientes *atual = iniciolistaclientes;
    while (atual != NULL)
    {
        if (atual->clientes.cliente_numero == id)
        {
            return atual->clientes.cliente_numero;
        }
        atual = atual->proximo;
    }
    return -1;
}
// procurar e listar um cliente pelo nif
void procurar_cliente(lista_clientes *iniciolista)
{
    int nif;
    printf("NIF do cliente: ");
    scanf("%d", &nif);
    lista_clientes *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->clientes.nif == nif)
        {
            printf("Nome do cliente: %s\n", atual->clientes.nome);
            printf("NIF do cliente: %d\n", atual->clientes.nif);
            printf("Endereco do cliente: %s\n", atual->clientes.endereco);
            printf("Telefone do cliente: %d\n", atual->clientes.telefone);
            printf("Numero do cliente: %d\n", atual->clientes.cliente_numero);
            return;
        }
        atual = atual->proximo;
    }
    printf("Cliente nao encontrado!\n");
}
// remover cliente
void remover_cliente(lista_clientes **iniciolista, lista_clientes **fimlista, int *num_clientes)
{
    int nif;
    printf("NIF do cliente: ");
    scanf("%d", &nif);
    lista_clientes *atual = *iniciolista;
    while (atual != NULL)
    {
        printf("%d", atual->clientes.nif);
        if (atual->clientes.nif == nif)
        {
            if (atual->anterior != NULL)
            {
                atual->anterior->proximo = atual->proximo;
            }
            else
            {
                *iniciolista = atual->proximo;
            }
            if (atual->proximo != NULL)
            {
                atual->proximo->anterior = atual->anterior;
            }
            else
            {
                *fimlista = atual->anterior;
            }
            // retirar do numero total de clientes
            (*num_clientes)--;
            free(atual);
            return;
        }
        atual = atual->proximo;
    }
    printf("Cliente nao encontrado!\n");
}
// alterar cliente (rever ainda nao completo)
void atualizar_cliente(lista_clientes *iniciolista)
{
    int nif;
    int telefone;
    char nome[100];
    char endereco[100];
    printf("NIF do cliente: ");
    scanf("%d", &nif);
    lista_clientes *atual = iniciolista;
    while (atual != NULL)
    {
        if (atual->clientes.nif == nif)
        {
            printf("Nome do cliente: ");
            scanf("%s", nome);
            fflush(stdin);
            printf("NIF do cliente: ");
            scanf("%d", &nif);
            fflush(stdin);
            printf("Endereco do cliente: ");
            scanf("%s", endereco);
            fflush(stdin);
            printf("Telefone do cliente: ");
            scanf("%d", &telefone);
            fflush(stdin);
            // anonimizar os dados do utilizador
            char anon;
            printf("Deseja anonimizar os dados do cliente? (s/n)");
            scanf("%c", &anon);
            if (anon == 's')
            {
                strcpy(atual->clientes.nome, "Anonimo");
                atual->clientes.nif = 999999999;
                strcpy(atual->clientes.endereco, "Anonimo");
                atual->clientes.telefone = 911111111;
            }
            else
            {
                strcpy(atual->clientes.nome, nome);
                atual->clientes.nif = nif;
                strcpy(atual->clientes.endereco, endereco);
                atual->clientes.telefone = telefone;
            }
            return;
        }
        atual = atual->proximo;
    }
    printf("Cliente nao encontrado!\n");
}
// guardar num ficheiro binario .dat e liberar memoria alocada de cada cliente
void guardar_clientes(lista_clientes *iniciolista)
{
    FILE *ficheiro;
    ficheiro = fopen("clientes.dat", "wb");
    lista_clientes *atual = iniciolista;
    while (atual != NULL)
    {
        fwrite(&atual->clientes, sizeof(clientes), 1, ficheiro);
        atual = atual->proximo;
    }
    fclose(ficheiro);
    atual = iniciolista;
    while (atual != NULL)
    {
        lista_clientes *aux = atual;
        atual = atual->proximo;
        free(aux);
    }
}

// carregar ficheiro binario .dat
void ler_clientes(lista_clientes **iniciolista, lista_clientes **fimlista, int *num_clientes)
{
    FILE *ficheiro;
    ficheiro = fopen("clientes.dat", "rb");
    if (ficheiro == NULL)
    {
        printf("Ficheiro nao encontrado!\n");
        return;
    }
    clientes cliente;
    while (fread(&cliente, sizeof(clientes), 1, ficheiro))
    {
        lista_clientes *novo = NULL;
        novo = (lista_clientes *)malloc(sizeof(lista_clientes));
        // VERIFICAR SE FOI POSSIVEL ALOCAR MEMORIA
        if (novo == NULL)
        {
            printf("Erro ao alocar memoria!\n");
            return;
        }
        novo->clientes = cliente;
        novo->proximo = NULL;
        novo->anterior = *fimlista;
        if (*fimlista != NULL)
        {
            (*fimlista)->proximo = novo;
        }
        else
        {
            *iniciolista = novo;
        }
        *fimlista = novo;
        (*num_clientes) = (*fimlista)->clientes.cliente_numero;
    }
    fclose(ficheiro);
}
// VENDA
/*
typedef struct {
    int ano;
    short mes;
    short dia;
    short hora;
    short minuto;
} Data;
typedef struct vendas
{
    int idcliente;
    Data data;
    int idproduto;
    float desconto;
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
/*####################################################################################################################################
#################################################################vendas###############################################################
######################################################################################################################################*/
// adicionar venda e remover o stock ao produto que esta na lista dos produtos
void adicionar_venda(lista_vendas **inicio_vendas, lista_vendas **fim_vendas, int *num_vendas, lista *iniciolista, int idproduto, int idcliente, int quantidade, int desconto, float precoproduto)
{
    Data data;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    data.ano = tm->tm_year + 1900;
    data.mes = tm->tm_mon + 1;
    data.dia = tm->tm_mday;
    data.hora = tm->tm_hour;
    data.minuto = tm->tm_min;

    char adicionar; 
    float desconto_aplicado; 
    float precototal;        
    desconto_aplicado  = (float)desconto/100;
    precototal = (precoproduto * quantidade) - (precoproduto * quantidade * desconto_aplicado);
    do
    {
        lista_vendas *novo = NULL;
        novo = (lista_vendas *)malloc(sizeof(lista_vendas));
        // VERIFICAR SE FOI POSSIVEL ALOCAR MEMORIA
        if (novo == NULL)
        {
            printf("Erro ao alocar memoria!\n");
            return;
        }

        novo->vendas.idcliente = idcliente;
        novo->vendas.data = data;
        novo->vendas.idproduto = idproduto;
        novo->vendas.desconto = desconto;
        novo->vendas.quantidade_total = quantidade;
        novo->vendas.preco_total = precototal;
        novo->vendas.id = (*num_vendas);
        novo->proximo = NULL;
        novo->anterior = NULL;
        if (*inicio_vendas == NULL)
        {
            *inicio_vendas = novo;
            *fim_vendas = novo;
        }
        else
        {
            novo->anterior = *fim_vendas;
            (*fim_vendas)->proximo = novo;
            *fim_vendas = novo;
        }
        (*num_vendas)++;
        printf("Deseja adicionar mais vendas? (s/n)");
        scanf("%c", &adicionar);
        fflush(stdin);
    } while (adicionar == 's');
}
