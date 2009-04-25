#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"LibWord.h"
#include"LibFile.h"
#include"LibMsg.h"
#include"LibOption.h"

#define TAMS 100
#define TMS 30

#define TAMIND 3

#define DATAINDN "dataindn.config"
#define DATAIND "dataind.config"

void PrintMenu(EFILE *e){
	Msg( e, 0);
	Msg( e, 1);
	Msg( e, 2);
	Msg( e, 3);
	Msg( e, 4);
	Msg( e, 5);
	Msg( e, 24);
	Msg( e, 25);
	Msg( e, 26);
	Msg( e, 27);
	Msg( e, 28);
	Msg( e, 29);
	Msg( e, 6);

	}

void VerOb(EFILE *e, DATASTYLE *data, REGIS matrix,  int i, int j){
	int y=0, k=0;
	for(y=0; y<i; y++){
		for(k=0; k<data->nfield; k++){

			if((data->ob[k] == 1) && (matrix[y][k][0] == EOS)){
				Msg(e, 12);
				printf("%d, %d\n", j+y+1 , k+1);
				exit(1);
			}
		}
	}
}

/*Verifica a obrigatoriedade de um registro*/
int VerOb1(EFILE *e, DATASTYLE *data, char **str,  int i){
		int k=0;
	
		for(k=0; k<data->nfield; k++){

			if((data->ob[k] == 1) && (str[k][0] == EOS)){
				Msg(e, 12);
				printf("%d, %d\n", i+1 , k+1);
                return 0;
			}
		}

        return 1;
}

int VerAl(EFILE *e, DATASTYLE *data, char **str,  int i){
		int k=0, ver=0;

	
		for(k=0; k<data->nfield; k++){

			if(str[k][0] == EOS || data->alpha[k] == 4)	continue;

			ver = VerAlnum(str[k]);
			if(ver==1 && data->alpha[k]==2){
				Msg(e, 16);
		   		printf("%d, %d\n", i+1 , k+1);
                return 0;
			}

			if(ver==2 && data->alpha[k]==1){
				Msg(e, 16);
				printf("%d, %d\n", i+1 , k+1);
                return 0;
			}
			
			if(ver==0 && data->alpha[k]!=0){
				Msg(e, 16);
				printf("%d, %d\n", i+1 , k+1);
                return 0;
			}
			if(ver==3 && data->alpha[k]!=3){
				Msg(e, 16);
				printf("%d, %d\n", i+1 , k+1);
                return 0;
			}
         
		}

        return 1;
}

int Fixtovar(EFILE *e, FILE *fi, FILE *fo1, DATASTYLE *data){
	char **str = NULL;
	int i = 0;
	for(i=0; ; i++){
		if(!ReadRegFix3(fi, &str, data->efield, data->nfield)) break;
		if(!VerOb1(e, data, str, i)){
		    FreeT(str, data->nfield);
            return 0;
        }
		if(!VerAl(e, data, str, i)){
             FreeT(str, data->nfield);
            return 0;
        }

		if(str[0][0] == 's'){
			PrintAll(fo1,PRINT_TAM,&str,1,data->nfield);	
		}
		FreeT(str, data->nfield);
	}

	return 1;
}

void PrintOne(DATASTYLE *data, char **str, int first){
	int i=0;
	for(i=first; i<data->nfield -1 ; i++){
		printf("%s = %s |", data->fieldname[i], str[i]);
	}
	printf("%s = %s\n", data->fieldname[i], str[i]);
}

int  Option1(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	char out[TAMS];
	FILE *fi, *fo1;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return 1;
	}

	Msg( e, 10);
	scanf("%s", out);
	fo1 = fopen(out, "w");
	if(fo1==NULL){
		Msg( e, 11);
		fclose(fi);
		return 1;
	}

	//-----------------
	if(!Fixtovar(e, fi, fo1, data)){
		fclose(fi);
		fclose(fo1);
		return 0;
	}

	fclose(fi);
	fclose(fo1);

    return 1;
}

