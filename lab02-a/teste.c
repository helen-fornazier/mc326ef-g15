#include <stdio.h>
#include <stdlib.h>
#include "LibWord.h"
#include "LibFile.h"

#define ARQ "arq.txt"
#define TAM 7
#define NFIELDS 8
#define LRA 7
#define LNOME 24
#define LCIDADE 15
#define LTELRES 9
#define LTELALT 9
#define LSEXO 2
#define LCURSO 2
#define LEND 1

int main(){
    FILE *f = fopen( ARQ, "r");
    int i = 0, ver = 0;
    char *str = NULL;
   // ver = ReadStr( f, &str, TAM);
  /*  for(i=0 ; ; i++){
        
        printf("%s\n", str );
        if(ver<TAM) break;

        ver = ReadStr( f, &str, TAM );
    }
    printf(".%s.\n", FillStr(str, ' ', 8));

   char **regList = InitRegis(NFIELDS);

*/

    int Len[10] = {LRA, LNOME, LCIDADE, LTELRES, LTELALT, LSEXO, LCURSO, LEND};
    char **List = NULL;
    FillFields(f, &List, Len, NFIELDS);
    char **ListCorrect = CorrectorList(List, NFIELDS);

    FILE *fw = fopen("out.txt", "w");
    char *divider = "|"; 
    PrintStrDiv(fw, ListCorrect, NFIELDS, divider);

    SetCursesC(f, '\n', 1);

    FillFields(f, &List, Len, NFIELDS);
    ListCorrect = CorrectorList(List, NFIELDS);
    PrintStrDiv(fw, ListCorrect, NFIELDS, divider);

    return 0;
}
