#include "listas.h"
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
    listar_produtos(iniciolista);
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
// ordem descendente de preço.
void ordenar_preco_desc(lista *iniciolista)
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
// listar produtos pelas categorias existentes percorrer as categorias verificar se a mesma existe depois verificar se tem produtos associados e se sim listar o produto
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
// adicionar cliente
void adicionar_cliente(clientes *cliente, int *num_clientes)
{
    char nome[100];
    int nif;
    char endereco[100];
    int telefone;
    printf("Nome do cliente: ");
    scanf("%s", &nome);
    fflush(stdin);
    printf("NIF do cliente: ");
    scanf("%d", &nif);
    fflush(stdin);
    printf("Endereco do cliente: ");
    scanf("%s", &endereco);
    fflush(stdin);
    printf("Telefone do cliente: ");
    scanf("%d", &telefone);
    fflush(stdin);
    cliente[*num_clientes].cliente_numero = *num_clientes;
    printf("pretende anonimizar os seus dados? (s/n)\n");
    char anonimizar;
    scanf("%c", &anonimizar);
    if (anonimizar == 's')
    {
        strcpy(cliente[*num_clientes].nome, "anonimo");
        cliente[*num_clientes].nif = 0;
        strcpy(cliente[*num_clientes].endereco, "anonimo");
        cliente[*num_clientes].telefone = 0;
    }
    else
    {
        strcpy(cliente[*num_clientes].nome, nome);
        cliente[*num_clientes].nif = nif;
        strcpy(cliente[*num_clientes].endereco, endereco);
        cliente[*num_clientes].telefone = telefone;
    }
    (*num_clientes)++;
}
// listar clientes
void listar_clientes(clientes *cliente, int num_clientes)
{
    for (int i = 0; i < num_clientes; i++)
    {
        printf("\t-----------------------------------------------------------\n");
        printf("Nome do cliente: %s\n", cliente[i].nome);
        printf("NIF do cliente: %d\n", cliente[i].nif);
        printf("Endereco do cliente: %s\n", cliente[i].endereco);
        printf("Telefone do cliente: %d\n", cliente[i].telefone);
        printf("Numero do cliente: %d\n", cliente[i].cliente_numero);
        printf("\t-----------------------------------------------------------\n");
    }
}
// ordenar clientes por ordem alfabetica de nome
void ordenar_clientes(clientes *cliente, int num_clientes)
{
    for (int i = 0; i < num_clientes; i++)
    {
        for (int j = i + 1; j < num_clientes; j++)
        {
            if (stricmp(cliente[i].nome, cliente[j].nome) > 0)
            {
                clientes temp = cliente[i];
                cliente[i] = cliente[j];
                cliente[j] = temp;
            }
        }
    }
}
// procurar e listar um cliente pelo nif
void procurar_cliente(clientes *cliente, int num_clientes)
{
    int nif_cliente;
    printf("NIF do cliente a procurar: ");
    scanf("%d", &nif_cliente);
    for (int i = 0; i < num_clientes; i++)
    {
        if (cliente[i].nif == nif_cliente)
        {
            printf("\t-----------------------------------------------------------\n");
            printf("Nome do cliente: %s\n", cliente[i].nome);
            printf("NIF do cliente: %d\n", cliente[i].nif);
            printf("Endereco do cliente: %s\n", cliente[i].endereco);
            printf("Telefone do cliente: %d\n", cliente[i].telefone);
            printf("Numero do cliente: %d\n", cliente[i].cliente_numero);
            printf("\t-----------------------------------------------------------\n");
            break;
        }
    }
}
// remover cliente
void remover_cliente(clientes *cliente, int *num_clientes)
{
    int numero_cliente;
    printf("Numero do cliente a remover: ");
    scanf("%d", &numero_cliente);
    for (int i = 0; i < *num_clientes; i++)
    {
        if (cliente[i].cliente_numero == numero_cliente)
        {
            for (int j = i; j < *num_clientes - 1; j++)
            {
                cliente[j] = cliente[j + 1];
            }
            (*num_clientes)--;
            break;
        }
    }
}
// alterar cliente (rever ainda nao completo)
void alterar_cliente(clientes *cliente, int num_clientes)
{
    int numero_cliente;
    printf("Numero do cliente a alterar: ");
    scanf("%d", &numero_cliente);
    for (int i = 0; i < num_clientes; i++)
    {
        if (cliente[i].cliente_numero == numero_cliente)
        {
            char nome[100];
            int nif;
            char endereco[100];
            int telefone;
            printf("Nome do cliente: ");
            scanf("%s", &nome);
            fflush(stdin);
            printf("NIF do cliente: ");
            scanf("%d", &nif);
            fflush(stdin);
            printf("Endereco do cliente: ");
            scanf("%s", &endereco);
            fflush(stdin);
            printf("Telefone do cliente: ");
            scanf("%d", &telefone);
            fflush(stdin);
            printf("pretende anonimizar os seus dados? (s/n)\n");
            char anonimizar;
            scanf("%c", &anonimizar);
            if (anonimizar == 's')
            {
                strcpy(cliente[numero_cliente].nome, "anonimo");
                cliente[numero_cliente].nif = 0;
                strcpy(cliente[numero_cliente].endereco, "anonimo");
                cliente[numero_cliente].telefone = 0;
            }
            else
            {
                strcpy(cliente[numero_cliente].nome, nome);
                cliente[numero_cliente].nif = nif;
                strcpy(cliente[numero_cliente].endereco, endereco);
                cliente[numero_cliente].telefone = telefone;
            }
            break;
        }
    }
}
// guardar num ficheiro binario .dat
void guardar_clientes(clientes *cliente, int num_clientes)
{
    FILE *ficheiro;
    ficheiro = fopen("clientes.dat", "wb");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }
    fwrite(&num_clientes, sizeof(int), 1, ficheiro);
    fwrite(cliente, sizeof(clientes), num_clientes, ficheiro);
    fclose(ficheiro);
}
// carregar ficheiro binario .dat
void ler_clientes(clientes *cliente, int *num_clientes)
{
    FILE *ficheiro;
    ficheiro = fopen("clientes.dat", "rb");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }
    fread(num_clientes, sizeof(int), 1, ficheiro);
    fread(cliente, sizeof(clientes), *num_clientes, ficheiro);
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
    clientes cliente;
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
// adicionar venda e remover o stock ao produto que esta na lista dos produtos
void adicionar_venda(lista_vendas **inicio_vendas, lista_vendas **fim_vendas, int *num_vendas, lista **iniciolista, clientes *clientes)
{
    int numero_cliente;
    printf("Numero do cliente: ");
    scanf("%d", &numero_cliente);

    int numero_produto;
    int quantidade;
    Data data;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    data.ano = tm->tm_year + 1900;
    data.mes = tm->tm_mon + 1;
    data.dia = tm->tm_mday;
    data.hora = tm->tm_hour;
    data.minuto = tm->tm_min;

    char adicionar;
    do
    {
        // listar produtos
        listar_produtos(*iniciolista);
        printf("Numero do produto: ");
        scanf("%d", &numero_produto);

        printf("Quantidade: ");
        scanf("%d", &quantidade);

        // Percorrer a lista de produtos para verificar se o número é igual e se a quantidade escolhida é suficiente
        lista *aux = *iniciolista;
        while (aux != NULL)
        {
            if (aux->produto.produto_numero == numero_produto)
            {
                if (aux->produto.quantidade >= quantidade)
                {
                    int quantidade_total = 0;
                    float preco_total = 0;
                    aux->produto.quantidade -= quantidade;
                    quantidade_total += quantidade;
                    preco_total += aux->produto.preco * quantidade;
                    lista_vendas *novo = (lista_vendas *)malloc(sizeof(lista_vendas));
                    novo->vendas.cliente = clientes[numero_cliente];
                    novo->vendas.data = data;
                    novo->vendas.quantidade_total = quantidade_total;
                    novo->vendas.preco_total = preco_total;
                    novo->vendas.id = *num_vendas;
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
                    break;
                }
                else
                {
                    printf("Quantidade insuficiente!\n");
                    break;
                }
            }
            aux = aux->proximo;
        }
        if (aux == NULL)
        {
            printf("Produto nao encontrado!\n");
        }

        printf("Deseja adicionar outra venda? (s/n) ");
        scanf(" %c", &adicionar);
    } while (adicionar == 's');
}
