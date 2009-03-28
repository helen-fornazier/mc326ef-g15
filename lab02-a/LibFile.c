
#ifndef LIB_FILE
#define LIB_FILE

#include <stdio.h>
#include <string.h>
#include "LibFile.h"
#ifndef EOS
#define EOS '\0'
#endif   /*def EOS*/


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

/*Fills the string str with the character c until str to complete len characteres
 *
 * Returns a new string, it does not modify the original one
 * If it failed in the memory allocation,  returns NULL
 * If len will be lesser or equal str, returns a copy of str
 * */
char* FillStr(char *str, char c, int len){
    int i;

    if((i = strlen(str) ) < len){
        char *strout = (char *)malloc( sizeof(char)*(len+1) );
        if (strout == NULL) return NULL;

        strcpy(strout, str);
        for( ; i<len; i++){
            strout[i] = c;
        }

        strout[i] = EOS;
        return strout;
    }

    else return strdup(str);
}

#endif   /*def LIB_FILE*/
