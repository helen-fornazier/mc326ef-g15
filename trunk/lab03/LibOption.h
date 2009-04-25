#ifndef LIB_OPT
#define LIB_OPT


void PrintMenu(EFILE *e);

int VerOb1(EFILE *e, DATASTYLE *data, char **str,  int i); //ver obrigatoriedade do campo

int VerAl(EFILE *e, DATASTYLE *data, char **str,  int i);	//Verifica config alphanum

int Option1(EFILE *e, DATASTYLE *data);

void Option2(EFILE *e, DATASTYLE *data);

void Option3(EFILE *e, DATASTYLE *data);

void Option4(EFILE *e, DATASTYLE *data);

DATASTYLE *Option6(EFILE *e, DATASTYLE *data);   //Já cria o datainit.config e retorna o datastyle dele

void Option7(EFILE *e, DATASTYLE *data);

void Option8(EFILE *e, DATASTYLE *data);

void Option9(EFILE *e, DATASTYLE *data);

DATASTYLE *Option10(EFILE *e, DATASTYLE *data);

void Option11(EFILE *e, DATASTYLE *search, DATASTYLE *find);

void Option12(EFILE *e, DATASTYLE *search, DATASTYLE *find);

/*Transforms a file fix to variable one
 * Returns 0 if the file fix does not according with
 * its configuration and free all allocs here allocates
 *
 * Returns 1 if right*/
int Fixtovar(EFILE *e, FILE *fi, FILE *fo1, DATASTYLE *data);

/*Prints in the style NAMEFIELD = FIELD*/
void PrintOne(DATASTYLE *data, char **str, int first);

/*Prints a fix file*/
void Printfix(EFILE *e, FILE *fi, DATASTYLE *data);

/*Prints a variable file*/
void Printvar(EFILE *e, FILE *fi, DATASTYLE *data);

/*Searchs for a key in the file fi whith its configuration
 * in data*/
void SearchandPrint(EFILE *e, FILE *fi, DATASTYLE *data, char *key);

/*Write in a file (default dataind.config) the DATASTYLE
 * of the file menu  (key address #)*/
DATASTYLE *WriteIndData(EFILE *e, DATASTYLE *data);

/*Prints in a file just one index register*/
int MakeOneInd(EFILE *e, FILE *fi, FILE *fo1, DATASTYLE *data);

/*Prints all the index register in a file, its a loop of the 
 * function MakeOneInd*/
void MakeInd(EFILE *e, FILE *fi, FILE *fo1, DATASTYLE *data);

/*Sort a file in alphabetic order by lines
 * if in==out,  its overwrite in with a sorted file*/
void Ordena(char *in, char *out);

/*Prints in stdout just one index register*/
int PrintOneInd(EFILE *e, FILE *fi,  DATASTYLE *data);

/*Prints in the stdout all of index register, its a loop of
 * the finction PrintOneInd*/
void PrintInd(EFILE *e, FILE *fi, DATASTYLE *data);

#endif    //LIB_OPT
