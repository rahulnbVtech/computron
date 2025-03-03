#include "computron.h"

#include <fstream>
#include <iomanip>

void load_from_file(std::array<int, memorySize>& memory, const std::string& filename)
{
	constexpr int sentinel{ -99999 };// terminates reading after -99999
	size_t i{ 0 };
	std::string line;
	int instruction;

    std::ifstream inputFile(filename);
    if (!inputFile) {
        throw std::runtime_error("invalid_input");
    }
        // throw runtime_error exception with string "invalid_input"


    while (std::getline(inputFile, line)) {
        instruction = std::stoi(line);
        if (instruction == sentinel)
            break;

            // Check if the instruction is valid using the validWord function
            // If the instruction is valid, store it in memory at position 'i' and increment 'i'
            // If the instruction is invalid, throw a runtime error with the message "invalid_input"

        if (validWord(instruction)) {
            memory[i] = instruction;
            i++;
        }
        else {
            throw std::runtime_error("invalid_input");
        }
    }
    inputFile.close();
}

Command opCodeToCommand(size_t opCode) {
    switch (opCode) {
        case 10: return Command::read;
        case 11: return Command::write;
        case 21: return Command::load;
        case 22: return Command::store;
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

void execute(std::array<int, memorySize>& memory, int* const acPtr, size_t* const icPtr, int* const irPtr, size_t* const opCodePtr, size_t* const opPtr, const std::vector<int>& inputs)
{
    size_t inputIndex{ 0 };

    do {
        //instruction counter to register


        *irPtr = memory[*icPtr];
        *opCodePtr = *irPtr / 100;
        *opPtr = *irPtr % 100;

        int word{};

        switch (opCodeToCommand(*opCodePtr)) {
        case Command::read:
            word = inputs[inputIndex];
            memory[*opPtr] = word;
            (*icPtr)++;
            inputIndex++;
            break;

        case Command::write:
            (*icPtr)++;
            break;

        case Command::load:
            *acPtr = memory.at(*opPtr);
            (*icPtr)++;
            break;

        case Command::store:
            memory.at(*opPtr) = *acPtr;
            (*icPtr)++;
            break;

        case Command::add:
            word = memory[*opPtr] + *acPtr;
            if (validWord(word)) {
                *acPtr = word;
                (*icPtr)++;
            }
            else {
                throw std::runtime_error("invalid_input");
            }
            break;

        case Command::subtract:
            word = *acPtr - memory[*opPtr];
            if (validWord(word)) {
                *acPtr = word;
                (*icPtr)++;
            }
            else {
                throw std::runtime_error("invalid_input");
            }
            break;

        case Command::multiply:
            word = memory[*opPtr] * *acPtr;
            if (validWord(word)) {
                *acPtr = word;
                (*icPtr)++;
            }
            else {
                throw std::runtime_error("invalid_input");
            }
            break;

        case Command::divide:
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

        case Command::branch:
            *icPtr = *opPtr;
            break;

        case Command::branchNeg:
            *acPtr < 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;

        case Command::branchZero:
            *acPtr == 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;

        case Command::halt:
            break;
        }

    }while (opCodeToCommand(*opCodePtr) != Command::halt);


};



void dump(std::array<int, memorySize>& memory, int accumulator, size_t instructionCounter, size_t instructionRegister, size_t operationCode, size_t operand)
{

}

bool validWord(int word)
{
    if (word >= minWord && word <= maxWord) {
        return true;
    }

    return false;
}

void output(std::string label, int width, int value, bool sign)
{

}
