#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int nParts = 0;

// ==================================================== STRUCTS ====================================================

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
    int quantidade;
    char *part_num;

    struct parts_sets *anterior, *proximo, *ultimo, *primeiro;

} PartsSets;

// ==================================================================================================================

// ===================================================== LISTS ======================================================

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

    nParts += stock;

    return list;
}

PartsSets *criarListaPartSets(char *set_num, int quantidade, char *part_num)
{

    PartsSets *list = (PartsSets *)malloc(sizeof(PartsSets));

    list->set_num = strdup(set_num);
    list->quantidade = quantidade;
    list->part_num = strdup(part_num);
    list->proximo = NULL;
    list->anterior = NULL;
    list->ultimo = list;
    list->primeiro = list;

    return list;
}

Sets * Inserir_Sets (Sets * list, char *set_num, char * set_nome, int ano, char * tema){

    assert(list);

    list->ultimo->proximo = criarListaSets(set_num,set_nome,ano,tema);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;

    return list;

}

Parts * Inserir_Parts(Parts * list, char *part_num, char * part_nome, char * part_classe, int stock){

    assert(list);


    list->ultimo->proximo = criarListaParts(part_num,part_nome,part_classe,stock);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;

    return list;
}

PartsSets * Inserir_PartSets(PartsSets * list, char * set_num, int quantidade, char * part_num){


    assert(list);

    list->ultimo->proximo = criarListaPartSets(set_num, quantidade ,part_num);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;


    return list;

}

// ==================================================================================================================

Sets * SetLista;
Parts * PartsLista;
PartsSets * partSetLista;

Sets *carregarSets(char *PATH)
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

Sets *carregarParts(char *PATH)
{

    Sets *PartsLista;




    if (access(PATH, F_OK) == true)
    {

        FILE *PartsFicheiro = fopen(PATH, "r");
        int contador = 0;

        while (!feof(PartsFicheiro))
        {

            char num[500];
            char nome[500];
            char classe[500];
            int stock;
            char linha[500];

            fgets(linha, 500, PartsFicheiro);

            if (feof(PartsFicheiro))
            {

                break;
            }

            if (contador >= 0)
            {

                sscanf(linha, "%|^\t |\t%|^\t|\t%|^\t|\t%|^t|%|^\t", num, nome, classe, stock);
            }

            if (contador == 0)
            {

                PartsLista = criarListaParts(num, nome, classe, stock);

               // printf("Foi criada uma lista. %s - %d - %s", part_num, quantidade, set_num); 
            }
            else
            {

                PartsLista = Inserir_Parts(PartsLista, num, nome, classe, stock);
            }

            contador++;
        }
        fclose(PartsFicheiro);
        return PartsFicheiro;
    }
    else

        return NULL;
}

Sets *carregarPartsSets(char *PATH)
{

    Sets *PartsSetsLista;


    if (access(PATH, F_OK) == true)
    {

        FILE *PartsSetsFicheiro = fopen(PATH, "r");
        int contador = 0;

        while (!feof(PartsSetsFicheiro))
        {

            char set_num[500];
            int quantidade;
            char part_num[500];
            char linha[500];

            fgets(linha, 500, PartsSetsFicheiro);

            if (feof(PartsSetsFicheiro))
            {

                break;
            }

            if (contador >= 0)
            {

                sscanf(linha, "%|^\t |\t%|^\t|\t%|^\t|", set_num, quantidade, part_num);
            }

            if (contador == 0)
            {

                PartsSetsLista = criarListaPartSets(set_num, quantidade, part_num);

               // printf("Foi criada uma lista. %s - %d - %s", part_num, quantidade, set_num);
            }
            else
            {

                PartsSetsLista = Inserir_PartSets(PartsSetsLista, num, nome, ano, classe,stock);
            }

            contador++;
        }
        fclose(PartsSetsFicheiro);
        return PartsSetsFicheiro;
    }
    else

        return NULL;
}

void main(){

    setLista = carregarSets("./DataSet/sets.tsv");
    partsLista = carregarParts("./DataSet/parts.tsv");
    partSetLista = carregarPartsSets("./DataSet/parts_sets.tsv");
    printf("hello\n");  

}


void listarConjuntoDeDeterminadoTema(){

    char tema[500];

    printf("Introduza o tema: ");
    gets("%s", tema);

    Sets * aux = setLista;

    while(aux){

    if(strcmp(aux->tema, tema) == 0){

        printf("%s\n", aux->tema);

    } else {

        printf("Nao foram encontrados conjuntos para o tema em questao.");
    }

    // FALTA ORDENAR
    
    }   
}

void listarPecasNumDeterminadoConjunto(){


    char * codConjunto[500];
    char * classe[500];

    printf("Introduza o conjunto pretendido: ");
    gets(codConjunto);
    printf("Introduza o tipo da peca: ");
    gets(classe);

    Parts * aux = partsLista;

    while(aux){

        if(strcmp(aux->set_num, codConjunto) == 0){
        
            Parts * aux2 = partsLista;
        
            while(aux2) {
        
                if(strcmp(aux2->num, aux->part_num) == 0 && strcmp(aux2->classe, classe) == 0) {
        
                printf("%s - %s", aux->part_num);
    
                }
            }
        }
    }
}

void pecasNecessariasParaConstruir(){ 

    char * codConjunto[500];

    printf("Insira o conjunto: ");
    gets(codConjunto);

    Parts * aux1 = partsLista; 
    PartsSets * aux2 = partSetLista;
    
    while(aux2){

        if(strcmp(aux2->set_num, codConjunto) == 0){

            while (aux1){

                if(strcmp(aux1->part_num, aux2->part_num) == 0){


                 printf("Num: %s || Nome: %s || Classe: %s || Stock: %d || Quantidade p/ construir: %d \n\n",aux1->part_num, aux1->part_nome,aux1->classe,aux1->stock,aux2->quantidade);

                }

            }

        }
    }
}

void totalPecasStock(){

    printf("%d",nParts);

}

void pecasIncluidasNumConjunto(){

    char * codConjunto [500];

    printf("Introduza o Conjunto: ");
    gets(codConjunto);

    PartsSets * aux = partSetLista;
    
    int total;

    while (aux){

        if(strcmp(aux-> set_num, codConjunto) == 0){

            total += aux-> quantidade;

        }

    }

    printf("Total de pecas: %d",total);

}

void alterarStockPeca(){

    char codPeca [500];
    int quantidade;

    printf("Digite o codigo da peca: ");
    gets(codPeca);

    Parts * aux = partsLista;

    printf("Qual e o novo numero de pecas em stock?\n");
    printf("Resposta: ");
    scanf("%d", &quantidade);

    if(strcmp(aux->part_num, codPeca)){

        aux-> stock = quantidade;

    }


}

void removerPecasClasse(){

    char * temp_class [500];

    Parts * aux = partsLista;

    printf("Introduza a classe que deseja remover: ");
    gets(temp_class);

    while (aux){

        if(strcmp(aux->classe,temp_class)){

            partsLista * temp = aux;
            aux->anterior->proximo = aux->proximo;
            aux->proximo->anterior = aux->anterior;
            free(temp);
        }
    }

}


void removerSetsTema(){


    char * temp_tema[500];

    printf("Introduza o tema: ");
    gets(temp_tema);

    Sets * aux = SetsLista;
    
    while(aux){


        if(strcmp(aux->tema,temp_tema)){

            SetsLista * temp = aux;
                aux->anterior->proximo = aux-> proximo;
                aux->proximo->anterior = aux-> anterior;
                free(temp);
        }
    }


}

// ==================================================================================================================



/*void mainMenu(){
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
*/
