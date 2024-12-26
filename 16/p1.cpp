#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define N 141
#define Y 139
#define X 1

using namespace std;

struct Reindeer { int y, x; char d; };
void bfs(char grid[N][N], long best[N][N]);
void considerPath(char grid[N][N], long best[N][N], queue<Reindeer>& q, Reindeer& r, char d, int dy, int dx, int cost);

int main() {
  ifstream input("input.txt");
  string s;
  char grid[N][N];
  long best[N][N];
  for (int i = 0; i != N; i++) {
    input >> s;
    for (int j = 0; j != N; ++j) {
      grid[i][j] = s[j];
      best[i][j] = LONG_MAX;
    }
  }
  best[Y][X] = 0;
  input.close();
  bfs(grid, best);
  cout << "the winner of the skibidi olympics had a score of " << best[X][Y] << endl;
  return 0;
}

void bfs(char grid[N][N], long best[N][N]) {
  queue<Reindeer> q;
  q.push(Reindeer{Y, X, '>'});
  while (!q.empty()) {
    int length = q.size();
    for (int i = 0; i != length; ++i) {
      Reindeer& r = q.front();
      q.pop();
      switch (r.d) {
        case '^':
          considerPath(grid, best, q, r, '^', -1, 0, 1);
          considerPath(grid, best, q, r, '>', 0, 1, 1001);
          considerPath(grid, best, q, r, '<', 0, -1, 1001);
          break;
        case 'v':
          considerPath(grid, best, q, r, 'v', 1, 0, 1);
          considerPath(grid, best, q, r, '<', 0, -1, 1001);
          considerPath(grid, best, q, r, '>', 0, 1, 1001);
          break;
        case '<':
          considerPath(grid, best, q, r, '<', 0, -1, 1);
          considerPath(grid, best, q, r, '^', -1, 0, 1001);
          considerPath(grid, best, q, r, 'v', 1, 0, 1001);
          break;
        case '>':
          considerPath(grid, best, q, r, '>', 0, 1, 1);
          considerPath(grid, best, q, r, 'v', 1, 0, 1001);
          considerPath(grid, best, q, r, '^', -1, 0, 1001);
          break;
      }
    }
  }
}

void considerPath(char grid[N][N], long best[N][N], queue<Reindeer>& q, Reindeer& r, char d, int dy, int dx, int cost) {
  if (grid[r.y + dy][r.x + dx] != '#' && best[r.y + dy][r.x + dx] > cost + best[r.y][r.x]) {
    if (grid[r.y + dy][r.x + dx] == '.') {
      q.push(Reindeer{r.y + dy, r.x + dx, d});  
    }
    best[r.y + dy][r.x + dx] = cost + best[r.y][r.x];
  } 
}