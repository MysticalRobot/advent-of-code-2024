#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  ifstream input("input.txt");
  unordered_map<int, vector<int>> rules;
  int x, y, i, j, result = 0;
  string line;
  // nonchalantly grab the first 1176 rules
  // map pages to a vector of pages they must come before
  for (i = 0; i != 1176; ++i) {
    getline(input, line);
    x = stoi(line.substr(0, 2));
    y = stoi(line.substr(3, 2));
    if (rules.find(x) == rules.end()) {
      rules[x] = vector<int> {y};
    } else {
      rules[x].push_back(y);
    }
  }
  vector<int> nums;
  bool valid;
  // for each update
  while (getline(input, line)) {
    // cheekily parse the update
    for (i = 0; i * 3 < line.size(); ++i) {
      nums.push_back(stoi(line.substr(i * 3, 2)));
    }
    // for each page
    valid = true;
    for (i = 0; i != nums.size(); ++i) {
      // if there are no pages it needs to come before, so be it
      if (rules.find(nums[i]) == rules.end()) {
        continue;
      }
      // make sure all the pages behind are allowed to be behind it
      vector<int>& v = rules[nums[i]];
      for (j = i - 1; j != -1; --j) {
        if (find(v.begin(), v.end(), nums[j]) != v.end()) {
          valid = false;
          break;
        }
      }
    }
    // if the update is valid, add the middle number to the result
    if (valid) {
      result += nums[nums.size() / 2];
    }
    nums.clear();
  }
  // toilet
  input.close();
  cout << "skibidi result = " << result << endl;
}