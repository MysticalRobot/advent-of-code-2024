#include <iostream>
using namespace std;

long powOf2(long power);
long comboOperand(long* registers, char literalOperand);

int main() {
  string program = "2,4,1,1,7,5,4,0,0,3,1,6,5,5,3,0";
  long goalRegisters[3]; 
  long registers[3];
  // A needs to be 0 for the program to quit
  long goalRegisters[3] = {0, 0, 0};
  long A = -1;
  for (int i = program.size() - 1; i != -2; i -= 2) {
    char goalOutput = program[i];
    
    while (output != goalOutput && registers[0] != goalRegisters[0] 
    && registers[1] != goalRegisters[1] 
    && registers[2] != goalRegisters[2]) {
      // increment A (start at 0)
      A += 1;
      // initialize registers
      registers[0] = A; registers[1] = 0; registers[2] = 0;
      // process the instruction and operand pairs
      char instruction, literalOperand, out;
      for (int j = 0; j != program.size() + 1;) {
        // by default, use the literal operand
        // get the combo operand as needed
        instruction = program[j], literalOperand = program[j + 2];
        switch (instruction) {
          case '0': // adv
            registers[0] /= powOf2(comboOperand(registers, literalOperand));
            break;
          case '1': // bxl
            registers[1] ^= (literalOperand - '0');
            break;
          case '2': // bst
            registers[1] = comboOperand(registers, literalOperand) % 8;
            break;
          case '3': // jnz
            if (registers[0] != 0) {
              // jump to instruction at literal operand
              j = (literalOperand - '0') * 4;
              continue;
            }
            break;
          case '4': // bxc
            registers[1] ^= registers[2];
            break;
          case '5': // out
            output += to_string(comboOperand(registers, literalOperand) % 8) + ',';
            break;
          case '6': // bdv
            registers[1] = registers[0] / powOf2(comboOperand(registers, literalOperand));
            break;
          case '7': // cdv
            registers[2] = registers[0] / powOf2(comboOperand(registers, literalOperand));
            break;
        }
        // skip to next instruction
        j += 4; 
      }
      // remove extra comma
    }
  }
  // yuhh
  return 0;
}

long powOf2(long power) {
  return power != 0 ? 2 << (power - 1) : 1;
}

long comboOperand(long* registers, char literalOperand) {
  switch (literalOperand) {
    case '4':
      // value of register A
      return registers[0];
    case '5':
      // value of register B
      return registers[1];
    case '6':
      // value of register C
      return registers[2];
    default:
      // treat as literal operand
      return literalOperand - '0';
  }
}

