#ifndef LIB_OPT
#define LIB_OPT

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"LibWord.h"
#include"LibFile.h"
#include"LibMsg.h"

void PrintMenu(EFILE *e);

int VerOb1(EFILE *e, DATASTYLE *data, char **str,  int i); //ver obrigatoriedade do campo

int VerAl(EFILE *e, DATASTYLE *data, char **str,  int i);	//Verifica config alphanum

int Option1(EFILE *e, DATASTYLE *data);

void Option2(EFILE *e, DATASTYLE *data);

void Option3(EFILE *e, DATASTYLE *data);

void Option4(EFILE *e, DATASTYLE *data);

void Option6(EFILE *e, DATASTYLE *data);

void Option7(EFILE *e, DATASTYLE *data);

#endif    //LIB_OPT
