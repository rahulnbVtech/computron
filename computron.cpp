#include "computron.h"

#include <fstream>
#include <iomanip>


/*
* method to load the file which has all the CML instructions
*/
void load_from_file(std::array<int, memorySize>& memory, const std::string& filename)
{
	constexpr int sentinel{ -99999 };// terminates reading after -99999
	size_t i{ 0 };
	std::string line;
	int instruction;

    std::ifstream inputFile(filename); // the input file

     
    if (!inputFile) { // if input file doesn't exist, it should throw a runtime error
        throw std::runtime_error("invalid_input");
    }


    while (std::getline(inputFile, line)) { // goes through the text file as long as there is a line
        instruction = std::stoi(line);
        if (instruction == sentinel)
            break;

        if (validWord(instruction)) { // checking to see if the word is valid
            memory[i] = instruction;
            i++;
        }
        else {
            throw std::runtime_error("invalid_input");
        }
    }
    inputFile.close();
}


/*
* method to determine what opcode returns what kind of command
*/
Command opCodeToCommand(size_t opCode) {
    switch (opCode) {
        case 10: return Command::read;
        case 11: return Command::write;
        case 20: return Command::load;
        case 21: return Command::store;
        case 30: return Command::add;
        case 31: return Command::subtract;
        case 32: return Command::divide;
        case 33: return Command::multiply;
        case 40: return Command::branch;
        case 41: return Command::branchNeg;
        case 42: return Command::branchZero;
        case 43: return Command::halt;
        default: return Command::halt;
    };
};

/*
* method to execute the CML instructions as given by the text file
*/
void execute(std::array<int, memorySize>& memory, int* const acPtr, size_t* const icPtr, int* const irPtr, size_t* const opCodePtr, size_t* const opPtr, const std::vector<int>& inputs)
{
    size_t inputIndex{ 0 };

    do {
        /*
        * instruction counter to register
        */
        *irPtr = memory[*icPtr]; //instructionRegister = memory [instructionCounter];
        *opCodePtr = *irPtr / 100; //operationCode = instructionRegister / 100; // divide
        *opPtr = *irPtr % 100; //operand = instructionRegister % 100; // remainder

        int word{}; // word to be used 

        switch (opCodeToCommand(*opCodePtr)) { // switch statement to determine what happens in each of the commands

        
        case Command::read: // reads word from vector into a particular memory location
            word = inputs[inputIndex];
            memory[*opPtr] = word;
            (*icPtr)++;
            inputIndex++;
            break;

        case Command::write: // writes word from a particular memory location onto the screen
            (*icPtr)++;
            break;

        case Command::load: // loads word from a particular memory location into the accumulator (the result is left in the accumulator)
            *acPtr = memory[*opPtr];
            (*icPtr)++;
            break;

        case Command::store: // stores word from accumulator into a particular memory location
            memory[*opPtr] = *acPtr;
            (*icPtr)++;
            break;

        case Command::add: // add word from memory location to the word in the accumulator (leave result in the accumulator)
            word = memory[*opPtr] + *acPtr;
            if (validWord(word)) {
                *acPtr = word;
                (*icPtr)++;
            }
            else {
                throw std::runtime_error("invalid_input");
            }
            break;

        case Command::subtract: // subtract word from memory location from the word in the accumulator (leave result in the accumulator)
            word = *acPtr - memory[*opPtr];
            if (validWord(word)) {
                *acPtr = word;
                (*icPtr)++;
            }
            else {
                throw std::runtime_error("invalid_input");
            }
            break;

        case Command::multiply: // multiply word from memory location to the word in the accumulator (leave result in the accumulator)
            word = memory[*opPtr] * *acPtr;
            if (validWord(word)) {
                *acPtr = word;
                (*icPtr)++;
            }
            else {
                throw std::runtime_error("invalid_input");
            }
            break;

        case Command::divide: // divide word from memory location into the word in the accumulator (leave result in the accumulator)
            if (memory[*opPtr] == 0) {
                throw std::runtime_error("invalid_input");
            }
            word = (int)(*acPtr / memory[*opPtr]);
            if (validWord(word)) {
                *acPtr = word;
                (*icPtr)++;
            }
            else {
                throw std::runtime_error("invalid_input");
            }
            break;

        case Command::branch: // branch to particular memory location
            *icPtr = *opPtr;
            break;

        case Command::branchNeg: // branch to particular memory location if accumulator is negative
            *acPtr < 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;

        case Command::branchZero: // branch to particular memory location if accumulator is zero
            *acPtr == 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;

        case Command::halt: // program has completed its task and the program should stop
            break;
        }

    }while (opCodeToCommand(*opCodePtr) != Command::halt);


};


/*
* dump method prints out the memory dump
*/
void dump(std::array<int, memorySize>& memory, int accumulator, size_t instructionCounter, size_t instructionRegister, size_t operationCode, size_t operand)
{

}

/*
* method checks to see if the word is valid or not
* valid word is determined by whether or not it is less than 9999 and greater -9999
*/
bool validWord(int word) 
{
    if (word >= minWord && word <= maxWord) {
        return true;
    }

    return false;
}

/*
* output function prints out the contents of all registers
*/
void output(std::string label, int width, int value, bool sign)
{

}
