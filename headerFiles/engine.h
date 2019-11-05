

void addToList(command *c){
	if(cmdList == NULL){
		cmdList = c;
		cmdCur = c;
	}else{
		cmdCur->next = c;
		cmdCur = cmdCur->next;
	}
}

void checkAddress(int address, int curAddress){
	if(address != curAddress){
		char s[100];
		sprintf(s, "Addres is %d! It should be %d!", address, curAddress);
 		yyerror(s);
	}
}

command *createIntCommand(int add, char *com, int val){
	command *c = malloc(sizeof(command));
	c->address = add;
	strcpy(c->command, com);
	c->value.i = val;

	return c;
}

command *createFloatCommand(int add, char *com, float val){
	command *c = malloc(sizeof(command));
	c->address = add;
	strcpy(c->command, com);
	c->value.f = val;

	return c;
}

command *createCharCommand(int add, char *com, char val){
	command *c = malloc(sizeof(command));
	c->address = add;
	strcpy(c->command, com);
	c->value.c = val;

	return c;
}

void addCommand(int add, char *com, int val){
	if(declarationEndAddress == -1) 
		declarationEndAddress = add-1;
 
	checkAddress(add, currentAddress); 
	addToList(createIntCommand(add, com, val)); 
	currentAddress++; 
}

