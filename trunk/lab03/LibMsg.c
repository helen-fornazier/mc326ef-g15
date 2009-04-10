#include<stdio.h>
#include<stdlib.h>
#include"LibWord.h"

typedef struct error{
	char **msg;   //where will be placed all messages from the program
	int n;
} EFILE;

//char **msg;


/* open the archive where the messages are writen and place them on memory */
/*abre o arquivo de mensagens e coloca na memória
 * se não conseguiu abrir, ou se houve falta de memória, retorna NULL. Se não, retorna um apontador
 * para EFILE*/

EFILE* MakeMsg(char *fname){
    FILE *f;
    char temp[200], temp0='\0';
    int i=0, j;
	EFILE *e = (EFILE*)malloc( sizeof(EFILE) );
	if(e==NULL)	return NULL;

    f=fopen(fname,"r");
    if(f==NULL) {
        printf("*Failure to open the language archive\nThe program will not print messages\n");
        return NULL;
    }
    if(f!=NULL){    
        fscanf(f,"%d",&(e->n));
   

        (e->msg)=(char**)malloc(sizeof(char*)*(e->n + 1)); 
        if(e->msg==NULL) return NULL;

        while(temp0!=EOF){
            if(i>e->n) break;
            while(temp0!='"'){ 
                fscanf(f,"%c",&temp0);
                if(temp0==EOF) break;
            }
            if(temp0==EOF) break;
            fscanf(f,"%c",&temp[0]);
            for(j=1;temp[j-1]!='"';j++){
                if(temp[j-1]==EOF) break;
                fscanf(f,"%c",&temp[j]);
            }
            temp0=temp[j-1];
            temp[j-1]='\0';
            (e->msg)[i++]=strdup(temp);
            if(temp0==EOF) break;
            fscanf(f,"%c",&temp0);
        }
    }
	fclose(f);
    return e;
}


/* print a message */
void Msg(EFILE* e, int n){
    if(e->msg!=NULL) printf("%s\n",e->msg[n]);
}

void CloseMsg(EFILE *e){
	FreeT(e->msg, e->n + 1);
	free(e);
}
