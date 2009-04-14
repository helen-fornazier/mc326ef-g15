#include <stdio.h>
#include <string.h>
#include "LibFile.h"
#include "LibWord.h"

#ifndef EOS
#define EOS '\0'
#endif   /*def EOS*/

#define PRINT_TAM 1
#define PRINT_DIV 0

//typedef char*** REGIS;

void MakeData(FILE *f, int ***tab, int *nfields){
	fscanf(f,"%d",nfields);
	*tab=(int**)malloc(sizeof(int*)*2);
	(*tab)[0]=(int*)malloc(sizeof(int)*(*nfields));
	(*tab)[1]=(int*)malloc(sizeof(int)*(*nfields));

	int i;
	for(i=0;i<*nfields;i++)
		fscanf(f,"%d",&((*tab)[0][i]));
	for(i=0;i<*nfields;i++)
		fscanf(f,"%d",&((*tab)[1][i]));
}

int Print(FILE *f, char *c){
    return fwrite(c,sizeof(char),strlen(c),f);
}

/*Mudei para imprimir o campo zero -- voltei*/
int PrintRegister(FILE *f, char **reg, int camp){
    int n=0, i;
    char vet[100], vet2[100];
    for(i=0;i<camp;i++){
        if(reg[i][0]!='\0'){
	   	   sprintf(vet,"%d>%s",(i+1),reg[i]);     
           sprintf(vet2,"<%d><%s",(int)strlen(vet),vet);
           n+=Print(f,vet2);
        }
    }
    return n;
}

int PrintAll(FILE *f, int type, REGIS reg, int treg, int camp){
    int n=0,i;
    char vet[3];
   // sprintf(vet,"%c\n",end);
    for(i=0;i<treg;i++){

        sprintf(vet, "%s\n", reg[i][camp-1]);
        if(type) n+=PrintRegister(f,reg[i],camp-1);
        else n+=PrintStrDiv(f,reg[i],camp-1,"|");
        n+=Print(f,vet);
    }
    return n;
}



int SetCursesC(FILE *f, char c, int n){
    if(feof(f))  return 0;
    char ch;

    if(fread((void*)(&ch), sizeof(char), 1, f ) != 1)    return 0;

    while(ch != c){
        if(feof(f))  return 0;
        if(fread((void*)(&ch), sizeof(char), 1, f ) != 1)    return 0;
    }

    if(fseek(f, (sizeof(char)*n) -1, SEEK_CUR) != 0) return 0;
    if(feof(f)) return 0;
    return 1;
}



/*Read of FILE f qnt registers with nfields of lengh iqual to len and put it REGIS reg
 * sum is increased with*/
