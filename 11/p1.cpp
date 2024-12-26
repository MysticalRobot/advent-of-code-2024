#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

int main() {
  ifstream input("input.txt");
  string rock;
  queue<string> rocks;
  // grab all the Dwayne Johnsons
  while (input >> rock) {
    rocks.push(rock);
  }
  input.close();
  // blink 25 times
  for (int i = 0; i != 25; ++i) {
    // update the rocks on this "level"
    int length = rocks.size();
    while (length != 0) {
      string curr = rocks.front();
      rocks.pop();
      // split Dwayne if he has an even # of digits
      if ((curr.size() & 1) == 0) {
        rocks.push(curr.substr(0, curr.size() / 2));
        int leadingZeroes = 0;
        for (int j = curr.size() / 2; j != curr.size(); ++j) {
          // earlier, i didn't break, and that messed me up
          if (curr[j] != '0') {
            break;
          } 
          ++leadingZeroes;
        }
        // remove leading zeroes, replace with 0 if all 0s
        if (curr.size() / 2 - leadingZeroes != 0) {
          rocks.push(curr.substr(curr.size() / 2 + leadingZeroes));
        } else {
          rocks.push("0");
        }
        // replace 0s with 1s
      } else if (curr[0] == '0') {
        rocks.push("1");
        // multiply odd Dwaynes by 2024
      } else {
        rocks.push(to_string(stoll(curr) * 2024));
      }
      --length;
    }
  }
  // yessir
  cout << "cal: i think we just saved christmas with "<< rocks.size() << " rocks\n";
  return 0;
}