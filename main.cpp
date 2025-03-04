#include "computron.h"

int main() {
    std::array<int, memorySize> memory{ 0 };
    int accumulator{ 0 };
    size_t instructionCounter{ 0 };
    int instructionRegister{ 0 }; 
    size_t operationCode{ 0 };
    size_t operand{ 0 };
    const std::vector<int> inputs{ 4,5 };

    load_from_file(memory, "p1.txt"); // loading the text file

    execute(memory, &accumulator, &instructionCounter, &instructionRegister,
        &operationCode, &operand, inputs); // executing the instructions from the test files

    dump(memory, accumulator, instructionCounter, instructionRegister, 
         operationCode, operand); // printing out the memory dump

    return 0;
}
