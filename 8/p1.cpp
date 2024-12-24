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
      int y1 = v[i].y, x1 = v[i].x;
      for (int j = 0; j != v.size(); ++j) {
        if (i == j) {
          continue;
        }
        int y2 = v[j].y, x2 = v[j].x;
        int yDist = y1 - y2, xDist = x1 - x2;
        if (y2 - yDist > -1 && y2 - yDist < grid.size() && x2 - xDist > -1 && x2 - xDist < grid[0].size()) {
          grid[y2 - yDist][x2 - xDist] = '#';
        }
        if (y1 + yDist > -1 && y1 + yDist < grid.size() && x1 + xDist > -1 && x1 + xDist < grid[0].size()) {
          grid[y1 + yDist][x1 + xDist] = '#';
        }
      }
    }
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