int ReadRegFix(FILE *f, REGIS *reg, int *len, int nfields, int qnt){
    (*reg) = (REGIS)malloc( sizeof(char **)*qnt );
    if((*reg) == NULL)       return 0;

    int i=0;

    char **correct = NULL;
    for(i=0; i<qnt; i++){
        
        if(!FillFields( f, &(*reg)[i], len, nfields ))   return i;

        correct = CorrectorList( (*reg)[i], nfields );
        if(correct == NULL) return 0;     //imprimir erro

        free( (*reg)[i] );
        (*reg)[i] = correct;

        if(!SetCursesC( f, '\n', 1 ))   break;    //EOF   so break

    }
    
    
    return i;
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

	if(len == 0){   //não tenho certeza se ele devolve cooloca null sem isso
		*str = NULL;
		return 0;
	}
    
    int ver = 0;
    ver = fread( (void*)*str, sizeof(char), len, f );
    if(ver == len) (*str)[len] = EOS;

    else{
        (*str)[ver-1] = EOS;  //ver-1 pois se ele não leu o que mandei ler,  quer dizer que ele encontrou o EOF, e se encontrou o EOF, antes dele possui o \n
        (*str) = realloc(*str, sizeof(char)*(ver));
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
        
        if( ver<lenList[i] ){
			FreeT((*fieldList), i+1);
			return 0;
		}

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

/*Description: Return a struct DATASTYLE alreary initialized*/
DATASTYLE *InitDatastyle(){
	DATASTYLE *data = (DATASTYLE*) malloc( sizeof(DATASTYLE) );
	if( data==NULL )	return NULL;
	

	data->nfield = 0;
	data->efield = NULL;
	data->ob = NULL;
	data->fieldname = NULL;
	
	return data;

}

/*Description: Ready the configuration file and fills 
 * a struct DATASTYLE and returns it
 *
 * fields readed:	
 * 		int nfields
 * 		int nfield;			
 *		int *efield;		
 *		int *ob;			
 *		char *fieldname;		
 *	*/
DATASTYLE* FillData(FILE* f){
	int i, j;

	if(f==NULL)		return NULL;

	DATASTYLE *data = InitDatastyle();
	if(data == NULL)	return NULL;

	int **table;
	MakeData(f, &table, &(data->nfield));
	
	data->efield = table[0];
	data->ob = table[1];
	free(table);

	data->fieldname = (char**) malloc (sizeof(char*) * data->nfield );
	if(data->fieldname == NULL ){
		free(data->efield);
		free(data->ob);
		return NULL;
	}

	/*ARRUMAR ESTE PEDAÇO*/
	
	for(i=0; i<data->nfield; i++){
		data->fieldname[i] = (char*) malloc( sizeof(char) * 200 );
	}

	for(i=0; i<data->nfield; i++){
			SetCursesC(f, '"', 1);	
		for(j=0; ; j++){

			fscanf(f, "%c", &(data->fieldname[i][j]));

			if(data->fieldname[i][j] == '"' || data->fieldname[i][j] == EOF ){
				data->fieldname[i][j] = EOS;
				break;
			}
		}
	}

	return data;
}


/*Description: Free all data of a struct DATASTYLE data*/
void CloseDatastyle(DATASTYLE *data){
	free(data->efield);
	free(data->ob);
	FreeT(data->fieldname, data->nfield);
	free(data);
}


/*Read a fixed register, aplies Corrector and set the
 * cursor f after \n
 *
 * f is the file tha will read
 * str is a table that will contain the data of one register
 * str doesn't need to be inicialized
 * len is the vector of lenght of each field
 * nfield is the number of fields
 *
 * return 0 if faild or finded EOS
 * */
int ReadRegFix3(FILE *f, char ***str, int *len, int nfields){
	if(!ReadRegFix2(f, str, len, nfields))	return 0;

	char **correct = NULL;
    correct = CorrectorList( (*str), nfields );
	
	FreeT((*str), nfields);

	(*str) = correct;

	return 1;
}

/*Read a fixed register without aplies Corrector and set the
 * cursor f after \n
 *
 * f is the file tha will read
 * str is a table that will contain the data of one register
 * str doesn't need to be inicialized
 * len is the vector of lenght of each field
 * nfield is the number of fields
 *
 * return 0 if faild or finded EOS
 * */
int ReadRegFix2(FILE *f, char ***str, int *len, int nfields){
		char **string = NULL;

		if(!FillFields( f, &string, len, nfields ))   return 0;

        if(!SetCursesC( f, '\n', 1 ))   return 0;    //EOF  
	
        (*str) = string;

		return 1;
}


/*Description: Reads a file f whth variable format and puts
 * in str
 *
 * =>f is the file thar will be readed
 * =>***str is the addres of char **str, doesn't need to be inicialized
 * =>nfields is the number of fields in str
 *
 * Return 0 if failed, 1 if not.
 */
//só funciona se o último campo antes do caracter for obrigatório
int ReadRegVar(FILE *f, char ***str,int nfields){
	int tam=0,  n=0, i=0;
	(*str) = (char**) malloc( sizeof(char*)*nfields);

	while(n<nfields-1){
		if(!SetCursesC( f, '<', 1)){
			FreeT((*str), n);	
			return 0;
		}
		fscanf(f, "%d", &tam);


		if(!SetCursesC( f, '<', 1)){
			FreeT((*str), n);	
			return 0;
		}
		fscanf(f, "%d", &n);

		if(!SetCursesC( f, '>', 1)){
			FreeT((*str), n);	
			return 0;
		}
 	

		for(; i<n; i++){                          
			(*str)[i] = (char*) malloc(sizeof(char));
			(*str)[i][0] = EOS;
		}
		
		free((*str)[n-1]);
		ReadStr(f, &( (*str)[n-1] ), tam-2);            //MUDAR DE N-1 PARA N SE O CAMPO 0 FOR A FLAG
	}

	ReadStr(f, &( (*str)[n] ), 1); //caracter separador
	//if(fseek(f, (sizeof(char)*2), SEEK_CUR) != 0) return 0; //anda dois
	return 1;
}


/*retorna 1 se encontrou, e deixa f setado no começo do registro encontrado
 * se não, f fica no começo*/

/*Description: Returns 1 if finded key in the principal key
 * return 0 if doesn't finded*/
int SearchKeyVar(FILE *f, char *key){
	int tam=0, n=0;
	int tam2=0;
	char *str = NULL;
	char *ex = NULL;
	while(1){
		
		if(!SetCursesC( f, '<', 1))		return 0;
		fscanf(f, "%d", &tam);
	
		if(!SetCursesC( f, '<', 1))		return 0;  //TRATAR ERRO COM N==0
		fscanf(f, "%d", &n);

		if(!SetCursesC( f, '>', 1))		return 0;

		ReadStr(f, &(ex), tam-2);

		if(!SetCursesC( f, '<', 1))		return 0;
		fscanf(f, "%d", &tam2);
	
		if(!SetCursesC( f, '<', 1))		return 0;  //TRATAR ERRO COM N==0
		fscanf(f, "%d", &n);

		if(!SetCursesC( f, '>', 1))		return 0;

		ReadStr(f, &(str), tam2-2);


		if(strcmp(key,str) == 0 && ex[0] == 's'){
			if(fseek(f, (-1)* (sizeof(char)*(tam+tam2 + 8)), SEEK_CUR) != 0) return 0;		//volta pro começo do registro
			free(ex);
			free(str);
			return 1;
		}
		
		free(ex);
		free(str);

		if(!SetCursesC( f, '\n', 1))	return 0;

	}
}
