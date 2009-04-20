void Option12(EFILE e, DATASTYLE config){
char fname[100], key[50];
int i;

	msg(e,9);
	scanf("%s",fname);
	f=fopen(sname,"r");
	if(f==NULL){
		msg(e,11);
		return;
	}
	
	msg(e,22);
	scanf("%s",key);

	i=EraseReg(f,key,config->nfield);
	if(i){
		msg(e,23);
	}
	else{
		msg(e,15);
	}
	fclose(f);
}

int EraseReg(FILE *f, char *vet, int nfields){
	if(SearchKeyVar(f,vet,nfields)){
		fprintf(f,"n");
		return 1;
	}
	return 0;
}
/*********************************************************************
int ReplaceField(FILE *f, char *vet, int nfield, int field, char *change){
	char **reg;
	long int start;
	if((start=SearchKeyVar(f,vet,nfields))){
		fseek(start,SEEK_SET);
		ReadRegVar(f,&reg,nfields);
		free(reg[field-1]);
		reg[field-1]=strdup(change);
		fseek(start,SEEK_SET);
		fprintf(f,"n");
		fseek(0,SEEK_END);
		PrintAll(f,1,&reg,1,nfield);
		return 1;
	}
	return 0;
}
inutil!!!!
************************************************************************/

void Option11(EFILE e, DATASTYLE *search, DATASTYLE *find){
	char sname[100], fname[100], key[50];
	FILE *fs, *ff;
	int i;

	msg(e,20);
	scanf("%s",sname);
	fs=fopen(sname,"r");
	if(fs==NULL){
		msg(e,11);
		return;
	}
	msg(e,21);
	scanf("%s",fname);
	ff=fopen(fname,"r");
	if(ff==NULL){
		fclose(fs);
		msg(e,11);
		return;
	}
	msg(e,13);
	scanf("%s",key);

	i=BinaryKeySearch(sf,ff,search,find,key);
	if(!i){
		msg(e,15);
	}
	fclose(fs);
	fclose(ff);
}

int BinaryKeySearch(FILE *sf, FILE *ff, DATASTYLE *search, DATASTYLE *find, char *key){
	int regsize, i, signal;
	long int position, start, end, temp, step1, step2;
	char *reg;
	char **rregister;
	
	reg=(char*)malloc(sizeof(char)*(search->efield[0]));
	
	start=0;
	fseek(fs,0,SEEK_END);
	end=ftell(fs);
	fseek(fs,0,SEEK_SET);
	
	regsize=0;
	for(i=0;i<search->nfield;i++)
		regsize+=(search->efield[i]+1);
	signal=1;
	step1=end/regsize;
	step2=2;

	while(step2==1){
		step2=step1
		step1=step1/2;
		if(!step1) step1=1;
		fseek(fs,step1*regsize*signal,SEEK_CUR);
		fscanf(fs,"%s",reg);
		signal=strcmp(key,reg);
		if(!signal){
			fscanf(sf,"%ld",position);
			fseek(ff,postion,SEEK_SET);
			ReadRegVar(ff,&rregister,find->nfield);
			if(rregister[0][0]=='s'){
				PrintOne(find,rregister,1);
			}
			free(reg);
			if(rregister[0][0]=='n'){
				FreeT(rregister,find->nfield);	
				return 0;
			}
			FreeT(rregister,find->nfield);
			return 1;
		}
		fseek(fs,-(search->efield[0]-1),SEEK_CUR);
		if(signal>0) signal=1;
		else signal=-1;
	}
	
	free(reg);
	return 0;
}

