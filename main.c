#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct sets // Definir Estrutura dos Conjutos
{
    char *num;
    char *nome;
    int ano;
    char *tema;

    struct sets *anterior, *proximo, *ultimo, *primeiro;
} Sets;

typedef struct parts //
{

    char *num;
    char *nome;
    char *classe;
    int stock;

    struct parts *anterior, *proximo, *ultimo, *primeiro;
} Parts;

typedef struct parts_sets // Relação de quantas peças é preciso para fazer um conjunto
{

    char *set_num;
    int quantity;
    char *part_num;

    struct parts_sets *anterior, *proximo, *ultimo, *primeiro;

} PartsSets;

Sets *criarListaSets(char *num, char *nome, int ano, char *tema)
{

    Sets *list = (Sets *)malloc(sizeof(Sets));
    list->num = strdup(num);
    list->nome = strdup(nome);
    list->ano = ano;
    list->tema = strdup(tema);
    list->proximo = NULL;
    list->anterior = NULL;
    list->ultimo = list;
    list->primeiro = list;

    return list;
}

Parts *criarListaParts(char *num, char *nome, char *classe, int stock)
{

    Parts *list = (Parts *)malloc(sizeof(Parts));
    list->num = strdup(num);
    list->nome = strdup(nome);
    list->classe = strdup(classe);
    list->stock = stock;
    list->proximo = NULL;
    list->anterior = NULL;
    list->ultimo = list;
    list->primeiro = list;

    return list;
}

PartsSets *criarListaPartSets(char *set_num, int quantity, char *part_num)
{

    PartsSets *list = (PartsSets *)malloc(sizeof(PartsSets));

    list->set_num = strdup(set_num);
    list->quantity = quantity;
    list->part_num = strdup(part_num);
    list->proximo = NULL;
    list->anterior = NULL;
    list->ultimo = list;
    list->primeiro = list;

    return list;
}

Sets * Inserir_Sets (Sets * list, char *num, char * nome, int ano, char * tema){

    assert(list);

    list->ultimo->proximo = criarListaSets(num,nome,ano,tema);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;

    return list;

}

Parts * Inserir_Parts(Parts * list, char *num, char * nome, char * classe, int stock){

    assert(list);


    list->ultimo->proximo = criarListaParts(num,nome,classe,stock);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;


    return list;
}

PartsSets * Inserir_PartSets(PartsSets * list, char * set_num, int quantity, char *part_num){


    assert(list);

    list->ultimo->proximo = criarListaPartSets(set_num,quantity,part_num);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;


    return list;

}




void listarConjuntoDeDeterminadoTema{

    char tema[500];

    printf("Introduza o tema: ");
    scanf("%s", tema);

    cria
    





}

void listarPecasNumDeterminadoConjunto{


    char idConjunto[500];
    char idPeca[500];



}



Sets *loadS(char *PATH)
{

    Sets *SetsLista;




    if (access(PATH, F_OK) == true)
    {

        FILE *SetsFile = fopen(PATH, "r");
        int contador = 0;

        while (!feof(SetsFile))
        {

            char num[500];
            char nome[500];
            int ano;
            char tema[500];
            char linha[500];

            fgets(linha, 500, SetsFile);

            if (feof(SetsFile))
            {

                break;
            }

            if (contador >= 0)
            {

                sscanf(linha, "%|^\t |\t%|^\t|\t%|^\t|\t%|^t |", num, nome, &ano, tema);
            }

            if (contador == 0)
            {

                SetsLista = criarListaSets(num, nome, ano, tema);

               // printf("Foi criada uma lista. %s - %d - %s", part_num, quantidade, set_num);
            }
            else
            {

                SetsLista = Inserir_Sets(SetsLista, num, nome, ano, tema);
            }

            contador++;
        }
        fclose(SetsFile);
        return SetsLista;
    }
    else

        return NULL;
}









void main(){


mainMenu();

}



void mainMenu(){
int option;

    printf("==== MENU ====\n");
    printf("1 - Conjuntos de um determinado tema.\n");
    printf("2 - As peças de um determinado tipo em determinado conjunto.");
    printf("3 - Quais as pecas necessarias para construir um dado conjunto, indicando os dados de cada peca e
            respetiva quantidade\n");
    printf("4 - O total de pecas em stock\n");
    printf("5 - O total de pecas incluidas num determinado conjunto\n");
    printf("6 - A peca que e utilizada em mais conjuntos diferentes, independentemente da quantidade em cada
           um deles\n");
    printf("7 - Lista dos conjuntos que se conseguem construir com o stock existente\n");
    printf("8 - Sair\n");
    printf("Opcao: ");
    scanf("%d",&option);

    switch option{


        case 1:

        break;

        case 2:

        break;

        case 3:

        break;

        case 4:

        break;

        case 5:

        break;

        case 6:

        break;

        case 7:

        break;

        default:

        exit(0);

        break;

    }

}
