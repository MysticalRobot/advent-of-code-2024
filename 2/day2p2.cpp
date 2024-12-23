#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

bool check(vector<int>& r, int i, int skip, int prev, int pattern) { 
  // processed all levels
  if (i == r.size()) {
    return true;
  }
  // skip index if you're at the skip
  if (i == skip) {
    return check(r, i + 1, skip, prev, pattern);
  }
  // set a prev if it has not been established yet
  if (i == 0 || prev == -1) {
    return check(r, i + 1, skip, r[i], pattern);
  }
  // set a patten if it has not been established yet
  // (1 means increasing, 0 means decreasing)
  if (pattern == -1) {
    pattern = 1 ? r[i] > prev : 0;
  }
  // false if diff too large
  int diff = r[i] - prev;
  if (abs(diff) > 3) {
    return false;
  }
  // false if pattern is not followed
  if (diff <= 0 && pattern == 1 || diff >= 0 && pattern == 0) {
    return false;
  }
  // keep going otherwise
  return check(r, i + 1, skip, r[i], pattern);
}

int main() {
  // open file
  ifstream input("input2.txt");
  if (!input.is_open()) {
    cout << "Error opening input file" << endl;
    exit(1);
  }
  int curr, result = 0;
  bool update = false;
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
    update = false;
    for (int i = 0; i != r.size(); ++i) {
      // i just try out removing each level (skull emoji)
      update = update || check(r, 0, i, -1, -1);
    }
    if (update) {
      ++result;
    }
    while (!r.empty()) {
      r.clear();
    }
  }
  // close file and print result
  input.close();
  cout << "The number of safe reports is " << result << endl;
  return 0;
}