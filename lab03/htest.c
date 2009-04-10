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

	//TESTE-----------------
	
	
	char **str = NULL;
	int i = 0;
	for(i=0; ; i++){
		if(!ReadRegFix1(fi, &str, data->efield, data->nfield)) break;
		VerOb1(e, data, str, i);
		PrintAll(fo1,PRINT_TAM,&str,1,data->nfield);	
		free(str);
	}

	//FIM TESTE----------
/*
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
*/

}


void Option2(){}
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
	if(argc == 2)	e = MakeMsg(argv[1]);	
	else	e = MakeMsg(IDIOM);

	int op=1;

	FILE *f = fopen(DATA, "r");		//file of configuration
	
	DATASTYLE *data = FillData(f);

	printf("NFIELDS %d\n", data->nfield);



	PrintMenu(e);

	while(op!=0){
		Msg( e, 8);
		scanf("%d", &op);
	
		switch(op){
		case 1:
			Option1(e, data);	break;
		case 2:
			Option2();	break;
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
