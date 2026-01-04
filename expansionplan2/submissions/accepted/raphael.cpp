#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int main() {
  int _n, q;
  cin >> _n >> q;
  string s;
  cin >> s;
  vector<int> v4, v8;
  for (char c : s) {
    v4.push_back(v4.empty() ? c == '4' : v4.back() + (c == '4'));
    v8.push_back(v8.empty() ? c == '8' : v8.back() + (c == '8'));
  }
  
  for (int i = 0; i < q; ++i) {
    int l, r, x, y;
    cin >> l >> r >> x >> y;
    l--;
    r--;
    const int n4 = v4[r] - (l - 1 >= 0 ? v4[l - 1] : 0);
    const int n8 = v8[r] - (l - 1 >= 0 ? v8[l - 1] : 0);
    x = abs(x);
    y = abs(y);
    const int n = n4 + n8;
    if (x <= n && y <= n && x + y <= 2 * n - n4) {
      cout << "YES" << "\n";
    } else {
      cout << "NO" << "\n";
    }
  }
}
