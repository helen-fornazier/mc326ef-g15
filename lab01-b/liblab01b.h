#define SPACE ' '
#define EOS '\0' /* End Of Sentence  */

/*Definicao de palavra: Todo agrupamento formado por caracteres alfanumericos*/


/*Substitui caracteres nao alfanumericos por espacos. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes*/
char* Cleaner(char *str);

/*Substitui muitos espacos seguidos por apenas 1. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes*/
char* Corrector(char *str);

/*Transforma todas as letras minusculas existentes em uma string em maiusculas. Nao modifica a string str. Retorna um ponteiro de uma nova string.*/
char* Shifter(char *str);

/*Retorna o numero de palavras em str*/
int WordCount(char *str);

/*Coloca cada palavra da string str em uma posicao diferente da tabela.No final da funcao words recebe o numero de palavras na tabela. Nao modifica a string str. Retorna o apontador da matriz de palavras*/
char** Divider(char *str, int *words);

/*Retorna o numero de vezes em que o caractere c aparece em str*/
int CountChrStr(char* str, char c);

/*Retorna o numero de vezes em que o caractere c aparece na matriz table de strings. nword e a quantidade de palavras presentes na tabela*/
int CountChrTable(char** table, int nwords, char c);

/*Retorna o numero de vezes que a palavra word repete na tabela de palavras table. words e o numero de palavras da tabela*/
int FindWord(char **table, int words, char *word);

/*Estrutura para guardar a palavra e o numero de vezes em que ela aparece no texto*/
typedef struct node{
    char *word;
    int count;
    struct node *left;
    struct node *right;
} node;

/*Cria um no com uma copia de word e com count 1*/
node* NewNode(char *word);

/*Insere a palavra word na arvore n*/
void InsertNode(node **n, char *word);

/*Imprime a arvore n na tela*/
void PrintNode(node *n);

/*Imprime a arvore n em um arquivo*/
void PrintNodeF(node *n, FILE* f);

/*Libera tabela de string criada no divider, recebendo o apontador table pra tabela e o numero de palavras que ela contem nword*/
void FreeT(char** table, int nword);

/*Libera uma árvore com nodes do tipo structure node*/
void FreeTr(node* tree);

/*Conta strings em str, considerando os separadores em accept
 * Ex: str = "@#@Bolo#De #Chocolate Congelado@"  accept = "#@"    
 * o valor retornado é 3 strings entre separadores*/
int CountStrStr(char* str, char* accept);
