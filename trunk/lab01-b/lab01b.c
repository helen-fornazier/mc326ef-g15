#include<string.h>
#include<stdio.h>
#include"liblab01b.h"


#define ARQUIVO "palavras.txt"
#define PARAMETERS 4
#define ERRO1 "too few arguments to function int main\n"
#define ERRO2 "too many arguments to function int main\n"
#define ERRO3 "argument 3 is not a character\n"
#define STRPOSITION argc-3
#define CHRPOSITION argc-2
#define WORDPOSITION argc -1

int main(int argc, char* argv[]){
/***************** error message */
    if(argc < PARAMETERS){
        perror(ERRO1);
        return 1;
    }
    else if(argc > PARAMETERS){
        perror(ERRO2);
        return 1;
    }
    if(strlen(argv[CHRPOSITION])!=1) perror(ERRO3);    
/*****************/

    FILE* f = fopen(ARQUIVO, "w");
    int nwords, i;
    node* tree = NULL;
    char* shift = Shifter(argv[STRPOSITION]); //transformando a frase recebida em maiuscula
    char* clean = Cleaner(argv[STRPOSITION]); //limpando os caracteres indesejaveis
    char** table = Divider(shift, &nwords); //dividindo em uma tabela de palavras

    for(i=0; i<nwords; i++){
        InsertNode(&tree, table[i]); //inserindo as palavras na arvore de organizacao
    }
    PrintNodeF(tree,f); //imprimindo no arquivo
    printf("%s\n", clean); //imprimindo a string sem pontuacao na tela

    /****finalizando***/
    fclose(f);
    free(clean);
    free(shift);
    FreeT(table,nwords);
    FreeTr(tree);
    return 0;
}
