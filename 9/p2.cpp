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
  // yuh
  cout << "checkmate? = " << checksum << endl;
  return 0;
}