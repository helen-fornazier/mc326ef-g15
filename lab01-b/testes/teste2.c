#include<stdio.h>
#include<stdlib.h>
#include"../liblab01b.h"

#define T1 "Bolo1 3de 5Chocolate"
#define T2 "bo478lo de#Cho123colate"
#define T3 "&$)( Bolo de#@#@#@###Chocolate"
#define T4 "Bolo de %$*!&chocolate#"
#define T5 "##BOLO de chocolate*$"
#define T6 "#Bolo $1!de chocolate#"
#define T7 "   ##@#B#@o@#l#o# #d@#e# #c#h#o#c#o#l#a#t#e#@##"

#define SEP "#@"
#define CHAR 'o'
#define WORD "de"

int main(){
    printf("\n**TEXTOS SELECIONADOS PARA TESTE**\n");
    printf(" T1 .%s.\n T2 .%s.\n T3 .%s.\n T4 .%s.\n T5 .%s.\n T6 .%s.\n T7 .%s.\n", T1, T2, T3, T4, T5, T6, T7);

    /***TESTES DA FUNÇÃO WORDCOUNT***/
    printf("\n**TESTES DA FUNÇÃO WORDCOUNT**\n");
    printf("T1 %d\nT2 %d\nT3 %d\nT4 %d\nT5 %d\nT6 %d\nT7 %d\n", WordCount(T1),WordCount(T2),WordCount(T3),WordCount(T4),WordCount(T5),WordCount(T6),WordCount(T7));

    /***TESTES DA FUNÇÃO STRCOUNT***/
    printf("\n**TESTES DA FUNÇÃO STRCOUNT**\n");
    printf("T1 %d\nT2 %d\nT3 %d\nT4 %d\nT5 %d\nT6 %d\nT7 %d\n", StrCount(T1,SEP),StrCount(T2,SEP),StrCount(T3,SEP),StrCount(T4,SEP),StrCount(T5,SEP),StrCount(T6,SEP),StrCount(T7,SEP));

     /***TESTES DA FUNÇÃO COUNTCHRSTR***/
    printf("\n**TESTES DA FUNÇÃO COUNTCHRSTR, CARACTERE ESCOLHIDO '%c' **\n", CHAR);
    printf("T1 %d\nT2 %d\nT3 %d\nT4 %d\nT5 %d\nT6 %d\nT7 %d\n", CountChrStr(T1,CHAR),CountChrStr(T2,CHAR),CountChrStr(T3,CHAR),CountChrStr(T4,CHAR),CountChrStr(T5,CHAR),CountChrStr(T6,CHAR),CountChrStr(T7,CHAR));

    printf("\n**TABELAS PARA TESTE DE DEMAIS FUNÇÕES**\n");

    int i;
    
    int n1;
    char **dividw1 = DividerW(T1, &n1);
    printf("T1 ");
    for(i=0; i<n1; i++) printf("|%s|", dividw1[i]);
    printf("\n");

    int n2;
    char **dividw2 = DividerW(T2, &n2);
    printf("T2 ");
    for(i=0; i<n2; i++) printf("|%s|", dividw2[i]);
    printf("\n");

    int n3;
    char **dividw3 = DividerW(T3, &n3);
    printf("T3 ");
    for(i=0; i<n3; i++) printf("|%s|", dividw3[i]);
    printf("\n");

    int n4;
    char **dividw4 = DividerW(T4, &n4);
    printf("T4 ");
    for(i=0; i<n4; i++) printf("|%s|", dividw4[i]);
    printf("\n");

    int n5;
    char **dividw5 = DividerW(T5, &n5);
    printf("T5 ");
    for(i=0; i<n5; i++) printf("|%s|", dividw5[i]);
    printf("\n");

    int n6;
    char **dividw6 = DividerW(T6, &n6);
    printf("T6 ");
    for(i=0; i<n6; i++) printf("|%s|", dividw6[i]);
    printf("\n");

    int n7;
    char **dividw7 = DividerW(T7, &n7);
    printf("T7 ");
    for(i=0; i<n7; i++) printf("|%s|", dividw7[i]);
    printf("\n");

 /***TESTES DA FUNÇÃO COUNTCHRTABLE***/
    printf("\n**TESTES DA FUNÇÃO COUNTCHRTABLE, CARACTERE ESCOLHIDO '%c' **\n", CHAR);
    printf("T1 %d\nT2 %d\nT3 %d\nT4 %d\nT5 %d\nT6 %d\nT7 %d\n", CountChrTable(dividw1, n1,CHAR),CountChrTable(dividw2, n2,CHAR),CountChrTable(dividw3, n3,CHAR),CountChrTable(dividw4, n4,CHAR),CountChrTable(dividw5, n5,CHAR),CountChrTable(dividw6, n6,CHAR),CountChrTable(dividw7, n7,CHAR));

 /***TESTES DA FUNÇÃO FINDWORD***/
    printf("\n**TESTES DA FUNÇÃO FINDWORD, PALAVRA ESCOLHIDA '%s' **\n", WORD);
    printf("T1 %d\nT2 %d\nT3 %d\nT4 %d\nT5 %d\nT6 %d\nT7 %d\n", FindWord(dividw1, n1,WORD), FindWord(dividw2, n2,WORD), FindWord(dividw3, n3,WORD), FindWord(dividw4, n4,WORD), FindWord(dividw5, n5,WORD), FindWord(dividw6, n6,WORD), FindWord(dividw7, n7,WORD));



    return 0;
}
