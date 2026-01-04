#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector v(n, vector(m, 0));
    for (auto &vv : v)
        for (auto &x : vv) cin >> x;
        
    if (n % 2 == 0) {
        sort(v.begin(), v.end());
        for (int i = 0; i < n; i += 2)
            for (auto x : v[i]) cout << x << ' ';
        cout << endl;
        return;
    }
    
    vector<int> end(n * m + 1);
    for (int i = 0; i < n; ++i) end[v[i][m / 2]] = i;

    vector<int> ans;
    ans.push_back(0);
    while (ans.size() <= n / 2) {
        int cur = ans.back();
        int match = end[v[cur][0]];
        ans.push_back(end[v[match][0]]);
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n / 2; ++i)
        for (auto x : v[ans[i]]) cout << x << ' ';
    for (int i = 0; i < m / 2; ++i) cout << v[0][i] << ' ';
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}
