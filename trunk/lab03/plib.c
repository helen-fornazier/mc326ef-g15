/*Arquivo para as funções desenvolvidas pelo Pirata.   Incluso na LibFile.
 * Para não correr o risco de modificarmos
 * o mesmo arquivo ao mesmo tempo*/

typedef struct registers{
	int n;
	int nfields;
	int *lengh;
	int *ob;
	char **name;
	int *type; /*0=numeric 1=alphanumeric*/
	char ***reg;
} REGISTERS

typedef struct wfiles{
	FILE *main;
	FILE *config;
	REGISTERS *a;
} WFILES

/*Receive the information from a .config*/
void ReceiveConfig(FILE *f; REGISTERS *a){
	int i;
	char name[100];

	fscanf(f,"%d",&a->nfields);
	
	a->lengh=(int*)malloc(sizeof(int)*a->nfield);
	for(i=0;i<a->nfields;i++) fscanf(f,"%d",&a->lengh[i]);

	a->ob=(int*)malloc(sizeof(int)*a->nfield);
	for(i=0;i<a->nfields;i++) fscanf(f,"%d",&a->ob[i]);

	a->type=(int*)malloc(sizeof(int)*a->nfield);
	for(i=0;i<a->nfields;i++) fscanf(f,"%d",a->type[i]);

	a->name=(char**)malloc(sizeof(char*)*a->nfield);
	for(i=0;i<a->nfields;i++){
		fscanf(f,"%s",name);
		a->name[i]=strdup(name);
	}

}

/*Verify if the array has only the wanted type of characters*/

int VerifyType(int type, char *vet){
	if(type==0){
		int i;
		for(i=0;vet[i]!='\0';i++)
			if(vet[i]<'0'||vet[i]>'9') return 0;
	}
	return 1;
}

/*Verify if there is something at the vet if it is obrigatory*/

int VerifyOb(int ob, char *vet){
	if(ob==1&&*vet=='\0') return 0;
	return 1;
}

/* 
 * Verify if the received registers obey the predicted order 
 * return 1 if the information is ok
 * return 0 if there is a flaw                        */

int Verify(REGISTERS *a){
	int i, j;
	for(i=0;i<n;i++){
		for(j=0;j<nfields;j++)
			if(!VerifyType(a->type[j],a->reg[n][j]) || !VerifyOb(a->ob[j],a->resg[n][j])) return 0;
	return 1;
}

/* print registers at file g
 * if they had no problem, return 1
 * else, return 0 */

int PrintRegFixX(FILE *f, REGISTERS *a, FILE *g){
	int i,j,temp;
	do{
		a->n=ReadRegFix(f,&a->reg,a->lengh,nfields,5);
		if(!Verify(a)) return 0;
		for(i=0;i<a->n;i++){
			for(j=0;j<a->nfields;j++){
				fprintf(g,"%s ",a->name[j]);
				fprintf(g,"%s ",a->reg[n][j]);
				temp=a->lengh[j]-strlen(a->reg[n][j]);
				for(;temp>0;temp--) fprintf(g," ");
			}	
			fprintf(g,"\n");
		}
	}while(a->n==5);
	return 1;
}

long int FindChar(FILE *f, char a){
	char b=a+1;
	while(b!=a){
		fscanf(f,"%c",&b);
		if(b==EOF) return 0;
	}
	return ftell(f);
}

int ReadCampVar(FILE *f, char *camp){
	int a,b,c;
	fscanf(f,"%d",&a);
	fscanf(f,"%d",&b);
	FindChar(f,'>');
	if(reg!=NULL) free(reg);
	reg=malloc(sizeof(char)*(1+b));
	fread(reg,sizeof(char),b,f);
	reg[b]='\0';
	return a;
}

/* the reg this functions recieve must be a &char** and it must be the char** must be NULL
 * the function will give you one register of a variable size file by the reg you will give and
 * will return the adress of the start of the reg. it will also place the cursor at the end of
 * the register*/

long int ReadRegVar(FILE *f, char ***reg, int nfields){
	int a, b, c;
	int i;
	long int start,end;
	char *temp;

	*reg=(char**)malloc(sizeof(char*)*nfields);
	b=nfields+1

	start=FindChar(f,'<');
	if(start==0) return 0;
	end=--start;
	b=1;
	c=0;

	while(1){
		a=ReadCampVar(f,temp);
		if(a>nfields) printf("Funtion: ReadRegVar has found a greater value of field from a camp then the permited by nfields \n");
		
		if(a>b){
			for(i=b-1;i<a-1;i++){
				(*reg)[i]=(char*)malloc(sizeof(char));
				*(*reg)[i]='\0';
			}
		}
		if(a<=c) break;
		reg[a-1]=strduo(temp);
		c=b=a;
		end=FindChar(f,'>');
	}
	free(temp);
	fseek(f,-(end-start),SEEK_CUR);
	return start;
}

/* the char*** from the REGISTERS must be NULL 
 * Print all registers from a variable file in a new file
 * witch the first information of each register becomes
 * the place where you can find them at the first file
 * return 0 if the programs fail, and 1 if it works*/

int PrintRegVarX(FILE *f,REGISTERS a, FILE *g){
	long int temp;
	int i;

	a->reg=(char***)malloc(sizeof(char**));
	temp=ReadRegVar(f,a->reg,a->nfields);
	if(temp==0){ 
		return 0;
	}
	
	while(temp){
		fprintf(g,"BYTE %ld ",temp);
		for(i=0;i<a->nfields;i++)
			fprintf(g,"%s %s ",a->name[i],a->reg[0][i]);
		fprintf(g,"\n");
		
		for(i=0;i<a->fields;i++) free(a->reg[0][i]);
		free(a->reg[0]);
		
		temp=ReadRegVar(f,a->reg,a->nfields);
	}
	return 1;
}

/*Receive a primary key vet of chars and search for it at the file
 * if fount, print it and return 1, else, return 0 */

int FindReg(FILE *f,REGISTERS *a,char *vet){
	int i;
	While(ReadRegVar(f,a->reg,a->nfields)){
		if(!strcmp(vet,a->reg[0][1])){
			for(i=0;i<nfields;i++) printf("%s %s ",a->name[i],a->reg[0][i]);
			printf("\n");
			return 1;
		}
		for(i=0;i<a->nfields;i++) free(a->reg[0][i]);
		free(a->reg[0]);
	}
	return 0; /*remember to send the error msg*/
}

/*create an organized list of primary keys*/
