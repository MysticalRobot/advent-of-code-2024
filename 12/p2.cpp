#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };

void dfs(vector<string>& grid, char start, int i, int j, int* area);
void countSides(vector<string>& grid, int startY, int startX, int currY, int currX, Direction d, int* sides);

int main() {
  ifstream input("input.txt");
  string line;
  // build greed (grid)
  vector<string> grid;
  while (getline(input, line)) {
    grid.push_back(line);
  }
  input.close();
  long price = 0;
  int sides, area;
  char start;
  // start dfs on unvisited spots (marked by uppercase letters)
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      sides = area = 0;
      if (grid[i][j] < 'a') {
        start = grid[i][j];
        // make lowercase to mark visited but retain group membership
        grid[i][j] += 32;
        dfs(grid, start, i, j, &area);
        countSides(grid, i, j, i, j, RIGHT, &sides);
        // add the price of the group
        price += max(4, sides) * area;
      }
    }
  }
  // not asking for much
  cout << "i need a small loan of: " << price << " vbucks\n";
  return 0;
}

void dfs(vector<string>& grid, char start, int i, int j, int* area) {
  // count the area of this spot
  ++*area;
  // continue dfs if next spot is part of the group
  if (i - 1 != -1 && grid[i - 1][j] == start) {
    grid[i - 1][j] += 32;
    dfs(grid, start, i - 1, j, area);
  }
  if (i + 1 != grid.size() && grid[i + 1][j] == start) {
    grid[i + 1][j] += 32;
    dfs(grid, start, i + 1, j, area);
  }
  if (j - 1 != -1 && grid[i][j - 1] == start) {
    grid[i][j - 1] += 32;
    dfs(grid, start, i, j - 1, area);
  }
  if (j + 1 != grid[0].size() && grid[i][j + 1] == start) {
    grid[i][j + 1] += 32;
    dfs(grid, start, i, j + 1, area);
  }
}

void countSides(vector<string>& grid, int startY, int startX, int currY, int currX, Direction d, int* sides) {
  switch (d) {
    case RIGHT:
      
      break;
  }
}