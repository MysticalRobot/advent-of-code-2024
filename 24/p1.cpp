#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <chrono>

struct Gate { std::string input1, input2, output; char operation; };

bool produceOutput(bool input1, bool input2, char operation);
long long toDecimal(std::vector<bool>& binaryNumber);

int main() {
  std::ifstream input("input.txt");
  std::string s;
  // gather the intial values for the x and y wires
  std::vector<bool> x(45, false), y(45, false), z(46, false);
  for (int i = 0; i != 90; ++i) {
    getline(input, s);
    if (s[5] == '1') {
      if (i < 45) {
        x[i] = true;
      } else {
        y[i - 45] = true;
      }
    }
  }
  // skip blank line
  getline(input, s);
  std::unordered_map<std::string, bool> outputs;
  std::queue<Gate> todo;
  std::string input1, input2, output;
  char operation;
  bool b1, b2;
  // for each gate
  while (getline(input, s)) {
    // indetify the input wires, operation, and output wire
    operation = s[4];
    int input2Index = operation == 'O' ? 7 : 8;
    input1 = s.substr(0, 3), input2 = s.substr(input2Index, 3);
    output = s.substr(input2Index + 7);
    // find the output if possible
    if (input1[0] == 'x' || input1[0] == 'y') {
      if (input1[0] == 'x') {
        b1 = x[stoi(input1.substr(1))];
      } else {
        b1 = y[stoi(input1.substr(1))];
      }
      if (input2[0] == 'x') {
        b2 = x[stoi(input2.substr(1))];
      } else {
        b2 = y[stoi(input2.substr(1))];
      }
      // send output to a z wire or to the outputs map
      if (output[0] == 'z') {
        z[stoi(output.substr(1))] = produceOutput(b1, b2, operation);
      } else {
        outputs[output] = produceOutput(b1, b2, operation); 
      }
    // unkown input(s) -> delay the outputting of the the gate  
    } else {
      todo.push(Gate{input1, input2, output, operation});
    }
  }
  input.close();
  // auto start = std::chrono::high_resolution_clock::now();
  // until all the gates' outputs have been found
  while (!todo.empty()) { 
    Gate& g = todo.front(); todo.pop();
    bool haveInput1 = outputs.find(g.input1) != outputs.end();
    bool haveInput2 = outputs.find(g.input2) != outputs.end();
    // have both inputs -> simply do operation
    if (haveInput1 && haveInput2) {
      if (g.output[0] == 'z') {
        z[stoi(g.output.substr(1))] = produceOutput(outputs[g.input1], outputs[g.input2], g.operation);
      } else {
        outputs[g.output] = produceOutput(outputs[g.input1], outputs[g.input2], g.operation);
      }
    // still missing input(s) -> delay the outputting of gate
    } else {
      todo.push(g);
    }
  }
  // ts is slow
  // auto end = std::chrono::high_resolution_clock::now();
  // std::cout << "time: " << (end - start).count() << " seconds\n";
  // combine z wires and find decimal result
  std::cout << toDecimal(z) << '\n';
  return 0;  
}

// produces output of gate
bool produceOutput(bool input1, bool input2, char operation) {
  if (operation == 'A') { // "AND"
    return input1 && input2;
  } else if (operation == 'O') { // "OR"
    return input1 || input2;
  } else { // "XOR"
    return input1 != input2;
  }
}

// converts binary number to decimal
long long toDecimal(std::vector<bool>& binaryNumber) {
  long long result = 0, powOfTwo = 1;
  for (int i = 0; i != binaryNumber.size(); ++i) {
    if (binaryNumber[i]) {
      result += powOfTwo;
    }
    powOfTwo <<= 1;
  }
  return result;
}