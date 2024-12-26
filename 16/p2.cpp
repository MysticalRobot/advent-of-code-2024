#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

/*
#define N 15
#define Y 13
#define X 1

#define N 17
#define Y 15
#define X 1
*/


#define N 141
#define Y 139
#define X 1

using namespace std;

struct Reindeer { int y, x; char d; Reindeer* prev; };
struct Path { Reindeer* r; int score; };
void bfs(char grid[N][N], int bestScores[N][N]);
void considerPath(char grid[N][N], int bestScores[N][N], queue<Reindeer>& q, vector<Path>& paths, Reindeer* r, char d, int dy, int dx, int cost);

int main() {
  ifstream input("input.txt");
  string s;
  char grid[N][N];
  int bestScores[N][N];
  for (int i = 0; i != N; i++) {
    input >> s;
    for (int j = 0; j != N; ++j) {
      grid[i][j] = s[j];
      bestScores[i][j] = INT_MAX;
    }
  }
  bestScores[Y][X] = 0;
  input.close();
  bfs(grid, bestScores);
  int tiles = 0;
  for (int i = 0; i != N; ++i) {
    for (int j = 0; j != N; ++j) {
      if (grid[i][j] == 'O') {
        ++tiles;
      }
      cout << grid[i][j];
    }
    cout << endl;
  }
  cout << "the winner of the skibidi olympics had a score of " << bestScores[X][Y] << endl;
  cout << "the number tiles used by the best paths is: " << tiles << endl;
  return 0;
}

void bfs(char grid[N][N], int bestScores[N][N]) {
  queue<Reindeer> q;
  q.push(Reindeer{Y, X, '>', NULL});
  vector<Path> paths;
  while (!q.empty()) {
    Reindeer* r = &(q.front());
    q.pop();
    switch (r->d) {
      case '^':
        considerPath(grid, bestScores, q, paths, r, '^', -1, 0, 1);
        considerPath(grid, bestScores, q, paths, r, '>', 0, 1, 1001);
        considerPath(grid, bestScores, q, paths, r, '<', 0, -1, 1001);
        break;
      case 'v':
        considerPath(grid, bestScores, q, paths, r, 'v', 1, 0, 1);
        considerPath(grid, bestScores, q, paths, r, '<', 0, -1, 1001);
        considerPath(grid, bestScores, q, paths, r, '>', 0, 1, 1001);
        break;
      case '<':
        considerPath(grid, bestScores, q, paths, r, '<', 0, -1, 1);
        considerPath(grid, bestScores, q, paths, r, '^', -1, 0, 1001);
        considerPath(grid, bestScores, q, paths, r, 'v', 1, 0, 1001);
        break;
      case '>':
        considerPath(grid, bestScores, q, paths, r, '>', 0, 1, 1);
        considerPath(grid, bestScores, q, paths, r, 'v', 1, 0, 1001);
        considerPath(grid, bestScores, q, paths, r, '^', -1, 0, 1001);
        break;
    }
  }
  cout << "there are " << paths.size() << " best paths\n";
  int bestScore = bestScores[X][Y];
  grid[X][Y] = 'O';
  for (Path& p : paths) {
    Reindeer* r = p.r;
    while (r != NULL) {
      grid[r->y][r->x] = 'O';
      r = r->prev;
    }
  }
}

void considerPath(char grid[N][N], int bestScores[N][N], queue<Reindeer>& q, vector<Path>& paths, Reindeer* prev, char d, int dy, int dx, int cost) {
  if (bestScores[prev->y + dy][prev->x + dx] >= cost + bestScores[prev->y][prev->x]) {
    Reindeer r = Reindeer{prev->y + dy, prev->x + dx, d, prev};
    switch (grid[prev->y + dy][prev->x + dx]) {
      case '.':
        q.push(r);
        break;
      case 'E':
        // idk why but putting &r instead of prev there gave me a seg fault
        paths.push_back(Path{prev, cost + bestScores[prev->y][prev->x]});  
        break;
      default: // '#'
        return;
    }
    bestScores[prev->y + dy][prev->x + dx] = cost + bestScores[prev->y][prev->x];
  } 
}