#ifndef LIB_MSG
#define LIB_MSG

/****ABERTURA DOS ARQUIVOS DE MENSAGEM****/


char **msg; //where will be placed all messages from the program

/*abre o arquivo de mensagens fname e coloca na memória
 * se não conseguiu abrir, ou se houve falta de memória, retorna 1. Se não, retorna 0*/
int MakeMsg(char *fname);

/* imprime a mensagem de número n no arquivo de mensagens carregada por MakeMsg*/
void Msg(int n);

/****FIM DOS MANIPULADORES DOS ARQUIVOS DE MENSAGENS****/

#endif /*LIB_MSG*/
