#include <stdio.h>
#include <stdlib.h>
#include "FileMan.c"

#define ARQ "arq.txt"
#define TAM 7

int main(){
    FILE *f = fopen( ARQ, "r");
    int i, ver;
    char *str = ReadStr( f, TAM , &ver);
    for( i=0; ; i++){
        
        printf("%s\n", str );
        if(ver<TAM) break;

        str = ReadStr(f, TAM, &ver);
    }

    return 0;
}
