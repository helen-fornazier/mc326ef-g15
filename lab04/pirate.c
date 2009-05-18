void quickSort(int i, int j, REGIS vet, int field){
	if(i>=j) return;
	int esq=i, dir = j;
	char **aux = vet[(i+j)/2], **aux2;
	int temp;

	while(1){
		while(1){
			temp=strcmp(aux[field],vet[esq][field]);
			if(temp>0) esq++;
			else break;
		}
		while(1){
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

int FirstOrder(FILE *f, int field, int memory, DATASTYLE *ds){
	int regsize=0,i;
	for(i=0;i<ds->nfield;i++) regsize+=ds->efield[i];
	int nreg=memory/(regize+1), readreg=nreg, nfile=0;
	REGIS matrix;
	char tempstr[TAMS];
	FILE *out;
	char *str;
	
	system("mkdir tempfolder");
	while(readreg==nreg){
		readreg=Div(f,&matrix,ds->efield,ds->nfields,nreg);
		if(readreg==0) break;
		quickSort(0,nreg-1,matrix,field);
		nfile++;
		sprintf(tempstr,"tempfolder/%d",nfile);
		out=fopen(tempstr,"w");
		TabletoStr(&str,matrix,readreg,regsize,ds->nfield);
		fwrite(str,sizeof(char),(regsize+1)*readreg);
		FreeTT(matrix,readreg,ds->nfield);
		free(str);
		fclose(out);
	}
	return nfile;
}

int MergeSort(int nfile, int field, int memory, DATASTYLE *ds, INFORMATION *info){
	int regsize=0, i;
	for(i=0;i<ds->nfield;i++) regsize+=ds->efield[i];
	int read=0, write=0, nreg=memory/(3*regsize), nread, nfilea, newfile ;
	int readrega, readregb, i, j, k, temp;
	FILE *a, *b, *c;
	char tempvet[TAMS];
	REGIS ra, rb, rc=(REGIS)malloc(sizeof(char**)*nreg), tempr;
	int re=0,wr=0,creatfile=0;
	char *str;

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
	readrega=Div(a,&ra,ds->efield,ds->nfields,nreg);
	re++;
	readregb=Div(b,&rb,ds->efield,ds->nfields,nreg);
	re++;
	while(){
		i=j=k=0
		while(){
			temp=strcmp(ra[i][field],rb[j][field]);
			if(temp<0){
				rc[k++]=ra[i++];
				if(i==readrega){
					FreeTT(readrega,ds->nfield);
					readrega=Div(a,&ra,ds->efield,ds->nfields,nreg);
					re++;
					i=0;
				}
			}
			else{
				rc[k++]=rb[j++];
				if(j==readregb){ 
					FreeTT(readregb,ds->nfield);
					readregb=Div(b,&rb,ds->efield,ds->nfields,nreg); 
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
				fwrite(str,sizeof(char),(regsize+1)*(readregb-j));
				free(str);
				wr++;
				
				while(!feof(b)){
					/*le memory em b*/
					readregb=Read(&str,regsize,nreg*3,b);
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
				fwrite(str,sizeof(char),(regsize+1)*(readrega-i));
				free(str)
	
				wr++;
				while(!feof(a)){
					readregb=Read(&str,regsize,nreg*3,a);
					fwrite(str,sizeof(char),readregb*(regsize+1),c);
					free(str);
	
					wr++;
				}
				break;
			}
		}
	
		seek(c,0,SEEK_SET);
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
		readrega=Div(a,&ra,ds->efield,ds->nfields,nreg);

		re++;
		readregb=Div(b,&rb,ds->efield,ds->nfields,nreg);
 
		re++;
	}
	info->file=newfile;
	info->write=wr;
	info->read=re;

	return 0;
}

#define DATA "data.config"
#include<time.h>

typedef struct information{
	int write, read, file;
	double time;
} INFORMATION

int main(int argc, char *argv[]){
	if(argc<4){ /*mensagem*/
		return 1;
	}
	
	FILE f = foppen(DATA,r);
	DATASTYLE *data=FillData(f);
	fclose(f);
	f=fopen(argv[1],r);
	int memory=atoi(argv[3]), temp, field;
	INFORMATION *info=(INFORMATION*)malloc(sizeof(INFORMATION));

	printf("\ndigite 0 se quizer ordenado por RA ou 1 por Nome\n");
	scanf("%d",&field);

	time_t start,end;
	time(&start);

	temp=FirstOrder(f,field,memory,data);
	fclose(f);
	MergeSort(temp,field,memory,data,info);

	time(&end);
	info->time=diftime(end,start);

	return 0;
}

