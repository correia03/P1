#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

typedef struct {
    int ano;
    short mes;
    short dia;
} Data;
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
// LISTA DE Vendas
typedef struct lista_vendas
{
    vendas vendas;
    struct lista_vendas *proximo;
    struct lista_vendas *anterior;
} lista_vendas;

