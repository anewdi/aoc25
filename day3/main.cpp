#include <fstream>
#include <iostream>

class Solution {
public:
  int maxJolt2Bat(std::ifstream &input) {
    int sum = 0;
    std::string in;
    while (std::getline(input, in)) {
      int indexMax = 0;
      int max = 0;
      for (int x = 0, y = in.length() - 1; x < y; ++x) {
        int tempval = (in[x] - '0');
        if (tempval > max) {
          max = tempval;
          indexMax = x;
        }
      }
      sum += max * 10;
      max = 0;
      for (int x = indexMax + 1, y = in.length(); x < y; ++x) {
        int tempval = (in[x] - '0');
        max = tempval < max ? max : tempval;
      }
      sum += max;
    }
    return sum;
  }

  long maxJolt12Bat(std::ifstream &input) {
    long sum = 0;
    std::string in;

    while (std::getline(input, in)) {
      int maxIndex = -1;
      long tempsum = 0;
      for (int i = 0; i < 12; ++i) {
        long max = 0;
        for (int x = maxIndex + 1, y = in.length() - 11 + i; x < y; ++x) {
          long tempval = (in[x] - '0');
          if (max < tempval) {
            max = tempval;
            maxIndex = x;
          }
        }
        tempsum *= 10;
        tempsum += max;
      }
      sum += tempsum;
    }
    return sum;
  }
};

int main() {
  Solution s;
  std::ifstream in("./input.txt");
  std::cout << s.maxJolt2Bat(in) << std::endl;
  std::ifstream in2("./input.txt");
  std::cout << s.maxJolt12Bat(in2) << std::endl;
};
