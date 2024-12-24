#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

struct Point { int y, x; };

// directions = holy yap sesh; i ain't reading allat

int main() {
  ifstream input("input.txt");
  string line;
  vector<string> grid;
  unordered_map<char, vector<Point>> occurences; 
  // create a grid with the input
  while (getline(input, line)) {
    grid.push_back(line);
  }
  input.close();
  // gather the locations of all the antennas
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      if (grid[i][j] == '.') {
        continue;
      }
      if (occurences.find(grid[i][j]) == occurences.end()) {
        occurences[grid[i][j]] = vector<Point>{Point{i, j}};
      } else {
        occurences[grid[i][j]].push_back(Point{i, j});
      }
    }
  }
  // for each possible pair of antennas, place the
  // antinodes if they don't go off the grid grid grid
  for (auto& pair : occurences) {
    vector<Point>& v = pair.second;
    for (int i = 0; i != v.size(); ++i) {
      for (int j = 0; j != v.size(); ++j) {
        if (i == j) {
          continue;
        }
        int y1 = v[i].y, x1 = v[i].x, y2 = v[j].y, x2 = v[j].x;
        int yDist = y1 - y2, xDist = x1 - x2;
        // starting at the second node, keep placing antinodes
        while (y2 > -1 && y2 < grid.size() && x2 > -1 && x2 < grid[0].size()) {
          grid[y2][x2] = '#';
          y2 -= yDist, x2 -= xDist;
        }
        // starting at the first node, keep placing antinodes
        while (y1 > -1 && y1 < grid.size() && x1 > -1 && x1 < grid[0].size()) {
          grid[y1][x1] = '#';
          y1 += yDist, x1 += xDist;
        }
      }
    }
  }
  for (string s : grid) {
    cout << s << endl;
  }
  // count the unique occurences
  int result = 0;
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      if (grid[i][j] == '#') {
        ++result;
      }
    }
  }
  // it is what it is
  cout << "the number of quirky locations is: " << result << endl;
  return 0;
}