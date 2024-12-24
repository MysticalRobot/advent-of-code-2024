#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

bool dp(vector<int>& vals, long total, long acc, int i);

int main() {
  ifstream input("input.txt");
  string equation, val;
  long total, result = 0;
  vector<int> vals;
  // for each equation
  while (getline(input, equation)) {
    // find the total and record the vals
    int i = equation.find(':');
    total = stol(equation.substr(0, i));
    stringstream ss(equation.substr(i + 2));
    while (ss >> val) {
      vals.push_back(stoi(val));
    }
    // dynamike from brawl stars
    if (dp(vals, total, vals[0], 1)) {
      result += total;
    }
    vals.clear();
  }
  // another victory for the ogs
  input.close();
  cout << "dynamic result is: " << result << endl;
  return 0;
}

bool dp(vector<int>& vals, long total, long acc, int i) {
  // every time, choose between + or * to do with acc
  // victory royale if accumulated sum == total at the end
  if (i == vals.size()) {
    return true ? acc == total : false;
  }
  return dp(vals, total, acc + vals[i], i + 1) || 
  dp(vals, total, acc * vals[i], i + 1);
}