#include<stdio.h>
#include<stdlib.h>
#include"../liblab01b.h"

#define T1 "Bolo1 3de 5Chocolate"
#define T2 "bolo de#Chocolate"
#define T3 "Bolo de#@#@#@###Chocolate"
#define T4 "Bolo de chocolate#"
#define T5 "##BOLO de chocolate"
#define T6 "#Bolo de chocolate#"
#define T7 "   ##@#B#@o@#l#o# #d@#e# #c#h#o#c#o#l#a#t#e#@##"

#define SEP "#@"

int main(){
    printf("\n**TEXTOS SELECIONADOS PARA TESTE**\n");
    printf(" T1 .%s.\n T2 .%s.\n T3 .%s.\n T4 .%s.\n T5 .%s.\n T6 .%s.\n T7 .%s.\n", T1, T2, T3, T4, T5, T6, T7);

    printf("\n**TESTES DA FUNÇÃO CLEANER**\n");
    char *clean1 = Cleaner(T1,SEP);
    char *clean2 = Cleaner(T2,SEP);
    char *clean3 = Cleaner(T3,SEP);
    char *clean4 = Cleaner(T4,SEP);
    char *clean5 = Cleaner(T5,SEP);
    char *clean6 = Cleaner(T6,SEP);
    char *clean7 = Cleaner(T7,SEP);


    printf(" T1 .%s.\n T2 .%s.\n T3 .%s.\n T4 .%s.\n T5 .%s.\n T6 .%s.\n T7 .%s.\n",clean1,clean2,clean3,clean4,clean5,clean6,clean7);

    printf("\n**TESTES DA FUNÇÃO CORRECTOR COM AS STRINGS GERADAS EM CLEANER**\n");
    char *correct1 = Corrector(clean1);
    char *correct2 = Corrector(clean2);
    char *correct3 = Corrector(clean3);
    char *correct4 = Corrector(clean4);
    char *correct5 = Corrector(clean5);
    char *correct6 = Corrector(clean6);
    char *correct7 = Corrector(clean7);

    
    printf(" T1 .%s.\n T2 .%s.\n T3 .%s.\n T4 .%s.\n T5 .%s.\n T6 .%s.\n T7 .%s.\n",correct1,correct2,correct3,correct4,correct5,correct6,correct7);

    printf("\nTESTES DA FUNÇÃO SHIFTER**\n");

    char *shift1 = Shifter(T1);
    char *shift2 = Shifter(T2);
    char *shift3 = Shifter(T3);
    char *shift4 = Shifter(T4);
    char *shift5 = Shifter(T5);
    char *shift6 = Shifter(T6);
    char *shift7 = Shifter(T7);


    printf(" T1 .%s.\n T2 .%s.\n T3 .%s.\n T4 .%s.\n T5 .%s.\n T6 .%s.\n T7 .%s.\n",shift1,shift2,shift3,shift4,shift5,shift6,shift7);

    /*LIBERANDO*/
    free(clean1); free(clean2); free(clean3); free(clean4); free(clean5); free(clean6); free(clean7);
    free(correct1); free(correct2); free(correct3); free(correct4); free(correct5); free(correct6); free(correct7);
    free(shift1); free(shift2); free(shift3); free(shift4); free(shift5); free(shift6); free(shift7);
    /****/

    printf("\n**TESTES DA FUNÇÃO DIVIDER2**\n");
    int n, i;

    char **divid1 = Divider2(T1, SEP, &n);
    printf("T1 ");
    for(i=0; i<n; i++) printf("|%s|", divid1[i]);
    printf("\n");

    char **divid2 = Divider2(T2, SEP, &n);
    printf("T2 ");
    for(i=0; i<n; i++) printf("|%s|", divid2[i]);
    printf("\n");

    char **divid3 = Divider2(T3, SEP, &n);
    printf("T3 ");
    for(i=0; i<n; i++) printf("|%s|", divid3[i]);
    printf("\n");

    char **divid4 = Divider2(T4, SEP, &n);
    printf("T4 ");
    for(i=0; i<n; i++) printf("|%s|", divid4[i]);
    printf("\n");

    char **divid5 = Divider2(T5, SEP, &n);
    printf("T5 ");
    for(i=0; i<n; i++) printf("|%s|", divid5[i]);
    printf("\n");

    char **divid6 = Divider2(T6, SEP, &n);
    printf("T6 ");
    for(i=0; i<n; i++) printf("|%s|", divid6[i]);
    printf("\n");

    char **divid7 = Divider2(T7, SEP, &n);
    printf("T7 ");
    for(i=0; i<n; i++) printf("|%s|", divid7[i]);
    printf("\n");


    printf("\n**TESTES DA FUNÇÃO DIVIDERW**\n");

    char **dividw1 = DividerW(T1, &n);
    printf("T1 ");
    for(i=0; i<n; i++) printf("|%s|", dividw1[i]);
    printf("\n");

    char **dividw2 = DividerW(T2, &n);
    printf("T2 ");
    for(i=0; i<n; i++) printf("|%s|", dividw2[i]);
    printf("\n");

    char **dividw3 = DividerW(T3, &n);
    printf("T3 ");
    for(i=0; i<n; i++) printf("|%s|", dividw3[i]);
    printf("\n");

    char **dividw4 = DividerW(T4, &n);
    printf("T4 ");
    for(i=0; i<n; i++) printf("|%s|", dividw4[i]);
    printf("\n");

    char **dividw5 = DividerW(T5, &n);
    printf("T5 ");
    for(i=0; i<n; i++) printf("|%s|", dividw5[i]);
    printf("\n");

    char **dividw6 = DividerW(T6, &n);
    printf("T6 ");
    for(i=0; i<n; i++) printf("|%s|", dividw6[i]);
    printf("\n");

    char **dividw7 = DividerW(T7, &n);
    printf("T7 ");
    for(i=0; i<n; i++) printf("|%s|", dividw7[i]);
    printf("\n");

    return 0;
}
