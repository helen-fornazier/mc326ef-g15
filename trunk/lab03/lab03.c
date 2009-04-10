/*Colocar o programa*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"LibWord.h"
#include"LibFile.h"
#include"LibMsg.h"

#define IDIOM "portugues.config" //MUDAR

void PrintMenu(EFILE *e){
	Msg( e, 0);
	Msg( e, 1);
	Msg( e, 2);
	Msg( e, 3);
	Msg( e, 4);
	Msg( e, 5);
	Msg( e, 6);
	}

void Option1(){}
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
	int op=1;

	if(argc == 2)	e = MakeMsg(argv[1]);	
	else	e = MakeMsg(IDIOM);

	PrintMenu(e);

	while(op!=0){
		Msg( e, 8);
		scanf("%d", &op);
	
		switch(op){
		case 1:
			Option1();	break;
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
