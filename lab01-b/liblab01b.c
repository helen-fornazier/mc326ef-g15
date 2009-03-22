#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"liblab01b.h"

#define SPACE ' '
#define EOS '\0' /* End Of Sentence  */

char **msg //where will be placed all messages from the program

/*Definicao de palavra: Todo agrupamento formado por caracteres alfanumericos*/

/*Take out signals different from letters or numbers from a string*/
/*Substitui caracteres em remove por espacos. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes,
 * ou se não houver, retorna uma cópia de str. Retorna NULL se houver falta de memória, ou se foi passado str NULL*/
char* Cleaner(char *str, char *remove){
    char *strout=strdup(str);
    if(strout==NULL) return NULL;

    char *temp = NULL;
    while(strpbrk(strout, remove)!=NULL){
      temp=strpbrk(strout, remove);
        *temp=SPACE;
    }
    return strout;
}

/*Take out double spacements betwen words in a string*/
/*Substitui muitos espacos seguidos por apenas 1. Nao modifica a string str. Retorna um ponteiro de uma nova string com as modificacoes
 * ou uma cópia de str se não houver modificações. Retorna NULL se houver falta de memória*/
char* Corrector(char *str){
    if(str==NULL) return NULL;

    int i, spaces=0;
    for(i=0;str[i]!=EOS;i++) //Conta os espacos sobrando
        if((str[i]==SPACE&&str[i+1]==SPACE) || (str[i]==SPACE&&str[i+1]==EOS)) spaces++;

    if(spaces){ //Se existe espaco sobrando
        char *strout=(char*)malloc(sizeof(char)*(strlen(str)-spaces+1)); //Malloca no tamanho certo, sem os espacos sobrando
        if(strout==NULL) return NULL; //Retorna NULL se houver erro de memória

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

    else return strdup(str); //Se nao houver espacos sobrando, retorna a duplicata da string passada como parametro. Retorna NULL se erro de memória
}

/*Shift all small letters*/
/*Transforma todas as letras minusculas existentes em uma string em maiusculas. Nao modifica a string str. Retorna um ponteiro de uma nova string.
 * Retorna NULL se erro de memória*/
char* Shifter(char *str){
    if(str==NULL) return NULL;

    int i;
    char *strout=(char*)malloc(sizeof(char)*(strlen(str)+1));
    if(strout==NULL) return NULL;

    for(i=0;str[i]!=EOS;i++)
        strout[i]=toupper(str[i]);
    strout[i]=EOS;

    return strout;
}

/*Retorna o numero de palavras alfanuméricos em str*/
int WordCount(char *str){
    if(str==NULL) return 0;

    int i, words=0;
    for(i=0;str[i]!=EOS;i++){
        if(isalnum(str[i])){
            words++;
            while(isalnum(str[i+1])) i++;    
        }
    }
    return words;
}

/*Conta strings em str, considerando os separadores em accept
 * Ex: str = "Bolo#De #Chocolate Congelado@"  divider = "#@"   
 * o valor retornado é 3 strings entre separadores*/
int StrCount(char *str, char *divider){
    if(str==NULL) return 0;

    int i, nstr=0;
    char *temp=str, *temp2=str;

    for(i=0;temp2!=NULL;i++){
      temp2=strpbrk(temp, divider);
        if((temp2-temp>=sizeof(char) && temp2!=NULL)){
            nstr++;
        }
	
	temp=temp2+sizeof(char);
    }
    if(strpbrk(&(str[strlen(str)-1]),divider)==NULL) nstr++;
    return nstr;
}


/*Coloca cada pedaço de str em uma matriz retornada, os caracteres em divider são considerados separadores
 e nword sai da função com o número de strings na tabela*/
char** Divider(char *str, int *words, char *divider){
    int k=0,i;
    char **table, *temp, *temp2;
    temp=str;
    
    *words=StrCount(str,divider);
    table=(char**)malloc(sizeof(char)*(*words));
    for(i=0;i<*words;i++) table[i]=NULL;

    while(k<*words){
        temp2=strpbrk(temp, divider);
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
            k++;
        }
        temp+=sizeof(char);
    }
    return table;
}

/*Coloca cada pedaço de str em uma matriz retornada, os caracteres em divider são considerados separadores
 e nword sai da função com o número de strings na tabela. Se str for passado NULL, nword sai igual a 0 e table
 igual a NULL. Retorna NULL se houver erro de memória*/
char** Divider2(char* str, char* divider, int* nword){
  if(str==NULL){
      (*nword)=0;
      return NULL;
  }
  *nword = StrCount(str,divider); //Conta o número de strings
  if(*nword==0) return NULL;

  char** table = (char**)malloc(sizeof(char)*(*nword)); //Malloca no tamanho certo
  if(table==NULL) return NULL;

  int i=0;
  
  for(i=0; i<*nword; i++){ //Iincializa table. Testado: se não inicializar antes, com muitos separadores não dá certo
    table[i] = NULL;
  }

  char* temp = str;
 
  for(i=0; i<*nword;){
    table[i] = CutStr(temp,divider); //Corte a string
    if(table[i]!=NULL){ //Se um separador não estiver na primeira posição
      temp = &temp[strlen(table[i])]; //temp vai além da string que já foi armazenada em table[i]
      i++; 
    }
    else temp = &temp[1]; //Se o separador estiver na primeira posição, avance um para cortar denovo
  }
  return table;
}


