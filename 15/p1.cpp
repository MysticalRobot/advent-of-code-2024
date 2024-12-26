#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void moveRobot(vector<string>& grid, char move, int* y, int* x);

int main() {
  ifstream input("input.txt");
  string s;
  // create a grid of the warehouse
  vector<string> grid, moves;
  for (int i = 0; i != 50; ++i) {
    getline(input, s);
    grid.push_back(s);
  } 
  // ignore empty line
  getline(input, s);
  // record the robot's moves
  while (getline(input, s)) {
    moves.push_back(s);
  }
  input.close();
  // robot's location (i peeped the input)
  int y = 24, x = 24;
  // carry out each move;
  for (int i = 0; i != moves.size(); ++i) {
    for (int j = 0; j != moves[0].size(); ++j) {
      moveRobot(grid, moves[i][j], &y, &x);
    }
  }
  // compute the GPS coordinates sum
  long long sum = 0;
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      cout << grid[i][j];
      if (grid[i][j] == 'O') {
        sum += 100 * i + j;
      }
    }
    cout << endl;
  }
  // teehee
  cout << "what's sum dude? " << sum << endl;
  return 0;
}

void moveRobot(vector<string>& grid, char move, int* y, int* x) {
  // figure out the change in y and change in x
  int dy, dx;
  if (move == '^') {
    dy = -1, dx = 0;
  } else if (move == '>') {
    dy = 0, dx = 1;
  } else if (move == '<') {
    dy = 0, dx = -1;
  } else { // move == 'v'
    dy = 1, dx = 0;
  }
  // check if an empty spot exists in the 
  // direction the the robot wishes to move
  int i = *y, j = *x, emptyY = -21, emptyX = - 69;
  while (grid[i + dy][j + dx] != '#') {
    i += dy, j += dx;
    // empty spot found (potentially after many 'O')
    if (grid[i][j] == '.') {
      emptyY = i, emptyX = j;
      break;
    }
  }
  // empty spot not found
  if (emptyY == -21) {
    return;
  }
  // empty the robot's previous spot
  grid[*y][*x] = '.';
  *y += dy, *x += dx;
  // swap the immediately next box with the empty spot
  // (eliminates need to shift every box)
  if (grid[*y][*x] == 'O') {
    grid[emptyY][emptyX] = 'O';
  }
  // move the robot forward
  grid[*y][*x] = '@';
}