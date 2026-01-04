// Complexity O(n log n) for each test case.

#include <iostream>
#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <algorithm>
#include <map>
#include <cstdint>

using namespace std;

int64_t solve(vector<int64_t> a, int64_t l, int64_t r) {
  sort(a.begin(), a.end());
  assert(a.size() >= 1);
  int64_t best = 0;

  // First option, we have the same number of pluses and minuses.
  // In that case, f(x) = sum(s_i * x) - sum(s_i * a_i) = -sum(s_i * a_i).
  // So its min over x in [l, r] is -sum(s_i * a_i), which we can
  // maximize greedily.
  int64_t cur = 0;
  for (int i = 0; i < a.size() / 2; ++i) {
    assert(a[i] >= 0);
    assert(a[a.size()  - i - 1] >= 0);
    cur += -a[i] + a[a.size() - i - 1];
  }
  best = max(best, cur);
  
  cur = 0;
  // Second option, more pluses than minuses.
  // f(x) = x * sum(s_i) - sum(s_i * a_i).
  // sum(s_i) > 0, so min(f(x), x in [l, r]) = f(l).
  // f(l) = sum(s_i * (l - a_i)) which we optimize greedily, making
  // sure there is at least one more s_i = 1 than s_i = -1.
  int i = 0;
  int j = a.size() - 1;
  // First "plus", use the most positive l - a_i.
  cur += l - a[i++];
  // One minus and one plus as long the minus in itself is >=0.
  // Otherwise (i.e. a[j] - l < 0), we can stop, as this minus
  // and subsequent ones (due to order of the a_i's) don't help and
  // don't allow adding more pluses (as we are not bounded in number
  // of pluses). 
  // Note that a[j] - a[i] is always >= 0 due to order of the a_i's.
  while (i < j && a[j] - l >= 0) {
    cur += l - a[i++];
    cur += a[j--] - l;
  }
  // Add last pluses that are positive.
  while (i <= j && l - a[i] >= 0) {
    cur += l - a[i++];
  }
  best = max(best, cur);

  cur = 0;
  // Third option, more minuses than pluses.
  // Miror to the second option, where the min of the function is f(r).
  i = 0;
  j = a.size() - 1;
  cur += a[j--] - r;
  // Only add the pluses that are useful.
  while (i < j && r - a[i] >= 0) {
    cur += r - a[i++];
    cur += a[j--] - r;
  }
  // Add last minuses that are positive.
  while (i <= j && a[j] - r >= 0) {
    cur += a[j--] - r;
  }
  best = max(best, cur);
  return best;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int64_t n, l, r;
    cin >> n >> l >> r;
    vector<int64_t> a;
    for (int i = 0; i < n; ++i) {
      cin >> a.emplace_back();
    }
    cout << solve(a, l, r) << endl;
  }
}
