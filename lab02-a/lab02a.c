#include"LibFile.h"
#include"LibMsg.h"
#include"LibWord.h"

#define IDIOM "english.config"
#define DATA "data.config"


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
    
	int **tab, nfields;
	FILE *fd=fopen(DATA,"r");
	MakeData(fd,&tab,&nfields);
	fclose(fd);


	REGIS matrix;
	int i=5, j=0, k=0, y=0;
	int n1=0, n2=0;
	
	while(i==5){
		i=ReadRegFix(fi,&matrix,tab[0],nfields,5);
        
        for(y=0; y<i; y++){
            for(k=0; k<nfields; k++){
                if((tab[1][k] == 1) && (matrix[y][k][0] == EOS)){
                    Msg(12);
                    printf("%d, %d\n", j+y+1 , k+1);
                }
            }
        }

		j+=i;
		n1+=PrintAll(fo1,PRINT_DIV,matrix,i,nfields);
		n2+=PrintAll(fo2,PRINT_TAM,matrix,i,nfields);

        FreeTT(matrix, i, nfields); 
	}
	
	int sum=0;
	for(i=0;i<nfields;i++)
		sum+=tab[0][i];
        Msg(11);
	printf("%d\n",j*(sum+1));	
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
