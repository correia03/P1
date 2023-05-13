#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct categoria
{
    char nome[100];
    char identificador[1];
} categoria;
//MAXIMO 250 PRODUTOS
typedef struct produto
{
    categoria *categoria;  
    char nome[100];
    char sku[20];
    float preco;
    int quantidade;
    int produto_numero;

} produto;

typedef struct lista
{
    produto *produto;
    struct lista *proximo;
    struct lista *anterior;
} lista;
