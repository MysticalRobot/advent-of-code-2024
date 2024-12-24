#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>

using namespace std;

// long ahh function prototype
void check (unordered_map<int, vector<int>>& rules, int* nums, 
int length, int* offender, int* offended);

int main() {
  ifstream input("input.txt");
  unordered_map<int, vector<int>> rules;
  int x, y, n, result = 0;
  string line;
  // nonchalantly grab the first 1176 rules, then
  // map pages to a vector of pages they must come before
  for (n = 0; n != 1176; ++n) {
    getline(input, line);
    x = stoi(line.substr(0, 2));
    y = stoi(line.substr(3, 2));
    if (rules.find(x) == rules.end()) {
      rules[x] = vector<int> {y};
    } else {
      rules[x].push_back(y);
    }
  }
  int* nums = NULL;
  int length, tmp;
  int offender = -1, offended = -1;
  // for each update
  while (getline(input, line)) {
    // cheekily parse the update
    length = 0;
    for (n = 0; n * 3 < line.size(); ++n) {
      length += 1;
    }
    if (nums == NULL) {
      nums = (int*) malloc(length * sizeof(int));  
    } else {
      nums = (int*) realloc(nums, length * sizeof(int));
    }
    nums = (int*) malloc(length * sizeof(int));
    for (n = 0; n < length; ++n) {
      nums[n] = stoi(line.substr(n * 3, 2));
    }
    // initial check to week out valid updates
    check(rules, nums, length, &offender, &offended);
    // if the update is valid, tell it to go kick rocks
    if (offender == -1 && offended == -1) {
      continue;
    }
    // luh swaparoos till invalid updates are valid
    while (offender != -1 && offended != -1) {
      tmp = nums[offender];
      nums[offender] = nums[offended];
      nums[offended] = tmp;
      check(rules, nums, length, &offender, &offended);
    }
    // add the middle value to the result
    result += nums[length / 2];
  }
  // toilet
  free(nums);
  input.close();
  cout << "skibidi result = " << result << endl;
}

void check (unordered_map<int, vector<int>>& rules, int* nums, 
int length, int* offender, int* offended) {
  *offender = -1;
  *offended = -1;
  for (int i = 0; i != length; ++i) {
    // if there are no pages it needs to come before, so be it
    if (rules.find(nums[i]) == rules.end()) {
      continue;
    }
    // make sure all the pages behind are allowed to be behind it
    vector<int>& v = rules[nums[i]];
    for (int j = i - 1; j != -1; --j) {
      if (find(v.begin(), v.end(), nums[j]) != v.end()) {
        *offender = i;
        *offended = j;
        return;
      }
    }
  }
}