void Printfix(EFILE *e, FILE *fi, DATASTYLE *data){
	char **str = NULL;

	while(1){
		if(!ReadRegFix3(fi, &str, data->efield, data->nfield)) break;
		
		
		if(str[0][0] != 'n'){
			//------
			PrintOne(data, str, 1);
		}
		FreeT(str, data->nfield);
	}

}

void Option2(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	FILE *fi;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}
//----------------

	Printfix(e, fi, data);

	fclose(fi);

}

void Printvar(EFILE *e, FILE *fi, DATASTYLE *data){
	char **str = NULL;
	
	int i=0;
    long int start=0, end=0, bytes=0;
    long int posi=0, posf=0;
    int len=0;

	while(1){
		if(!(start=ReadRegVar(fi, &str, data->nfield))) break;
        start = start-1; //Pois a função acima detorna a posição mais 1
        end = ftell(fi); //cursor posicionado no final do registro depois do /n
        end=end-2;
        bytes = end - start + 1;

        posi = posi + start + 3;
		if(str[0][0] == 's'){

            Msg(e, 17);
            printf("*****(%ld-%ld|%ld bytes) => ", start, end, bytes);
			for(i=0; i<data->nfield -1 ; i++){
                len = strlen(str[i]);
                posf = posi + len-1;
				printf("%s = %s (%ld-%ld|%d bytes)|", data->fieldname[i], str[i],posi, posf, len);
                posi = posf+3;
			}

            len = strlen(str[i]);
            posf = posi + len -1;
			printf("%s = %s (%ld-%ld|%d bytes)\n", data->fieldname[i], str[i], posi, posf, len);
		}

		FreeT(str, data->nfield);
	}

}


void Option3(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	FILE *fi;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}

	//------------
	Printvar(e, fi, data);

	fclose(fi);
}


void SearchandPrint(EFILE *e, FILE *fi, DATASTYLE *data, char *key){
	char **str;


	if(SearchKeyVar(fi, key,data->nfield)){
		if(!ReadRegVar(fi, &str, data->nfield)){
			Msg(e, 14);
			return;
		}
		//----
		PrintOne(data, str, 1);		
		FreeT(str, data->nfield);
	}
	else Msg( e, 15);
}

void Option4(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	FILE *fi;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}
	
//----------------
	char key[TAMS];
	Msg( e, 13);
	scanf("%s", key);
	SearchandPrint(e, fi, data, key);
	
	fclose(fi);
}

DATASTYLE *WriteIndData(EFILE *e, DATASTYLE *data){
	FILE *find = fopen(DATAIND, "w");
//	char **names = {NAME1, NAME2, NAME3};
	if(find == NULL){
		Msg( e, 11);
		return NULL;
	}

	DATASTYLE *dataind = InitDatastyle();

	fprintf(find, "%d\n", TAMIND);
	dataind->nfield = TAMIND;
	fprintf(find, "%d %d %d\n", data->efield[1], sizeof(long int), data->efield[data->nfield-1]);

	dataind->efield = (int*) malloc(sizeof(int) * TAMIND);

	dataind->efield[0] = data->efield[1];
	dataind->efield[1] = sizeof(long int);
	dataind->efield[2] = data->efield[data->nfield-1];

	FILE* fn = fopen(DATAINDN, "r");
	if(fn==NULL){
		Msg( e, 30);
		fclose(find);
		return NULL;
	}
	MakeDataS(fn, &(dataind->fieldname), dataind->nfield);
	fclose(fn);
	

	fclose(find);
	
	return dataind;
}

