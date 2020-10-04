#include "vm.h"

virtualMachine::virtualMachine(){
    memory.reserve(10000000000);
    reg[R_PC] = 0x00000000; //starting point for the program usable memory
    reg[R_DS] = 0x0000F000;
    reg[R_DC] = 0x0000F000;
}

void virtualMachine::loadInstructions(std::vector<i32> prog){
    /* Loading all the instruction into the memory */
    i32 i;
    i32 pc = reg[R_PC];
    // i32 sp = reg[R_SP];
    std::cout << pc << " " << sp << std::endl;
    for(i = 0;i<prog.size();i++){
        memory[pc] = prog[i];
        pc++;
    }
    std::cout << pc << std::endl;
    reg[R_END] = pc;

}

i32 signextend(i32 x, int bit_count){

    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFFFFFF << bit_count);
    }
    return x;
}

i32 virtualMachine::readMemory(i32 address){
    return memory[address];
}

void virtualMachine::writeMemory(i32 address, i32 val){
    memory[address] = val;
    // reg[R_PC]+=1;
}

void virtualMachine::executeInstruction(i32 instruction){
    /* Running intructions from the memory */
    i32 operation;
    operation = (instruction >> 24) & 0x000000FF;
    switch (operation){
        case OP_ADD: {  //working
            //add
            std::cout << "Adding ..." << std::endl;
            i32 option = (instruction >> 10) & 0x00000001;
            i32 dest = (instruction >> 18) & 0x0000003F;
            i32 src1 = (instruction >> 12) & 0x0000003F;
            std::cout << dest << " " <<src1 << std::endl;
            if(option == 0){
                // Register Mode
                i32 src2 = instruction & 0x0000003F;
                std::cout << src2 << std::endl;
                reg[dest] = reg[src1] + reg[src2];
            } else {
                // Immediate Mode
                std::cout << "Immediate Mode" << std::endl;
                i32 mem = instruction & 0x000003FF;
                i32 imm5 = signextend(mem,10);
                reg[dest] = reg[src1] + imm5;
            }
            // reg[R_SP]+=1;
            std::cout << "finished Adding" << std::endl;
            break;
        }
        case OP_LOAD:{      //working
            //Load
            std::cout << "Loading Data" << std::endl;
            i32 dest = (instruction >> 18) & 0x0000003F;
            i32 pc = instruction & 0x0002FFFF;
            std::cout << "pc : "  << pc << std::endl;
            i32 pcoffset = signextend(pc,18);
            std::cout << "Offset : " << pcoffset <<std::endl;
            // reg[dest] = readMemory(reg[R_PC] + pcoffset);
            reg[dest] = readMemory(reg[R_DS] + pcoffset);
            break;
        }

        case OP_STR:       //working
            //Store
            {
            std::cout << "Storing Into Memory" << std::endl;
            i32 sr = (instruction >> 18) & 0x0000003F;
            std::cout << reg[sr] << std::endl;
            i32 off = (instruction & 0x0002FFFF);
            i32 offset = signextend(off,12);
            std::cout << offset << std::endl;
            writeMemory(reg[R_DS] + offset,reg[sr]);
            std::cout << "Memory written" << std::endl;
            reg[6] = readMemory(reg[R_DS] + offset);
            break;

            }
        // case OP_JMPR:
            //Jump register
        case OP_BAND:   //working
        {
             //bitwise and
            std::cout << "Bitwise And" << std::endl;
            i32 option = (instruction >> 10) & 0x00000001;
            i32 dest = (instruction >> 18) & 0x0000003F;
            i32 src1 = (instruction >> 12) & 0x0000003F;
            if(option == 0){
                // Register Mode
                i32 src2 = instruction & 0x0000003F;
                reg[dest] = reg[src1] & reg[src2];
            } else {
                // Immediate Mode
                i32 mem = instruction & 0x000003FF;
                i32 imm5 = signextend(mem,10);
                reg[dest] = reg[src1] & imm5;
            }
            // reg[R_SP]=+1;
            break;
        }
        case OP_LDR:{
            //load register
            i32 dest = (instruction >> 18) & 0x0000003F;
            i32 r1 = (instruction >> 12) & 0x0000003F;
            i32 off = (instruction & 0x00000FFF);
            i32 offset = signextend(off,12);
            reg[dest] = readMemory(reg[r1] + offset);
            break;

        } 
        case OP_STRR:
            //store register
            {
                i32 r0 = (instruction >> 18) & 0x0000003F;
                i32 r1 = (instruction >> 12) & 0x0000003F;
                i32 offset = signextend(instruction & 0x00000FFF, 12);
                writeMemory(reg[r1] + offset, reg[r0]);
                break;
            }
        // case OP_UNS:
            //unused
        case OP_BNOT:       //working
            //bitwise not
            {
            std::cout << "Noting" << std::endl;
            i32 r0 = (instruction >> 18) & 0x0000003F;
            i32 r1 = (instruction >> 12) & 0x0000003F;
            reg[r0] = ~reg[r1];
            // sp++;
            break;
            }
        case OP_LDID:
            // load indirect
            {
            i32 dest = (instruction >> 18) & 0x6;
            i32 pc = instruction & 0x00000010;
            i32 pcoffset = signextend(pc,16);
            reg[dest] = readMemory(readMemory(reg[R_DS] + pcoffset));
            break;
            }
        case OP_STRID:
            //store indirect
            {
            i32 sr = (instruction >> 18) & 0x6;
            i32 off = (instruction & 0xC);
            i32 offset = signextend(off,12);
            writeMemory(readMemory(reg[R_DS] + offset),reg[sr]);
            break;
            }
        case OP_JMP:{
            //jump
            i32 r1 = (instruction >> 12) & 0x0000003F;
            reg[R_PC] = reg[r1];
            break;
        }
            
        // case OP_RSD:
            //reserved
        case OP_LDEFAD:
            //load effective address
            {
            i32 dest = (instruction >> 18) & 0x0000003F;
            i32 pc = instruction & 0x0002FFFF;
            i32 pcoffset = signextend(pc,18);
            reg[dest] = reg[R_PC] + pcoffset;
            break;
            }
        // case OP_TRP:
            //execute trap
            // break;

    }
    // reg[R_SP]+=1;
}

void virtualMachine::readAllRegisters(){
    int i = 0;
    for(i = 0;i<10;i++){
        std::cout << reg[i] << std::endl;
    }
}

void virtualMachine::writeData(i32 data){
    writeMemory(reg[R_DC],data);
    reg[R_DC]+=1;
}

/* Helper function to test the working of the virtual Machine */
void virtualMachine::initialise_register(int r, i32 val){
    reg[r] = val;
}

void virtualMachine::run(){
    /* Fetching instruction from the memory and executing it */
    while(reg[R_PC] != reg[R_END]){
        i32 instructionAddress = reg[R_PC];
        reg[R_PC]+=1;
        executeInstruction(memory[instructionAddress]);
    }
}

