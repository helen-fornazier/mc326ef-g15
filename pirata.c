
int PrintRegister(file *f,char **reg, int nfields){
	int i, n;
	n=0;
	for(i=0;i<nfields;i++)
		if(*reg[i]!='\0'){
			fprintf(f,"%c%c%s",(char)(strlen(reg[i])+2),(char)i,vet[i]);
			n+=strlen(reg[i])+2;
		}
	return n;
}

int ReadField(file *f, char *vet, char sep){
	int size, field;

	if(vet!=NULL) free(vet);
	
	fscanf(f,"%c",&(char)size);
	if(size==(int)sep || (char)size==EOF) return 0;
	fscanf(f,"%c",&(char)field);
	vet=(char*)malloc(sizeof(char)*(size-2));
	fread(vet,sizeof(char),size-2,f);

	return field;
}

long int ReadRegister(file *f, char ***reg, int fields, char sep){
	int n, i=1;
	char *vet;
	long int start=ftell(f);

	if(reg!=NULL) printf("reading function receives non null char***\n");
	*reg=(char**)malloc(sizeof(char*)*fields);
	while(1){
		n=ReadField(f,vet,sep);
		
		if(n=0) break;
		
		if(n>fields) printf("number of fields in file is greater than expected \n");
		for(;i<n;i++){
			(*reg)[i-1]=(char*)malloc(sizeof(char));
			(*reg)[i-1][0]='\0';
		}
		(*reg)[i-1]=strdup(vet);
		free(vet);
		i++;
	}
	
	if(i==1) return 0;
	return start;
}
