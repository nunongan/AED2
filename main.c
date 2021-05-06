#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int nParts = 0;


//==================================================== INICIALIZAR FUNÇOES ====================================================

void listarConjuntoDeDeterminadoTema();
void listarPecasNumDeterminadoConjunto();
void pecasNecessariasParaConstruir();
void totalPecasStock();
void pecasIncluidasNumConjunto();
void alterarStockPeca();
void removerPecasClasse();
void removerSetsTema();
void adicaoStockIdConjunto();
void construirConstruirStockExistente();
void menu();

// ==================================================== STRUCTS ====================================================

typedef struct sets{
    
    char *set_num;
    char *set_nome;
    int set_ano;
    char * set_tema;

    struct sets *anterior, *proximo, *ultimo, *primeiro;

} Sets;

typedef struct part{

    char *part_num;
    char *part_nome;
    char * part_classe;
    int part_stock;

    struct part *anterior, *proximo, *ultimo, *primeiro;

} Part;

typedef struct parts_sets{

    char * psSet_num;
    int quantidade;
    char * psPart_num;

    struct parts_sets *anterior, *proximo, *ultimo, *primeiro;

} PartsSets;

// ==================================================================================================================

// ===================================================== LISTS ======================================================

Sets * criarListaSets(char * set_num, char * set_nome, int set_ano, char * set_tema){

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

Part * criarListaParts(char *part_num, char * part_nome, char * part_classe, int part_stock){

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

PartsSets *criarListaPartSets(char *psSet_num, int quantidade, char * psPart_num){

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

Sets *carregarSets(char *PATH){

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

                sscanf(linha, "%[^\t]\t%[^\t]\t%d\t%[^\n]", num, nome, &ano, tema);
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

Part *carregarParts(char *PATH){

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

                sscanf(linha, "%[^\t]\t%[^\t]\t%[^\t]\t%d", num, nome, classe, stock);
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

PartsSets *carregarPartsSets(char *PATH){

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

                sscanf(linha, "%[^\t]\t%d\t%[^\n]", set_num, quantidade, part_num);
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

    getchar();
    getchar();

    char * tema;

    printf("Introduza o tema: ");
    gets(tema);

    printf(tema);
    printf(tema);
    Sets *aux =setsLista;
    printf(tema);

    while(aux){

    printf("teste");
    
    if(strcmp(aux->set_tema, tema) == 0){

        printf("%s", aux->set_tema);

    } else {

        printf("\nNao foram encontrados conjuntos para o tema em questao.");
    }

    // FALTA ORDENAR
    aux= aux->proximo;
    }   
}

void listarPecasNumDeterminadoConjunto(){


    char codConjunto[500];
    char classe[500];

    getchar();

    printf("Introduza o conjunto pretendido:\n");
    printf("Resposta: \n");
    gets(codConjunto);

    printf(codConjunto);
    
    printf("Introduza o tipo da peca.\n");
    printf("Resposta: \n");
    gets(classe);

    printf(classe);

    PartsSets *aux = partSetLista;

    while(aux){

        printf("teste");

        if(strcmp(aux->psSet_num, codConjunto) == 0){
        
            Part * aux2 = partsLista;
        
            while(aux2) {
        
                if(strcmp(aux2->part_num, aux->psPart_num) == 0 && strcmp(aux2->part_classe, classe) == 0) {
        
                printf("%s", aux->psPart_num);

                
                }
                aux2 = aux2->proximo;
            }

        }
        aux = aux->proximo;
    }
}

void pecasNecessariasParaConstruir(){ 

    char * codConjunto;

    getchar();

    printf("Insira o conjunto: ");
    gets(codConjunto);

    Part * aux1 = partsLista; 
    PartsSets * aux2 = partSetLista;
    
    while(aux2){

        if(strcmp(aux2->psSet_num, codConjunto) == 0){

            while (aux1){

                if(strcmp(aux1->part_num, aux2->psPart_num) == 0){


                 printf("\n\nNum: %s || Nome: %s || Classe: %s || Stock: %d || Quantidade p/ construir: %d",aux1->part_num, aux1->part_nome,aux1->part_classe,aux1->part_stock,aux2->quantidade);

                }

                aux1 = aux1->proximo;
            }

        }
        aux2 = aux2->proximo;
    }
}

void totalPecasStock(){

    printf("\n%d e o numero total de pecas em stock.",nParts);

}

void pecasIncluidasNumConjunto(){

    char * codConjunto;

    getchar();


    printf("Introduza o Conjunto: ");
    gets(codConjunto);

    PartsSets * aux = partSetLista;
    
    int total;

    while (aux){

        if(strcmp(aux-> psSet_num, codConjunto) == 0){

            total += aux-> quantidade;

        }
        aux = aux->proximo;
    }

    printf("\n\nTotal de pecas: %d",total);

}

void alterarStockPeca(){

    char * codPeca;
    int quantidade;

    getchar();

    printf("Digite o codigo da peca: ");
    gets(codPeca);

    Part * aux = partsLista;

    printf("\n\nQual e o novo numero de pecas em stock?\n");
    printf("Resposta: ");
    scanf("%d", &quantidade);

    if(strcmp(aux->part_num, codPeca)){

        aux-> part_stock = quantidade;

    }


}

void removerPecasClasse(){

    char * temp_class;

    Part * aux = partsLista;

    getchar();

    printf("Introduza a classe que deseja remover: ");
    gets(temp_class);

    while (aux){

        if(strcmp(aux->part_classe,temp_class)){

            Part * temp = aux;
            aux->anterior->proximo = aux->proximo;
            aux->proximo->anterior = aux->anterior;
            free(temp);
        }
        aux = aux->proximo;
    }

}

void removerSetsTema(){


    char * temp_tema;

    getchar();

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
        aux = aux->proximo;
    }
}

void adicaoStockIdConjunto(){

    char * codConjunto;
    int quantidade;

    getchar();

    printf("Introduza o codigo do conjunto: ");
    gets(codConjunto);
    printf("\n\nQual sera o novo stock: ");
    scanf("%d", &quantidade);

    
    Part * aux = partsLista;

    PartsSets * aux1 = partSetLista;

    while(aux1){

        if(strcmp(aux1->psSet_num, codConjunto)== 0){

            while(aux){

                aux->part_stock += quantidade;

             aux = aux ->proximo;   
            }

        }

        aux1 = aux1->proximo;
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

                            printf("\n\n%s",aux->psSet_num);
                            break;
                        }
                        aux2 = aux2->proximo;
                    }
                }
            }
            aux1 = aux1->proximo;
        }
        aux = aux->proximo;
    }
}

