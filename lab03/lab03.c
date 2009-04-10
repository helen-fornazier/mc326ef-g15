/*Colocar o programa*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"LibWord.h"
#include"LibFile.h"
#include"LibMsg.h"

#define IDIOM "english.config"

void PrintMenu(){
	printf("Opcão 1:  Conversão do arquivo de formato fixo para formato variável\n");	
	printf("Opcão 2:  Listar o arquivo de dados no formato fixo\n");	
	printf("Opcão 3:  Listar o arquivo de dados no formato variável\n");	
	printf("Opcão 4:  Pesquisa de um determinado registro pela chave primária\n");	
	printf("Opcão 6:  Extração das chaves\n");	
	printf("Opcão 7:  Classificação do arquivo  das chaves\n");	
	printf("\n");	
}

int main(int argc, char *argv[]){
	//PrintMenu();
	EFILE *e;
	e = MakeMsg(IDIOM);
	Msg(e, 12);
	CloseMsg(e);

	return 0;
}
