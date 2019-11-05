%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headerFiles/macros.h"
#include "headerFiles/structs.h"

int yylex();
int yyerror();
void addToList();
void checkAddress(int, int);
command *createIntCommand(int, char *, int);
command *createFloatCommand(int, char*, float);
command *createCharCommand(int, char*, char);
void addCommand(int, char*, int);
int executeOperation(operation);

int yyline = 0, error = 0;

int n = 0, k = 0, i = 0;

//Bitne adrese u programu
int memAddress, startAddress = -1, declarationEndAddress = -1, endAddress = -1, currentAddress = -1;

//Lista komandi
command *cmdList, *cmdCur;

variable *variables;

operation *operations;

variable accumulator;

//Indeks registri
int indexReg[15];

char * red = "";
char * grn = "";
char * yel = "";
char * blu = "";
char * mag = "";
char * cyn = "";
char * wht = "";
char * reset = "";

#include "headerFiles/engine.h"

%}

%union{
	int ival;
	float fval;
	char *sval;
}

%token DM DC DR DZ SAB ODU MNO DEL PZA SABF ODUF MNOF DELF PZAF KON DIS NEG POL POD MUA AUM NES NUS BES ZAR
%token <ival> ADDRESS
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING
%%

program:
	memory
	declarations
	commands;

memory: ADDRESS DM INT {
			if(startAddress == -1)
				startAddress = currentAddress = $1;			
		
			for(i = 0; i < $3; i++){
				addToList(createIntCommand(currentAddress, "DM", 1));
				currentAddress ++; 
			}
		};

declarations:
	declarations ADDRESS DC {memAddress = $2; checkAddress($2, currentAddress);} intAttributes
	| declarations ADDRESS DR {memAddress = $2; checkAddress($2, currentAddress);} floatAttributes
	| declarations ADDRESS DZ {memAddress = $2; checkAddress($2, currentAddress);} stringAttributes
	| ADDRESS DC {memAddress = $1; checkAddress($1, currentAddress);} intAttributes
	| ADDRESS DR {memAddress = $1; checkAddress($1, currentAddress);} floatAttributes
	| ADDRESS DZ {memAddress = $1; checkAddress($1, currentAddress);} stringAttributes;

intAttributes: INT {
			addToList(createIntCommand(memAddress, "DC", $1));

			memAddress++;
			currentAddress++;

		} intAttributes 
	| INT {
			addToList(createIntCommand(memAddress, "DC", $1));

			currentAddress++;
	};

floatAttributes: FLOAT {
			addToList(createFloatCommand(memAddress, "DR", $1));

			memAddress++;
			currentAddress++;

		} floatAttributes 
	| FLOAT {
			addToList(createFloatCommand(memAddress, "DR", $1));

			currentAddress++;
	};

stringAttributes: STRING {
			
			int slen = strlen($1);
			
			for(i = 0; i < slen; i++){		

				addToList(createCharCommand(memAddress, "DZ", $1[i]));

				memAddress++;
				currentAddress++;
			}			

		} stringAttributes 
	| STRING {

			int slen = strlen($1);
			
			for(i = 0; i < slen; i++){		

				addToList(createCharCommand(memAddress, "DZ", $1[i]));

				memAddress++;
				currentAddress++;
			}

	};

commands: 
			ADDRESS SAB INT { addCommand($1, "SAB", $3); } commands
			| ADDRESS ODU INT { addCommand($1, "ODU", $3); } commands
			| ADDRESS MNO INT { addCommand($1, "MNO", $3); } commands
			| ADDRESS DEL INT { addCommand($1, "DEL", $3); } commands
			| ADDRESS PZA { addCommand($1, "PZA", -1); } commands
			| ADDRESS SABF INT { addCommand($1, "SABF", $3); } commands
			| ADDRESS ODUF INT { addCommand($1, "ODUF", $3); } commands
			| ADDRESS MNOF INT { addCommand($1, "MNOF", $3); } commands
			| ADDRESS DELF INT { addCommand($1, "DELF", $3); } commands
			| ADDRESS PZAF { addCommand($1, "PZAF", -1); } commands
			| ADDRESS KON INT { addCommand($1, "KON", $3); } commands
			| ADDRESS DIS INT { addCommand($1, "DIS", $3); } commands
			| ADDRESS NEG { addCommand($1, "NEG", -1); } commands
			| ADDRESS POL INT { addCommand($1, "POL", $3); } commands
			| ADDRESS POD INT { addCommand($1, "POD", $3); } commands
			| ADDRESS MUA INT { addCommand($1, "MUA", $3); } commands
			| ADDRESS AUM INT { addCommand($1, "AUM", $3); } commands
			| ADDRESS NES INT { addCommand($1, "NES", $3); } commands
			| ADDRESS NUS INT { addCommand($1, "NUS", $3); } commands
			| ADDRESS BES INT { addCommand($1, "BES", $3); } commands
			| ADDRESS ZAR { addCommand($1, "ZAR", -1); } commands
			| ADDRESS NES INT { addCommand($1, "NES", $3); } 
			| ADDRESS NUS INT { addCommand($1, "NUS", $3); } 
			| ADDRESS BES INT { addCommand($1, "BES", $3); } 
			| ADDRESS ZAR { addCommand($1, "ZAR", -1); };
