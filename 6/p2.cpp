#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };
struct Point { int y, x; };

void move(vector<string>& grid, int* y, int* x, Direction* d);

int main() {
  ifstream input("input.txt");
  string row;
  vector<string> grid;
  int startY = -1, startX = -1;
  // create a grid and figure out the guard's pos
  while (getline(input, row)) {
    grid.push_back(row);
    if (startY != -1) {
      continue;
    }
    for (int i = 0; i != row.size(); ++i) {
      if (row[i] == '^') {
        startY = grid.size() - 1, startX = i;
        break;
      }
    }
  }
  input.close();
  Direction d = UP;
  int y = startY, x = startX;
  // i'm assuming the guard walks off (will not get stuck on grid) 
  // -> just move broski till they're gone and mark each visited spot
  while (y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size()) {
    if (grid[y][x] != '^') {
      grid[y][x] = 'X';
    }
    move(grid, &y, &x, &d);
  }
  // record all the unique X locations
  vector<Point> patrolled;
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      if (grid[i][j] == 'X') {
        patrolled.push_back(Point{i, j});
      }
    }
  }
  // for each point
  int movesLeft, result = 0;
  for (Point p : patrolled) {
    // start back at the guard's og spot
    y = startY, x = startX, movesLeft = grid.size() * grid[0].size(), d = UP;
    grid[p.y][p.x] = '#';
    // try to find a path out
    while (y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size()) {
      move(grid, &y, &x, &d);
      --movesLeft;
      // abort mission if you have made more moves than spots on the board
      if (movesLeft == -1) {
        ++result;
        break;
      }
    }
    // revert the spot where the new obstacle was placed
    grid[p.y][p.x] = 'X';
  }
  // output the devious result
  cout << "devious result: " << result << endl;
  return 0;
}

void move(vector<string>& grid, int* y, int* x, Direction* d) {
  switch (*d) {
    // basically:
    // - turn right if obstacle encountered
    // - else, keep going off the grid grid grid
    case UP:
      if (*y - 1 != -1 && grid[*y - 1][*x] == '#') {
        *d = RIGHT; 
      } else {
        --*y;
      }
      break;
    case DOWN:
      if (*y + 1 != grid.size() && grid[*y + 1][*x] == '#') {
        *d = LEFT;
      } else {
        ++*y;
      }
      break;
    case LEFT:
      if (*x - 1 != -1 && grid[*y][*x - 1] == '#') {
        *d = UP;
      } else {
        --*x;
      }
      break;
    case RIGHT:
      if (*x + 1 != grid[0].size() && grid[*y][*x + 1] == '#') {
        *d = DOWN;
      } else {
        ++*x;
      }
      break;
  }
}