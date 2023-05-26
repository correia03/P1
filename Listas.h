#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct categoria
{
    char nome[100];
    char identificador[100];
} categoria;
// MAXIMO 250 PRODUTOS
typedef struct produto
{
    categoria *categoria;
    char nome[100];
    float preco;
    char sku[20];
    int quantidade;
    int produto_numero;

} produto;

typedef struct lista
{
    produto produto;
    struct lista *proximo;
    struct lista *anterior;
} lista;
typedef struct clientes
{
    char nome[100];
    int nif;
    char endereco[100];
    int telefone;
    int cliente_numero;

}clientes;

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
// LISTA DE Vendas
typedef struct lista_vendas
{
    vendas vendas;
    struct lista_vendas *proximo;
    struct lista_vendas *anterior;
} lista_vendas;

