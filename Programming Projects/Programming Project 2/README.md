#Disassemblr.o

### About Disassemblr
Disassemblr.o reads in 32-bit MIPS binary instructions and converts them to human-readable MIPS assembly code. **Notice**: Disassmblr.o does not support all MIPS assembly commands. For a list of currently supported commands please read our "Supported Commands" section.

### How to use Disassemblr.o
Disassmblr can be used via command-line:

* `cd /path/to/disassemblr.o`
* `./disassemblr.o /path/to/text-file-containing-binary-MIPS-commands`

Or alternatively

* `cd /path/to/disassemblr.o`
* `./disassemblr.o`
* Enter 32-bit MIPS binary commands manually line by line.

### How to Read Disassemblr.o Output
Disassemblr will output correctly formatted MIPS commands preceeded with a line number from the passed in text file. For example: `1. add $t0, $t1, $t2`. If an unrecognized register or command is attempted to be used Disassemblr will give an error and fill the space in the formatted output with `NULL`. (For example: `2. add NULL, $zero, $t0`) For fatal errors, Disassemblr will print where the error occured and an error message. 

### Suppoted MIPS Commands

#### Supported R-Format Functions
* `add`
* `addu`
* `and`
* `jr`
* `nor`
* `or`
* `slt`
* `sltu`
* `sll`
* `srl`
* `sub`
* `subu`

#### Supported I-Format Commands
* `addi`
* `addiu`
* `andi`
* `beq`
* `bne`
* `lbu`
* `lhu`
* `ll`
* `lui`
* `lw`
* `ori`
* `slti`
* `sltiu`
* `sb`
* `sc`
* `sh`
* `sw`

#### Supported J-Format Commands
* `j`
* `jal`
