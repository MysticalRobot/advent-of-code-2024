#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;
// 1 3 5 8 9
//     ^
bool check(vector<int>& r, int i, int prev, bool inc, bool first) { 
  if (i == r.size()) {
    return true;
  }
  int curr = r[i], diff = abs(curr - prev);
  if (i == 0) {
    return check(r, i + 1, curr, inc, first);
  }
  // not inc or dec
  if (diff == 0) {
    if (!first) {
      return false;
    }
    return check(r, i + 1, prev, inc, !first);
  }
  // change is too big
  if (diff > 3) {
    if (!first) {
      return false;
    }
    if (i != 1) {
      return check(r, i + 1, prev, inc, !first);
    }
    bool c1, c2;
    if (r[i + 1] > prev) {
      c1 = check(r, i + 1, prev, true, !first);
    } else {
      c1 = check(r, i + 1, prev, false, !first);
    }
    if (r[i + 1] > curr) {
      c2 = check(r, i + 1, curr, true, !first);
    } else {
      c2 = check(r, i + 1, curr, false, !first);
    }
    return c1 or c2;
  }
  if (i != 1) {
    // violation of pattern (inc or dec)
    if ((inc && curr < prev) || (!inc && curr > prev)) {
      if (!first) {
        return false;
      }
      return check(r, i + 1, prev, inc, !first);
    }
  } else { // i == 1, set pattern
    inc = true ? curr > prev : false;
  }
  return check(r, i + 1, curr, inc, first);
}

int main() {
  // open file
  ifstream input("input2.txt");
  if (!input.is_open()) {
    cout << "Error opening input file" << endl;
    exit(1);
  }
  int curr, result = 0;
  string line;
  vector<int> r;
  // for each line (report) in the input
  while (getline(input, line)) {
    stringstream report(line);
    // obtain each number (level) in the report
    while (!report.eof()) {
      report >> curr;
      r.push_back(curr);
    }
    if (check(r, 0, 0, true, true)) {
      ++result;
    }
    while (!r.empty()) {
      r.pop_back();
    }
  }
  // close file and print result
  input.close();
  cout << "The number of safe reports is " << result << endl;
  return 0;
}