#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "LibFile.h"
#include "LibWord.h"
#include "LibOption.h"
#include "LibMsg.h"

#ifndef EOS
#define EOS '\0'
#endif   /*def EOS*/

#define PRINT_TAM 1
#define PRINT_DIV 0
int MakeData(FILE *f, int **tab, int *nfields){
	(*tab)=(int*)malloc(sizeof(int)*(*nfields));
	if( (*tab) == NULL ){
		free(*tab);
		return 0;
	}

	int i;
	for(i=0;i<*nfields;i++){
		if(fscanf(f,"%d",&((*tab)[i])) == EOF){
			free(*tab);
			(*tab)=NULL;
			return 0;
		}
	}
	return 1;
}

int Print(FILE *f, char *c){
    return fwrite(c,sizeof(char),strlen(c),f);
}

int PrintRegister(FILE *f,char **reg, int nfields){
	int i, n;
	n=0;
	char vet[TAMS];
	
	for(i=0;i<nfields;i++)
		if(*reg[i]!='\0'){		
			vet[0]=strlen(reg[i])+2;
			vet[1]=i+1;
			sprintf(vet+2,"%s",reg[i]);

			fprintf(f,"%s",vet);

			n+=strlen(reg[i])+2;
		}
	return n;
}

int PrintAll(FILE *f, int type, REGIS reg, int treg, int camp){
    int n=0,i;
    char vet[TMS];
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
		if(ver==0)	(*str)[ver] = EOS; 
		else (*str)[ver-1] = EOS;  //ver-1 pois se ele não leu o que mandei ler,  quer dizer que ele encontrou o EOF, e se encontrou o EOF, antes dele possui o \n
        (*str) = realloc(*str, sizeof(char)*(ver));
        if(*str == NULL) return 0;
    }

    return ver;
}

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
	data->alpha = NULL;

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
DATASTYLE* FillData(FILE* f){  //MUDEI PARA PREENCHER OS DADOS EXISTENTES EM DATA
	if(f==NULL)		return NULL;

	DATASTYLE *data = InitDatastyle();
	if(data == NULL)	return NULL;

	if(feof(f))	return data;

	fscanf(f,"%d", &(data->nfield));
	
	//int **table;
	if(!MakeData(f, &(data->efield), &(data->nfield)))	return data;

	if(!MakeData(f, &(data->ob), &(data->nfield)))	return data;
	if(feof(f))	return data;

	if(!MakeDataS(f, &(data->fieldname), data->nfield)){
		return data;
		if(feof(f))	return data;
	}

	if(!MakeData(f, &(data->alpha), &(data->nfield)))	return data;

	return data;
}

int MakeDataS(FILE *f, char ***str, int nfield){
	(*str) = InitRegis(nfield);
	if((*str) == NULL ){
		return 0;
	}

	int i=0, j=0;
	/*ARRUMAR ESTE PEDAÇO*/
	
	for(i=0; i<nfield; i++){
		(*str)[i] = (char*) malloc( sizeof(char) * TAMS );
		if((*str)[i] == NULL){
			FreeT((*str), nfield);
			return 0;
		}
	}

	for(i=0; i<nfield; i++){
			SetCursesC(f, '"', 1);	//VER QUANDO ELE ENCONTRA O EOF
		for(j=0; ; j++){
			
			if(feof(f)){
				FreeT((*str), nfield);
				return 0;
			}

			fscanf(f, "%c", &((*str)[i][j]));

			if((*str)[i][j] == '"' || (*str)[i][j] == EOF ){
				(*str)[i][j] = EOS;
				break;
			}
		}
	}
	
	return 1;
}

