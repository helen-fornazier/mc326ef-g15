void quickSort(int i, int j, REGIS vet, int field){
	if(i>=j) return;
	int esq=i, dir = j;
	char **aux = vet[(i+j)/2], **aux2;
	int temp;

	while(1){
		while(1){
			temp=strcmp(aux[field],vet[esq][field]);
			if(temp>0) esq++;
			else break;
		}
		while(1){
			temp=strcmp(vet[dir][field],aux[field]);
			if(temp>0) dir--;
			else break;
		}
		if(esq<=dir){
			aux2=vet[esq];
			vet[esq]=vet[dir];
			vet[dir]=aux2;
			esq++; dir--;
		}
		else break;
	}
	quickSort(i,dir,vet,field);
	quickSort(esq,j,vet,field);
}
