%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "y.tab.h"
extern int yyline;
%}

%%
[ \t] ;
^[0-9]+ {yylval.ival = atoi(yytext); return ADDRESS;}
DM return DM;
DC return DC;
DR return DR;
DZ return DZ;
SAB return SAB;
ODU return ODU;
MNO return MNO;
DEL return DEL;
PZA return PZA;
SABF return SABF;
ODUF return ODUF;
MNOF return MNOF;
DELF return DELF;
PZAF return PZAF;
KON return KON;
DIS return DIS;
NEG return NEG;
POL return POL;
POD return POD;
MUA return MUA;
AUM return AUM;
NES return NES;
NUS return NUS;
BES return BES;
ZAR return ZAR;
[+-]?[0-9]+ {yylval.ival = atoi(yytext); return INT;}
[+-]?[0-9]+\.[0-9]+ {yylval.fval = atof(yytext); return FLOAT;}
[a-zA-Z]+ {
	int n = strlen(yytext)+1;
	char *res = malloc(n*sizeof(char));
	strcpy(res, yytext);
	yylval.sval = res;
	return STRING;
}

\n yyline++;
. ;
%%
