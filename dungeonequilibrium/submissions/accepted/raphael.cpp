#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> occ(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    assert(x >= 0);
    assert(x <= n);
    ++occ[x];
  }
  int res = 0;
  for (int i = 0; i < occ.size(); ++i) {
    if (occ[i] > i) {
      res += occ[i] - i;
    } else if (occ[i] < i) {
      res += occ[i];
    }
  }
  cout << res << endl;
}
