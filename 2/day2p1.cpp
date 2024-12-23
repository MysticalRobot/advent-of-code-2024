#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>

using namespace std;

int check(vector<int>& r, int l, int i, bool inc) {
  while (i < length) {
    if (i == 0) {
      ++i;
      continue;
    }
    diff = abs(curr - prev);
    // not inc or dec or change is too big
    if (diff == 0 || diff > 3) {
      safe = false;
    }
    if (i != 1) {
      // violation of pattern (inc or dec)
      if ((inc && curr < prev) || (!inc && curr > prev)) {
        safe = false;
      }
    } else { // i == 1, set pattern
      inc = true ? curr > prev : false;
    }
    ++i;
    // if no violations occured in report, increment result
    if (safe) {
      ++result;
    } else if (first) {
      curr = prev;
      first = false;
    }
  }
}

int main() {
  // open file
  ifstream input("input2.txt");
  if (!input.is_open()) {
    cout << "Error opening input file" << endl;
    exit(1);
  }
  int result = 0, i, prev, curr, diff;
  string line;
  bool inc, safe, first;
  vector<int> report;
  // for each line (report) in the input
  while (getline(input, line)) {
    i = 0;
    safe = true, first = true;
    stringstream r(line);
    // obtain each number (level) in the report
    while (!r.eof()) {
      r >> curr;
      report.push_back(curr);
    }
    check(report, report.size(), 0);
  }
  // close file
  input.close();
  // print result
  cout << "The number of safe reports is " << result << endl;
  return 0;
}
