#ifndef LIB_WORD
#define LIB_WORD

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define SPACE ' '
#define EOS '\0' /* End Of Sentence  */

/*Definicao de palavra: Todo agrupamento formado por caracteres alfanumericos*/

/*Estrutura para guardar a palavra e o numero de vezes em que ela aparece no texto*/
typedef struct node{
    char *word;
    int count;
    struct node *left;
    struct node *right;
} node;


/**********CONTADORES*****************/

/*Retorna o numero de vezes em que o caractere c aparece em str*/
int CountChrStr(char* str, char c);

/*Retorna o numero de vezes em que o caractere c aparece na matriz table de strings. nword e a quantidade de palavras presentes na tabela*/
int CountChrTable(char** table, int nwords, char c);

/*Retorna o numero de vezes que a palavra word repete na tabela de palavras table. words é o numero de palavras da tabela*/
int FindWord(char **table, int words, char *word);

/*Conta strings em str, considerando os separadores em accept
 * Ex: str = "Bolo#De #Chocolate Congelado@"  divider = "#@"   
 * o valor retornado é 3 strings entre separadores*/
int StrCount(char* str, char* divider);

/*Retorna o numero de palavras alfanuméricos em str*/
int WordCount(char *str);

/*******FIM DE CONTADORES*************/


/******GERADORES DE NOVAS STRINGS********/

/*Substitui caracteres em remove por espacos. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes,
 * ou se não houver, retorna uma cópia de str. Retorna NULL se houver falta de memória, ou se foi passado str NULL*/
char* Cleaner(char *str, char *remove);

/*Substitui muitos espacos seguidos por apenas 1. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes
 * ou uma cópia de str se não houver modificações. Retorna NULL se houver falta de memória*/
char* Corrector(char *str);

/*  Applies in all strins in the list strList with len strings the function 
 *Corrector described above
 *
 *  Returns a new list, does not modified the original one
 *  If it failed, it returns NULL 
 *  
 * */
char **CorrectorList(char **strList, int len);


/*Devolve uma cópia da string str cortada até o primeiro caractere que se encontra no divider
  Ex: str = "Bolo#de cholocate#@" divider = "#@"    devolverá a string "Bolo". Se um dos caracteres
  de divider se encontrar na primeira posição, retorna NULL, e se não houver um dos caracteres
  retorna uma cópia de str */
char* CutStr(char* str, char* divider);

/*Fills the string str with the character c until str to complete len characteres
 *
 * Returns a new string, it does not modify the original one
 * If it failed in the memory allocation,  returns NULL
 * If len will be lesser or equal str, returns a copy of str
 * */
char* FillStr(char *str, char c, int len);

/*Devolve uma cópia da primeira string que aparecer em str limitado pelo caractere em divider,
 pulando os primeiros caracteres:             OBS: Não modifica a string original.
 str= “,*Cama e + Banho.” e divider=”, +*.” (o branco está depois da virgula) a rotina deve
 retornar “Cama */
char* FirstStr(char* str, char* divider);

/*Faz a mesma coisa que FirstStr só que leng é o índice onde se inicia srt e soma com o número de caracteres que ele andou em str.
 * leng = 0, str= “,*Cama e + Banho.” e divider=”, +*.” (o branco está depois da virgula) a rotina deve retornar “Cama" e leng = leng + 6
 * Na próxima chamada da função, len = 6, str = *“,*Cama e + Banho.”, e divider=”, +*.”, como leng inicialmente vale 6, a palavra que ele
 * irá retornar é "e" e leng = leng + 1.*/
char* FirstStrL(char* str, char* divider, int* leng);

/*Transforma todas as letras minusculas existentes em uma string em maiusculas. Nao modifica a string str. Retorna um ponteiro de uma nova string.
 * Retorna NULL se erro de memória*/
char* Shifter(char *str);

/*******FIM DOS GERADORES DE STRING******/


/*******GERADORES DE TABELA DE STRING****/

/*Coloca cada pedaço de str em uma matriz retornada, os caracteres em divider são considerados separadores
 e nword sai da função com o número de strings na tabela. Se str for passado NULL, nword sai igual a 0 e table
 igual a NULL. Retorna NULL se houver erro de memória*/
char** Divider2(char* str, char* divider, int* nword);

/*Similar a Divider, só que considera como divisor tudo o que não é alfanumérico*/
char** DividerW(char *str, int *words);

/******FIM DOS GERADORES DE STRING******/


/*****MANIPULADORES DE STRUCTURE********/

/*Insere a palavra word na arvore n*/
void InsertNode(node **n, char *word);

/*Cria um nó com uma copia de word e com count 1, se houver algum erro de memória
 * libera o que foi alocado e retorna NULL*/
node* NewNode(char *word);

/*****FIM DOS MANIPULADORES DE STRUCTURE******/


/***IMPRESSORES***/

/*Imprime a arvore n na tela*/
void PrintNode(node *n);

/*Imprime a arvore n em um arquivo*/
void PrintNodeF(node *n, FILE* f);

/*Imprime uma tabela de strings (table) sendo len o número de strings que ela contém*/
void PrintTable(char** table, int len);

/****FIM DOS IMPRESSORES****/


/****LIBERADORES****/

/*Libera tabela de string criada no divider, recebendo o apontador table pra tabela e o numero de palavras que ela contem nword*/
void FreeT(char** table, int nword);

/*Libera uma matriz de tabela de string
 * Recebe a matriz table, a quantidade de listas de strings nregis e a quantidade
 * de strings em cada lista nword*/
void FreeTT(char ***table, int nregis, int nword);

/*Libera uma árvore com nodes do tipo structure node*/
void FreeTr(node* tree);

/****FIM DOS LIBERADORES****/




#endif /*LIB_WORD*/
