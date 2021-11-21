#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using ull = unsigned long long;

int digitSum(ull n) {
  n *= 10;

  int res = 0;

  while (n) res += (n /= 10) % 10;

  return res;
}

int solve(ull j, int k) {

  int sumJ = digitSum(j);

  if (sumJ == k)
    sumJ = digitSum(j += 9);

  if (sumJ > k) { 

  }

  if (sumJ < k) {

    int diff = k - sumJ;

  }

  return j;
}

int main() {
  int T;

  std::cin >> T;

  for (int i = 0; i < T; ++i) { 

    ull j;
    int k;

    std::cin >> j >> k;

    std::cout << solve(j, k) << std::endl;
  }

  return 0;
}