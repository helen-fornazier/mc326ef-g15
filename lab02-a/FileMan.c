#include <stdio.h>
#include <string.h>
#ifndef EOS
#define EOS '\0'
#endif

typedef struct regis{
    char *ra;
    char *nome;
    char *cidade;
    char *telres;
    char *telalt;
    char *sexo;
    char *curso;
    char *fimreg;
} regis_t;

regis_t *NewRegis(char *ra, char *nome, char *cidade, char *telres, char *telalt, char *sexo, char* curso, char* fimreg){
    regis_t *reg = (regis_t *)malloc( sizeof(regis_t) );
    reg->ra = (char *)malloc( sizeof(char)*strlen(ra) );
    reg->nome = (char *)malloc( sizeof(char)*strlen(nome) );
    reg->cidade = (char *)malloc( sizeof(char)*strlen(cidade) );
    reg->telres = (char *)malloc( sizeof(char)*strlen(telres) );
    reg->telalt = (char *)malloc( sizeof(char)*strlen(telalt) );
    reg->sexo = (char *)malloc( sizeof(char)*strlen(sexo) );
    reg->curso = (char *)malloc( sizeof(char)*strlen(curso) );
    reg->fimreg = (char *)malloc( sizeof(char)*strlen(fimreg) );
    
    return reg;
}

regis_t *InitRegis(){
   regis_t *reg = (regis_t *)malloc( sizeof(regis_t) );
   reg->ra = NULL;
   reg->nome = NULL;
   reg->cidade = NULL;
   reg->telres = NULL;
   reg->telalt = NULL;
   reg->sexo = NULL;
   reg->curso = NULL;
   reg->fimreg = NULL;

   return reg; 
}

void PrintRegD(regis_t *reg, char *divider){
    if(reg->ra!=NULL) printf("%s", reg->ra);
    if(divider!=NULL) printf("%s", divider);
    if(reg->nome!=NULL) printf("%s", reg->nome);
    if(divider!=NULL) printf("%s", divider);
    if(reg->cidade!=NULL) printf("%s", reg->cidade);
    if(divider!=NULL) printf("%s", divider);
    if(reg->telres!=NULL) printf("%s", reg->telres);
    if(divider!=NULL) printf("%s", divider);
    if(reg->telalt!=NULL) printf("%s", reg->telalt);
    if(divider!=NULL) printf("%s", divider);
    if(reg->sexo!=NULL) printf("%s", reg->sexo);
    if(divider!=NULL) printf("%s", divider);
    if(reg->curso!=NULL) printf("%s", reg->curso);
    if(divider!=NULL) printf("%s", divider);
    if(reg->fimreg!=NULL) printf("%s", reg->fimreg);
    printf("\n");
}

void FprintRegD( FILE *f, regis_t *reg, char *divider){
    if(reg->ra!=NULL) fprintf(f, "%s", reg->ra);
    if(divider!=NULL) fprintf(f, "%s", divider);
    if(reg->nome!=NULL) fprintf(f, "%s", reg->nome);
    if(divider!=NULL) fprintf(f, "%s", divider);
    if(reg->cidade!=NULL) fprintf(f, "%s", reg->cidade);
    if(divider!=NULL) fprintf(f, "%s", divider);
    if(reg->telres!=NULL) fprintf(f, "%s", reg->telres);
    if(divider!=NULL) fprintf(f, "%s", divider);
    if(reg->telalt!=NULL) fprintf(f, "%s", reg->telalt);
    if(divider!=NULL) fprintf(f, "%s", divider);
    if(reg->sexo!=NULL) fprintf(f, "%s", reg->sexo);
    if(divider!=NULL) fprintf(f, "%s", divider);
    if(reg->curso!=NULL) fprintf(f, "%s", reg->curso);
    if(divider!=NULL) fprintf(f, "%s", divider);
    if(reg->fimreg!=NULL) fprintf(f, "%s", reg->fimreg);
    fprintf(f, "\n");
}

void FprintRegN( FILE *f, char *campo, char *open, char *close){
    if(camp!=NULL)
        fprintf("%s%d%s%s", open, strlen(campo), close, open, close );
}

/*Return a string read in f whith n characters.
 *ver is the number of characters readed
 *
 *Return NULL if failed
 */
char *ReadStr( FILE* f, int n, int *ver ){
    char *str = (char*)malloc( sizeof(char)*( n+1 ) );
    if( str==NULL ) return NULL;

    *ver = fread( (void*)str, sizeof(char), n, f );
    if(*ver == n) str[n] = EOS;

    else{
        str[*ver-1] = EOS;
        if(realloc(str, sizeof(char)*(*ver-1)) == NULL) return NULL;
    }
    return str;
}


char* FillStr(char *str, char c, int len){
    int i;

    if((i = strlen(str) ) < len){
        char *strout = (char *)malloc( sizeof(char)*(len+1));
        strcpy(strout, str);
        for( ; i<len; i++){
            strout[i] = c;
        }
        strout[i] = EOS;
        return strout;
    }

    else return strdup(str);
}
