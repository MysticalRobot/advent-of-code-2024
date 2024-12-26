#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

void blink(queue<string>& rocks, unordered_map<string, vector<string>>& blank);

int main() {
  ifstream input("input.txt");
  string rock;
  queue<string> rocks;
  // past tense of blink
  unordered_map<string, vector<string>> blank;
  blank["0"] = vector<string>{"1"};
  // grab all the Dwayne Johnsons
  while (input >> rock) {
    rocks.push(rock);
  }
  input.close();
  long numRocks = 0;
  // blink 75 times
  for (int b = 0; b != 75; ++b) {
    cout << b << endl;
    blink(rocks, blank);
  }
  // writing this while it's running... uh oh... i think it'll work eventually...
  // 
  cout << "cal: i think we just saved christmas with "<< numRocks << " rocks\n";
  return 0;
}

void blink(queue<string>& rocks, unordered_map<string, vector<string>>& blank) {
  // update the rocks on this "level"
  int length = rocks.size();
  while (length != 0) {
    string curr = rocks.front();
    rocks.pop();
    // split Dwayne if he has an even # of digits
    if (blank.find(curr) != blank.end()) {
      for (string s : blank[curr]) {
        rocks.push(s);
      }
    } else if ((curr.size() & 1) == 0) {
      vector<string> result;
      result.push_back(curr.substr(0, curr.size() / 2));
      rocks.push(result.back());
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
        result.push_back(curr.substr(curr.size() / 2 + leadingZeroes));
      } else {
        result.push_back("0");
      }
      rocks.push(result.back());
      blank[curr] = result;
    } else {
      rocks.push(to_string(stoll(curr) * 2024));
      blank[curr] = vector<string>{rocks.back()};
    }
    --length;
  }
}