int executeOperation(operation o){

	int target = o.value;
	
	if(strcmp(o.command, "SAB") == 0){

		VAR_OUT_OF_BOUNDS_CHECK(target);
		ACM_TYPE_CHECK('R');
		VAR_TYPE_DOUBLE_CHECK(target, 'R', 'C');

		if(variables[VARIABLE_TO_LOCAL(target)].type == 'R'){
			accumulator.value.f += variables[VARIABLE_TO_LOCAL(target)].value.f;
		}else{
			accumulator.value.f += variables[VARIABLE_TO_LOCAL(target)].value.i;
		}
		
		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "ODU") == 0){
	
		VAR_OUT_OF_BOUNDS_CHECK(target);
		ACM_TYPE_CHECK('R');
		VAR_TYPE_DOUBLE_CHECK(target, 'R', 'C');

		if(variables[VARIABLE_TO_LOCAL(target)].type == 'R'){
			accumulator.value.f -= variables[VARIABLE_TO_LOCAL(target)].value.f;
		}else{
			accumulator.value.f -= variables[VARIABLE_TO_LOCAL(target)].value.i;
		}

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "MNO") == 0){
				
		VAR_OUT_OF_BOUNDS_CHECK(target);		
		ACM_TYPE_CHECK('R');
		VAR_TYPE_DOUBLE_CHECK(target, 'R', 'C');

		if(variables[VARIABLE_TO_LOCAL(target)].type == 'R'){
			accumulator.value.f *= variables[VARIABLE_TO_LOCAL(target)].value.f;
		}else{
			accumulator.value.f *= variables[VARIABLE_TO_LOCAL(target)].value.i;
		}

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "DEL") == 0){
				
		VAR_OUT_OF_BOUNDS_CHECK(target);
		ACM_TYPE_CHECK('R');
		VAR_TYPE_DOUBLE_CHECK(target, 'R', 'C');

		if(variables[VARIABLE_TO_LOCAL(target)].type == 'R'){
			accumulator.value.f /= variables[VARIABLE_TO_LOCAL(target)].value.f;
		}else{
			accumulator.value.f /= variables[VARIABLE_TO_LOCAL(target)].value.i;
		}

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "PZA") == 0){
		
		ACM_TYPE_CHECK('R');

		accumulator.value.f = -accumulator.value.f;

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "SABF") == 0){
				
		VAR_OUT_OF_BOUNDS_CHECK(target);
		ACM_VAR_TYPE_CHECK(target, 'C');

		accumulator.value.i += variables[VARIABLE_TO_LOCAL(target)].value.i;

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "ODUF") == 0){
						
		VAR_OUT_OF_BOUNDS_CHECK(target);
		ACM_VAR_TYPE_CHECK(target, 'C');

		accumulator.value.i -= variables[VARIABLE_TO_LOCAL(target)].value.i;

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "MNOF") == 0){
						
		VAR_OUT_OF_BOUNDS_CHECK(target);
		ACM_VAR_TYPE_CHECK(target, 'C');

		accumulator.value.i *= variables[VARIABLE_TO_LOCAL(target)].value.i;

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "DELF") == 0){
						
		VAR_OUT_OF_BOUNDS_CHECK(target);
		ACM_VAR_TYPE_CHECK(target, 'C');

		accumulator.value.i /= variables[VARIABLE_TO_LOCAL(target)].value.i;

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "PZAF") == 0){
		
		ACM_TYPE_CHECK('C');

		accumulator.value.i = -accumulator.value.i;

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "KON") == 0){
			
		VAR_OUT_OF_BOUNDS_CHECK(target);

		accumulator.value.c =  accumulator.value.c & variables[VARIABLE_TO_LOCAL(target)].value.c;

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "DIS") == 0){

		VAR_OUT_OF_BOUNDS_CHECK(target);

		accumulator.value.c =  accumulator.value.c | variables[VARIABLE_TO_LOCAL(target)].value.c;

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "NEG") == 0){

		switch(accumulator.type){
			case 'M':
				variables[VARIABLE_TO_LOCAL(target)].value.i *= -1;
			break;
			case 'C':
				variables[VARIABLE_TO_LOCAL(target)].value.i *= -1;
			break;
			case 'R':
				variables[VARIABLE_TO_LOCAL(target)].value.f *= -1;
			break;
			case 'Z':
				NEGATIVE_CHAR_TYPE_ERROR;
			break;
		}

		return OPERATION_TO_LOCAL(o.address) + 1;
	}else if(strcmp(o.command, "POL") == 0){
		
		switch(accumulator.type){
			case 'M':
				accumulator.value.i <<= target;
			break;
			case 'C':
				accumulator.value.i <<= target;
			break;
			case 'R':
				BIT_SHIFTING_FLOATING_POINT_ERROR("POL");
			break;
			case 'Z':
				accumulator.value.c <<= target;
			break;
		}

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "POD") == 0){
			
		switch(accumulator.type){
			case 'M':
				accumulator.value.i >>= target;
			break;
			case 'C':
				accumulator.value.i >>= target;
			break;
			case 'R':
				BIT_SHIFTING_FLOATING_POINT_ERROR("POD");
			break;
			case 'Z':
				accumulator.value.c >>= target;
			break;
		}

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "MUA") == 0){
	
		VAR_OUT_OF_BOUNDS_CHECK(target);

		switch(variables[VARIABLE_TO_LOCAL(target)].type){
			case 'M':
				accumulator.type = 'M';
				accumulator.value.i = variables[VARIABLE_TO_LOCAL(target)].value.i;
			break;
			case 'C':
				accumulator.type = 'C';
				accumulator.value.i = variables[VARIABLE_TO_LOCAL(target)].value.i;
			break;
			case 'R':
				accumulator.type = 'R';
				accumulator.value.f = variables[VARIABLE_TO_LOCAL(target)].value.f;
			break;
			case 'Z':
				accumulator.type = 'Z';
				accumulator.value.c = variables[VARIABLE_TO_LOCAL(target)].value.c;
			break;
		}
		
		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "AUM") == 0){
	
		VAR_OUT_OF_BOUNDS_CHECK(target);		

		switch(accumulator.type){
			case 'M':
				variables[VARIABLE_TO_LOCAL(target)].type = 'M';
				variables[VARIABLE_TO_LOCAL(target)].value.i = accumulator.value.i;
			break;
			case 'C':
				variables[VARIABLE_TO_LOCAL(target)].type = 'C';
				variables[VARIABLE_TO_LOCAL(target)].value.i = accumulator.value.i;
			break;
			case 'R':
				variables[VARIABLE_TO_LOCAL(target)].type = 'R';
				variables[VARIABLE_TO_LOCAL(target)].value.f = accumulator.value.f;
			break;
			case 'Z':
				variables[VARIABLE_TO_LOCAL(target)].type = 'Z';
				variables[VARIABLE_TO_LOCAL(target)].value.c = accumulator.value.c;
			break;
		}
		
		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "NES") == 0){
		
		OPERATION_OUT_OF_BOUNDS_CHECK(target);		

		if(accumulator.value.i < 0)
			return OPERATION_TO_LOCAL(target);

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "NUS") == 0){
		
		OPERATION_OUT_OF_BOUNDS_CHECK(target);		

		if(accumulator.value.i == 0)
			return OPERATION_TO_LOCAL(target);

		return OPERATION_TO_LOCAL(o.address) + 1;

	}else if(strcmp(o.command, "BES") == 0){
		
		OPERATION_OUT_OF_BOUNDS_CHECK(target);		
		return OPERATION_TO_LOCAL(target);

	}else if(strcmp(o.command, "ZAR") == 0){
		return -100;
	}
	
	return 0;
}
