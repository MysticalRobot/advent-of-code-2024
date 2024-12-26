#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<string>& grid, char start, int i, int j, int* perimeter, int* area);

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
  int perimeter, area;
  char start;
  // start dfs on unvisited spots (marked by uppercase letters)
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      perimeter = area = 0;
      if (grid[i][j] < 'a') {
        start = grid[i][j];
        // make lowercase to mark visited but retain group membership
        grid[i][j] += 32;
        dfs(grid, start, i, j, &perimeter, &area);
        // add the price of the group
        price += perimeter * area;
      }
    }
  }
  // not asking for much
  cout << "i need a small loan of: " << price << " vbucks\n";
  return 0;
}

void dfs(vector<string>& grid, char start, int i, int j, int* perimeter, int* area) {
  // count the area of this spot
  ++*area;
  // if next spot out of bounds, or it is not a part of the group, inc perimeter
  if (i - 1 == -1 || (grid[i - 1][j] != start && grid[i - 1][j] != (char) (start + 32))) {
    ++*perimeter;
  // if next spot is an unvisited group member, go!
  } else if (grid[i - 1][j] == start) {
    grid[i - 1][j] += 32;
    dfs(grid, start, i - 1, j, perimeter, area);
  }
  if (i + 1 == grid.size() || (grid[i + 1][j] != start && grid[i + 1][j] != (char) (start + 32))) {
    ++*perimeter;
  } else if (grid[i + 1][j] == start) {
    grid[i + 1][j] += 32;
    dfs(grid, start, i + 1, j, perimeter, area);
  }
  if (j - 1 == -1 || (grid[i][j - 1] != start && grid[i][j - 1] != (char) (start + 32))) {
    ++*perimeter;
  } else if (grid[i][j - 1] == start) {
    grid[i][j - 1] += 32;
    dfs(grid, start, i, j - 1, perimeter, area);
  }
  if (j + 1 == grid[0].size() || (grid[i][j + 1] != start && grid[i][j + 1] != (char) (start + 32))) {
    ++*perimeter;
  } else if (grid[i][j + 1] == start) {
    grid[i][j + 1] += 32;
    dfs(grid, start, i, j + 1, perimeter, area);
  }
}