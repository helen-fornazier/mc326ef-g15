#ifndef LIB_FILE
#define LIB_FILE

#include <stdio.h>
#include <string.h>
#include "LibWord.h"

#ifndef EOS
#define EOS '\0'
#endif   /*def EOS*/

#define PRINT_TAM 1
#define PRINT_DIV 0

typedef char*** REGIS;

/* Take from a file information about the registers 
f-> the file that contains the information in this format:
number of fields, size of each field, obligatory information
tab-> adress of the matrix that will containd the size of the fields and it's obligatoriety
nfields-> adres of an int where will be place the number of fields that the registers have

*/
void MakeData(FILE *f, int ***tab, int *nfields);

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


#endif  /*LIB_FILE*/
