#include<string.h>
#include<stdio.h>
#include"liblab01b.h"


#define ARQUIVO "palavras.txt"
#define PARAMETERS 3   //Número dos parâmetros passados no int main, pode sem 3 ou 2
#define ARGPS 1
#define SEPARATOR "#"
#define NSPEC 3
#define DIVIDER ",;!.?():"
#define LENGUAGE "Eng"

int main(int argc, char* argv[]){
/***************** error message */
    if(argc==3){
        if(MakeMsg(argv[2]))
            MakeMsg(LENGUAGE);
    }    
    else
        MakeMsg(LENGUAGE);
   
    if(argc<2) Msg(0);
    if(argc>3) Msg(1);
    int nimput = 0;
    char **imput = Divider2(argv[ARGPS], SEPARATOR, &nimput);

    if(imput==NULL) Msg(6);
    if(nimput<NSPEC){
        Msg(3);
        return 1;
    }
    if(nimput>NSPEC){
        Msg(4);
        return 1;
    }
    if(strlen(imput[1])!=1) Msg(2);
    
/*****************/

    FILE* f = fopen(ARQUIVO, "w");
    if(f==NULL) Msg(8);
    int nwords, i;
    node* tree = NULL;
    char* shift = Shifter(imput[0]); //transformando a frase recebida em maiuscula
    if(shift==NULL) Msg(6);
    char* shiftC = Shifter(imput[1]); //tranformando a letra recebida em maiúscula
    if(shiftC==NULL) Msg(6);
    char* shiftPal = Shifter(imput[2]); //transformando a palavra em maiúscula
    if(shiftPal==NULL) Msg(6);
    char* clean = Cleaner(imput[0], DIVIDER); //limpando os caracteres indesejaveis
    if(clean==NULL) Msg(6);
    char* correct = Corrector(clean); //Removendo os espaços sobrando
    if(correct==NULL) Msg(6);
    char** table = DividerW(shift, &nwords); //dividindo em uma tabela de palavras
    if(table==NULL) Msg(6);

    for(i=0; i<nwords; i++){
                InsertNode(&tree, table[i]); 
    }

    if(tree==NULL) Msg(9);
    Msg(10);
    printf("=> %d\n", CountChrStr(shift, shiftC[0])); //imprimindo a quantidade de vezes em que c aparece no texto
    Msg(11);
    printf("=> %d\n", FindWord(table, nwords, shiftPal)); //imprimindo a quantidade de vezes em que pal aparece no texto
    Msg(12);
    printf("=> %s\n", clean); //imprimindo a string sem pontuacao na tela
    Msg(13);
    printf("=> %s\n", correct);

    /****finalizando**/
    fclose(f);
    free(clean);
    free(shift);
    FreeT(table,nwords);
    FreeT(imput,nimput);
    FreeTr(tree);
    return 0;
}
