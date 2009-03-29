
#ifndef LIB_FILE
#define LIB_FILE

#include <stdio.h>
#include <string.h>
#include "LibFile.h"
#ifndef EOS
#define EOS '\0'
#endif   /*def EOS*/


/*Matrix to keep the registers*/
typedef char*** regis_t;

int Print(FILE *f, char *c){
    /*place error*/
    return fwrite(&c,sizeof(char),strlen(c),f);
}

int PrintRegister(FILE *f, char **reg, int camp){
    int n=0, i;
    char vet[100], vet2[100];
    for(i=0;9<camp;i++){
        sprintf(vet,"%d>%s",(camp+1),reg[camp]);
        sprintf(vet2,"<%d><%s",(int)strlen(vet),vet);
        n+=Print(f,vet);
    }
    return n;
}

int PrintAll(FILE *f, int type, char ***reg, int treg, char end, int camp){
    int n=0,i;
    char vet[3];
    sprintf(vet,"%c\n",end);
    for(i=0;i<treg;i++){
        if(type) n+=PrintRegister(f,reg[i],camp);
        else n+=PrintStrDiv(f,reg[i],camp,"|");
        n+=Print(f,vet);
    }
    return n;
}

/*Initializes and returns a list with nfield NULL fields
 *
 * Receives the number of fields
 * 
 * Returns a (char **) type with all fields iqual to NULL
 * or Return NULL if failed
 * */
char **InitRegis(int nfield){
    char **regList = (char **)malloc(sizeof(char *) * nfield);
    if(regList == NULL) return NULL;

    int i;
    for(i=0; i<nfield; i++){
        regList[i] = NULL;
    }

    return regList;
}


/*Description: reads len characteres in FILE f and puts in the string str
 *
 * The char **str is the address of the string str
 *
 * This function already allocate memory for str
 *
 *Returns the number of characteres readed
 *Returns 0 if does not readed something or memory error
 **/
int ReadStr( FILE* f, char **str, int len){
    *str = (char*)malloc( sizeof(char)*( len+1 ) );
    if( *str==NULL ) return 0;
    
    int ver = 0;
    ver = fread( (void*)*str, sizeof(char), len, f );
    if(ver == len) *str[len] = EOS;

    else{
        (*str)[ver-1] = EOS;  //ver-1 pois se ele não leu o que mandei ler,  quer dizer que ele encontrou o EOF, e se encontrou o EOF, antes dele possui o \n
        realloc(*str, sizeof(char)*(ver-1));
        if(*str == NULL) return 0;
    }

    return ver;
}

/*FALTA COLOCAR UNS AVISOS*/
/*
 * f is a FILE the will be readed.
 * fieldList is a (char **) type that will be filled whith strings.
 * lenList[i] indicate the number of characteres that will be readed from
 * f and put in fieldList[i]
 *
 * Return the number of all characteres readed
 * If does not readed the right number of characteres in f, returns 0 
 * */
int FillFields(FILE *f, char ***fieldList, int *lenList, int nfields){
    (*fieldList) = InitRegis(nfields);
    if(*fieldList == NULL) return 0;

    int i=0, sum=0, ver=0;
    for(i=0; i<nfields; i++){
        ver = ReadStr(f, &((*fieldList)[i]), lenList[i]);
        
        if( ver<lenList[i] ) return 0;
        sum+= ver;
    }

    return sum;
}

/*Prints in the FILE f the list of string (strList with lengh len) separate by the character c
 *
 * Returns the number of characteres writed in f*/
int PrintStrDiv(FILE *f, char **strList, int len, char *divider){
    int i=0, som=0;


    for(i=0; i<len-1; i++){
        som+= Print(f, strList[i]);
        som+= Print(f, divider);
    }

    som+= Print(f, strList[i]);

    return som;
}



#endif   /*def LIB_FILE*/
