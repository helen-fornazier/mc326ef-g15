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

void Option1(EFILE *e, DATASTYLE *data){  //TEM UM MAIS OTIMIZADO NO MEU TESTE ..
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

	REGIS matrix;
	int i=5, j=0;
	int n1=0, n2=0;
	
	while(i==5){
		i=ReadRegFix(fi,&matrix,data->efield,data->nfield,5);
		        
		VerOb(e, data, matrix, i, j);
      		
		j+=i;
//		n1+=PrintAll(fo1,PRINT_DIV,matrix,i,data->nfield);
		n2+=PrintAll(fo1,PRINT_TAM,matrix,i,data->nfield);

        FreeTT(matrix, i, data->nfield); 
	}
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
		for(i=0; i<data->nfield -1 ; i++){
			printf("%s = %s |", data->fieldname[i], str[i]);
		}
		printf("%s = %s\n", data->fieldname[i], str[i]);
		free(str);
	}
}



void Option3(){}
void Option4(){}
void Option6(){}
void Option7(){}
void Option8(){}
void Option9(){}
void Option10(){}
void Option11(){}
void Option12(){}

int main(int argc, char *argv[]){
	EFILE *e;
	int op=1;

	if(argc == 2)	e = MakeMsg(argv[1]);	
	else	e = MakeMsg(IDIOM);

	FILE *fd = fopen(DATA, "r");		//file of configuration
	DATASTYLE *data = FillData(fd);		//liberar no final

	PrintMenu(e);

	while(op!=0){
		Msg( e, 8);
		scanf("%d", &op);
	
		switch(op){
		case 1:
			Option1(e, data);	break;
		case 2:
			Option2(e, data);	break;
		case 3:
			Option3();	break;
		case 4:
			Option4();	break;
		case 6:
			Option6();	break;
		case 7:
			Option7();	break;
		case 13:
			op = 0;		break;
		default:
			Msg(e, 7);
		}
	}



	CloseMsg(e);
	return 0;
}
