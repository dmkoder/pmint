#define RED   red
#define GRN   grn
#define YEL   yel
#define BLU   blu
#define MAG   mag
#define CYN   cyn
#define WHT   wht
#define RESET reset


#define VARIABLES_SIZE (declarationEndAddress - startAddress + 1)
#define OPERATIONS_SIZE (endAddress - declarationEndAddress)
#define VARIABLE_TO_LOCAL(address) (address - startAddress)
#define OPERATION_TO_LOCAL(address) (address - declarationEndAddress - 1)

#define CHECK_VARIABLE_ADDRESS(address) (VARIABLE_TO_LOCAL(address) < 0 || VARIABLE_TO_LOCAL(address) > VARIABLES_SIZE)
#define CHECK_OPERATION_ADDRESS(address) (OPERATION_TO_LOCAL(address) < 0 || OPERATION_TO_LOCAL(address) > OPERATIONS_SIZE)

#define VAR_OUT_OF_BOUNDS_CHECK(address) if(CHECK_VARIABLE_ADDRESS(address)) \
									{ printf("%s RUNTIME ERROR: %s >>> Out of bounds! Address %d is not defined! <<< \n%s", RED, YEL, address, RESET); return -1404; }

#define VAR_TYPE_DOUBLE_CHECK(address, varTypeA, varTypeB) if(variables[VARIABLE_TO_LOCAL(address)].type != varTypeA && variables[VARIABLE_TO_LOCAL(address)].type != varTypeB) \
									{ printf("%s RUNTIME ERROR: %s >>> Type mismatch! Variable type: %c. Type should be: %c or %c! <<< \n%s" , RED, YEL, variables[VARIABLE_TO_LOCAL(address)].type, varTypeA, varTypeB, RESET); return -1505; }

#define ACM_VAR_TYPE_CHECK(address, varType) if(accumulator.type != varType || variables[VARIABLE_TO_LOCAL(address)].type != varType) \
									{ printf("%s RUNTIME ERROR: %s >>> Type mismatch! Accumulator type: %c. Variable type: %c. Type should be: %c! <<< \n%s", RED, YEL, accumulator.type, variables[VARIABLE_TO_LOCAL(address)].type, varType, RESET); return -1505; }

#define ACM_TYPE_CHECK(varType) if(accumulator.type != varType) \
									{ printf("%s RUNTIME ERROR: %s >>> Type mismatch! Accumulator type: %c. Type should be: %c! <<< \n%s", RED, YEL, accumulator.type, varType, RESET); return -1505; }

#define OPERATION_OUT_OF_BOUNDS_CHECK(address) if(CHECK_OPERATION_ADDRESS(address)) \
									{ printf("%s RUNTIME ERROR: %s >>> Out of bounds! Address %d is not defined! <<< \n%s", RED, YEL, address, RESET); return -1404; }

#define BIT_SHIFTING_FLOATING_POINT_ERROR(direction) printf("%s RUNTIME ERROR: %s >>> Bit shifting operation error! It is not posible to do %s operation on floating point type! <<< \n%s", RED, YEL, direction, RESET); return -1606;

#define NEGATIVE_CHAR_TYPE_ERROR printf("%s RUNTIME ERROR: %s >>> Negative char type error! It is not posible to do NEG operation on char type! <<< \n%s", RED, YEL, RESET); return -1707;

