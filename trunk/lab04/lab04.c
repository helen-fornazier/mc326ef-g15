#define DATA "data.config"
#include<time.h>
#include"LibFile.h"
#include"LibWord.h"
#include"LibMsg.h"

#define TAMS 100
#define TMS 10


typedef struct information{
	int write, read, file, merge, totreg;
	double time;
} INFORMATION;


int FirstOrder(FILE *f, int field, int memory, DATASTYLE *ds, int *totreg){
	int regsize=0,i;
	for(i=0;i<ds->nfield;i++) regsize+=ds->efield[i];
	int nreg=memory/(regsize+1), readreg=nreg, nfile=0;
	REGIS matrix = NULL;
	char tempstr[TAMS]; 
	FILE *out;
	char *str;
	*totreg=0;

	system("mkdir tempfolder");
	while(readreg==nreg){
		readreg=Div(f,&matrix,ds->efield,ds->nfield,nreg);
		*totreg+=readreg;
		if(readreg==0) break;
		quickSort(0,readreg-1,matrix,field);
		nfile++;
		sprintf(tempstr,"tempfolder/%d",nfile);
		out=fopen(tempstr,"w");
		TabletoStr(&str,matrix,readreg,regsize,ds->nfield);
		fwrite(str,sizeof(char),(regsize+1)*readreg,out);
		FreeTT(matrix,readreg,ds->nfield);
		free(str);
		fclose(out);
	}
	return nfile;
}


char** copyReg(char** reg, DATASTYLE *ds){
	char** out=(char**)malloc(sizeof(char*)*ds->nfield);
	int i;
	for(i=0;i<ds->nfield;i++){
		out[i]=strdup(reg[i]);
	}
	return out;
}

void merge2files(FILE *a, FILE *b, FILE *c, int field, int memory, DATASTYLE *ds, INFORMATION *info){
	int regsize, nreg, temp, i, j, k, l;
	int readrega, readregb;
	REGIS ra, rb, rc;
	char *str;

	regsize=0;
	for(i=0;i<ds->nfield;i++) regsize+=ds->efield[i];
	nreg=memory/(3*regsize);

	readrega=Div(a,&ra,ds->efield,ds->nfield,nreg);
	info->read++;
	readregb=Div(b,&rb,ds->efield,ds->nfield,nreg);
	info->read++;
	rc=(char***)malloc(sizeof(char**)*nreg);
	
	i=j=k=0;
	while(1){
		temp=strcmp(ra[i][field],rb[j][field]);
		if(temp<0){
			rc[k++]=copyReg(ra[i++],ds);
			if(i==readrega){
				FreeTT(ra,readrega,ds->nfield);
				readrega=Div(a,&ra,ds->efield,ds->nfield,nreg);
				info->read++;
				i=0;
			}
		}	
		else{
			rc[k++]=copyReg(rb[j++],ds);
			if(j==readregb){
				FreeTT(rb,readregb,ds->nfield);
				readregb=Div(b,&rb,ds->efield,ds->nfield,nreg); 
				info->read++;
				j=0;
			}	
		}
		if(k==nreg){ 
			TabletoStr(&str,rc,k,regsize,ds->nfield);
			fwrite(str,sizeof(char),(regsize+1)*k,c);
			free(str);
			for(l=0;l<nreg;l++) FreeT(rc[l],ds->nfield);
			info->write++;
			k=0;
		}	
		if(feof(a)){
			TabletoStr(&str,rc,k,regsize,ds->nfield);
			fwrite(str,sizeof(char),(regsize+1)*k,c);
			free(str);
			for(l=0;l<k;l++) FreeT(rc[l],ds->nfield);
			free(rc);
			info->write++;
	
			TabletoStr(&str,&rb[j],(readregb-j),regsize,ds->nfield);
			fwrite(str,sizeof(char),(regsize+1)*(readregb-j),c);
			FreeTT(rb,readregb,ds->nfield);
			free(str);
			info->write++;
			
			while(!feof(b)){
				readregb=Read(b,&str,regsize,nreg*3);
				fwrite(str,sizeof(char),readregb*(regsize+1),c);
				free(str);
				info->write++;
			}
			break;
		}	
		if(feof(b)){
			TabletoStr(&str,rc,k,regsize,ds->nfield);
			fwrite(str,sizeof(char),(regsize+1)*k,c);
			free(str);	
			for(l=0;l<k;l++) FreeT(rc[l],ds->nfield);
			free(rc);
			info->write++;
	
			TabletoStr(&str,&ra[j],(readrega-i),regsize,ds->nfield);
			fwrite(str,sizeof(char),(regsize+1)*(readrega-i),c);
			FreeTT(ra,readrega,ds->nfield);
			free(str);
			info->write++;
			
			while(!feof(a)){
				readrega=Read(a,&str,regsize,nreg*3);
				fwrite(str,sizeof(char),readrega*(regsize+1),c);
				free(str);
				info->write++;
			}
			break;
		}			
	}
}

