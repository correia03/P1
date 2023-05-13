#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct categoria
{
    char nome[100];
    char identificador[100];
} categoria;
//MAXIMO 250 PRODUTOS
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
    produto *produto;
    struct lista *proximo;
    struct lista *anterior;
} lista;
