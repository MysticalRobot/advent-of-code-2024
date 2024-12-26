#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<string>& grid, int* score, int i, int j, int currHeight);

int main() {
  ifstream input("input.txt");
  string line;
  // create grid with input
  vector<string> grid;
  while (getline(input, line)) {
    grid.push_back(line);
  }
  input.close();
  // start dfs on each trailhead 
  int score = 0;
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      if (grid[i][j] == '0') {
        // pass copy of grid to mark visited locations
        vector<string> copy = grid;
        copy[i][j] = 'X';
        dfs(copy, &score, i, j, 0);
      }
    }
  }
  // yeah aight
  cout << "scoreeee: " << score << endl;
  return 0;
}

void dfs(vector<string>& grid, int* score, int i, int j, int currHeight) {
  // if reached trail end, increment score
  if (currHeight == 9) {
    ++*score;
    return;
  }
  // ensure next pos is inbounds, not visited, and 1 higher than current
  if (i - 1 != -1 && grid[i - 1][j] != 'X' && (grid[i - 1][j] - '0') - currHeight == 1) {
    grid[i - 1][j] = 'X';
    dfs(grid, score, i - 1, j, currHeight + 1);
  }
  if (i + 1 != grid.size() && grid[i + 1][j] != 'X' && (grid[i + 1][j] - '0') - currHeight == 1) {
    grid[i + 1][j] = 'X';
    dfs(grid, score, i + 1, j, currHeight + 1);
  }
  if (j - 1 != -1 && grid[i][j - 1] != 'X' && (grid[i][j - 1] - '0') - currHeight == 1) {
    grid[i][j - 1] = 'X';
    dfs(grid, score, i, j - 1, currHeight + 1);
  }
  if (j + 1 != grid[0].size() && grid[i][j + 1] != 'X' && (grid[i][j + 1] - '0') - currHeight == 1) {
    grid[i][j + 1] = 'X';
    dfs(grid, score, i, j + 1, currHeight + 1);
  }
}