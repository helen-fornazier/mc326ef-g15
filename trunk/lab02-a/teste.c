#include <stdio.h>
#include <stdlib.h>
#include "LibWord.h"
#include "LibFile.h"

#define ARQ "arq.txt"
#define TAM 7
#define NFIELDS 8
#define LRA 6
#define LNOME 24
#define LCIDADE 15
#define LTELRES 8

int main(){
    FILE *f = fopen( ARQ, "r");
    int i = 0, ver = 0;
    char *str = NULL;
    ver = ReadStr( f, &str, TAM);
    for(i=0 ; ; i++){
        
        printf("%s\n", str );
        if(ver<TAM) break;

        ver = ReadStr( f, &str, TAM );
    }
    printf(".%s.\n", FillStr(str, ' ', 8));

   char **regList = InitRegis(NFIELDS);


    return 0;
}
