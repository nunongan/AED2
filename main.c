//==================================================== INCLUDES ===============================================================

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// ============================================================================================================================

int contaPecasStock = 0; // -> Variavel global para a função totalPecasStock();

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
void construirComBaseStockExistente();
void menu();

// =======================================================================================================================

// ==================================================== STRUCTS ==========================================================

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

// =======================================================================================================================

// ===================================================== CRIAR LISTS ======================================================

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

    contaPecasStock += part_stock;

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
// =======================================================================================================================

// ===================================================== PRINT LISTS =====================================================

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

// =======================================================================================================================

// ===================================================== LOAD FILES ======================================================

Sets * setsLista;
Part * partsLista;
PartsSets * partSetLista;



Sets *carregarSets(){

    Sets *setsLista;

        FILE *SetsFicheiro = fopen("sets.tsv", "r");
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

Part *carregarParts(){

    Part *partsLista;

        
        FILE *PartsFicheiro = fopen("parts.tsv", "r");
        int contador = 0;
        
        
        while (!feof(PartsFicheiro))
        {
            char num[500];
            char nome[500];
            char classe[500];
            char stock[500];
            char linha[500];

            fgets(linha, 500, PartsFicheiro);

            if (contador >= 0)
            {
                sscanf(linha, "%[^\t]\t%[^\t]\t%[^\t]\t%s", num, nome, classe, stock);
            }

            if (contador == 0)
            {
                partsLista = criarListaParts(num, nome, classe, atoi(stock));

            }
            else
            {
                partsLista = Inserir_Parts(partsLista, num, nome, classe, atoi(stock));
            }

            contador++;
        }
        fclose(PartsFicheiro);
        return partsLista;
}

PartsSets *carregarPartsSets(){

    PartsSets *PartsSetsLista;

        FILE *PartsSetsFicheiro = fopen("parts_sets.tsv", "r");
        int contador = 0;

        while (!feof(PartsSetsFicheiro))
        {

            char set_num[500];
            char quantidade[500];
            char part_num[500];
            char linha[500];

            fgets(linha, 500, PartsSetsFicheiro);

            if (feof(PartsSetsFicheiro))
            {

                break;
            }

            if (contador >= 0)
            {

                sscanf(linha, "%[^\t]\t%s\t%[^\n]", set_num, quantidade, part_num);
            }

            if (contador == 0)
            {

                PartsSetsLista = criarListaPartSets(set_num, atoi(quantidade), part_num);

               // printf("Foi criada uma lista. %s - %d - %s", part_num, quantidade, set_num);
            }
            else
            {

                PartsSetsLista = Inserir_PartSets(PartsSetsLista, set_num, atoi(quantidade), part_num);
            }

            contador++;
        }
        fclose(PartsSetsFicheiro);
        return PartsSetsLista;
}

// =======================================================================================================================

// ===================================================== FUNCTIONS =======================================================

void listarConjuntoDeDeterminadoTema(){

    getchar();

    char tema[500];

    printf("Introduza o tema do conjunto: ");
    gets(tema);

    Sets *aux =setsLista;


    while(aux){
    
    if(strcmp(aux->set_tema, tema) == 0){

        printf("|| %s || %s || %s ||\n", aux->set_num, aux->set_nome, aux->set_tema);

    }

    // FALTA ORDENAR
    aux= aux->proximo;
    }

    printf("\n===================================================");
    printf("\n\nPressione qualquer tecla para voltar ao menu...\n");
    getchar();
    system("cls || clear");
    menu();

}

void listarPecasNumDeterminadoConjunto(){


    char codConjunto[500];
    char classe[500];

    getchar();

    printf("Introduza o ID do conjunto pretendido:\n");
    printf("Resposta: ");
    gets(codConjunto);


    
    printf("Introduza a classe da peca.\n");
    printf("Resposta: ");
    gets(classe);


    PartsSets *aux = partSetLista;

    while(aux){ 

        if(strcmp(aux->psSet_num, codConjunto) == 0){
        
            Part * aux2 = partsLista;
        
            while(aux2) {
        
                if(strcmp(aux2->part_num, aux->psPart_num) == 0 && strcmp(aux2->part_classe, classe) == 0) {
        
                printf("%s\n", aux->psPart_num);
                
                }
                aux2 = aux2->proximo;
            }

        }
        aux = aux->proximo;
    }


    printf("\n===================================================");
    printf("\n\nPressione qualquer tecla para voltar ao menu...\n");
    getchar();
    system("cls || clear");
    menu();
}

void pecasNecessariasParaConstruir(){ 

    char codConjunto[500];

    getchar();

    printf("Insira o ID do conjunto: ");
    gets(codConjunto);

    Part * aux1 = partsLista; 
    PartsSets * aux2 = partSetLista;
    
    while(aux2){

        if(strcmp(aux2->psSet_num, codConjunto) == 0){

            while (aux1){

                if(strcmp(aux1->part_num, aux2->psPart_num) == 0){


                 printf("\n\nNum: %s || Nome: %s || Classe: %s || Stock: %d || Quantidade p/ construir: %d\n",aux1->part_num, aux1->part_nome,aux1->part_classe,aux1->part_stock,aux2->quantidade);

                }

                aux1 = aux1->proximo;
            }

        }
        aux2 = aux2->proximo;
    }

    printf("\n===================================================");
    printf("\n\nPressione qualquer tecla para voltar ao menu...\n");
    getchar();
    system("cls || clear");
    menu();
}

void totalPecasStock(){

    printf("\n%d e o numero total de pecas em stock.",contaPecasStock);

    printf("\n===================================================");
    printf("\n\nPressione qualquer tecla para voltar ao menu...\n");
    getchar();
    system("cls || clear");
    menu();

}

void pecasIncluidasNumConjunto(){

    char codConjunto[500];

    getchar();

    printf("Introduza o ID do conjunto: ");
    gets(codConjunto);

    PartsSets * aux = partSetLista;
    
    int total = 0;

    while (aux){

        if(strcmp(aux-> psSet_num, codConjunto) == 0){

            total += aux-> quantidade;

        }
        aux = aux->proximo;
    }

    printf("\n\nTotal de pecas: %d",total);

    printf("\n===================================================");
    printf("\n\nPressione qualquer tecla para voltar ao menu...\n");
    getchar();
    system("cls || clear");
    menu();

}

void alterarStockPeca(){

    char codPeca[500];
    int quantidade = 0;

    getchar();

    printf("Digite o ID da peca: ");
    gets(codPeca);

    Part * aux = partsLista;

    printf("\n\nQual e o novo numero de pecas em stock?\n");
    printf("Resposta: ");
    scanf("%d", &quantidade);

    if(strcmp(aux->part_num, codPeca)){

        aux-> part_stock = quantidade;

    }

    printf("\n===================================================");
    printf("Stock Alterado.\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getchar();
    system("cls || clear");
    menu();


}

void removerPecasClasse(){

    char temp_class[500];

    Part * aux = partsLista;

    getchar();

    printf("Introduza a classe da peca que deseja remover: ");
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

    printf("\n===================================================");
    printf("Pecas removidas com sucesso da classe %s.\n",temp_class);
    printf("Pressione qualquer tecla para retornar ao menu.\n");
    getchar();
    menu();

}

void removerSetsTema(){


    char temp_tema[500];

    getchar();

    printf("Introduza o tema do conjunto: ");
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

    printf("\n===================================================");
    printf("Conjunto removido com sucesso do tema.\n");
    printf("Pressione qualquer tecla para retornar ao menu.\n");
    system("pause");
    menu();
}

void adicaoStockIdConjunto(){

    char codConjunto[500];
    int quantidade;

    getchar();

    printf("Introduza o ID do conjunto: ");
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

    printf("\n===================================================");
    printf("Stock Adicionado.\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getchar();
    system("cls || clear");
    menu();

}

void construirComBaseStockExistente(){

    getchar();
    Sets * aux = setsLista->primeiro;
    int contPerSet, contPecasSetStock, contador;
    contador = 0;
    bool verificar_possibilidade = false;

    while(aux)
    {
        PartsSets * aux1 = partSetLista->primeiro;
        contPerSet = 0;
        contPecasSetStock = 0;
        verificar_possibilidade = false;
        
        while(aux1)
        {
            if(verificar_possibilidade == false)
            {
                if(strcmp(aux->set_num, aux1->psSet_num) == 0){

                    Part * aux2 = partsLista->primeiro;
                
                    while(aux2)
                    {
                        if(strcmp(aux1->psPart_num, aux2->part_num) == 0)
                        {
                            contPerSet++;

                            if(aux1->quantidade <= aux2->part_stock)
                            {
                                contPecasSetStock++;
                            }
                            else
                            {
                                verificar_possibilidade = true;
                            }

                        }
                        aux2 = aux2->proximo;
                    } 
                }
            }
            else
            {
                break;
            }
            aux1 = aux1->proximo;    
        }
        if(contPerSet == contPecasSetStock)
        {
            contador++;
            printf("%d Set: %s\n", contador, aux->set_nome);
        }
        aux = aux->proximo;
    }

    printf("\n===================================================");
    printf("Pressione qualquer tecla para voltar ao menu...");
    getchar();
    system("cls || clear");
    menu();
    
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
  scanf("%d", &opcao);


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

        construirComBaseStockExistente();

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
        
        system("cls || clear");        

        removerSetsTema();

        break;

        default:

        system("cls || clear");

        printf("Programa terminado.\n\n");

        exit(0);

        break;
    }
}

// =======================================================================================================================

// ===================================================== MAIN =======================================================

void main(){

    setsLista = carregarSets();
    partsLista = carregarParts();
    partSetLista = carregarPartsSets();
    menu();
    
}

// =======================================================================================================================

