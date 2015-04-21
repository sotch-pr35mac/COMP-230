/*
 * File: disassemble.h
 * Author: Preston Stosur-Bassett
 * Date: 17.4.15
 * Description: TODO: write this
*/

/*
 * @Description: <code>opCode</code> gets the decimal value of the MIPS instruction op code and returns it as an integer.
 * @Pre-Condition <code>char instruction[]</code> is a 'string' (an array of char's) is a valid 32-bit MIPS instruction, where the first 6 bits is the op-code.
 * @Post-Condition: returns the correct decimal representation for the 6-bit opcode of the valid 32-bit MIPS instruction.
*/
int opCode(char instruction[]);

/*
 * @Description: <code>getFormat</code> gets the format of the MIPS instruction and returns it as a char
 * @Pre-Condition: <code>int decimalOpCode</code> is the decimal representation of the valid 32-bit MIPS instruction opCode.
 * @Post-Condition: returns the correct format for the instruction that was passed.
*/
char* getFormat(int decimalOpCode);

/*
 * @Description: <code>getRFunction</code> gets the function name of the valid 32-bit MIPS R-format instruction.
 * @Pre-Codition: <code>int functionDecimal</code> is a integer of the decimal representation of the R-format function code.
 * @Post-Condition: returns the name of the function code if found, otherwise returns "NULL"
*/
char* getRFunction(int functionDecimal);

/*
 * @Description: <code>getICommand</code> gets the name of the valid 32-bit MIPS instruction that is of type-I
 * @Pre-Condition: <code>int opCode</code> is the valid decimal opcode (the first 6-bits of the 32-bit MIPS instruction).
 * @Post-Condition: returns the correct command name for the given op code, if not found, returns "NULL"
*/
char* getICommand(int opCode);

/*
 * @Description: <code>getJCommand</code> gets the name of the valid 32-bit MIPS instruction J-Command
 * @Pre-Condition: <code>int opCode</code> is a valid deciaml opCode for a 32-bit MIPS instruction in J-Format
 * @Post-Condition: returns the correct J-format command, if not found, returns "NULL"
*/
char* getJCommand(int opCode);

/* TODO: put function spec here */
int getShiftAmount(char instruction[]);

/* TODO: put function spec here */
int getFunctionCode(char instruction[]);

/* TODO: put the function spec here */
int getRegNum(char instruction[], int regPlacement);
