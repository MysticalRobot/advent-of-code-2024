#include <fstream>
#include <iostream>
#include <vector>

struct HeightTree { std::vector<HeightTree*> children; };

void insert(HeightTree* ht, std::vector<int>* heights);
bool contains(HeightTree* ht, std::vector<int>* heights);
int countPairs(HeightTree* ht, std::vector<int>* heights, int i);
void freeTheHomies(HeightTree* ht);

int main() {
  // parse the input, store the lock height in a 2d vector
  // and store the key heights in a prefix tree
  std::vector<std::vector<int>*> locks;
  HeightTree* keys = new HeightTree{std::vector<HeightTree*>(6, nullptr)};
  std::ifstream input("input.txt");
  std::string s;
  while (getline(input, s)) {
    // start height at -1 so that the smallest height end up being 0
    std::vector<int>* heights = new std::vector<int>(5, -1);
    // first row contains a '#' -> lock
    bool isLock = s[0] == '#' ? true : false;
    // parse all 7 rows and skip the blank line after
    for (int i = 0; i != 7; ++i) {
      for (int j = 0; j != 5; ++j) {
        if (s[j] == '#') {
          ++(*heights)[j];
        }
      }
      getline(input, s);
    }
    // direct result to the appropriate structure
    if (isLock) {
      locks.push_back(heights);
    } else {
      insert(keys, heights);
    }
  }
  input.close();
  // find all the possible pairs of locks and keys
  int uniquePairs = 0;
  while (!locks.empty()) {
    std::vector<int>* heights = locks.back();
    locks.pop_back();
    uniquePairs += countPairs(keys, heights, 0);
    delete heights;
  }
  // free the homies!!! (more like delete but whatever)
  freeTheHomies(keys);
  // shiiii
  std::cout << "num unique pairs: " << uniquePairs << '\n';
  return 0;
}

// inserts the the heights into the tree
void insert(HeightTree* ht, std::vector<int>* heights) {
  // start at root, add new trees as needed while moving down tree
  for (int i = 0; i != 5; ++i) { // num of heights
    if (ht->children[(*heights)[i]] == nullptr) {
      ht->children[(*heights)[i]] = new HeightTree{std::vector<HeightTree*>(6, nullptr)};
    }
    ht = ht->children[(*heights)[i]];
  }
}

// checks if the tree contains the heights
bool contains(HeightTree* ht, std::vector<int>* heights) {
  for (int i = 0; i != 5; ++i) { // num of heights
    if (ht->children[(*heights)[i]] == nullptr) {
      return false;
    }
    ht = ht->children[(*heights)[i]];
  } 
  return true;
}

// counts the number of heights that match the given heights
int countPairs(HeightTree* ht, std::vector<int>* heights, int i) {
  if (i == 5) { // num of heights
    return 1;
  }
  int sum = 0;
  for (int j = 0; j <= 5 - (*heights)[i]; ++j) {
    if (ht->children[j] != nullptr) {
      sum += countPairs(ht->children[j], heights, i + 1);
    }
  }
  return sum;
}

// delete *cough* i mean free the homies!!
void freeTheHomies(HeightTree* ht) {
  for (int i = 0; i != 5; ++i) {
    if (ht->children[i] != nullptr) {
      freeTheHomies(ht->children[i]);
    }
  }
  delete ht;
}