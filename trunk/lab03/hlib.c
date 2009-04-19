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


int ReadReadVar(FILE *f, char ***str,int nfields){
	int tam, tam2, n;
	int i;

	(*str) = (char**)malloc(sizeof(char)*nfields);

	if(fread(&tam, sizeof(char), 1, f)!=1); //ERR
	if(fread(&n, sizeof(char), 1, f)!=1); //ERR

	ReadStr(f, &((*str)[n-1]), tam2-2);
	for(; i<n; i++){
		(*str)[i] = (char*)malloc(sizeof(char));
		(*str)[i][0] = EOS;
	}

	
}


/**Description:   Returns 1 if str is num
 * 				  Returns 2 if str is alp
 * 				  Returns 3 if str is alphanum
 * 				  Returns 0 if str none of the ones
 * 			before, or if str is NULL
 */
int VerAlnum(char *str){
	if(str==NULL)	return 0;

	int alp=0, dig=0;
	int i=0;
	while(str[i]!=EOS){
		if(isalpha(str[i]))
			alp++;
		if(isdigit(str[i]))
			dig++;

		i++;
	}

	if(alp){
		if(dig)		return 3;
		
		return 2;
	}
	
	if(dig)	return 1;

	return 0;
}
