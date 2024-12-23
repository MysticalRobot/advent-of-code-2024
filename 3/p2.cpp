#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <queue>

using namespace std;

int main() {
  ifstream input("input.txt");
  queue<int> donts, dos;
  string line;
  long result = 0;
  int length, i, j, k, x, y;
  bool valid, enabled = true;
  // for each line
  while (getline(input, line)) {
    length = line.size(), i = 0, j = 0, k = 0;
    // find the indices of the don't instructions
    while (j < length) {
      if ((j = line.find("don't()", j)) == string::npos) {
        break;
      }
      donts.push(j);
      j += 7;
    }
    // find the indices of the do instructions
    while (k < length) {
      if ((k = line.find("do()", k)) == string::npos) {
        break;
      }
      dos.push(k);
      k += 4; 
    }
    // for each mul instruction
    while ((i = line.find("mul(", i)) != string::npos) {
      // pop old do/don't instructions, update enabled status
      while (!donts.empty() && donts.front() < i) {
        enabled = false;
        donts.pop();
      }
      while (!dos.empty() && dos.front() < i) {
        enabled = true;
        dos.pop();
      }
      i = i + 4, j = i;
      if (!enabled) {
        continue;
      }
      valid = true;
      // validate the first number
      while (j < min(i + 3, length) && line.at(j) != ',') {
        if (!isdigit(line.at(j))) {
          valid = false;
        }
        ++j;
      }
      if (j == length || line.at(j) != ',' || !valid) {
        continue;
      }
      // validate the second number
      k = j + 1;
      while (k < min(j + 4, length) && line.at(k) != ')') {
        if (!isdigit(line.at(k))) {
          valid = false;
        }
        ++k;
      }
      if (k == length || line.at(k) != ')' || !valid) {
        continue;
      }
      // add the result of multiplying the numbers
      x = stoi(line.substr(i, j - i));
      y = stoi(line.substr(j + 1, k - j - 1));
      result += x * y;
    }
  }
  // close the input and return the result
  input.close();
  cout << "Result: " << result << endl;
  return 0;
}
