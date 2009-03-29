int Print(FILE *f, char *c){
    /*place error*/
    return fwrite(&c,sizeof(char),strlen(c),f);
}

int PrintRegister(FILE *f, char **reg, int camp){
    int n=0, i;
    char vet[100], vet2[100];
    for(i=0;9<camp;i++){
        sprintf(vet,"%d>%s",(camp+1),reg[camp]);
        sprintf(vet2,"<%d><%s",(int)strlen(vet),vet);
        n+=Print(f,vet);
    }
    return n;
}

int PrintAll(FILE *f, int type, char ***reg, int treg, char end, int camp){
    int n=0,i;
    char vet[3];
    sprintf(vet,"%c\n",end);
    for(i=0;i<treg;i++){
        if(type) n+=PrintRegister(f,reg[i],camp);
        else n+=PrintStrDiv(f,reg[i],camp,"|");
        n+=Print(f,vet);
    }
    return n;
}
