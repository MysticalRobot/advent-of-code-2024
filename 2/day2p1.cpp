#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>

using namespace std;

int main() {
  // open file
  ifstream input("input2.txt");
  if (!input.is_open()) {
    cout << "Error opening input file" << endl;
    exit(1);
  }
  int result = 0, i, prev, curr, diff;
  string line;
  bool inc, safe;
  // for each line (report) in the input
  while (getline(input, line)) {
    i = 0;
    safe = true;
    stringstream report(line);
    // obtain each number (level) in the report
    while (!report.eof()) {
      prev = curr;
      report >> curr;
      if (i == 0) {
        ++i;
        continue;
      }
      diff = abs(curr - prev);
      // not inc or dec or change is too big
      if (diff == 0 || diff > 3) {
        safe = false;
        break;
      }
      if (i != 1) {
        // violation of pattern (inc or dec)
        if ((inc && curr < prev) || (!inc && curr > prev)) {
          safe = false;
          break;
        }
      } else { // i == 1, set pattern
        inc = true ? curr > prev : false;
      }
      ++i;
    }
    // if no violations occured in report, increment result
    if (safe) {
      ++result;
    }
  }
  // close file
  input.close();
  // print result
  cout << "The number of safe reports is " << result << endl;
  return 0;
}