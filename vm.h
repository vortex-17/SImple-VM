#ifndef VM
#define VM

#include <iostream>
#include <vector>

/*
* VM2 is a 32-bit Virtual Machine with a Memory of 500 MB.
* This header file defines the hardware of the the Virtual Machine
* We will define the Registers, Memory Set, Instruction Set
*/

/*
 *** Instruction Format ***
Instruction length = 32 bit
*/

typedef uint32_t i32;

/* 
Registers : We have 8 General Purpose Registers
We have 3 Special Purpose Registers
*/ 
enum Registers {
    R_R0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, //Program Counter
    // R_SP, // Stack pointer
    R_END, // To determine the address of the last instruction in the memory to increment the value of PC
    R_COND, //Conditional Register
    R_DS, //for start for data 
    R_DC, //data counter
    R_COUNT
};

/*
OPCODES : There are 16 Opcodes which define different Functions
*/

enum OPCODES {
    OP_BR = 0x00000001, //BRANCH
    OP_ADD = 0x00000002, //ADD
    OP_LOAD = 0x00000003, //LOAD
    OP_STR = 0x00000004, //STORE
    OP_JMPR = 0x00000005, // JUMP REGISTER
    OP_BAND = 0x00000006, //BITWISE ADD
    OP_LDR = 0x00000007, //LOAD REGISTER
    OP_STRR = 0x00000008, //STORE REGISTER
    OP_UNS = 0x00000009, // UNUSED
    OP_BNOT = 0x0000000A, //BITWISE NOT
    OP_LDID = 0x0000000B, //LOAD INDIRECT
    OP_STRID = 0x0000000C, //STORE INDIRECT
    OP_JMP = 0x0000000D, //JUMP
    OP_RSD = 0x0000000E, //RESERVED (UNUSED)
    OP_LDEFAD = 0x0000000F, //LOAD EFFECTIVE ADDRESS
    OP_TRP = 0x0000001F//EXECUTE TRAP
};

/*  TRAP CODES */

enum TRAP {
    TRAP_GETC = 0x20,  /* get character from keyboard, not echoed onto the terminal */
    TRAP_OUT = 0x21,   /* output a character */
    TRAP_PUTS = 0x22,  /* output a word string */
    TRAP_IN = 0x23,    /* get character from keyboard, echoed onto the terminal */
    TRAP_PUTSP = 0x24, /* output a byte string */
    TRAP_HALT = 0x25   /* halt the program */
};


class virtualMachine {
    private:
    i32 pc = 0; //program counter
    i32 sp = 0;     //stack pointer
    i32 reg[R_COUNT];
    std::vector<i32> memory; //needs to be changed to accomodate for 500 MB
    i32 readMemory(i32 address);
    void writeMemory(i32 address, i32 val);
    
    
    public:
    i32 ds;
    virtualMachine();
    void run();
    void loadInstructions(std::vector<i32> prog);
    void executeInstruction(i32 instruction);
    void readAllRegisters();
    void writeData(i32 data);
    void clearMemory();

    //helper function to test
    void initialise_register(int r, i32 val);


};



#endif