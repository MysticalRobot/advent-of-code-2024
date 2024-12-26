#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ifstream input("input.txt");
  string layout;
  vector<int> compacted;
  long checksum = 0;
  // grab the long line
  getline(input, layout);
  input.close();
  // create a vector that represents that layout
  for (int i = 0; i != layout.size(); ++i) {
    int id = i / 2;
    if (i & 1) {
      id = -1;
    }
    for (int j = 0; j != (layout[i] - '0'); ++j) {
      compacted.push_back(id);
    }
  }
  // while all the free spots are not filled
  int l = 0, r = compacted.size() - 1;
  while (l < r) {
    // pop free spots at the end
    while (compacted.back() == -1) {
      compacted.pop_back();
      --r;
    }
    // skip over filled spots on the left to reach free spots
    while (l < compacted.size() - 1 && compacted[l] != -1) {
      ++l;
    }
    // move part of file over to the left if possible, pop free space
    if (l < compacted.size() - 1) {
      compacted[l] = compacted.back();
      compacted.pop_back();
      ++l;
      --r;
    }
  }
  // compute filesystem checksum
  for (int i = 0; i != compacted.size(); ++i) {
    checksum += compacted[i] * i;
  }
  // yuh
  cout << "checkmate? = " << checksum << endl;
  return 0;
}