void menu(){

    int opcao = 0;

    printf("============================== M E N U ==============================\n\n");

    printf("   1 - Conjuntos de um determinado tema\n");
    printf("   2 - As pecas de um determinado tipo em determinado conjunto\n");
    printf("   3 - Pecas necessarias para construir um conjunto");
    printf("\n     indicando os dados de cada peca e respetiva quantidade\n");
    printf("   4 - Total de pecas em stock\n");
    printf("   5 - O total de pecas incluidas num determinado conjunto\n");
    printf("   6 - A peca que e utilizada em mais conjuntos diferentes,\n"); 
    printf("       independentemente da quantidade em cada um deles\n");
    printf("   7 - A lista dos conjuntos que se conseguem construir com o stock existente\n");
    printf("   8 - Alterar o numero de pecas em stock\n");
    printf("   9 - A adicao de stock com base no identificador de um conjunto\n");
    printf("   10 - Remover todas as pecas de determinada classe\n");
    printf("   11 - Remover todos os sets de determinado tema\n");
    printf("   12 - Sair");
  
  printf("\n\n============================== < 1 / 2 > ==============================\n");

  printf("Opcao: ");
  scanf("%d",&opcao);

 /* while (opcao <= 0 && opcao > 12){

    system("cls || clear");

    printf("============================== M E N U ==============================\n\n");

    printf("   1 - Conjuntos de um determinado tema\n");
    printf("   2 - As pecas de um determinado tipo em determinado conjunto\n");
    printf("   3 - Pecas necessarias para construir um conjunto");
    printf("\n     indicando os dados de cada peca e respetiva quantidade\n");
    printf("   4 - Total de pecas em stock\n");
    printf("   5 - O total de pecas incluidas num determinado conjunto\n");
    printf("   6 - A peca que e utilizada em mais conjuntos diferentes,"); 
    printf("       independentemente da quantidade em cada um deles\n");
    printf("   7 - A lista dos conjuntos que se conseguem construir com o stock existente\n");
    printf("   8 - Alterar o numero de pecas em stock\n");
    printf("   9 - A adicao de stock com base no identificador de um conjunto\n");
    printf("   10 - Remover todas as pecas de determinada classe");
    printf("   11 - Remover todos os sets de determinado tema");
    printf("   12 - Sair");
  
  printf("\n\n============================== < 1 / 2 > ==============================\n");

  printf("Opcao: ");
  scanf("%d",&opcao);

  }*/


    switch (opcao){


        case 1:

        system("cls || clear");

        listarConjuntoDeDeterminadoTema();

        break;


        case 2:

        system("cls || clear");

        listarPecasNumDeterminadoConjunto();

        break;


        case 3:

        system("cls || clear");

        pecasNecessariasParaConstruir();

        break;

        case 4:

        system("cls || clear");

        totalPecasStock();

        break;

        case 5:

        system("cls || clear");

        pecasIncluidasNumConjunto();

        break;

        case 6:

        system("cls || clear");

        // NOT DONE

        break;

        case 7:

        system("cls || clear");

        construirConstruirStockExistente();

        break;

        case 8:

        system("cls || clear");

        alterarStockPeca();

        break;

        case 9:

        system("cls || clear");

        adicaoStockIdConjunto();

        break;

        case 10:

        system("cls || clear");

        removerPecasClasse();

        break;

        case 11:

        removerSetsTema();

        break;

        default:

        system("cls || clear");

        printf("Programa terminado.\n\n");

        exit(0);

        break;
    }
}

void main(){

    int opcao;

    setsLista = carregarSets("./DataSet/sets.tsv");
    partsLista = carregarParts("./DataSet/parts.tsv");
    partSetLista = carregarPartsSets("./DataSet/parts_sets.tsv");
    
    menu();

}
