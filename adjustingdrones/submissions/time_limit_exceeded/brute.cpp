#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    sort(v.begin(), v.end());
    int ans = 0;
    for (; ans <= n; ++ans) {
        int cnt = 1;
        int max_freq = 0;
        for (int i = 1; i < n; ++i) {
            if (v[i] == v[i - 1])
                ++cnt;
            else
                cnt = 1;
            max_freq = max(max_freq, cnt);
        }
        if (max_freq <= k) break;

        for (int i = n; --i;)
            if (v[i] == v[i - 1]) ++v[i];
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}
