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




/*Substitui caracteres em remove por espacos. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes*/
char* Cleaner(char *str, char *remove);

/*Substitui muitos espacos seguidos por apenas 1. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes*/
char* Corrector(char *str);

/*Transforma todas as letras minusculas existentes em uma string em maiusculas. Nao modifica a string str. Retorna um ponteiro de uma nova string.*/
char* Shifter(char *str);

/*Retorna o numero de palavras em str*/
int WordCount(char *str);

/*Conta strings em str, considerando os separadores em divider
 * Ex: str = "@#@Bolo#De #Chocolate Congelado@"  accept = "#@"    
 * o valor retornado é 3 strings entre separadores*/
int StrCount(char* str, char* divider);

/*Coloca cada palavra da string str em uma posicao diferente da tabela.No final da funcao words recebe o numero de palavras na tabela. Nao modifica a string str. Retorna o apontador da matriz de palavras*/
char** Divider(char *str, int *words, char *divider);

/*Coloca cada pedaço de str em uma matriz retornada, os caracteres em divider são considerados separadores
 e nword sai da função com o número de strings na tabela*/
char** Divider2(char* str, char* divider, int* nword);

/*Retorna o numero de vezes em que o caractere c aparece em str*/
int CountChrStr(char* str, char c);

/*Retorna o numero de vezes em que o caractere c aparece na matriz table de strings. nword e a quantidade de palavras presentes na tabela*/
int CountChrTable(char** table, int nwords, char c);

/*Retorna o numero de vezes que a palavra word repete na tabela de palavras table. words e o numero de palavras da tabela*/
int FindWord(char **table, int words, char *word);

/*Cria um no com uma copia de word e com count 1*/
node* NewNode(char *word);

/*Insere a palavra word na arvore n*/
void InsertNode(node **n, char *word);

/*Imprime a arvore n na tela*/
void PrintNode(node *n);

/*Imprime a arvore n em um arquivo*/
void PrintNodeF(node *n, FILE* f);

/*Imprime uma tabela de strings (table) sendo len o número de strings que ela contém*/
void PrintTable(char** table, int len);

/*Libera tabela de string criada no divider, recebendo o apontador table pra tabela e o numero de palavras que ela contem nword*/
void FreeT(char** table, int nword);

/*Libera uma árvore com nodes do tipo structure node*/
void FreeTr(node* tree);

/*Devolve uma cópia da string str cortada até o primeiro caractere que se encontra no divider
  Ex: str = "Bolo#de cholocate#@" divider = "#@"    devolverá a string "Bolo". Se um dos caracteres
  de divider se encontrar na primeira posição, retorna NULL, e se não houver um dos caracteres
  retorna uma cópia de str */
char* CutStr(char* str, char* divider);

/*Devolve uma cópia da primeira string que aparecer em str limitado pelo caractere em divider,
 pulando os primeiros caracteres:             OBS: Não modifica a string original.
 texto= “,*Cama e + Banho.” e SEP=”, +*.” (o branco está depois da virgula) a rotina deve
 retornar “Cama */
char* FirstStr(char* str, char* divider);

/*Similar a FirstStr, só que modifica a string str com o resto da string
  Ex: str = "BOLO# DE CHOCOLATE"  divider = "#" a função deve retornar "BOLO"
   e str deve ser modificado para "# DE CHOCOLATE"*/
char *FirstStrM(char **str, char *divider);   //NÃO ESTÁ MODIFICANDO str ..  VER O CÓDIGO DE NOVO
