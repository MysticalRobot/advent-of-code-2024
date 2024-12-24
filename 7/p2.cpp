#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// used strings instead to make the concatenation manageable
bool dp(vector<string>& vals, long total, string acc, int i);

int main() {
  ifstream input("input.txt");
  string equation, val;
  long total;
  // long long long long long long long
  long long result = 0;
  vector<string> vals;
  // for each equation
  while (getline(input, equation)) {
    // find the total and record the vals
    int i = equation.find(':');
    total = stol(equation.substr(0, i));
    stringstream ss(equation.substr(i + 2));
    while (ss >> val) {
      vals.push_back(val);
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

bool dp(vector<string>& vals, long total, string acc, int i) {
  // every time, choose between +, *, or || (concatenation)
  // victory royale if accumulated sum == total at the end
  long long accVal = stoll(acc);
  if (i == vals.size()) {
    return true ? accVal == total : false;
  }
  int currVal = stoi(vals[i]);
  return dp(vals, total, to_string(accVal + currVal), i + 1) || 
  dp(vals, total, to_string(accVal * currVal), i + 1) ||
  dp(vals, total, acc + vals[i], i + 1);
}