/*Description: Free all data of a struct DATASTYLE data*/
void CloseDatastyle(DATASTYLE *data){
	if(data->efield!=NULL)	free(data->efield);
	if(data->ob!=NULL)	free(data->ob);
	if(data->alpha!=NULL)	free(data->alpha);
	if(data->fieldname!=NULL)	FreeT(data->fieldname, data->nfield);
	if(data!=NULL)	free(data);
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




/*Description:  Reads just a field
 *
 * Returns the number of the field*/
int ReadField(FILE *f, char **vet){
	int size, field;
	unsigned char temp;
	
	if(feof(f)) return 0;
	fscanf(f,"%c",&temp);
	size=temp;
	if(feof(f)) return 0;
	fscanf(f,"%c",&temp);
	field=temp;
	
	if(ReadStr(f,vet,size-2)<size-2){ 
		free(*vet);
		return 0;
	}

	return field;
}


/*Description: Reads a file f whth variable format and puts
 * in reg
 *
 * =>f is the file thar will be readed
 * =>***reg is the addres of char **reg, doesn't need to be inicialized
 * =>nfields is the number of fields in str
 *
 * Return 0 if failed, 1 if not.
 */

long int ReadRegVar(FILE *f, char ***reg, int fields){
	int n, i=1;
	char *vet;
	long int start=ftell(f);

	(*reg)=(char**)malloc(sizeof(char*)*fields);
	while(1){
		n=ReadField(f,&vet);

		if(n==0){ 		
			FreeT(*reg,i-1);
			return 0;
		}

		if(n>fields) printf("number of fields in file is greater than expected \n");
		for(;i<n;i++){
			(*reg)[i-1]=(char*)malloc(sizeof(char));
			(*reg)[i-1][0]='\0';
		}
		(*reg)[i-1]=strdup(vet);
		free(vet);
		i++;
		
		if(n==fields-1) break;
	}

	ReadStr(f,&(*reg)[n],1);
	
	SetCursesC(f,'\n',1);

	if(i==1) return 0;
	return start+1;
}


/*retorna 1 se encontrou, e deixa f setado no começo do registro encontrado
 * se não, f fica no começo*/
/*Description: Returns 1 if finded key in the principal key
 * return 0 if doesn't finded*/
int SearchKeyVar(FILE *f, char *key, int nfields){
	char **reg;
	long int start;
	while((start=ReadRegVar(f,&reg,nfields))){
		if(!strcmp(reg[1],key) &&  reg[0][0]=='s'){
			fseek(f,start-1,SEEK_SET);
			FreeT(reg,nfields);
			return 1;
		}
		FreeT(reg,nfields);
	}
	return 0;
}


/*Description:	Returns 1 if str is num
 * 				Returns 2 if str is alpha
 * 				Returns 3 if str is alphanum
 * 				Returns 0 if none of the ones
 * 			before, or if str is NULL
 * */
int VerAlnum(char *str){
	if(str==NULL)	return 0;

	int alp=0, dig=0;
	int i=0;
	while(str[i]!=EOS){
		if(isblank(str[i])){ i++; continue;}
		if(!(isalpha(str[i])) && !(isdigit(str[i])))	return 0;

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

	if(dig)		return 1;

	return 0;
}

int EraseReg(FILE *sf, FILE *ff, DATASTYLE *search, DATASTYLE *find, char *key){
	if(BinaryKeySearch(sf,ff,search,find,key)){
		fseek(ff,2,SEEK_CUR);
		if(fwrite("n",sizeof(char),1,ff)) return 1;
	}
	return 0;
}

int BinaryKeySearch(FILE *sf, FILE *ff, DATASTYLE *search, DATASTYLE *find, char *key){
	int regsize, i, signal;
	long int position, start, end, step1, step2;
	char *reg;
	reg=(char*)malloc(sizeof(char)*(search->efield[0]));
	
	start=0;
	fseek(sf,0,SEEK_END);
	end=ftell(sf);
	fseek(sf,0,SEEK_SET);
	
	

	regsize=0;
	for(i=0;i<search->nfield;i++)
		regsize+=(search->efield[i]);
	regsize++;

	
	signal=1;
	step1=end/regsize;
	step2=2;
	

	while(step2!=1){
		step2=step1;
		step1=step1%2+step1/2;
		if(!step1) step1=1;
		fseek(sf,step1*regsize*signal,SEEK_CUR);
		fscanf(sf,"%s",reg);
		
		
		signal=strcmp(key,reg);
		if(!signal){
			fseek(sf,1,SEEK_CUR);
			fread(&position,sizeof(long int),1,sf);

			fseek(ff,position,SEEK_SET);
			free(reg);
			return 1;
		}
		fseek(sf,-(search->efield[0]-1),SEEK_CUR);
		if(signal>0) signal=1;
		else signal=-1;
	}
	
	free(reg);
	return 0;
}


/*Sorts a table of registers with i = position of the first register,
 * j = position of last register, ver is the table of registers and field
 * is the field of the register that will be Sorted by*/
void quickSort(int i, int j, REGIS vet, int field){
	if(i>=j) return;
	int esq=i, dir = j;
	char **aux = vet[(i+j)/2], **aux2;
	int temp;

	while(1){
		while(esq<=j){
			temp=strcmp(aux[field],vet[esq][field]);
			if(temp>0) esq++;
			else break;
		}
		while(dir>=i){
			temp=strcmp(vet[dir][field],aux[field]);
			if(temp>0) dir--;
			else break;
		}
		if(esq<=dir){
			aux2=vet[esq];
			vet[esq]=vet[dir];
			vet[dir]=aux2;
			esq++; dir--;
		}
		else break;
	}
	quickSort(i,dir,vet,field);
	quickSort(esq,j,vet,field);
}



/*Reads to a big vector nregis from f and put in char *str
 *
 *char **str is the addres of a char *str
 *
 * len is the lenght of a register
 *
 * Returns the number of registers readed
 *
 * if it could not read nregis registers, it realocs the string
 * str with integers register with \n in the end*/
int Read(FILE *f, char **str, int len, int nregis){
	int n = (len+1)*nregis;						//n contém o número de bites totais a ser lido, contando com os \n

	int ch = ReadStr(f, str, n);				//ch contém o número de caracteres lidos
	
	int res = ch%(len+1);

	nregis = ch/(len+1);

	if(res){

		(*str)[ch-res+1] = EOS;

		(*str) = (char*)realloc(*str, sizeof(char)*(ch-res+1));

		return nregis;
	}

	return nregis;
}

/*Description: reads len characteres in string scan and puts in the string str
 *
 * This function already allocate memory for str
 *
 *Returns the number of characteres readed
 *Returns 0 if does not readed something or memory error
 **/
int ReadStr2( char *scan, char* *str, int len){
    (*str) = (char*)malloc( sizeof(char)*( len+1 ) );
    if( *str==NULL ) return 0;
    
    int ver = 0;
    (*str) = strncpy(*str, scan, len);
	
	(*str)[len] = EOS;

	ver = strlen(*str);

    if(ver<len){
		(*str)[ver] = EOS;

        (*str) = realloc(*str, sizeof(char)*(ver+1));
        if(*str == NULL) return 0;
    }
    return ver;
}



/*FALTA COLOCAR UNS AVISOS*/
/*
 * scan is the string that will be readed.
 * fieldList is a (char **) type that will be filled whith strings.
 * lenList[i] indicate the number of characteres that will be readed from
 * the string scan and put in fieldList[i]
 *
 * Returns the number of all characteres readed
 * If does not readed the right number of characteres scan, returns 0 
 * */
int FillFields2(char *scan, char* **fieldList, int *lenList, int nfields){
    (*fieldList) = InitRegis(nfields);
    if(*fieldList == NULL) return 0;

	char *scanaux = scan;
    int i=0, sum=0, ver=0;

    for(i=0; i<nfields; i++){
        ver = ReadStr2(scanaux, &((*fieldList)[i]), lenList[i]);
        
        if( ver<lenList[i] ) return 0;

        sum+= ver;

		scanaux+=ver;		//anda com o vetor de string para scanear o próximo campo
    }

    return sum;
}


/*Reads f and fill REGIS reg 
 * 
 * vlen[i] contain the lenght of the field i
 * qnt is the quantity of registers tha will be readed
 * nfield is the quantity of the fields in the register
 *
 * */
int Div(FILE *f ,REGIS *reg,  int *vlen, int nfield, int qtd){
	int len = 0;
	int i = 0;

	

	for(i=0; i<nfield; i++){			//loop que preenche len com o tamanho total de um registro
		len+=vlen[i];
	}

	char *bigstr = NULL;
	int nregis = Read(f, &bigstr, len, qtd);
	char *bigstraux = bigstr;			//vetor para andar com bigstr  (string com todos os registros
	
	for(i=0; i <nregis; i++){			//loop que preenche o reg
		FillFields2(bigstraux,&((*reg)[i]), vlen, nfield);
		
		bigstraux+=len+1;
	}

	free(bigstr);

	return i;
}


/*Converts a table REGIS to a string str
 *
 * nregist is the number of the registers that will be copy
 * tamregis is the number of the register
 * nfield is the quantity of field that contain in a registers*/
int TabletoStr(char* *str, REGIS reg, int nregis, int tamregis, int nfield){
	(*str) = (char*)malloc( sizeof(char)*(nregis*(tamregis+1) ));			//maloca nregis* (tamregis+1)     contando com os \n


	int i=0;
	int j=0;
	int k=0;

	char *straux = str;

	for(i=0; i<nregis; i++){			//loop que anda com os registros

		for(j=0; j<nfield; j++){		//loop que anda com os campos
			

			//k=sscanf(reg[i][j], "%s", straux );
			k = strlen(reg[i][j]);

			straux = strncpy(straux, reg[i][j], k);

			straux+=k;
		}
		
		sprintf(straux, "\n");			//no final do registro coloca \n

		straux++;
	
	}

	return i;

}


/*Prints in the file filename the table in the struct item
 *
 * Opens the file with "a",  writes at the end of the file
 * Creates a new one if the file does not exist
 * */
void WriteLin(char *filename, ITENS item){
	int i=0;
	int len = 0;

	FILE *f = fopen(filename, "a");

	for(i=0; i<item.nitens; i++){
		len+=strlen(item.linha[i]);
	}
	
	if(len + item.nitens<= 0)	printf("ERROOOOOOOOOOO\n");
	char *str = (char*)malloc( sizeof(char)*( len + item.nitens + 1) ) ;
	if(str == NULL) {perror("Error: In malloc of the function WriteLin\n");		return;}

	char *straux = str;
	
	for(i=0; i<item.nitens -1 ; i++){				//vai até o penultimo
		
		sprintf(straux, "%s,", item.linha[i]);

		straux+=strlen(item.linha[i]) + 1;
	
	}
	
	sprintf(straux, "%s\n", item.linha[i]);

	fwrite(str, sizeof(char), len + item.nitens, f);

	free(str);

	fclose(f);


}


/*Loads the names of the file csv.config*/
ITENS CarregaCsv(char *filename, int nitens){

	FILE *f = fopen(filename, "r");
	if(f==NULL){	printf("Error: to open file in function CarrecaCsv\n");	exit(0);}
	
	ITENS it;
	int i=0;
	int j=0;
	
	it.linha = (char**)malloc(sizeof(char*)*nitens);
	it.nitens = nitens;


	for(i=0; i<nitens; i++){

		it.linha[i] = (char*)malloc(sizeof(char)*TMS);

		j=fscanf(f, "%s", it.linha[i]);
		if(j==0)	{perror("Error: in file csvconfig\n");	exit(0);}

		it.linha[i] = (char*)realloc(it.linha[i], strlen(it.linha[i]) +1 );


	}

	return it;

}

/*Same as WriteLin, but if the filename does not exist,
 * it writes the name of the colums*/
void WriteCsv(char *filename, ITENS item, char *csvconfig){
	FILE *f = fopen(filename, "r");
	if(f == NULL){
		ITENS it = CarregaCsv(csvconfig, item.nitens);

		WriteLin(filename, it);	

		//FreeT(it.linha, it.nitens);
	
	}
	else fclose(f);

	WriteLin(filename, item);

}



