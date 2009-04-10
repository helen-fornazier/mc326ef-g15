/*Arquivo para as funções desenvolvidas pela Amapá.   Incluso na LibFile.
 * Para não correr o risco de modificarmos
 * o mesmo arquivo ao mesmo tempo*/

//#define FIX 1
//#define VAR 0
/*
typedef struct datastyle{
	int nfield;			//how many field exist
	int *efield;		//lengh of each field
	int *ob;			//list of oblibatoriety
	char *fieldname;	//name of each fields

}	DATASTYLE;

typedef struct regis{
	int nregis;		//number of registers
	int fix;		//if is a file with fixed lenght filds, fix == 1, if isn't,  fix == 0
	int nrem;		//the number of registers set as removed
	DATASTYLE *datastyle;		//if a file of variable lenght fields, datastyle is NULL
	FILE* fi;		//a pointer to the beginning of the file
	FILE* fe;		//a pointer to the last register

} REGIS_t;
*/


DATASTYLE *InitDatastyle(){
	DATASTYLE *data = (DATASTYLE*) malloc( sizeof(DATASTYLE) );
	if( data==NULL )	return NULL;
	

	data->nfield = 0;
	data->efield = NULL;
	data->ob = NULL;
	data->fieldname = NULL;
	
	return data;

}

DATASTYLE* FillData(FILE* f){
	if(f==NULL)		return NULL;

	DATASTYLE *data = InitDatastyle();
	if(data == NULL)	return NULL;

	int **table;
	MakeData(f, &table, &(data->nfield));
	
	data->efield = table[0];
	data->ob = table[1];
	
	return data;
}

/*Read of FILE f qnt registers with nfields of lengh iqual to len and put it REGIS reg
 * sum is increased with*/
/*
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
}*/

/*Lê apenas um registro, retorna 1 se leu o registro por inteiro
 * retorna 0 se não leu, ou erro de memória
 * */
int ReadRegFix1(FILE *f, char ***str, int *len, int nfields){
		char **string = NULL;
		char **correct = NULL;


		if(!FillFields( f, &string, len, nfields ))   return 0;

        correct = CorrectorList( string, nfields );
        if(correct == NULL) return 0;     //imprimir erro

        free(string);

        if(!SetCursesC( f, '\n', 1 ))   return 0;    //EOF  
	
        (*str) = correct;

		return 1;
}



