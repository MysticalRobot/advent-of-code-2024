#include <fstream>
#include <iostream>
using namespace std;

int powOf2(int power);
int comboOperand(int* registers, char literalOperand);

int main() {
  ifstream input("input.txt");
  string s;
  int registers[3]; 
  // initialize registers A, B, C, and receive program
  int i;
  for (i = 0; i != 3; ++i) {
    // skip first two words
    input >> s; input >> s; input >> s;
    registers[i] = stoi(s);
  }
  // skip first word
  input >> s; input >> s; 
  input.close();
  // process the instruction and operand pairs
  string output = "output: ";
  char instruction, literalOperand;
  i = 0;
  while (i != s.size() + 1) {
    // by default, use the literal operand
    // get the combo operand as needed
    instruction = s[i], literalOperand = s[i + 2];
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
          i = (literalOperand - '0') * 4;
          continue;
        }
        break;
      case '4': // bxc
        registers[1] ^= registers[2];
        break;
      case '5': // out
        output += to_string(comboOperand(registers, literalOperand) % 8) + ",";
        break;
      case '6': // bdv
        registers[1] = registers[0] / powOf2(comboOperand(registers, literalOperand));
        break;
      case '7': // cdv
        registers[2] = registers[0] / powOf2(comboOperand(registers, literalOperand));
        break;
    }
    // skip to next instruction
    i += 4; 
  }
  // remove extra comma
  output.pop_back();
  // yuhh
  cout << output << endl;
  return 0;
}

// uhhh
int powOf2(int power) {
  return power != 0 ? 2 << (power - 1) : 1;
}

int comboOperand(int* registers, char literalOperand) {
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