int MakeOneInd(EFILE *e, FILE *fi, FILE *fo1, DATASTYLE *data){
	long int start;
	char **vet;

	if((start=ReadRegVar(fi,&vet,data->nfield))){
		if(vet[0][0]=='s'){
			fprintf(fo1,"%s ",vet[1]);
			start = start-1;
			//fprintf(fo1,"%ld\n",start);
			fwrite(&(start), sizeof(long int), 1, fo1);
			fprintf(fo1, "%c\n", vet[data->nfield-1][0]);
		}

		FreeT(vet,data->nfield);
	return 1;
	}
	return 0;
}


void MakeInd(EFILE *e, FILE *fi, FILE *fo1, DATASTYLE *data){

	while(MakeOneInd(e, fi, fo1, data));
	
}

DATASTYLE *Option6(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	char out[TAMS];
	FILE *fi, *fo1;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return NULL;
	}

	Msg( e, 10);
	scanf("%s", out);
	fo1 = fopen(out, "w");
	if(fo1==NULL){
		Msg( e, 11);
		fclose(fi);
		return NULL;
	}

	//-----------------
	
	MakeInd(e, fi, fo1, data);
	
	fclose(fi);
	fclose(fo1);

	DATASTYLE *dataind = NULL;
	dataind = WriteIndData(e, data);

	if( dataind == NULL){
		Msg( e, 18);
		return NULL;
	}

	return dataind;
}

void Ordena(char *in, char *out){
	char sys[TMS];

	if(strcmp(in,out)!=0){
		sprintf(sys, "sort -d %s > %s", in, out);
		system(sys);
	}

	else{
		sprintf(sys, "sort -d %s > temp.txt", in);
		system(sys);
		sprintf(sys, "mv temp.txt %s", in);
		system(sys);
	}
	
}


char* VerificaRepitidoOrdenado(FILE *f){
	char vet1[TAMS]="chuchu", vet2[TAMS]="brogis";
	char *ret=NULL;
	while(!feof(f)){
		if(fread(vet1,sizeof(char),6,f)<6) break;
		if(!strcmp(vet1,vet2)){
			ret=strdup(vet1);
			break;
		}
		if(fseek(f,sizeof(long int)+3,SEEK_CUR)) break;
		if(fread(vet2,sizeof(char),6,f)<6) break;
		if(!strcmp(vet1,vet2)){
			ret=strdup(vet1);
			break;
		}
		fseek(f,sizeof(long int)+3,SEEK_CUR);
	}
	return ret;
}

void Option7(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	char out[TAMS];

	Msg( e, 9);
	scanf("%s", in);

	Msg( e, 10);
	scanf("%s", out);

	//-----------

	Ordena(in, out);

	FILE *f=fopen(out,"r");
	char *ret=VerificaRepitidoOrdenado(f);
	if(ret!=NULL){
		Msg(e,31);
		printf("%s\n",ret);
		free(ret);
	}
	fclose(f);

}


int PrintOneInd(EFILE *e, FILE *fi,  DATASTYLE *data){
	char **str = NULL;
	int i = 0;
	long int *ld = NULL;

		if(!ReadRegFix2(fi, &str, data->efield, data->nfield)) return 0;
		
		
		for(i=0; i<data->nfield -1 ; i++){
			if(i==1){
				ld=(long int*)str[i];
//				fread(ld,sizeof(long int),1,str[1]);
				printf("%s = %ld |", data->fieldname[i], (*ld));
			}
			else printf("%s = %s |", data->fieldname[i], str[i]);
		}
		printf("%s = %s\n", data->fieldname[i], str[i]);
		
		FreeT(str, data->nfield);
		return 1;
}

	


void PrintInd(EFILE *e, FILE *fi, DATASTYLE *data){
	while(PrintOneInd(e, fi, data));
	
}

//Já supondo que dataind != null
void Option8(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	FILE *fi;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}
	//-------
	PrintInd(e, fi,data);

	fclose(fi);

	
}
void Option9(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	FILE *fi;

	Msg( e, 9);
	scanf("%s", in);
	Ordena(in,in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}

	PrintInd(e, fi, data);
	
	fclose(fi);
}

