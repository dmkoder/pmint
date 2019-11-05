union Data {
	int i;
	float f;
	unsigned int c;
};

typedef struct Variable{
	int address;
	char type;
	union Data value;
} variable;

typedef struct Operation{
	int address;
	char command[5];
	int value;
} operation;

typedef struct Command{
	int address;
	char command[5];
	union Data value;
	struct Command *next;
} command;
