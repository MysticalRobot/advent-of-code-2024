#include <fstream>
#include <iostream>

void mix(long long int* secretNum, long long int otherVal);
void prune(long long int* secretNum);

int main() {
  std::ifstream input("input.txt");
  long long int secretNum, sum;
  // find the 2000th secret number for each input number
  while (input >> secretNum) {
    for (int i = 0; i != 2000; ++i) {
      // multiply by 64, mix result, then prune
      mix(&secretNum, secretNum << 6);
      prune(&secretNum);
      // divide by 32, mix result, then prune
      mix(&secretNum, secretNum >> 5);
      prune(&secretNum);
      // multiply by 2048, mix result, then prune
      mix(&secretNum, secretNum << 11);
      prune(&secretNum);
    }
    // add to sum of 2000th secret numbers
    sum += secretNum;
  }
  // i told her man's not hot
  input.close();
  std::cout << sum << '\n';
  return 0;
}

void mix(long long int* secretNum, long long int otherVal) {
  // bitwise XOR
  *secretNum ^= otherVal;
}
void prune(long long int* secretNum) {
  // mod 16777216
  *secretNum %= 16777216;
}