%%

int yyerror(char *s){
	error = 1;
	printf("%sERROR: %s >>> %s <<< %s LINE: %s %d\n",RED, YEL, s, GRN, RESET, yyline);
}

int main(int argc, char **argv){

	int inputFileIndex = -1;

	for(i = 0; i < argc; i++){
		if(strcmp(argv[i], "-c") == 0){
			RED = "\x1B[31m";
			GRN = "\x1B[32m";
			YEL = "\x1B[33m";
			BLU = "\x1B[34m";
			MAG = "\x1B[35m";
			CYN = "\x1B[36m";
			WHT = "\x1B[37m";
			RESET = "\x1B[0m";
		}

		if(strcmp(argv[i], "-f") == 0){
			if(argc >= i + 2 && strlen(argv[i+1]) > 4 && !strcmp(argv[i+1] + strlen(argv[i+1]) - 4, ".txt")){
				inputFileIndex = i+1;
			}else{
				printf("%sMorate da navedete ulazni fajl sa ekstenzijom .txt odmah nakon zastavice -f!\n%s", YEL, RESET);
				exit(0);
			}
		}
	}

	if(inputFileIndex == -1) {
		printf("%sMorate da navedete ulazni fajl sa ekstenzijom .txt upotrebom zastavice -f!\n%s", YEL, RESET);
		exit(0);
	}

	extern FILE *yyin;
	yyin = fopen(argv[inputFileIndex], "r");

	yyparse();

	fclose(yyin);
	
	if(!error){
		
		endAddress = currentAddress - 1;
	
		variables = (variable*)malloc(VARIABLES_SIZE * sizeof(variable));
		operations = (operation*)malloc(OPERATIONS_SIZE * sizeof(operation));

		accumulator.type = 'M';
		accumulator.value.i = 0;

		command *pom = cmdList;
		
		//Create variables array	
		i = 0;
		while(pom != NULL){
			if(i == VARIABLES_SIZE) break;			
			
			if(pom->command[1] == 'M'){
				variables[i].address = pom->address; variables[i].type = 'M'; variables[i].value.i = 0;
			}else if(pom->command[1] == 'C'){
				variables[i].address = pom->address; variables[i].type = 'C'; variables[i].value.i = pom->value.i;
			}else if(pom->command[1] == 'R'){
				variables[i].address = pom->address; variables[i].type = 'R'; variables[i].value.f = pom->value.f;
			}else if(pom->command[1] == 'Z'){
				variables[i].address = pom->address; variables[i].type = 'Z'; variables[i].value.c = pom->value.c;
			}
			pom = pom->next;
			i++;
		}

		//Create operations array
		i = 0;
		while(pom != NULL){
			operations[i].address = pom->address;
			strcpy(operations[i].command, pom->command);
			operations[i].value = pom->value.i;
		
			pom = pom->next;
			i++;		
		}
		
		//Execute program	
		i = 0;
		while(i >= 0)
			i = executeOperation(operations[i]);
		
		//Print results
		if(i == -100){
			
			for(i = 0; i < VARIABLES_SIZE; i++)
				switch(variables[i].type){
					case 'M':
						printf("%s%d %sM : %s%d\n", GRN, variables[i].address, YEL, CYN, variables[i].value.i);
					break;
					case 'C':
						printf("%s%d %sC : %s%d\n", GRN, variables[i].address, YEL, CYN, variables[i].value.i);
					break;
					case 'R':
						printf("%s%d %sR : %s%f\n", GRN, variables[i].address, YEL, CYN, variables[i].value.f);
					break;
					case 'Z':
						printf("%s%d %sZ : %s(", GRN, variables[i].address, YEL, CYN) ;
						printf("%c", variables[i].value.c >> 24);
						printf("%c", variables[i].value.c >> 16);
						printf("%c", variables[i].value.c >> 8);
						printf("%c)\n", variables[i].value.c);
					break;
				}
		}
	}
	return 0;
}

