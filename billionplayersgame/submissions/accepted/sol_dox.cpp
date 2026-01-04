#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    sort(v.begin(), v.end());
    vector<int> small, big;
    deque<int> mid;
    for (auto x : v) {
        if (x < l)
            small.push_back(x);
        else if (x > r)
            big.push_back(x);
        else
            mid.push_back(x);
    }

    ll ans = 0;
    while (small.size() && big.size()) {
        ans += big.back() - small.back();
        big.pop_back();
        small.pop_back();
    }

    while (mid.size() && big.size()) {
        ans += big.back() - mid.front();
        mid.pop_front();
        big.pop_back();
    }

    while (mid.size() && small.size()) {
        ans += mid.back() - small.back();
        mid.pop_back();
        small.pop_back();
    }

    for (auto x : small) ans += l - x;
    for (auto x : big) ans += x - r;
    while (mid.size() > 1) {
        ans += mid.back() - mid.front();
        mid.pop_back();
        mid.pop_front();
    }

    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}
