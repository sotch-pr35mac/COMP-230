/*
 * File: disassemble.h
 * Author: Preston Stosur-Bassett
 * Date: 17.4.15
 * Description: This is the .h file that contains all the functions present in disassemble.c
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

/*
 * @Description: <code>getShiftAmount</code> gets the shift amount of the valid 32-bit MIPS instruction and returns it as an integer
 * @Pre-Condition: <code>char instruction[]</code> is a valid 32-bit MIPS instruction
 * @Post-Condition: returns the correct integer for R-type instructions that have a shift amount
*/
int getShiftAmount(char instruction[]);

/*
 * @Description: <code>getFunctionCode</code> gets the function decimal value for a valid 32-bit MIPS R-type MIPS instruction
 * @Pre-Condition: <code>char instruction[]</code> is a valid 32-bit MIPS instruction
 * @Post-Condition: returns the decimal equivalent of the R-Type function code as an integer value
*/
int getFunctionCode(char instruction[]);

/*
 * @Description: <code>getRegNum</code> gets the decimal value of the register
 * @Pre-Condition: <code>char instruction[]<code> is a valid 32-bit MIPS instruction. <code>int regPlacement</code> is the placement register number that should get returned (0 for rs, 1 for rt, 2 for rd)
 * @Post-Condition: returns the decimal value of the register number as an integer
*/
int getRegNum(char instruction[], int regPlacement);
