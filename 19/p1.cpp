#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdlib>
#define N 6 // num of stripe colors

// WHITE : 'w', BLUE: 'u', BLACK: 'b', RED: 'r', GREEN: 'g', END: ''
enum Color { WHITE, BLUE, BLACK, RED, GREEN, END};
// prefix forest :)
struct Trie { std::array<Trie*, N> colors; };

Trie* newTrie();
int findColor(char color);
void insert(Trie* t, std::string& s);
bool isPossible(std::vector<std::unordered_map<Trie*, bool>>& checked, Trie* root, Trie* curr, std::string& s, int i);
bool contains(Trie* t, std::string& s, int i);
void freeTheHomies(Trie* t);

int main() {
  // set up a trie with all the patterns
  std::ifstream input("input.txt");
  std::string s;
  getline(input, s);
  std::stringstream ss(s);
  Trie* t = newTrie();
  while (ss >> s) {
    insert(t, s);
    /* 
    // ts let me verify that I inserted everything succesfully
    if (contains(t, s, 0)) {
      std::cout << s << ", ";
    }
    */
  }
  // skip ts (not typescript)
  getline(input, s);
  // count the number of designs that are possible to make
  int possible = 0;
  std::vector<std::string> designs;
  while (getline(input, s)) {
    std::vector<std::unordered_map<Trie*, bool>> checked(s.size() + 1);
    if (isPossible(checked, t, t, s, 0)) {
      std::cout << s << " is possible\n";
      ++possible;
    } else {
      std::cout << s << " is not possible\n";
    }
  }
  // gotta free the homies
  freeTheHomies(t);
  // zehahahahaha
  std::cout << possible << " designs are possible\n";
  return 0;
}

// creates trie, makes child pointers null 
Trie* newTrie() {
  Trie* t = (Trie*) malloc(1 * sizeof(Trie));
  t->colors.fill(NULL);
  return t;
}

// matches color with its index in the trie
int findColor(char color) {
  switch (color) {
    case 'w':
      return WHITE;
    case 'u':
      return BLUE;
    case 'b':
      return BLACK;
    case 'r':
      return RED;
    default: // 'g'
      return GREEN;
  }
}

// inserts string into the trie
void insert(Trie* t, std::string& s) {
  // remove extra comma if it exists
  if (s.back() == ',') {
    s.pop_back();
  }
  // start at the root
  Trie* curr = t;
  int color;
  for (int i = 0; i != s.size(); ++i) {
    // figure out the stripe's color
    color = findColor(s[i]);
    // make child with that color if it does not exist
    if (curr->colors[color] == NULL) {
      curr->colors[color] = newTrie();
    }
    // move to the child trie
    curr = curr->colors[color];
  }
  // insert the end of the pattern (string)
  curr->colors[END] = newTrie();
}

bool isPossible(std::vector<std::unordered_map<Trie*, bool>>& checked, Trie* root, Trie* curr, std::string& s, int i) {
  // prevent the solving of subproblems that don't need to be resolved
  if (checked[i].find(curr) != checked[i].end()) {
    return checked[i][curr];
  }
  bool result = false;
  int color = i != s.size() ? findColor(s[i]) : END;
  // pattern is not available at current or root level or trie
  if (curr->colors[color] == NULL) {
    // consider switching pattern if it ends here
    if (curr != root && curr->colors[END] != NULL) {
      result = isPossible(checked, root, root, s, i);
    }
    checked[i][curr] = result;
    return result;
  }
  // processed entire design -> design is possible
  if (i == s.size()) {
    checked[i][curr] = true;
    return true;
  }
  // consider switching patterns 
  if (curr->colors[END] != NULL) {
    result = isPossible(checked, root, root, s, i);
  }
  // continue processing the rest of the design with the current pattern
  result |= isPossible(checked, root, curr->colors[color], s, i + 1);
  // record solution and return result 
  checked[i][curr] = result;
  return result;
}

// (used this to verify that all the patterns were successfully inserted)
bool contains(Trie* t, std::string& s, int i) {
  bool result = false;
  int color = i != s.size() ? findColor(s[i]) : END;
  // pattern is not available for the current stripe
  if (t->colors[color] == NULL) {
    return false;
  }
  // processed entire design -> design is possible
  if (i == s.size()) {
    return true;
  }
  // consider processing the rest of the design with a longer pattern
  return contains(t->colors[color], s, i + 1);
}

// recursively free all the homies
void freeTheHomies(Trie* t) {
  for (Trie*& child : t->colors) {
    if (child != NULL) {
      freeTheHomies(child);
    }
  }
  free(t);
}