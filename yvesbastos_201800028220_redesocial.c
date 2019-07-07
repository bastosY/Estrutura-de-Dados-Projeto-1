#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa
{

    char nome[51];
    struct pessoa *proximo;
    struct pessoa *anterior;

} pessoa;

typedef struct redeSocial
{

    pessoa *cabeca;

} redeSocial;


redeSocial *init()
{

    redeSocial *lista = malloc(sizeof(redeSocial));
    lista->cabeca = NULL;

    return lista;
}

void ADD(redeSocial *lista, char nome[51],  FILE **arquivo)
{

    pessoa *novaPessoa = malloc(sizeof(pessoa));
    strcpy(novaPessoa->nome, nome);

    if (lista->cabeca == NULL)
    {
        novaPessoa->proximo = novaPessoa;
        novaPessoa->anterior = novaPessoa;
        lista->cabeca = novaPessoa;
        fprintf(*arquivo, "[ OK  ] ADD %s\n", nome);
    }
    else
    {
        pessoa *aux = lista->cabeca;
        while (1)
        {
            if (!(strcmp(aux->nome, nome)))
            {
                fprintf(*arquivo, "[ERROR] ADD %s\n", nome);
                break;
            }
            else
            {
                aux = aux->proximo;
                if (aux == lista->cabeca)
                {
                    novaPessoa->proximo = lista->cabeca;
                    novaPessoa->anterior = lista->cabeca->anterior;

                    lista->cabeca->anterior->proximo = novaPessoa;
                    lista->cabeca->anterior = novaPessoa;
                    fprintf(*arquivo, "[ OK  ] ADD %s\n", nome);
                    break;
                }
            }
        }
    }
}

void REMOVE(redeSocial *lista, char nome[51],  FILE **arquivo)
{
    if (lista->cabeca == NULL)
    {
    }
    
    else
    {

        pessoa *aux = lista->cabeca;
        while (1)
        {
            if (!(strcmp(aux->nome, nome)))
            {
                aux->anterior->proximo = aux->proximo;
                aux->proximo->anterior = aux->anterior;
                aux->proximo = NULL;
                aux->anterior = NULL;
                aux = NULL;
                free(aux);
                fprintf(*arquivo, "[ OK  ] REMOVE %s\n", nome);
                break;
            }
            else
            {
                aux = aux->proximo;
                if (aux == lista->cabeca)
                {
                    fprintf(*arquivo, "[ERROR] REMOVE %s\n", nome);
                    break;
                }
            }
        }
    }
}

void SHOW(redeSocial *lista, char nome[51], FILE **arquivo)
{
    if (lista->cabeca == NULL)
    {
    }
    else
    {
        pessoa *aux = lista->cabeca;
        while (1)
        {
            if (!(strcmp(aux->nome, nome)))
            {
                fprintf(*arquivo, "[ OK  ] %s<-%s->%s\n", aux->anterior->nome, aux->nome, aux->proximo->nome);
                break;
            }
            else
            {
                aux = aux->proximo;
                if (aux == lista->cabeca)
                {
                    fprintf(*arquivo, "[ERROR] ?<-%s->?\n", nome);
                    break;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    redeSocial *lista = init();

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    char frase[51];
    char funcao[51];

    frase[0] = '\0';
    while (fscanf(input, "%50s %50[^\n]s", funcao, frase) != EOF)
   {
       if(!(strcmp("ADD", funcao))){
           ADD(lista ,frase, &output);
       }
       else if(!(strcmp("SHOW", funcao))){
           SHOW(lista, frase, &output);
       }
       else{
           REMOVE(lista ,frase, &output);
       }
   }


    fclose(input);
    fclose(output);

    return 0;
}
