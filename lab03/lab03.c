#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"LibWord.h"
#include"LibFile.h"
#include"LibMsg.h"
#include"LibOption.h"

#define IDIOM "english.config"
#define DATA "data.config"

int main(int argc, char *argv[]){
	EFILE *e;
	if(argc == 2)	e = MakeMsg(argv[1]);	
	else	e = MakeMsg(IDIOM);

	int op=1;

	FILE *f = fopen(DATA, "r");		//file of configuration
	
	DATASTYLE *data = FillData(f);
	fclose(f);


	PrintMenu(e);

	while(op!=0){
		printf("\n");
		Msg( e, 8);
		scanf("%d", &op);
	
		switch(op){
		case 1:
			if(!Option1(e, data))   op=0;	
            break;
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
