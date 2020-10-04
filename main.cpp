#include "vm.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void parser(string name);
void lexer(vector<string>ins);

int main(int argc, char *argv[]){
    vector<i32> prog;
    prog.push_back(0b00000110000010000000010000000001);
    prog.push_back(0b00000010000011000000000000000001);
    prog.push_back(0b00000011000100000000000000000000);
    prog.push_back(0b00000100000000000000000000000000);
    prog.push_back(0b00001010000000000001111111111111);
    virtualMachine *vm = NULL;
    cout << "Creating a new Virtual Machine" << endl;
    vm = new virtualMachine();
    cout << "Initialising Registers" << endl;
    vm->initialise_register(0,5);
    vm->initialise_register(1,6);
    vm->writeData(13);
    cout << "Loading Instructions" << endl;
    vm->loadInstructions(prog);
    cout << "Running Instructions" << endl;
    vm->run();
    vm->readAllRegisters();
    int x = 0b000100;
    return 0;
}

void parser(string name){
    //read file
    ifstream infile;
    infile.open(name);
    if(!infile.is_open()){
        cout << "Error : Could not open the file" << endl;
        exit(1);
    }

    string line;
    string content;

    while(getline(infile,line)){
        vector<string>ins;
        string word = "";
        for(auto x:line){
            if(x == ' '){
                ins.push_back(word);
                word = "";
            } else {
                word = word+x;
            }
        }

        ins.push_back(word);
        lexer(ins);
            
    }
    infile.close();

}

void lexer(vector<string>ins){
    string operation = ins[0];
    string Reg = ins[1];
    if(operation == "OP_BR"){

    } else if(operation == "OP_ADD"){
            
    } else if(operation == "OP_LOAD"){

    } else if(operation == "OP_STR"){

    } else if(operation == "OP_JMPR"){

    } else if(operation == "OP_BAND"){

    } else if(operation == "OP_BNOT"){

    } else if(operation == "OP_JMP"){ 

    } else if(operation == "OP_TRP"){

    } else {
        cout << "Wrong Instruction" << endl;
    }

    /* For Register */
    if(Reg == "R0"){

    } else if(Reg == "R1"){

    } else if(Reg == "R2"){

    } else if(Reg == "R3"){

    } else if(Reg == "R4"){

    } else if(Reg == "R5"){

    } else if(Reg == "R6"){

    } else if(Reg == "R7"){

    } else {
        cout << "Wrong Register" << endl;
    }
}