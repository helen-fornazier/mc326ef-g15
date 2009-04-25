#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"LibWord.h"
#include"LibFile.h"
#include"LibMsg.h"
#include"LibOption.h"

#define IDIOM "english.config"
#define DATA "data.config"
#define DATAIND "dataind.config"
#define DATAN "dataindn.config"

int main(int argc, char *argv[]){
	EFILE *e;
	if(argc == 2)	e = MakeMsg(argv[1]);	
	else	e = MakeMsg(IDIOM);

	int op=1;

	FILE *f = fopen(DATA, "r");		//file of configuration
	if(f==NULL){
		Msg( e, 19);
		return 1;
	}

	DATASTYLE *data = FillData(f);
	if(data==NULL){
		Msg( e, 19);
		return 1;
	}
	fclose(f);
	
	DATASTYLE *dataind = NULL;
	FILE *find = fopen(DATAIND, "r");		//file of configuration
	FILE *findn;
	if(find!=NULL){
		dataind = FillData(find);
		findn= fopen(DATAN, "r");
		if(findn!=NULL){
			MakeDataS(findn, &(dataind->fieldname), dataind->nfield);
			fclose(findn);
		}
		else{
			dataind->fieldname = InitRegis(dataind->nfield);
			Msg( e, 19);
		}
		fclose(find);
	}



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
			dataind = Option6(e, data);	break;
		case 7:
			Option7(e, data);	break;
		case 8:
			if(dataind == NULL){
				Msg( e, 19);
				break;
			}
			Option8(e, dataind);
			break;
		case 9:
			if(dataind == NULL){
				Msg( e, 19);
				break;
			}
			Option9(e, dataind);
			break;

		case 10:
			dataind = Option10(e, data);	break;
			
		case 11:
			if(dataind == NULL){
				Msg( e, 19);
				break;
			}
			Option11(e, dataind, data);
			break;

		case 12:
			Option12(e, dataind, data);
			break;
			
		case 13:
			op = 0;		break;
		default:
			Msg(e, 7);	break;
		

		case 14:
			PrintMenu(e);	break;

		}
	}


	if(data!=NULL)	CloseDatastyle(data);
	if(dataind!=NULL)	CloseDatastyle(dataind);
	if(e!=NULL)	CloseMsg(e);

	return 0;
}
