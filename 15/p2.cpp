#include <fstream>
#include <iostream>
#include <vector>
#include <list>
using namespace std;
#define M 10
#define N 20

struct Point { int y, x; };

bool canMoveRobot(vector<string>& grid, int dy, int dx, int y, int x);
void moveRobot(vector<string>& grid, int dy, int dx, int y, int x);
bool isCovered(list<Point>& points, int x);

int main() {
  ifstream input("input.txt");
  string s;
  // create grid with widened version of input
  vector<string> grid, moves;
  for (int i = 0; i != M; ++i) {
    getline(input, s);
    string anothaOne;
    for (int j = 0; j != N / 2; ++j) {
      char current = s[j];
      if (current == 'O') {
        anothaOne.push_back('[');
        anothaOne.push_back(']');  
      } else if (current == '@') {
        anothaOne.push_back('@');
        anothaOne.push_back('.');
      } else {
        anothaOne.push_back(current);
        anothaOne.push_back(current);
      }
    }
    grid.push_back(anothaOne);
    cout << grid.back() << endl;
  } 
  
  // ignore empty line
  getline(input, s);
  // record the robot's moves
  while (getline(input, s)) {
    moves.push_back(s);
  }
  input.close();
  // robot's location (i peeped the input)
  int dy, dx, y = 4, x = 8;
  char move;
  // carry out each move;
  for (int i = 0; i != moves.size(); ++i) {
    for (int j = 0; j != moves[0].size(); ++j) {
      move = moves[i][j];
      if (move == '^') {
        dy = -1, dx = 0;
      } else if (move == '>') {
        dy = 0, dx = 1;
      } else if (move == '<') {
        dy = 0, dx = -1;
      } else { // move == 'v'
        dy = 1, dx = 0;
      }
      if (canMoveRobot(grid, dy, dx, y, x)) {
        moveRobot(grid, dy, dx, y, x);
        y += dy, x += dx;
        for (int m = 0; m != M; ++m) {
          for (int n = 0; n != N; ++n) {
            cout << grid[m][n];
          }
          cout << endl;
        }
      }
      cout << move << endl;
    }
  }
  // compute the GPS coordinates sum
  long long sum = 0;
  for (int i = 0; i != M; ++i) {
    for (int j = 0; j != N; ++j) {
      cout << grid[i][j];
      if (grid[i][j] == '[') {
        sum += 100 * i + j;
      }
    }
    cout << endl;
  }
  // teehee
  cout << "what's sum dude? " << sum << endl;
  return 0;
}

bool canMoveRobot(vector<string>& grid, int dy, int dx, int y, int x) {
  list<Point> points;
  points.push_back(Point{y, x});
  int length, numEmpty;
  char nextChar;
  while (!points.empty()) {
    length = points.size(), numEmpty = 0;
    for (int i = 0; i != length; ++i) {
      Point& current = points.front();
      points.pop_front();
      Point next = Point{current.y + dy, current.x + dx};
      nextChar = grid[next.y][next.x];
      if (nextChar == '.') {
        ++numEmpty;
      } else if (nextChar == ']') {
        points.push_back(next);
        if (abs(dy) == 1 && (grid[current.y][current.x] == '@' || grid[current.y][current.x - 1] == '.')) {
          points.push_back(Point{next.y, next.x - 1});  
        }
      } else if (nextChar == '[') {
        points.push_back(next);
        if (abs(dy) == 1 && (grid[current.y][current.x] == '@' || grid[current.y][current.x + 1] == '.')) {
          points.push_back(Point{next.y, next.x + 1});  
        }
      } else { // ... == '#'
        return false;
      }
    }
  }
  return false ? numEmpty != length : true;
}

void moveRobot(vector<string>& grid, int dy, int dx, int y, int x) {
  list<Point> points;
  points.push_back(Point{y, x});
  list<char> replacements;
  replacements.push_back('.');
  int length;
  char replacement, nextChar;
  while (!points.empty()) {
    length = points.size();
    for (int i = 0; i != length; ++i) {
      Point& current = points.front();
      points.pop_front();
      replacement = replacements.front();
      replacements.pop_front();
      Point next = Point{current.y + dy, current.x + dx};
      nextChar = grid[next.y][next.x];
      if (nextChar == '.') {
        grid[next.y][next.x] = grid[current.y][current.x];
      } else if (nextChar == ']') {
        points.push_back(next);
        replacements.push_back(grid[current.y][current.x]);
        if (abs(dy) == 1 && !isCovered(points, current.x - 1)) {
          points.push_back(Point{next.y, next.x - 1});
          replacements.push_back('.');
        }
      } else if (nextChar == '[') {
        points.push_back(next);
        replacements.push_back(grid[current.y][current.x]);
        if (abs(dy) == 1 && !isCovered(points, current.x + 1)) {
          points.push_back(Point{next.y, next.x + 1});
          replacements.push_back('.');
        }
      }
      grid[current.y][current.x] = replacement;
    }
  }
}

bool isCovered(list<Point>& points, int x) {
  for (Point& point : points) {
    if (point.x == x) {
      return true;
    }
  }
  return false;
}