/*Retorna o numero de vezes em que o caractere c aparece em str*/
int CountChrStr(char* str, char c){
    if(str==NULL) return 0;

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
    if(table==NULL) return 0;

    int total = 0, i;
    for(i=0; i<nwords; i++){
        total+=CountChrStr(table[i],c);
    }
    return total;
}

/*Retorna o numero de vezes que a palavra word repete na tabela de palavras table. words é o numero de palavras da tabela*/
int FindWord(char **table, int words, char *word){
    if(table==NULL) return 0;

    int i, total=0;
    for(i=0;i<words;i++){
        if(!memcmp(table[i],word,sizeof(char)*(strlen(word)+1))) total++;
    }
    return total;
}


/*Cria um nó com uma copia de word e com count 1, se houver algum erro de memória
 * libera o que foi alocado e retorna NULL*/
node* NewNode(char *word){
    node *n=(node*)malloc(sizeof(node));
    if(n==NULL) return NULL;

    n->word=strdup(word);
    if(n->word==NULL){
        free(n);
        return NULL;
    }

    n->count=1;
    return n;
}

/*Insere a palavra word na arvore n. Retorna 0 se não inseriu*/
int InsertNode(node **n, char *word){
    if(n==NULL){
        n = (node**)malloc(sizeof(node*));
        if(n==NULL) return 0;
    }

    if(*n==NULL){
        *n=NewNode(word);
        if((*n)==NULL) return 0;
    }

    int ver1 = 0;
    int ver2 = 0;

    else{
        int i=strcmp((*n)->word,word);
        if(!i) (*n)->count++;
        else if(i>0) ver1 = InsertNode(&(*n)->left,word);
        else if(i<0) ver2 = InsertNode(&(*n)->right,word);
    }

    if(ver1==0 && ver2==0) return 0;
    return 1;
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

/*Imprime uma tabela de strings (table) sendo len o número de strings que ela contém*/
void PrintTable(char** table, int len){
  int i=0;
  for(i=0; i<len; i++){
    printf("%s\n", table[i]);
  }
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



/*Devolve uma cópia da string str cortada até o primeiro caractere que se encontra no divider
  Ex: str = "Bolo#de cholocate#@" divider = "#@"    devolverá a string "Bolo". Se um dos caracteres
  de divider se encontrar na primeira posição, retorna NULL, e se não houver um dos caracteres
  retorna uma cópia de str.*/
char* CutStr(char* str, char* divider){
  if(str == NULL) return NULL;

  char* temp = strpbrk(str, divider);
  if(temp == NULL) return strdup(str);
  if(temp == str) return NULL;
  else{
    char* strout = strndup(str, strlen(str)-strlen(temp));
    return strout;
  }
}


/*Devolve uma cópia da primeira string que aparecer em str limitado pelo caractere em divider,
 pulando os primeiros caracteres:             OBS: Não modifica a string original.
 str= “,*Cama e + Banho.” e divider=”, +*.” (o branco está depois da virgula) a rotina deve
 retornar “Cama */
char* FirstStr(char* str, char* divider){
    if(str == NULL) return NULL;

    char* strout =CutStr(str,divider);
    int i =0, len = strlen(str);
  
    for(i=0; i<len && strout==NULL ; i++){
        strout = CutStr(&str[i],divider);
     }
    return strout;
}

/*Faz a mesma coisa que FirstStr só que leng é o índice onde se inicia srt e soma com o número de caracteres que ele andou em str.
 * leng = 0, str= “,*Cama e + Banho.” e divider=”, +*.” (o branco está depois da virgula) a rotina deve retornar “Cama" e leng = leng + 6
 * Na próxima chamada da função, len = 6, str = *“,*Cama e + Banho.”, e divider=”, +*.”, como leng inicialmente vale 6, a palavra que ele
 * irá retornar é "e" e leng = leng + 1.*/
char* FirstStrL(char* str, char* divider, int* leng){
    if(str == NULL) return NULL;

    char* strout =CutStr(&str[*leng],divider);
    int i =0, len = strlen(&str[*leng]);
  
    for(i=0; i<len && strout==NULL ; i++){
         strout = CutStr(&str[i+(*leng)],divider);
     }

    (*leng) = (*leng) + i + strlen(strout);
    return strout;
}


/* open the archive where the messages are writen and place them on memory */
void MakeMsg(char *fname){
    FILE *f;
    char temp[100], temp0='\0';
    int n, i=0, j;

    f=fopen(fname,"r");
    if(f==NULL) 
        printf("failure to open the language archive\n the program will not print messages\n");
    if(f!=NULL){    
        fscanf(f,"%d",&n);
    
        msg=(char**)malloc(sizeof(char*)*n); //global variable

        while(temp0!=EOF){
            while(temp0!='"') fscanf(f,"%c",&temp0);
            fscanf(f,"%c",&temp[0]);
            for(j=1;temp[j-1]!='"';j++)
                fscanf(f,"%c",&temp[j]);
            temp[j-1]='\0';
            msg[i++]=strdup(temp);
            fscanf(f,"%c",&temp0);
        }
    }
}


/* print a message */
void Msg(int n){
    if(msg!=NULL) printf("%s\n",msg[n]);
}

