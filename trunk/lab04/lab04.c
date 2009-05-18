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
		quickSort(0,nreg-1,matrix,field);
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

int MergeSort(int nfile, int field, int memory, DATASTYLE *ds, INFORMATION *info){
	int regsize=0, i;
	for(i=0;i<ds->nfield;i++) regsize+=ds->efield[i];
	int nreg=memory/(3*regsize), nfilea, newfile ;
	int readrega, readregb, j, k, temp;
	FILE *a, *b, *c;
	char tempvet[TAMS];
	REGIS ra, rb, rc=(REGIS)malloc(sizeof(char**)*nreg);
	int re=0,wr=0;
	char *str=NULL;

	if(nfile<=1) return 1;

	nfilea=1;
	sprintf(tempvet,"tempfolder/%d",nfilea);
	a=fopen(tempvet,"r");
	nfilea++;
	sprintf(tempvet,"tempfolder/%d",nfilea);
	b=fopen(tempvet,"r");
	newfile=nfile+1;
	sprintf(tempvet,"tempfolder/%d",newfile);
	c=fopen(tempvet,"w");
	readrega=Div(a,&ra,ds->efield,ds->nfield,nreg);
	re++;
	readregb=Div(b,&rb,ds->efield,ds->nfield,nreg);
	re++;
	while(1){
		i=j=k=0;
		while(1){
			temp=strcmp(ra[i][field],rb[j][field]);
			if(temp<0){
				rc[k++]=ra[i++];
				if(i==readrega){
					FreeTT(ra,readrega,ds->nfield);
					readrega=Div(a,&ra,ds->efield,ds->nfield,nreg);
					re++;
					i=0;
				}
			}
			else{
				rc[k++]=rb[j++];
				if(j==readregb){ 
					FreeTT(rb,readregb,ds->nfield);
					readregb=Div(b,&rb,ds->efield,ds->nfield,nreg); 
					re++;
					j=0;
				}
			}
			if(k==nreg){ 
				TabletoStr(&str,rc,k,regsize,ds->nfield);
				fwrite(str,sizeof(char),(regsize+1)*k,c);
				free(str);
				wr++;
				k=0;
			}
			if(feof(a)){
				TabletoStr(&str,rc,k,regsize,ds->nfield);
				fwrite(str,sizeof(char),(regsize+1)*k,c);
				free(str);
				wr++;
		
				TabletoStr(&str,&rb[j],(readregb-j),regsize,ds->nfield);
				fwrite(str,sizeof(char),(regsize+1)*(readregb-j),c);
				free(str);
				wr++;
				
				while(!feof(b)){
					/*le memory em b*/
					readregb=Read(b,&str,regsize,nreg*3);
					fwrite(str,sizeof(char),readregb*(regsize+1),c);
					free(str);
					wr++;
				}
				break;
			}
			if(feof(b)){ 
				TabletoStr(&str,rc,k,regsize,ds->nfield);
				fwrite(str,sizeof(char),(regsize+1)*k,c);
				free(str);
	
				wr++;
				TabletoStr(&str,&ra[j],(readrega-i),regsize,ds->nfield);
				fwrite(str,sizeof(char),(regsize+1)*(readrega-i),c);
				free(str);
	
				wr++;
				while(!feof(a)){
					readregb=Read(a,&str,regsize,nreg*3);
					fwrite(str,sizeof(char),readregb*(regsize+1),c);
					free(str);
	
					wr++;
				}
				break;
			}
		}
	
		fseek(c,0,SEEK_SET);
		fclose(a);
		fclose(b);
		a=c;
		nfilea++;
		if(nfilea>nfile){ 
			fclose(c);
			break;
		}
		sprintf(tempvet,"tempfolder/%d",nfilea);
		b=fopen(tempvet,"r");
		newfile++;
		c=fopen(tempvet,"w");
		readrega=Div(a,&ra,ds->efield,ds->nfield,nreg);

		re++;
		readregb=Div(b,&rb,ds->efield,ds->nfield,nreg);
 
		re++;
	}
	info->file=newfile;
	info->write=wr;
	info->read=re;

	return 0;
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
	MergeSort(temp,field,memory,data,info);
	
	sprintf(str,"mv tempfolder/%d %s",info->file,argv[2]);
	system(str);
	system("rmdir tempfolder");

	time(&end);
	info->time=difftime(end,start);
	info->merge=info->file-temp;

	ITENS itens;
	itens.nitens=9;
	itens.linha=(char**)malloc(sizeof(char*)*itens.nitens);

	int i=0;
	itens.linha[0]=argv[1];
	for(i=1; i<itens.nitens; i++){
		itens.linha[i] = (char*)malloc(sizeof(char)*TMS);
		itens.linha[i][TMS] = EOS;
	}

	sprintf(itens.linha[1], "%d", info->totreg );
	sprintf(itens.linha[2], "%d", memory );
	sprintf(itens.linha[3], "%d", field );
	sprintf(itens.linha[4], "%d", info->file );
	sprintf(itens.linha[5], "%d", info->merge );
	sprintf(itens.linha[6], "%d", info->read );
	sprintf(itens.linha[7], "%d", info->write );
	sprintf(itens.linha[8], "%lf", info->time );

	WriteCsv("relatorio.csv", itens, "csv.config");				//ARRUMAR DEFINES PARA OS NOMES DOS ARQUIVOS
	return 0;
}

