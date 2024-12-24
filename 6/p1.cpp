#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

int main() {
  ifstream input("input.txt");
  string row;
  vector<string> grid;
  int x = -1, y = -1;
  // create a grid and figure out the guard's pos
  while (getline(input, row)) {
    grid.push_back(row);
    if (x != -1) {
      continue;
    }
    for (int i = 0; i != row.size(); ++i) {
      if (row[i] == '^') {
        y = grid.size() - 1;
        x = i;
        grid[y][x] = 'X';
        break;
      }
    }
  }
  input.close();
  Direction d = UP;
  // i'm assuming the guard walks off (will not get stuck on grid) 
  // -> just move broski till they're gone and mark each visited spot
  while (y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size()) {
    grid[y][x] = 'X';
    switch (d) {
      case UP:
        if (y - 1 > -1 && grid[y - 1][x] == '#') {
          d = RIGHT; 
        } else {
          --y;
        }
        break;
      case DOWN:
        if (y + 1 < grid.size() && grid[y + 1][x] == '#') {
          d = LEFT;
        } else {
          ++y;
        }
        break;
      case LEFT:
        if (x - 1 > -1 && grid[y][x - 1] == '#') {
          d = UP;
        } else {
          --x;
        }
        break;
      case RIGHT:
        if (x + 1 < grid[0].size() && grid[y][x + 1] == '#') {
          d = DOWN;
        } else {
          ++x;
        }
        break;
    }
  }
  // count the number of X's
  int result = 0;
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      if (grid[i][j] == 'X') {
        ++result;
      }
    }
  }
  // output the devious result
  cout << "devious result: " << result << endl;
  return 0;
}