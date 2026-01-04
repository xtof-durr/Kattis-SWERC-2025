#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int solve(const vector<int>& v) {
  assert(v.size() >= 2);
  for (int i = 1; i < v.size(); ++i) {
    if (v[i - 1] >= v[i]) {
      assert(v[i-1] % (v[i] - 1) == 0);
      return v[i-1] / (v[i] - 1);
    }
  }
  // One single run.
  int d = v[1] - v[0];
  assert(d > 0);
  return max(d, v.back() / d);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<int> v;
    for (int i = 0; i < n; ++i) {
      cin >> v.emplace_back();
    }
    cout << solve(v) << endl;
      
  }
}
