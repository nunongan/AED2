#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int nParts = 0;

// ==================================================== STRUCTS ====================================================

typedef struct sets
{
    
    char *set_num;
    char *set_nome;
    int set_ano;
    char * set_tema;

    struct sets *anterior, *proximo, *ultimo, *primeiro;

} Sets;

typedef struct part //
{

    char *part_num;
    char *part_nome;
    char * part_classe;
    int part_stock;

    struct part *anterior, *proximo, *ultimo, *primeiro;

} Part;

typedef struct parts_sets
{

    char * psSet_num;
    int quantidade;
    char * psPart_num;

    struct parts_sets *anterior, *proximo, *ultimo, *primeiro;

} PartsSets;

// ==================================================================================================================

// ===================================================== LISTS ======================================================

Sets * criarListaSets(char * set_num, char * set_nome, int set_ano, char * set_tema)
{

    Sets * list = (Sets *)malloc(sizeof(Sets));
    list->set_num = strdup(set_num);
    list->set_nome = strdup(set_nome);
    list->set_ano = set_ano;
    list->set_tema = strdup(set_tema);
    list->proximo = NULL;
    list->anterior = NULL;
    list->ultimo = list;
    list->primeiro = list;

    return list;
}

Part * criarListaParts(char *part_num, char * part_nome, char * part_classe, int part_stock)
{

    Part *list = (Part *)malloc(sizeof(Part));
    list->part_num = strdup(part_num);
    list->part_nome = strdup(part_nome);
    list->part_classe = strdup(part_classe);
    list->part_stock = part_stock;
    list->proximo = NULL;
    list->anterior = NULL;
    list->ultimo = list;
    list->primeiro = list;

    nParts += part_stock;

    return list;
}

PartsSets *criarListaPartSets(char *psSet_num, int quantidade, char * psPart_num)
{

    PartsSets *list = (PartsSets *)malloc(sizeof(PartsSets));

    list->psSet_num = strdup(psSet_num);
    list->quantidade = quantidade;
    list->psPart_num = strdup(psPart_num);
    list->proximo = NULL;
    list->anterior = NULL;
    list->ultimo = list;
    list->primeiro = list;

    return list;
}

Sets * Inserir_Sets (Sets * list, char *set_id, char * set_nome, int set_ano, char * set_tema){

    assert(list);

    list->ultimo->proximo = criarListaSets(set_id,set_nome,set_ano,set_tema);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;

    return list;

}

Part * Inserir_Parts(Part * list, char *part_num, char * part_nome, char * part_classe, int part_stock){

    assert(list);


    list->ultimo->proximo = criarListaParts(part_num,part_nome,part_classe,part_stock);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;

    return list;
}

PartsSets * Inserir_PartSets(PartsSets * list, char * psSet_num, int quantidade, char * psPart_num){


    assert(list);

    list->ultimo->proximo = criarListaPartSets(psSet_num, quantidade, psPart_num);
    list->ultimo->proximo->anterior = list->ultimo;
    list->ultimo->proximo->primeiro = list;
    list->ultimo = list->ultimo->proximo;


    return list;

}

// ==================================================================================================================

Sets * setsLista;
Part * partsLista;
PartsSets * partSetLista;

Sets *carregarSets(char *PATH)
{

    Sets *setsLista;




    if (access(PATH, F_OK) == true)
    {

        FILE *SetsFicheiro = fopen(PATH, "r");
        int contador = 0;

        while (!feof(SetsFicheiro))
        {

            char num[500];
            char nome[500];
            int ano;
            char tema[500];
            char linha[500];

            fgets(linha, 500, SetsFicheiro);

            if (feof(SetsFicheiro))
            {

                break;
            }

            if (contador >= 0)
            {

                sscanf(linha, "%|^\t |\t%|^\t|\t%|^\t|\t%|^t |", num, nome, &ano, tema);
            }

            if (contador == 0)
            {

                setsLista = criarListaSets(num, nome, ano, tema);

               // printf("Foi criada uma lista. %s - %d - %s", part_num, quantidade, set_num);
            }
            else
            {

                setsLista = Inserir_Sets(setsLista, num, nome, ano, tema);
            }

            contador++;
        }
        fclose(SetsFicheiro);
        return setsLista;
    }
    else

        return NULL;
}

Part *carregarParts(char *PATH)
{

    Part *partsLista;




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

                partsLista = criarListaParts(num, nome, classe, stock);

               // printf("Foi criada uma lista. %s - %d - %s", part_num, quantidade, set_num); 
            }
            else
            {

                partsLista = Inserir_Parts(partsLista, num, nome, classe, stock);
            }

            contador++;
        }
        fclose(PartsFicheiro);
        return partsLista;
    }
    else

        return NULL;
}

PartsSets *carregarPartsSets(char *PATH)
{

    PartsSets *PartsSetsLista;


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

                PartsSetsLista = Inserir_PartSets(PartsSetsLista, set_num, quantidade, part_num);
            }

            contador++;
        }
        fclose(PartsSetsFicheiro);
        return PartsSetsLista;
    }
    else

        return NULL;
}


