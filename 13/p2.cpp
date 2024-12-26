#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

// bottom up dp solution to find the min number of tokens to win
void dp(int* a, int*b, long long* tokens, long long rows, long long cols);

int main() {
  ifstream input("input.txt");
  string s;
  long cost = 0;
  int a[2], b[2];
  long long* tokens = NULL;
  int commaIndex;
  long long rows, cols;
  // for each machine (4 lines in input)
  while (getline(input, s)) {
    // process a move info
    commaIndex = s.find(',');
    a[0] = stoi(s.substr(commaIndex + 4));
    a[1] = stoi(s.substr(12, commaIndex));
    getline(input, s);
    // process b move info
    commaIndex = s.find(',');
    b[0] = stoi(s.substr(commaIndex + 4));
    b[1] = stoi(s.substr(12, commaIndex));
    getline(input, s);
    // process prize info
    commaIndex = s.find(',');
    // now I need to add 10 trillion...
    rows = stoi(s.substr(commaIndex + 4)) + 1 + 10000000000000;
    cols = stoi(s.substr(9, commaIndex)) + 1 + 10000000000000;
    // skip over blank line
    getline(input, s);
    tokens = (long long*) realloc(tokens, rows * cols * sizeof(long long));
    dp(a, b, tokens, rows, cols);
    if (tokens[rows * cols - 1] != -1) {
      cout << tokens[rows * cols - 1] << endl;
      cost += tokens[rows * cols - 1];
    }    
  }
  free(tokens);
  cout << "hand over " << cost << " berries\n";
  return 0;
}

void dp(int* a, int*b, long long* tokens, long long rows, long long cols) {
  // int* curr;
  // prize at x = 0, y = 0, min tokens to win = 0
  tokens[0] = 0;
  // find the min number of tokens to win for each prize
  for (long long i = 0; i != rows; ++i) {
    for (long long j = 0; j != cols; ++j) {
      if (i == 0 && j == 0) {
        continue;
      }
      if (i - a[0] < 0 || j - a[1] < 0 || tokens[(i - a[0]) * cols + j - a[1]] == -1) {
        tokens[i * cols + j] = -1;
      } else {
        tokens[i * cols + j] = 3 + tokens[(i - a[0]) * cols + j - a[1]];
      }
      if (i - b[0] < 0 || j - b[1] < 0 || tokens[(i - b[0]) * cols + j - b[1]] == -1) {
        tokens[i * cols + j] = fmax(tokens[i * cols + j], -1);
      } else if (tokens[i * cols + j] == -1) {
        tokens[i * cols + j] = 1 + tokens[(i - b[0]) * cols + j - b[1]];
      } else {
        tokens[i * cols + j] = fmin(tokens[i * cols + j], 1 + tokens[(i - b[0]) * cols + j - b[1]]);
      }
    }
  }
}