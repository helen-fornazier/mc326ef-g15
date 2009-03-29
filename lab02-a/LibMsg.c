#include<stdio.h>
#include<stdlib.h>


char **msg; //where will be placed all messages from the program

/* open the archive where the messages are writen and place them on memory */
/*abre o arquivo de mensagens e coloca na memória
 * se não conseguiu abrir, ou se houve falta de memória, retorna 1. Se não, retorna 0*/
int MakeMsg(char *fname){
    FILE *f;
    char temp[200], temp0='\0';
    int n, i=0, j;

    f=fopen(fname,"r");
    if(f==NULL) {
        printf("*Failure to open the language archive\nThe program will not print messages\n");
        return 1;
    }
    if(f!=NULL){    
        fscanf(f,"%d",&n);
   

        msg=(char**)malloc(sizeof(char*)*n); //global variable
        if(msg==NULL) return 1;

        while(temp0!=EOF){
            if(i>n) break;
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
            msg[i++]=strdup(temp);
            if(temp0==EOF) break;
            fscanf(f,"%c",&temp0);
        }
    }
    return 0;
}


/* print a message */
void Msg(int n){
    if(msg!=NULL) printf("%s\n",msg[n]);
}

