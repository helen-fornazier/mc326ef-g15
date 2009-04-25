#ifndef LIB_FILE
#define LIB_FILE

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "LibWord.h"
//#include "LibOption.h"
#include "LibMsg.h"

#ifndef EOS
#define EOS '\0'
#endif   /*def EOS*/

#define PRINT_TAM 1
#define PRINT_DIV 0

typedef char*** REGIS;

#define FIX 1
#define VAR 0

typedef struct datastyle{
	int nfield;			//how many field exist
	int *efield;		//lengh of each field
	int *ob;			//list of oblibatoriety
	char **fieldname;	//name of each fields
	int *alpha;			//1=num, 2=alph, 3=aphnum, 0=none

}	DATASTYLE;

typedef struct regis{
	int nregis;		//number of registers
	int fix;		//if is a file with fixed lenght filds, fix == 1, if isn't,  fix == 0
	int nrem;		//the number of registers set as removed
	DATASTYLE *datastyle;		//if a file of variable lenght fields, datastyle is NULL
	FILE* fi;		//a pointer to the beginning of the file
	FILE* fe;		//a pointer to the last register

} REGIS_t;


/* Take from a file information about the registers 
 * f-> the file that contains the information in this format:
 * number of fields, size of each field, obligatory information
 * tab-> adress of the matrix that will containd the size of the fields and it's obligatoriety
 * nfields-> adres of an int where will be place the number of fields that the registers have
 */
int MakeData(FILE *f, int **tab, int *nfields);

/*Description:  Prints the string c in file f
 *
 * Returns the number of characteres writed
 * */
int Print(FILE *f, char *c);

/*Description: Prints a list of string (reg) in file f
 * with the model: Ex. reg = {"Helen", "Pedro T"}
 * The file will stay: <7><1>Helen<9><2>Pedro T
 * camp is the number os fields,  in this case is 2
 *
 * Return the number of characteres writed
 * */
int PrintRegister(FILE *f, char **reg, int camp);

/*Description: Prints in file f the register reg with treg registers.
 * Each register keeps camp fields
 * In each registers, it prints in the end the characteres end
 * The model of the print is given by the type:
 *      type:
 *          PRINT_TAM   model of the PrintRegister function:  <7><1>Helen<9><2>Pedro T#
 *          PRINT_DIV   model of the PrintStrDiv function:    Helen|Pedro T#
 *          */
int PrintAll(FILE *f, int type, REGIS reg, int treg, int camp);

/*Description: Find the character c in file f (from current cursor)
 * and set the cursor n chararacteres after c
 *
 * If c was not finded, in the other way, if it finded the EOF
 * the cursor stays in it
 *
 * Return 0 if the cursor set EOF
 * else return 1
 * */
int SetCursesC(FILE *f, char c, int n);

/*Read of FILE f qnt registers with nfields fields, each field with lengh iqual
 * to len and put in REGIS reg
 * 
 * Return the number of only integer register readed
 * */
int ReadRegFix(FILE *f, REGIS *reg, int *len, int nfields, int qnt);

/*Initializes and returns a list with nfield NULL fields
 *
 * Receives the number of fields
 * 
 * Returns a (char **) type with all fields iqual to NULL
 * or Return NULL if failed
 * */
char **InitRegis(int nfield);

/*Description: reads len characteres in FILE f and puts in the string str
 *
 * The char **str is the address of the string str
 *
 * This function already allocate memory for str
 *
 *Returns the number of characteres readed
 *Returns 0 if does not readed something or memory error
 **/
int ReadStr( FILE* f, char **str, int len);

/*
 * f is a FILE the will be readed.
 * fieldList is a (char **) type that will be filled whith strings.
 * lenList[i] indicate the number of characteres that will be readed from
 * f and put in fieldList[i]
 *
 * Return the number of all characteres readed
 * If does not readed the right number of characteres in f, returns 0 
 * */
int FillFields(FILE *f, char ***fieldList, int *lenList, int nfields);

/*Prints in the FILE f the list of string (strList with lengh len) separate by the character c
 *
 * Returns the number of characteres writed in f*/
int PrintStrDiv(FILE *f, char **strList, int len, char *divider);

/*Description: Return a struct DATASTYLE alreary initialized*/
DATASTYLE *InitDatastyle();

/*Description: Ready the configuration file and fills 
 * a struct DATASTYLE and returns it
 *
 * fields readed:	
 * 		int nfields
 * 		int nfield;			
 *		int *efield;		
 *		int *ob;			
 *		char *fieldname;		
 *	*/
DATASTYLE* FillData(FILE* f);

/*Description: Free all data of a struct DATASTYLE data*/
void CloseDatastyle(DATASTYLE *data);

/*Read a fixed register, aplies Corrector and set the
 * cursor f after \n
 *
 * f is the file tha will read
 * str is a table that will contain the data of one register
 * str doesn't need to be inicialized
 * len is the vector of lenght of each field
 * nfield is the number of fields
 *
 * return 0 if faild or finded EOS
 * */
int ReadRegFix3(FILE *f, char ***str, int *len, int nfields);

/*Read a fixed register without aplies Corrector and set the
 * cursor f after \n
 *
 * f is the file tha will read
 * str is a table that will contain the data of one register
 * str doesn't need to be inicialized
 * len is the vector of lenght of each field
 * nfield is the number of fields
 *
 * return 0 if faild or finded EOS
 * */
int ReadRegFix2(FILE *f, char ***str, int *len, int nfields);

/*Description: Reads a file f whth variable format and puts
 * in str
 *
 * =>f is the file thar will be readed
 * =>***str is the addres of char **str, doesn't need to be inicialized
 * =>nfields is the number of fields in str
 *
 * Return 0 if failed, 1 if not.
 */
//só funciona se o último campo antes do caracter for obrigatório
long int ReadRegVar(FILE *f, char ***reg, int fields);

/*retorna 1 se encontrou, e deixa f setado no começo do registro encontrado
 * se não, f fica no começo*/

/*Description: Returns 1 if finded key in the principal key
 * return 0 if doesn't finded*/
int SearchKeyVar(FILE *f, char *key, int nfields);

/*Description:  Reads just a field
 *
 * Returns the number of the field*/
int ReadField(FILE *f, char **vet);

/*Description:	Returns 1 if str is num
 * 				Returns 2 if str is alpha
 * 				Returns 3 if str is alphanum
 * 				Returns 0 if none of the ones
 * 			before, or if str is NULL
 * */
int VerAlnum(char *str);

/* Receives a file, the number of fields each register has and a primary key that the user
 * wants to be logicaly removed.
 * Returns 0 if the key is not found
 * and 1 if it is deleted*/
int EraseReg(FILE *f, char *vet, int nfields);

/* entry:
 * sf-> menu file where the key will be searched
 * ff-> file where the register will be stracted
 * search-> structure of sf
 * find-> structure of ff
 * the function will return 1 if it has been sucssesfull or 0 if not */
int BinaryKeySearch(FILE *sf, FILE *ff, DATASTYLE *search, DATASTYLE *find, char *key);


int MakeDataS(FILE *f, char ***str, int nfield);

#endif  /*LIB_FILE*/
