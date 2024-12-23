#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int check(vector<string>& grid, int i, int j);

int main() {
  ifstream input("input.txt");
  vector<string> grid;
  string row;
  int result = 0;
  // gather every line and use the resulting 
  // vector of strings as a grid
  while (getline(input, row)) {
    grid.push_back(row);
  }
  // check if A's are the center of an X-MAS
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      if (grid[i][j] == 'A') {
        result += check(grid, i, j);
      }
    }
  }
  cout << "and the result is... " << result << endl;
  return 0;
}

int check(vector<string>& grid, int i, int j) {
  // no way A is at the center of an X-MAS
  if (i < 1 || j < 1 || i >= grid.size() - 1 || j >= grid[0].size() - 1) {
    return 0;
  } 
  // check if the X-MAS pattern exists
  int matchingDiagonals = 0;
  if (grid[i - 1][j - 1] == 'M' && grid[i + 1][j + 1] == 'S') {
    ++matchingDiagonals;
  } else if (grid[i - 1][j - 1] == 'S' && grid[i + 1][j + 1] == 'M') {
    ++matchingDiagonals;
  }
  if (grid[i - 1][j + 1] == 'M' && grid[i + 1][j - 1] == 'S') {
    ++matchingDiagonals;
  } else if (grid[i - 1][j + 1] == 'S' && grid[i + 1][j - 1] == 'M') {
    ++matchingDiagonals;
  }
  return 1 ? matchingDiagonals == 2 : 0;
}