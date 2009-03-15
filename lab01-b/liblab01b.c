#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define SPACE ' '
#define EOS '\0' /* End Of Sentence  */

/*Definicao de palavra: Todo agrupamento formado por caracteres alfanumericos*/

/*Take out signals different from letters or numbers from a string*/
/*Substitui caracteres nao alfanumericos por espacos. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes*/
char* Cleaner(char *str, char *remove){
    char *strout=strdup(str);
    char *temp;
    while(strpbrk(remove,strout)!=NULL){
        temp=strpbrk(remove,strout);
        *temp=SPACE;
    }
    return strout;
}

/*Take out double spacements betwen words in a string*/
/*Substitui muitos espacos seguidos por apenas 1. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes*/
char* Corrector(char *str){
    int i, spaces=0;
    for(i=0;str[i]!=EOS;i++) //Conta os espacos sobrando
        if((str[i]==SPACE&&str[i+1]==SPACE) || (str[i]==SPACE&&str[i+1]==EOS)) spaces++;
    if(spaces){ //Se existe espaco sobrando
        char *strout=(char*)malloc(sizeof(char)*(strlen(str)-spaces+1)); //Malloca no tamanho certo, sem os espacos sobrando
        int j=0;
        for(i=0;str[i]!=EOS;i++){
            if(str[i]==SPACE) continue; //Se encontrou um espaco, nao copie, continue
            else{
                strout[j++]=str[i]; //Se nao for espaco, copie
                if(str[i+1]==SPACE) strout[j++]=SPACE; // e se o proximo for espaco, copie o espaco
            }
        }
        if(strout[j-1]==SPACE){ //Se o ultimo caractere for um espaco, transforma este em um EOS.( Nao se perde memoria, pois ao haver
            strout[j-1]=EOS;    //espaco no final, o j eh incrementado )
        }
        else strout[j]=EOS; //Se nao, finaliza 
        return strout;
    }
    else return strdup(str); //Se nao houver espacos sobrando, retorna a duplicata da string passada como parametro
}

/*Shift all small letters*/
/*Transforma todas as letras minusculas existentes em uma string em maiusculas. Nao modifica a string str. Retorna um ponteiro de uma nova string.*/
char* Shifter(char *str){
    int i;
    char *strout=(char*)malloc(sizeof(char)*(strlen(str)+1));
    for(i=0;str[i]!=EOS;i++)
        strout[i]=toupper(str[i]);
    strout[i]=EOS;
    return strout;
}

/*Retorna o numero de palavras em str*/
int WordCount(char *str, char *divider){
    int i, words=0;
    char *temp=str, *temp2=str;
    for(i=0;temp2!=NULL;i++){
        temp2=strpbrk(divider,temp);
        if((temp2-temp)>=sizeof(char)){
            words++;
            temp=temp2+sizeof(char);
        }        
    }
    if(strpbrk(divider,&(str[strlen(str)]))!=NULL) words++;
    return words;
}

char** Divider(char *str, int *words, char *divider){
    int k=0,i;
    char **table, *temp, *temp2;
    temp=str;
    

    *words=WordCount(divider,str);
    table=(char**)malloc(sizeof(char)*(*words));
    while(k<*words){
        temp2=strpbrk(divider,temp);
        if(temp2-temp>=sizeof(char)){
            table[k]=(char*)malloc(temp2-temp+1);
            for(i=0;temp!=temp2;i++){
                table[k][i]=*temp;
                temp+=sizeof(char);
            }
            k++;
        }
        if(temp2==NULL){
            table[k]=strdup(temp);
        }
    }
    return table;
}
/*Retorna o numero de vezes em que o caractere c aparece em str*/
int CountChrStr(char* str, char c){
    int total=0;
    char* position = memchr(str,c,sizeof(char)*strlen(str));
    while(position!=NULL){
        total++;
        position = memchr(&(position[1]),c,sizeof(char)*(strlen(position)-1));
    }
    return total;
}

/*Retorna o numero de vezes em que o caractere c aparece na matriz table de strings. nword e a quantidade de palavras presentes na tabela*/
int CountChrTable(char** table, int nwords, char c){
    int total = 0, i;
    for(i=0; i<nwords; i++){
        total+=CountChrStr(table[i],c);
    }
    return total;
}

/*Retorna o numero de vezes que a palavra word repete na tabela de palavras table. words e o numero de palavras da tabela*/
int FindWord(char **table, int words, char *word){
    int i, total=0;
    for(i=0;i<words;i++){
        if(!memcmp(table[i],word,sizeof(char)*(strlen(word)+1))) total++;
    }
    return total;
}

/*Estrutura para guardar a palavra e o numero de vezes em que ela aparece no texto*/
typedef struct node{
    char *word;
    int count;
    struct node *left;
    struct node *right;
} node;

/*Cria um no com uma copia de word e com count 1*/
node* NewNode(char *word){
    node *n=(node*)malloc(sizeof(node));
    n->word=strdup(word);
    n->count=1;
    return n;
}

/*Insere a palavra word na arvore n*/
void InsertNode(node **n, char *word){
    if(n==NULL) n = (node**)malloc(sizeof(node*));
    if(*n==NULL) *n=NewNode(word);
    else{
        int i=strcmp((*n)->word,word);
        if(!i) (*n)->count++;
        else if(i>0) InsertNode(&(*n)->left,word);
        else if(i<0) InsertNode(&(*n)->right,word);
    }
}

/*Imprime a arvore n na tela*/
void PrintNode(node *n){
    if(n!=NULL){
        PrintNode(n->left);
        printf("%s;%d\n",n->word,n->count);
        PrintNode(n->right);
    }
}

/*Imprime a arvore n em um arquivo*/
void PrintNodeF(node *n, FILE* f){
    if(n!=NULL){
        PrintNodeF(n->left, f);
        fprintf(f, "%s;%d\n",n->word,n->count);
        PrintNodeF(n->right, f);
    }
}

/*Libera tabela de string criada no divider, recebendo o apontador table pra tabela e o numero de palavras que ela contem nword*/
void FreeT(char** table, int nword){
        int i;
        for(i=0; i<nword;i++){
	        free(table[i]);
        }
	free(table);
}

/*Libera uma árvore com nodes do tipo structure node*/
void FreeTr(node* tree){
        if(tree==NULL){
                free(tree);
        return;
        }
        FreeTr(tree->left);
        FreeTr(tree->right);
        free(tree->word);
}
