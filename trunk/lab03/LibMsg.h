#ifndef LIB_MSG
#define LIB_MSG

/****ABERTURA DOS ARQUIVOS DE MENSAGEM****/

#include"LibWord.h"

typedef struct error{
	char **msg;
	int n;
} EFILE;


//char **msg; //where will be placed all messages from the program

/*abre o arquivo de mensagens fname e coloca na memória
 * se não conseguiu abrir, ou se houve falta de memória, retorna NULL. Se não,
 * retorna um apontador para a struct EFILE*/
EFILE* MakeMsg(char *fname);

/* imprime a mensagem de número n no arquivo de mensagens carregada na struct e
 * retornada por MakeMsg*/
void Msg(EFILE* e, int n);

/*Libera e*/
void CloseMsg(EFILE *e);
/****FIM DOS MANIPULADORES DOS ARQUIVOS DE MENSAGENS****/

#endif /*LIB_MSG*/
