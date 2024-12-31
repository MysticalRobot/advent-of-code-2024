#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define KEYPADHEIGHT 4
#define KEYPADWIDTH 3
using namespace std;

enum NumericKeyPad { SEVEN, EIGHT, NINE, FOUR, FIVE, SIX, ONE, TWO, THREE, BLANK, ZERO, A };
enum DirectionalKeyPad { GAP, UP, START, LEFT, DOWN, RIGHT };
struct Point { int y, x; };
char nextToCurr(Point& dir);

int main() {
  for (int i = 0; i != KEYPADHEIGHT; ++i) {
    for (int j = 0; j != KEYPADWIDTH; ++j) {
      vector<vector<char>> result(KEYPADHEIGHT * KEYPADWIDTH, vector<char>());
      vector<vector<char>> seen(KEYPADHEIGHT * KEYPADWIDTH, vector<char>());
      result[i * KEYPADWIDTH + j].push_back('\0');
      queue<Point> q;
      q.push(Point{i, j});
      while (q.empty()) {
        Point& p = q.front();
        q.pop();
        for (Point& dir : {Point{-1, 0}, Point{1, 0}, Point{0, -1}, Point{0, 1}}) {
          int ny = p.y + dir.y, nx = p.x + dir.x;
          if (ny != -1 && ny != KEYPADHEIGHT && nx != -1 && ny != KEYPADWIDTH 
          && (result[ny * KEYPADWIDTH + nx].empty() || result[ny * KEYPADWIDTH + nx].size())) {
            result[ny * KEYPADWIDTH + nx].push_back(nextToCurr(dir));
            q.push(Point{ny, nx});
          }
        }
      }
    }
  }
  for (int i = 0; i != A + 1; ++i) {
    for (int j = 0; j != KEYPADHEIGHT; ++j) {
      for (int k = 0; k != KEYPADWIDTH; ++k) {
        printf("%2.2lu ", moves[i][j][k][0].size());
      }
      puts("");
    }
    puts("--------------------");
  }
  ifstream input("input.txt");
  queue<string> sq1Options, bestSq1Options, sq2Options, ehSq2Options, bestSq2Options, sq3Options, ehSq3Options;
  string code;
  int curr, next, length, sum = 0;
  while (input >> code) {
    curr = A;
    for (int i = 0; i != code.size(); ++i) {
      switch(code[i]) {
        case '7':
          next = SEVEN;
          break;
        case '8':
          next = EIGHT;
          break;
        case '9':
          next = NINE;
          break;
        case '4':
          next = FOUR;
          break;                
        case '5':
          next = FIVE;
          break;
        case '6':
          next = SIX;
          break;
        case '1':
          next = ONE;
          break;
        case '2':
          next = TWO;
          break;
        case '3':
          next = THREE;
          break;
        case '0':
          next = ZERO;
          break;
        default: // 'A'
          next = A;
          break;
      }
      if (sq1Options.empty()) {
        for (string& move : moves[next][indexes[curr].y][indexes[curr].x]) {
          sq1Options.push(move + 'A');
        }
      } else {
        length = sq1Options.size();
        while (length != 0) {
          string& sequence = sq1Options.front();
          sq1Options.pop();
          for (string& move : moves[next][indexes[curr].y][indexes[curr].x]) {
            sq1Options.push(sequence + move + 'A');
          }
          --length;
        }
      }
      curr = next;
    }
    // find smallest sequence length
    length = sq1Options.front().size();
    for (string& sequence : sq1Options) {
      if (sequence.size() < length) {
        length = sequence.size();
      }
    }
    // only continue to process smallest sequences
    while (!sq1Options.empty()) {
      string& sequence = sq1Options.back();
      sq1Options.pop_back();
      if (sequence->size() == length) {
        bestSq1Options.push_back(sequence);
      } else {
        delete sequence;
      }
    }
    curr = START;
    while (!bestSq1Options.empty()) {
      auto& currSq = bestSq1Options.back();
      bestSq1Options.pop_back();
      for (int i = 0; i != currSq->size(); ++i) {
        switch((*currSq)[i]) {
          case '^':
            next = UP;
            break;
          case '<':
            next = LEFT;
            break;
          case '>':
            next = RIGHT;
            break;
          case 'v':
            next = DOWN;
            break;
          default: // 'A'
            next = START;
        }
        if (sq2Options.empty()) {
          for (string& move : moves[next][indexes[curr].y][indexes[curr].x]) {
            sq2Options.push_back(new string(move + 'A'));
          }
        } else {
          length = sq2Options.size();
          while (length != 0) {
            auto& sequence = sq2Options.front();
            sq2Options.pop_front();
            for (string& move : moves[next][indexes[curr].y][indexes[curr].x]) {
              sq2Options.push_back(new string(*sequence + move + 'A'));
            }
            --length;
          }
        }
        curr = next;
        delete currSq;
      }
      length = sq2Options.front()->size(); 
      while (!sq2Options.empty()) {
        auto& sequence = sq2Options.back();
        sq2Options.pop_back();
        if (sequence->size() <= length) {
          ehSq2Options.push_back(sequence);
        } else {
          delete sequence;
        }
      }
    }
    // find smallest sequence length
    length = ehSq2Options.front()->size();
    for (auto& sequence : ehSq2Options) {
      if (sequence->size() < length) {
        length = sequence->size();
      }
    }
    // only continue to process smallest sequences
    while (!ehSq2Options.empty()) {
      auto& sequence = ehSq2Options.back();
      ehSq2Options.pop_back();
      if (sequence->size() == length) {
        bestSq2Options.push_back(sequence);
      } else {
        delete sequence;
      }
    }
    curr = START;
    while (!bestSq2Options.empty()) {
      auto& currSq = bestSq2Options.back();
      bestSq2Options.pop_back();
      for (int i = 0; i != currSq->size(); ++i) {
        switch((*currSq)[i]) {
          case '^':
            next = UP;
            break;
          case '<':
            next = LEFT;
            break;
          case '>':
            next = RIGHT;
            break;
          case 'v':
            next = DOWN;
            break;
          default: // 'A'
            next = START;
        }
        if (sq3Options.empty()) {
          for (string& move : moves[next][indexes[curr].y][indexes[curr].x]) {
            sq3Options.push_back(new string(move + 'A'));
          }
        } else {
          length = sq3Options.size();
          while (length != 0) {
            auto& sequence = sq3Options.front();
            sq3Options.pop_front();
            for (auto& move : moves[next][indexes[curr].y][indexes[curr].x]) {
              sq3Options.push_back(new string(*sequence + move + 'A'));
            }
            --length;
          }
        }
        curr = next;
        delete currSq;
      }
      length = sq3Options.front()->size(); 
      while (!sq3Options.empty()) {
        auto& sequence = sq3Options.back();
        sq3Options.pop_back();
        if (sequence->size() <= length) {
          ehSq3Options.push_back(sequence);
        } else {
          delete sequence;
        }
      }
      delete currSq;
    }
    // find smallest sequence length
    length = ehSq3Options.front()->size();
    for (auto& sequence : ehSq3Options) {
      if (sequence->size() < length) {
        length = sequence->size();
      }
    }
    sum += length * stoi(code.substr(0, code.size() - 1));
    while (!ehSq3Options.empty()) {
      auto& sequence = ehSq3Options.back();
      ehSq3Options.pop_back();
      delete sequence;
    }
  }
  input.close();
  printf("sum of complexities: %d\n", sum);
  return 0;
}
