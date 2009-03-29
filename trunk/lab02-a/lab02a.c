#include"LibFile.h"
#include"LibMsg.h"
#include"LibWord.h"

#define NFIELDS 7
#define FS1 7
#define FS2 24
#define FS3 15
#define FS4 9
#define FS5 9
#define FS6 2
#define FS7 2

int main(int argc, char *argv[]){
		
	MakeMsg("english.config");
	
	if(argc!=2){ 
		Msg(1);
		return 1;
	}

	FILE *fi=fopen(argv[1],"r");
	if(fi==NULL) Msg(2); 
	FILE *fo1=fopen("out1.txt","w");
	if(fo1==NULL) Msg(3);
	FILE *fo2=fopen("out2.txt","w");
	if(fo2==NULL) Msg(4);
	int fieldsize[NFIELDS]={FS1,FS2,FS3,FS4,FS5,FS6,FS7};
	REGIS matrix;
	int i=5, j=0;
	int n1=0, n2=0;
	
	while(i==5){
		i=ReadRegFix(fi,&matrix,fieldsize,NFIELDS,5);
		j+=i;
		n1+=PrintAll(fo1,0,matrix,i,'#',7);
		n2+=PrintAll(fo2,1,matrix,i,'#',7);
	}

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
