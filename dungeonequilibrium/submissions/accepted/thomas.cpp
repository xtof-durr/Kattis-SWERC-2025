#include <iostream>
#include <cassert>
#include <vector>

int main(void) {
  int n;
  std::cin >> n;
  std::vector<int> a;
  a.reserve(n);
  for (int i = 0 ; i < n ; i++) {
    int x;
    std::cin >> x;
    a.push_back(x);
  }
  std::vector<int> counts(n+1);
  for (const auto & x : a) {
    assert(x <= n);
    counts[x]++;
    // std::cout << x << std::endl;
  }
//    for (int i = 0 ; i <= n ; i++) {
//      std::cout << "counts[" << i << "] = " << counts[i] << std::endl;
//    }
  int ops = 0;
  for (int i = 0; i <= n ; i++) {
  	if (counts[i] > i) {
  		ops += counts[i] - i;
  	} else if (counts[i] < i) {
  		ops += counts[i];
  	}
  }
  std::cout << ops << std::endl;
  return 0;
}