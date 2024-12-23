#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Direction {
  N,
  S,
  E,
  W,
  NE,
  NW,
  SE,
  SW
};

int check(vector<string>& grid, Direction dir, char letter, int i, int j);

int main() {
  ifstream input("input.txt");
  vector<string> grid;
  string row;
  int result = 0, count;
  // gather every line and use the resulting 
  // vector of strings as a grid
  while (getline(input, row)) {
    grid.push_back(row);
  }
  // if you come across an X, check all possible directions
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      if (grid[i][j] != 'X') {
        continue;
      }
      // cout << "yes king" << endl;
      count = 0;
      for (int dir = N; dir <= SW; ++dir) {
        count += check(grid, static_cast<Direction>(dir), 'X', i, j);
      }
      result += count;
    }
  }
  cout << "and the result is... " << result << endl;
  return 0;
}

int check(vector<string>& grid, Direction dir, char letter, int i, int j) {
  // if out of bounds or XMAS doesn't exist on this path
  if (i >= grid.size() || j >= grid[0].size() || grid[i][j] != letter) {
    return 0;
  } 
  // update the next letter to check
  switch (letter) {
    case 'X':
      letter = 'M';
      break;
    case 'M':
      letter = 'A';
      break;
    case 'A':
      letter = 'S';
      break;
    case 'S':
      return 1;
  } 
  // update the coordinates
  switch (dir) {
    case N:
      return check(grid, dir, letter, i + 1, j);
      break;
    case S:
      return check(grid, dir, letter, i - 1, j);
      break;
    case E:
      return check(grid, dir, letter, i, j + 1);
      break;
    case W:
      return check(grid, dir, letter, i, j - 1);
      break;
    case NE:
      return check(grid, dir, letter, i + 1, j + 1);
      break;
    case NW:
      return check(grid, dir, letter, i + 1, j - 1);
      break;
    case SE:
      return check(grid, dir, letter, i - 1, j + 1);
      break;
    case SW:
      return check(grid, dir, letter, i - 1, j - 1);
      break;
  }
}