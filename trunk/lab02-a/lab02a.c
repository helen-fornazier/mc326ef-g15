#include"LibFile.h"
#include"LibMsg.h"
#include"LibWord.h"

#define IDIOM "english.config"

#define NFIELDS 8
#define FS1 7
#define FS2 24
#define FS3 15
#define FS4 9
#define FS5 9
#define FS6 2
#define FS7 2
#define FS8 1

#define OBLIST {1, 1, 0, 0, 0, 0, 1, 1}

#define PIN 1
#define POUT1 2
#define POUT2 3
#define PLENG 4
int main(int argc, char *argv[]){
		
	if(argc==PLENG+1){
		if(MakeMsg(argv[PLENG])!=0) MakeMsg(IDIOM);
	} else MakeMsg(IDIOM);
	
	if(argc<PLENG || argc> PLENG+1){ 
		Msg(1);
		return 1;
	}

	FILE *fi=fopen(argv[PIN],"r");
	if(fi==NULL) Msg(2); 
	FILE *fo1=fopen(argv[POUT1],"w");
	if(fo1==NULL) Msg(3);
	FILE *fo2=fopen(argv[POUT2],"w");
	if(fo2==NULL) Msg(4);
    
    //RECEBER NFIELD
	int fieldsize[NFIELDS]={FS1,FS2,FS3,FS4,FS5,FS6,FS7, FS8}; //COLOCAR AQUI A LISTA DOS TAMANHO DOS CAMPOS
    int oblist[NFIELDS] = OBLIST;    //COLOCAR AQUI A LISTA DE OBRIGATORIEDADE
	REGIS matrix;
	int i=5, j=0, k=0, y=0;
	int n1=0, n2=0;
	
	while(i==5){
		i=ReadRegFix(fi,&matrix,fieldsize,NFIELDS,5);
        
        for(y=0; y<i; y++){
            for(k=0; k<NFIELDS; k++){
                if((oblist[k] == 1) && (matrix[y][k][0] == EOS)){
                    Msg(12);
                    printf("%d, %d\n", j+y+1 , k+1);
                }
            }
        }

		j+=i;
		n1+=PrintAll(fo1,PRINT_DIV,matrix,i,NFIELDS);
		n2+=PrintAll(fo2,PRINT_TAM,matrix,i,NFIELDS);

        FreeTT(matrix, i, NFIELDS); 
	}

        Msg(11);
	printf("%d\n",j*(FS1+FS2+FS3+FS4+FS5+FS6+FS7+FS8+1));	
	Msg(8);
	printf("%d\n",j);
	Msg(9);
	printf("%d\n",n1);
	Msg(10);
	printf("%d\n",n2);

	i=fclose(fi);
	if(i) Msg(5);
	i=fclose(fo1);
	if(i) Msg(6);
	i=fclose(fo2);	
	if(i) Msg(7);
	

	return 0;
}