DATASTYLE *Option10(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	char out[TAMS];
	FILE *fi, *fo1;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return NULL;
	}

	Msg( e, 10);
	scanf("%s", out);
	fo1 = fopen(out, "w");
	if(fo1==NULL){
		Msg( e, 11);
		fclose(fi);
		return NULL;
	}

	//-----------------

	MakeInd(e, fi, fo1, data);

	fclose(fi);
	fclose(fo1);

	DATASTYLE *dataind = NULL;
	dataind = WriteIndData(e, data);

	if( dataind == NULL){
		Msg( e, 18);
		return NULL;
	}

	Ordena(out, out);
	return dataind;

}






/******************

void Option11(EFILE *e, DATASTYLE *search, DATASTYLE *find){
	char sname[TAMS], fname[TAMS], key[TMS];
	FILE *sf, *ff;
	int i;

	Msg(e,20);
	scanf("%s",sname);
	sf=fopen(sname,"r");
	if(sf==NULL){
		Msg(e,11);
		return;
	}
	Msg(e,21);
	scanf("%s",fname);
	ff=fopen(fname,"r");
	if(ff==NULL){
		fclose(sf);
		Msg(e,11);
		return;
	}
	Msg(e,13);
	scanf("%s",key);

	i=BinaryKeySearch(sf,ff,search,find,key);
	if(!i){
		Msg(e,15);
	}
	fclose(sf);
	fclose(ff);
}


void Option12(EFILE *e, DATASTYLE *config){
	char fname[TAMS], key[TMS];
	int i;

	Msg(e,9);
	scanf("%s",fname);
	FILE *f=fopen(fname,"r+");
	if(f==NULL){
		Msg(e,11);
		return;
	}
	
	Msg(e,22);
	scanf("%s",key);

	i=EraseReg(f,key,config->nfield);
	if(i){
		Msg(e,23);
	}
	else{
		Msg(e,15);
	}
	fclose(f);
}

******************/



void Option11(EFILE *e, DATASTYLE *search, DATASTYLE *find){
	char sname[TAMS], fname[TAMS], key[TMS];
	FILE *sf, *ff;
	int i;
	char **rregister;

	Msg(e,20);
	scanf("%s",sname);
	sf=fopen(sname,"r");
	if(sf==NULL){
		Msg(e,11);
		return;
	}
	Msg(e,21);
	scanf("%s",fname);
	ff=fopen(fname,"r");
	if(ff==NULL){
		fclose(sf);
		Msg(e,11);
		return;
	}
	Msg(e,13);
	scanf("%s",key);

	i=BinaryKeySearch(sf,ff,search,find,key);
	if(!i){
		Msg(e,15);
	}
	
			ReadRegVar(ff,&rregister,find->nfield);
			if(rregister[0][0]=='s'){
				PrintOne(find,rregister,1);
				
			}

			if(rregister[0][0]=='n'){
					
				Msg(e,15);
			}
			FreeT(rregister,find->nfield);	

	fclose(sf);
	fclose(ff);
}


void Option12(EFILE *e, DATASTYLE *search, DATASTYLE *find){
	char sname[TAMS], fname[TAMS], *key=(char*)malloc(sizeof(char)*50);
	FILE *sf, *ff;
	int i;

	Msg(e,20);
	scanf("%s",sname);
	sf=fopen(sname,"r");
	if(sf==NULL){
		Msg(e,11);
		free(key);
		return;
	}
	Msg(e,21);
	scanf("%s",fname);
	ff=fopen(fname,"r+");
	if(ff==NULL){
		fclose(sf);
		Msg(e,11);
		free(key);
		return;
	}
	Msg(e,13);
	scanf("%s",key);



	i=EraseReg(sf,ff,search,find,key);
	if(i){
		Msg(e,23);
	}
	else{
		Msg(e,15);
	}
	
	free(key);
	fclose(sf);
	fclose(ff);
}





