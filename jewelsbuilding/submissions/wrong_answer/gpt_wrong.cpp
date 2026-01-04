#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<long long> a(n), b(m);
        for (auto &v : a) cin >> v;
        for (auto &v : b) cin >> v;

        vector<vector<char>> dp(n + 1, vector<char>(m + 1, 0));
        dp[0][0] = 1;

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < m; ++j) if (dp[i][j]) {
                long long x = b[j];

                /* take one element */
                if (i < n && (x == 1 || x == a[i]))
                    dp[i + 1][j + 1] = 1;

                /* take a segment of length x (x >= 2) */
                if (x >= 2 && i + x <= n)
                    dp[i + (int)x][j + 1] = 1;
            }
        }

        cout << (dp[n][m] ? "YES\n" : "NO\n");
    }
    return 0;
}