void listarConjuntoDeDeterminadoTema(){

    char * tema;

    printf("Introduza o tema: ");
    gets(tema);

    Sets * aux = setsLista;

    while(aux){

    if(strcmp(aux->set_tema, tema) == 0){

        printf("%s\n", aux->set_tema);

    } else {

        printf("Nao foram encontrados conjuntos para o tema em questao.");
    }

    // FALTA ORDENAR
    
    }   
}

void listarPecasNumDeterminadoConjunto(){


    char * codConjunto;
    char * classe;

    printf("Introduza o conjunto pretendido: ");
    gets(codConjunto);
    printf("Introduza o tipo da peca: ");
    gets(classe);

    PartsSets * aux = partSetLista;

    while(aux){

        if(strcmp(aux->psSet_num, codConjunto) == 0){
        
            Part * aux2 = partsLista;
        
            while(aux2) {
        
                if(strcmp(aux2->part_num, aux->psPart_num) == 0 && strcmp(aux2->part_classe, classe) == 0) {
        
                printf("%s", aux->psPart_num);
    
                }
            }
        }
    }
}

void pecasNecessariasParaConstruir(){ 

    char * codConjunto;

    printf("Insira o conjunto: ");
    gets(codConjunto);

    Part * aux1 = partsLista; 
    PartsSets * aux2 = partSetLista;
    
    while(aux2){

        if(strcmp(aux2->psSet_num, codConjunto) == 0){

            while (aux1){

                if(strcmp(aux1->part_num, aux2->psPart_num) == 0){


                 printf("Num: %s || Nome: %s || Classe: %s || Stock: %d || Quantidade p/ construir: %d \n\n",aux1->part_num, aux1->part_nome,aux1->part_classe,aux1->part_stock,aux2->quantidade);

                }

            }

        }
    }
}

void totalPecasStock(){

    printf("%d",nParts);

}

void pecasIncluidasNumConjunto(){

    char * codConjunto;

    printf("Introduza o Conjunto: ");
    gets(codConjunto);

    PartsSets * aux = partSetLista;
    
    int total;

    while (aux){

        if(strcmp(aux-> psSet_num, codConjunto) == 0){

            total += aux-> quantidade;

        }

    }

    printf("Total de pecas: %d",total);

}

void alterarStockPeca(){

    char * codPeca;
    int quantidade;

    printf("Digite o codigo da peca: ");
    gets(codPeca);

    Part * aux = partsLista;

    printf("Qual e o novo numero de pecas em stock?\n");
    printf("Resposta: ");
    scanf("%d", &quantidade);

    if(strcmp(aux->part_num, codPeca)){

        aux-> part_stock = quantidade;

    }


}

void removerPecasClasse(){

    char * temp_class;

    Part * aux = partsLista;
    
    printf("Introduza a classe que deseja remover: ");
    gets(temp_class);

    while (aux){

        if(strcmp(aux->part_classe,temp_class)){

            Part * temp = aux;
            aux->anterior->proximo = aux->proximo;
            aux->proximo->anterior = aux->anterior;
            free(temp);
        }
    }

}

void removerSetsTema(){


    char * temp_tema;

    printf("Introduza o tema: ");
    gets(temp_tema);

    Sets * aux = setsLista;
    
    while(aux){


        if(strcmp(aux->set_tema,temp_tema)){

            Sets * temp = aux;
                aux->anterior->proximo = aux-> proximo;
                aux->proximo->anterior = aux-> anterior;
                free(temp);
        }
    }
}

void AdicaoStockIdConjunto(){

    char * codConjunto;
    int quantidade;

    printf("Introduza o codigo do conjunto: ");
    gets(codConjunto);
    printf("Qual sera o novo stock: ");
    scanf("%d", &quantidade);

    
    Part * aux = partsLista;

    PartsSets * aux1 = partSetLista;

    while(aux1){

        if(strcmp(aux1->psSet_num, codConjunto)== 0){

            while(aux){

                aux->part_stock += quantidade;
                
            }

        }

    }


}

void construirConstruirStockExistente(){

    PartsSets * aux = partSetLista;
    Part * aux1 = partsLista;
    Sets * aux2 = setsLista;

    while (aux){

        aux1 = aux1->primeiro;

        while(aux1){

            if(strcmp(aux->psPart_num,aux1->part_num)){

                if(aux1->part_stock >= aux->quantidade){
                    
                    while(aux2){

                        if(strcmp(aux->psSet_num,aux2->set_num)){

                            printf("%s",aux->psSet_num);
                            break;
                        }
                    }
                }
            }
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

void main(){

    setsLista = carregarSets("./DataSet/sets.tsv");
    partsLista = carregarParts("./DataSet/parts.tsv");
    partSetLista = carregarPartsSets("./DataSet/parts_sets.tsv");
    printf("hello\n");  

}
