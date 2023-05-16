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
    produto *produto;
    struct lista *proximo;
    struct lista *anterior;
} lista;

//utilizador
typedef struct utilizador
{
    char nome[100];
    char email[100];
    char password[100];
    bool admin;
    int id;
} utilizador;
// LISTA DE UTILIZADORES
typedef struct lista_utilizadores
{
    utilizador *utilizador;
    struct lista_utilizadores *proximo;
    struct lista_utilizadores *anterior;
} lista_utilizadores;

