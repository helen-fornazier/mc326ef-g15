#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"LibWord.h"
#include"LibFile.h"
#include"LibMsg.h"
#include "LibOption.h"

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
	
	
	char **str = NULL;
	int i = 0;
	for(i=0; ; i++){
		if(!ReadRegFix3(fi, &str, data->efield, data->nfield)) break;
		if(!VerOb1(e, data, str, i)){
		    FreeT(str, data->nfield);
	        fclose(fi);
	        fclose(fo1);
            return 0;
        }
		if(!VerAl(e, data, str, i)){
             FreeT(str, data->nfield);
	        fclose(fi);
	        fclose(fo1);
            return 0;
        }

		if(str[0][0] == 's'){
			PrintAll(fo1,PRINT_TAM,&str,1,data->nfield);	
		}
		FreeT(str, data->nfield);
	}

	fclose(fi);
	fclose(fo1);

    return 1;
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

	char **str = NULL;
	int i = 0;

	while(1){
		if(!ReadRegFix3(fi, &str, data->efield, data->nfield)) break;
		
		
		if(str[0][0] != 'n'){
			for(i=1; i<data->nfield -1 ; i++){
				printf("%s = %s |", data->fieldname[i], str[i]);
			}
			printf("%s = %s\n", data->fieldname[i], str[i]);
		}
		FreeT(str, data->nfield);
	}
	
	fclose(fi);

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
	fclose(fi);
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
	
	int i=0;
	char **str;
	char key[TAMS];
	Msg( e, 13);
	scanf("%s", key);


	if(SearchKeyVar(fi, key,data->nfield)){
		if(!ReadRegVar(fi, &str, data->nfield)){
			Msg(e, 14);
			return;
		}
		
		for(i=1; i<data->nfield -1 ; i++){
			printf("%s = %s |", data->fieldname[i], str[i]);
		}
		printf("%s = %s\n", data->fieldname[i], str[i]);
		FreeT(str, data->nfield);
	}
	else Msg( e, 15);

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
	MakeDataS(fn, &(data->fieldname), data->nfield);
	fclose(fn);
	

	fclose(find);
	
	return dataind;
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
	DATASTYLE *dataind = NULL;
	long int start;
	char **vet;

	while((start=ReadRegVar(fi,&vet,data->nfield))){
		if(vet[0][0]=='s'){
			fprintf(fo1,"%s ",vet[1]);
			start = start-1;
			//fprintf(fo1,"%ld\n",start);
			fwrite(&(start), sizeof(long int), 1, fo1);
			fprintf(fo1, "%c\n", vet[data->nfield-1][0]);
		}
		FreeT(vet,data->nfield);
	}

	fclose(fi);
	fclose(fo1);

	dataind = WriteIndData(e, data);

	if(  dataind == NULL){
		Msg( e, 18);
		return NULL;
	}

	return dataind;
}


void Option7(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	char out[TAMS];
	char sys[TMS];

	Msg( e, 9);
	scanf("%s", in);

	Msg( e, 10);
	scanf("%s", out);

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


//Já supondo que dataind != null
void Option8(EFILE *e, DATASTYLE *data){
	char in[TAMS];
	FILE *fi;
	long int *ld;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}

	char **str = NULL;
	int i = 0;

	while(1){
		if(!ReadRegFix3(fi, &str, data->efield, data->nfield)) break;
		
		
		if(str[0][0] != 'n'){
			for(i=0; i<data->nfield -1 ; i++){
				if(i==1){
					ld=(long int)str[i];
					printf("%s = %ld |", data->fieldname[i], *ld);
				}
				else printf("%s = %s |", data->fieldname[i], str[i]);
			}
			printf("%s = %s\n", data->fieldname[i], str[i]);
		}
		FreeT(str, data->nfield);
	}
	
	fclose(fi);

	
}
void Option9(){}
void Option10(){}
void Option11(){}
void Option12(){}



