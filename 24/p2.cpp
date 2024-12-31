#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <chrono>

struct Gate { std::string input1, input2, output; char operation; };

bool produceOutput(bool input1, bool input2, char operation);
bool addUp(std::vector<bool> x, std::vector<bool> y, std::vector<bool> z);
std::vector<std::vector<short>> enumerateSwaps(short swap);
void swapOutputWires(std::vector<Gate>& unknowns, std::vector<short>& swap);
void processGates(std::unordered_map<std::string, bool>& knowns, std::vector<Gate>& unknowns, std::vector<bool>& z);

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
  std::unordered_map<std::string, bool> knowns;
  std::vector<Gate> unknowns;
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
        knowns[output] = produceOutput(b1, b2, operation); 
      }
    // unkown input(s) -> delay the outputting of the the gate  
    } else {
      unknowns.push_back(Gate{input1, input2, output, operation});
    }
  }
  input.close();
  // enumerate all the sets of 8 output wires who's values are unknown
  std::vector<std::vector<short>> swaps = enumerateSwaps(unknowns.size());
  std::cout << swaps.size() << '\n'; 
  // for each possibility
  for (std::vector<short>& swap : swaps) {
    // swap
    swapOutputWires(unknowns, swap);
    processGates(knowns, unknowns, z);
    // check if it worked
    if (addUp(x, y, z)) {
      for (short& index : swap) {
        std::cout << unknowns[index].output << ' ';
      }
      std::cout << '\n';
      break;
    }
    // swap back if it didn't
    swapOutputWires(unknowns, swap);
  }
  return 0;
}

bool produceOutput(bool input1, bool input2, char operation) {
  if (operation == 'A') { // "AND"
    return input1 && input2;
  } else if (operation == 'O') { // "OR"
    return input1 || input2;
  } else { // "XOR"
    return input1 != input2;
  }
}

bool addUp(std::vector<bool> x, std::vector<bool> y, std::vector<bool> z) {
  bool carry = false;
  for (int i = 0; i != 45; ++i) {
    if (carry & x[i] & y[i]) {
      if (!z[i]) return false;    
      // carry = true;
    } else if (!carry & x[i] & y[i]) {
      if (z[i]) return false;
      carry = true;
    } else if (carry & !x[i] & y[i]) {
      if (z[i]) return false;
      // carry = true;
    } else if (carry & x[i] & !y[i]) {
      if (z[i]) return false;
      // carry = true;
    } else if (!carry & !x[i] & y[i]) {
      if (!z[i]) return false;
      // carry = false;
    } else if (carry & !x[i] & !y[i]) {
      if (!z[i]) return false;
      carry = false;
    } else if (!carry & x[i] & !y[i]) {
      if (!z[i]) return false;
      // carry = false;
    } else if (!carry & !x[i] & !y[i]) {
      if (z[i]) return false;
      // carry = false;
    }    
  }
  // carry -> z is the sum of x and y
  return carry;
}

// hopefully enumerates all the possible swaps
std::vector<std::vector<short>> enumerateSwaps(short size) {
  std::vector<std::vector<short>> result;
  std::queue<std::vector<short>> q;
  q.push(std::vector<short>());
  for (short i = 0; i != size; ++i) {
    // should hopefully prevent duplicate indexes
    int swaps = q.size();
    std::cout << swaps << '\n';
    if (swaps > 10000) {
      break;
    }
    while (swaps != 0) {
      std::vector<short> swap = q.front(); q.pop();
      --swaps;
      std::cout << swap.size() << '\n';
      // the indexes of 8 wires have been enumerated -> done
      if (swap.size() == 8) {
        result.push_back(swap);
      } else {
      // include current index and also skip it
        std::vector<short> newSwap(swap);
        newSwap.push_back(i);
        q.push(swap);
        q.push(newSwap);
      }
    }
  }
  return result;
}

void swapOutputWires(std::vector<Gate>& unknowns, std::vector<short>& swap) {
  // this is literally just one way to swap the 8 ouput wires
  // i'm gonna crash out
  for (int i = 0; i != 4; ++i) {
    std::string tmp = unknowns[swap[i]].output;
    unknowns[swap[i]].output = unknowns[swap[7 - i]].output;
    unknowns[swap[7 - i]].output = tmp;
  }
}

void processGates(std::unordered_map<std::string, bool>& knowns, std::vector<Gate>& unknowns, std::vector<bool>& z) {
  // copy the unchanging information
  std::unordered_map<std::string, bool> outputs(knowns);
  std::queue<Gate> todo;
  for (Gate& g : unknowns) {
    todo.push(g);
  }
  // auto start = std::chrono::high_resolution_clock::now();
  // until all the gates' outputs have been found
  while (!todo.empty()) { 
    Gate& g = todo.front(); todo.pop();
    bool haveInput1 = outputs.find(g.input1) != outputs.end();
    bool haveInput2 = outputs.find(g.input2) != outputs.end();
    bool haveOutput = false, derivedOutput;
    // have both inputs -> simply do operation
    if (haveInput1 && haveInput2) {
      haveOutput = true;
      derivedOutput = produceOutput(outputs[g.input1], outputs[g.input2], g.operation);
    // have one input -> can derive output under right conditions
    } else if (haveInput1 || haveInput2) {
      bool knownInput = outputs[haveInput1 ? g.input1 : g.input2];
      if (knownInput && g.operation == 'O') {
        haveOutput = true, derivedOutput = 1;
      } else if (!knownInput && g.operation == 'A') {
        haveOutput = true, derivedOutput = 0;
      }
    }
    // direct output to a z wire or the outputs map
    if (haveOutput) {
      if (g.output[0] == 'z') {
        z[stoi(g.output.substr(1))] = derivedOutput;
      } else {
        outputs[g.output] = derivedOutput;
      }
    // still missing input(s) -> delay the outputting of gate
    } else {
      todo.push(g);
    }
  }
  // ts is fast
  // auto end = std::chrono::high_resolution_clock::now();
  // std::cout << "time: " << (end - start).count() << " seconds\n";
}
