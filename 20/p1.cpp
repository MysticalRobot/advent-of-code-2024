#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Point { int y, x; };

int main() {
  std::ifstream input("input.txt");
  std::string s;
  // holds entire input
  std::vector<std::vector<char>> grid;
  // holds times taken to reach each position
  std::vector<std::vector<int>> times;
  // holds each point on the racetrack (everything except '#')
  std::vector<Point> racetrack;
  int startY, startX;
  for (int i = 0; getline(input, s); ++i) {
    grid.push_back(std::vector<char>());
    times.push_back(std::vector<int>());
    for (int j = 0; j != s.size(); ++j) {
      grid[i].push_back(s[j]);
      // -1 time -> no path can reach (i, j) quicker
      if (s[j] == '#') {
        times[i].push_back(-1);
        continue;
      }  
      // find the start pos
      if (s[j] == 'S') {
        startY = i, startX = j;
      }
      // big number -> guaranteed that (i, j) can be reached quicker
      times[i].push_back(INT_MAX);
      racetrack.push_back(Point{i, j});
    }
  }
  // bfs to find the times to reach each point on the racetrack
  Point p = Point{startY, startX};
  int time = 0;
  times[startY][startX] = time;
  while (grid[p.y][p.x] != 'E') {
    // only one path so only need to consider one direction
    if (times[p.y - 1][p.x] > time) {
      --p.y;
    } else if (times[p.y + 1][p.x] > time) {
      ++p.y;
    } else if (times[p.y][p.x - 1] > time) {
      --p.x;
    } else { // times[p.y][p.x + 1] > time
      ++p.x;
    }
    // time to reach next spot = 1 + time to reach current spot
    times[p.y][p.x] = ++time;
  }
  // number of cheats that save at least 100 picoseconds
  int n = 0;
  // consider cheating in each direction for every point
  for (Point& p : racetrack) {
    if (p.y - 2 != -1 && grid[p.y - 1][p.x] == '#' && grid[p.y - 2][p.x] != '#'
    && (times[p.y - 2][p.x] - times[p.y][p.x] - 2) >= 2) {
      ++n;
    } 
    if (p.y + 2 != grid.size() && grid[p.y + 1][p.x] == '#' && grid[p.y + 2][p.x] != '#' 
    && (times[p.y + 2][p.x] - times[p.y][p.x] - 2) >= 2) {
      ++n;
    } 
    if (p.x - 2 != -1 && grid[p.y][p.x - 1] == '#' && grid[p.y][p.x - 2] != '#'
     && (times[p.y][p.x - 2] - times[p.y][p.x] - 2) >= 2) {
      ++n;
    } 
    if (p.x + 2 != grid[0].size() && grid[p.y][p.x + 1] == '#' && grid[p.y][p.x + 2] != '#' 
    && (times[p.y][p.x + 2] - times[p.y][p.x] - 2) >= 2) {
      ++n;
    } 
  }
  std::cout << "i use " << n << " cheats on fortnite" << '\n';
  return 0;
}