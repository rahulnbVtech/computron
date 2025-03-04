#ifndef COMPUTRON_H
#define COMPUTRON_H

#include <iostream>
#include <array>
#include <string>
#include <vector>

constexpr size_t memorySize{ 100 }; // size of the memory
constexpr int minWord{ -9999 }; // value of min word
constexpr int maxWord{ 9999 }; // value of max word


/*
* class definition for commands
*/
enum class Command {
	read = 10, write,
	load = 20, store,
	add = 30, subtract, divide, multiply,
	branch = 40, branchNeg, branchZero, halt
};

/*
* method to load the file which has all the CML instructions
*/
void load_from_file(std::array<int, memorySize>& memory, const std::string& filename);

/*
* method to execute the CML instructions as given by the text file
*/
void execute(std::array<int, memorySize>& memory, int* const acPtr,
	size_t* const icPtr, int* const irPtr,
	size_t* const opCodePtr, size_t* const opPtr,
	const std::vector<int>& inputs);

/*
* dump method prints out the memory dump
*/
void dump(std::array<int, memorySize>& memory, int accumulator,
	size_t instructionCounter, size_t instructionRegister,
	size_t operationCode, size_t operand);

/*
* method checks to see if the word is valid or not
* valid word is determined by whether or not it is less than 9999 and greater -9999
*/
bool validWord(int word);

/*
* output function prints out the contents of all registers
*/
void output(std::string label, int width, int value, bool sign);


#endif // !COMPUTRON_H