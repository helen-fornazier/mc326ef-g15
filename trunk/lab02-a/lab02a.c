#include"LibFile.h"
#include"LibMsg.h"
#include"LibWord.h"

#define IDIOM "english.config"
#define DATA "data.config"


#define PIN 1
#define POUT1 2
#define POUT2 3
#define PLENG 4

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


/*Reads in a big vector nregis from f and put in char *str
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
 * If does not readed the right number of characteres in f, returns 0 
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


/*Reads f and fill REGIS reg, */
int Div(FILE *f ,REGIS *reg,  int *vlen, int nfield, int qtd){

   (*reg) = (REGIS)malloc( sizeof(char **)*qtd );
    if((*reg) == NULL)       return 0;	

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
int TabletoStr(char **str, REGIS reg, int nregis, int tamregis, int nfield){
	(*str) = (char*)malloc( sizeof(char)*((nregis*(tamregis+1)) + 1));			//maloca nregis* (tamregis+1)     contando com os \n
	if((*str)==NULL) perror("Error: Memory allocation\n");

	int i=0;
	int j=0;
	int k=0;

	char *straux = (*str);

	for(i=0; i<nregis; i++){			//loop que anda com os registros

		for(j=0; j<nfield; j++){		//loop que anda com os campos
			

			//k=sscanf(reg[i][j], "%s", straux );
			k = strlen(reg[i][j]);

			straux = strncpy(straux, reg[i][j], k);

			straux+=k;
		}
		
		sprintf(straux, "\n%c", EOS);			//no final do registro coloca \n

		straux++;
	
	}

	return i;

}




int main(int argc, char *argv[]){
		
	if(argc==PLENG+1){
		if(MakeMsg(argv[PLENG])!=0) MakeMsg(IDIOM);
	} else MakeMsg(IDIOM);
	
	if(argc<PLENG || argc> PLENG+1){ 
		Msg(1);
		return 1;
	}

	FILE *fi=fopen(argv[PIN],"r");
	if(fi==NULL) Msg(2); 
	FILE *fo1=fopen(argv[POUT1],"w");
	if(fo1==NULL) Msg(3);
	FILE *fo2=fopen(argv[POUT2],"w");
	if(fo2==NULL) Msg(4);
    
	int **tab, nfields;
	FILE *fd=fopen(DATA,"r");
	MakeData(fd,&tab,&nfields);
	fclose(fd);


	REGIS matrix;
	int i=5, j=0, k=0, y=0;
	int n1=0, n2=0;
	
	while(i==10){
		i=Div(fi,&matrix,tab[0],nfields,i);

		quickSort(0, i-1, matrix, 1);
        
        for(y=0; y<i; y++){
            for(k=0; k<nfields; k++){
                if((tab[1][k] == 1) && (matrix[y][k][0] == EOS)){
                    Msg(12);
                    printf("%d, %d\n", j+y+1 , k+1);
                }
            }
        }
		

		int var =0;
		int count=0;

		for(var=0; var<nfields; var++){
			count+=tab[0][var];
		
		}



		char *STRING = NULL;
		TabletoStr(&STRING, matrix, i, count, nfields );
		free(STRING);


//		printf("%s", STRING);

		j+=i;
//		n1+=PrintAll(fo1,PRINT_DIV,matrix,i,nfields);
//		n2+=PrintAll(fo2,PRINT_TAM,matrix,i,nfields);

        FreeTT(matrix, i, nfields); 
	}
	
	int sum=0;
	for(i=0;i<nfields;i++)
		sum+=tab[0][i];
        Msg(11);
	printf("%d\n",j*(sum+1));	
	Msg(8);
	printf("%d\n",j);
	Msg(9);
	printf("%d\n",n1);
	Msg(10);
	printf("%d\n",n2);

	i=fclose(fi);
	if(i) Msg(5);
	i=fclose(fo1);
	if(i) Msg(6);
	i=fclose(fo2);	
	if(i) Msg(7);
	

	return 0;
}
