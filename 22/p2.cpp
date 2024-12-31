#include <fstream>
#include <iostream>
#include <vector>

struct Price { short int val, change; };

std::vector<std::vector<Price>> findPrices();
short int countBananas(std::vector<Price>& prices, const std::vector<short int>& currSq);
int bananasYielded(const std::vector<std::vector<Price>>& buyers, const std::vector<short int>& currSq);

int main() {
  int mostBananas = 0;
  std::vector<short int> bestSequence = {6, 9, 2, 1};
  const std::vector<std::vector<Price>> buyers = findPrices();
  // try out every sequence possible... LOL... nvm ts takes too long
  for (short int first = -9; first != 10; ++first) {
    for (short int second = -9; second != 10; ++first) {
      for (short int third = -9; third != 10; ++first) {
        for (short int fourth = -9; fourth != 10; ++fourth) {
          const std::vector<short int> currSq = {first, second, third, fourth};
          const int bananas = bananasYielded(buyers, currSq);
          // std::cout << "bananas yielded: " << bananas << '\n';
          // only update if sequence performed the best so far
          if (bananas > mostBananas) {
            mostBananas = bananas;
            bestSequence = currSq;
          }
        }
      }
    }
  }
  // i told her man's not hot
  std::cout << "Best sequence of 4 changes in prices: ";
  for (const short int& change : bestSequence) {
    std::cout << change << ' ';
  } 
  std::cout << '\n';
  std::cout << "Most bananas yielded: " << mostBananas << '\n';
  return 0;
}

std::vector<std::vector<Price>> findPrices() {
  std::vector<std::vector<Price>> buyers;
  std::ifstream input("input.txt");
  long long int secretNum;
  // find the 2000 prices and price changes for each input number
  while (input >> secretNum) {
    std::vector<Price> prices(2001);
    short int val = secretNum % 10;
    // set initial price
    prices[0] = Price{val, 0};
    for (short int i = 1; i != 2001; ++i) {
      // multiply by 64, mix result, then prune
      secretNum ^= secretNum << 6;
      secretNum %= 16777216;
      // divide by 32, mix result, then prune
      secretNum ^= secretNum >> 5;
      secretNum %= 16777216;
      // multiply by 2048, mix result, then prune
      secretNum ^= secretNum << 11;
      secretNum %= 16777216;
      // figure out price (one's digit) and change in price
      val = secretNum % 10;
      prices[i] = Price{val, (short int) (val - prices[i - 1].val)};
    }
    buyers.push_back(prices);
  }
  input.close();
  return buyers;
}

short int countBananas(const std::vector<Price>& prices, const std::vector<short int>& currSq) {
  for (short int i = 1; i != 1998; ++i) {
    if (prices[i].change == currSq[0] && prices[i + 1].change == currSq[1]
    && prices[i + 2].change == currSq[2] && prices[i + 3].change == currSq[3]) {
      std::cout << prices[i + 3].val << '\n';
      return prices[i + 3].val;
    }
  }
  return 0;
}

int bananasYielded(const std::vector<std::vector<Price>>& buyers, const std::vector<short int>& currSq) {
  int bananas = 0;
  for (const std::vector<Price>& prices : buyers) {
    bananas += countBananas(prices, currSq);
  }
  return bananas;
}