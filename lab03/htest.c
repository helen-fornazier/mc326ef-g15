/*Colocar o programa*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"LibWord.h"
#include"LibFile.h"
#include"LibMsg.h"

#define IDIOM "portugues.config" //MUDAR
#define DATA "data.config"

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
			}
		}
	}
}

/*Verifica a obrigatoriedade de um registro*/
void VerOb1(EFILE *e, DATASTYLE *data, char **str,  int i){
		int k=0;
	
		for(k=0; k<data->nfield; k++){

			if((data->ob[k] == 1) && (str[k][0] == EOS)){
				Msg(e, 12);
				printf("%d, %d\n", i+1 , k+1);
			}
		}
}





void Option1(EFILE *e, DATASTYLE *data){
	char in[100];
	char out[100];
	FILE *fi, *fo1;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}

	Msg( e, 10);
	scanf("%s", out);
	fo1 = fopen(out, "w");
	if(fo1==NULL){
		Msg( e, 11);
		fclose(fi);
		return;
	}

	//-----------------
	
	
	char **str = NULL;
	int i = 0;
	for(i=0; ; i++){
		if(!ReadRegFix3(fi, &str, data->efield, data->nfield)) break;
		VerOb1(e, data, str, i);
		if(str[0][0] == 's'){
			PrintAll(fo1,PRINT_TAM,&str,1,data->nfield);	
		}
		FreeT(str, data->nfield);
	}

	fclose(fi);
	fclose(fo1);
}


void Option2(EFILE *e, DATASTYLE *data){
	char in[100];
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
		if(!ReadRegFix2(fi, &str, data->efield, data->nfield)) break;
		
		if(str[0][0] == 's'){
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
	char in[100];
	FILE *fi;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}

	char **str = NULL;
	
//	ReadRegVar(fi, &str, data->nfield);
	int i=0;
	while(1){
		if(!ReadRegVar(fi, &str, data->nfield)) break;

		if(str[0][0] == 's'){
			for(i=1; i<data->nfield -1 ; i++){
				printf("%s = %s |", data->fieldname[i], str[i]);
			}
			printf("%s = %s\n", data->fieldname[i], str[i]);
		}

		FreeT(str, data->nfield);
	}
	fclose(fi);
}

void Option4(EFILE *e, DATASTYLE *data){
	char in[100];
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
	char key[100];
	Msg( e, 13);
	scanf("%s", key);


	if(SearchKeyVar(fi, key)){
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

void Option6(EFILE *e, DATASTYLE *data){
	char in[100];
	char out[100];
	FILE *fi, *fo1;

	Msg( e, 9);
	scanf("%s", in);
	fi = fopen(in, "r");
	if(fi == NULL){
		Msg(e, 11);
		return;
	}

	Msg( e, 10);
	scanf("%s", out);
	fo1 = fopen(out, "w");
	if(fo1==NULL){
		Msg( e, 11);
		fclose(fi);
		return;
	}

	//-----------------

	long int addres = 0;
	char *str = NULL;
	char *ex = NULL;
	int tam=0, n=0;
	int tam2=0;


	
	while(1){

		addres = ftell(fi);

		if(!SetCursesC( fi, '<', 1)){
			fclose(fi);
			fclose(fo1);
			return;
		}
		fscanf(fi, "%d", &tam);
	
		if(!SetCursesC( fi, '<', 1)){
			fclose(fi);
			fclose(fo1);
			return;
		}
		fscanf(fi, "%d", &n);

		if(!SetCursesC( fi, '>', 1)){
			fclose(fi);
			fclose(fo1);
			return;
		}
 

		ReadStr(fi, &(ex), tam-2);

		if(!SetCursesC( fi, '<', 1)){
			free(ex);
			fclose(fi);
			fclose(fo1);
			return;
		}
 
		fscanf(fi, "%d", &tam2);
	
		if(!SetCursesC( fi, '<', 1)){
			free(ex);
			fclose(fi);
			fclose(fo1);
			return;
		}
 
		fscanf(fi, "%d", &n);

		if(!SetCursesC( fi, '>', 1)){
			free(ex);
			fclose(fi);
			fclose(fo1);
			return;
		}
 

		ReadStr(fi, &(str), tam2-2);
		
		if(ex[0] == 's'){
			fprintf(fo1, "%s ", str);
			fprintf(fo1, "%ld\n", addres);

		}
		

		free(ex);
		free(str);

		if(!SetCursesC( fi, '\n', 1)){
			fclose(fi);
			fclose(fo1);
			return;
		}
 

	}

	fclose(fi);
	fclose(fo1);

}

void Option7(EFILE *e, DATASTYLE *data){
	char in[100];
	char out[100];
	char sys[30];

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


void Option8(){}
void Option9(){}
void Option10(){}
void Option11(){}
void Option12(){}


int main(int argc, char *argv[]){
	EFILE *e;
	if(argc == 2)	e = MakeMsg(argv[1]);	
	else	e = MakeMsg(IDIOM);

	int op=1;

	FILE *f = fopen(DATA, "r");		//file of configuration
	
	DATASTYLE *data = FillData(f);
	fclose(f);

	printf("NFIELDS %d\n", data->nfield);



	PrintMenu(e);

	while(op!=0){
		printf("\n");
		Msg( e, 8);
		scanf("%d", &op);
	
		switch(op){
		case 1:
			Option1(e, data);	break;
		case 2:
			Option2(e, data);	break;
		case 3:
			Option3(e, data);	break;
		case 4:
			Option4(e, data);	break;
		case 6:
			Option6(e, data);	break;
		case 7:
			Option7(e, data);	break;
		case 13:
			op = 0;		break;
		default:
			Msg(e, 7);
		}
	}


	CloseDatastyle(data);
	CloseMsg(e);

	return 0;
}