void MergeSort(int nfile, int field, int memory, DATASTYLE *ds, INFORMATION *info){
	int nfilea, newfile;
	char tempvet[TAMS];
	FILE *a, *b, *c;

	info->merge=0;
	info->write=nfile;
	info->read=nfile;
	info->file=nfile;

	if(nfile<2) return;
	
	nfilea=1;
	newfile=nfile+1;

	sprintf(tempvet,"tempfolder/%d",nfilea);
	a=fopen(tempvet,"r");
	nfilea++;
	sprintf(tempvet,"tempfolder/%d",nfilea);
	b=fopen(tempvet,"r");
	sprintf(tempvet,"tempfolder/%d",newfile);
	c=fopen(tempvet,"w");
	
	merge2files(a,b,c,field,memory,ds,info);
	info->merge++;
	info->file++;
	fclose(a);
	fclose(b);
	fclose(c);
	
	while(nfilea<nfile){
		
		sprintf(tempvet,"tempfolder/%d",newfile);
		a=fopen(tempvet,"r");
		nfilea++;
		sprintf(tempvet,"tempfolder/%d",nfilea);
		b=fopen(tempvet,"r");
		newfile++;
		sprintf(tempvet,"tempfolder/%d",newfile);
		c=fopen(tempvet,"w");
		merge2files(a,b,c,field,memory,ds,info);
		fclose(a);
		fclose(b);
		fclose(c);
		info->merge++;
		info->file++;
	}

}



int main(int argc, char *argv[]){
	if(argc<4){ /*mensagem*/
		return 1;
	}
	
	char str[TAMS];
	sprintf(str,"%s.config",argv[1]);
	FILE *f = fopen(str,"r");
	DATASTYLE *data=FillData(f);
	fclose(f);
	f=fopen(argv[1],"r");
	int memory=atoi(argv[3]), temp, field;
	INFORMATION *info=(INFORMATION*)malloc(sizeof(INFORMATION));
	

	/**/
	scanf("%d",&field);

	time_t start,end;
	time(&start);

	temp=FirstOrder(f,field,memory,data,&(info->totreg));
	fclose(f);
/*********************************/
printf("\n\nantes do merge\n\n");
/**********************************/
	MergeSort(temp,field,memory,data,info);

/********************************/
printf("\n \n SAIU DO MERGE \n \n");
/*********************************/

	sprintf(str,"mv tempfolder/%d %s",info->file,argv[2]);
	system(str);
	system("rm -rf tempfolder");

	time(&end);
	info->time=difftime(end,start);
	info->merge=info->file-temp;
/**************************/
printf("\n \n Passo um \n \n");
/**************************/
	ITENS itens;
	itens.nitens=9;
	itens.linha=(char**)malloc(sizeof(char*)*itens.nitens);

	int i=0;
	itens.linha[0]=argv[1];
	for(i=1; i<itens.nitens; i++){
		itens.linha[i] = (char*)malloc(sizeof(char)*TMS);
		itens.linha[i][TMS-1] = EOS;
	}
/*************************/
printf("\n \n Passo dois \n \n");
/*************************/
	sprintf(itens.linha[1], "%d", info->totreg );
	sprintf(itens.linha[2], "%d", memory );
	sprintf(itens.linha[3], "%d", field );
	sprintf(itens.linha[4], "%d", info->file );
	sprintf(itens.linha[5], "%d", info->merge );
	sprintf(itens.linha[6], "%d", info->read );
	sprintf(itens.linha[7], "%d", info->write );
	sprintf(itens.linha[8], "%lf", info->time );

/**************************/
printf("\n\n Passo tres \n\n");
/**************************/
	WriteCsv("relatorio.csv", itens, "csv.config");				//ARRUMAR DEFINES PARA OS NOMES DOS ARQUIVOS
	for(i=1;i<itens.nitens;i++) free(itens.linha[i]);
	free(itens.linha); 

/***************************/
printf("\n\n Final do programa \n\n");
/***************************/
	return 0;
}

