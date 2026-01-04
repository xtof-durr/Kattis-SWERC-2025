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
  int ops = 0;
  for (int i = 0; i < n ; i++) {
    int count = 0;
    if (a[i] == -1) {
      continue;
    }
    int val = a[i];
    for (int j = 0; j < n ; j++) {
      if (val == a[j]) {
        count++;
        a[j] = -1;
      }
    }
    // std::cout << "Count of " << val << " " << count << std::endl;
    if (count > val) {
  		ops += count - val;
  	} else if (count < val) {
  		ops += count;
  	}
  }
  std::cout << ops << std::endl;
  return 0;
}