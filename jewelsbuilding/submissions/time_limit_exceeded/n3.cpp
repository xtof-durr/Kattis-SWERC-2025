#include <bits/stdc++.h>
using namespace std;

/* -------------------------------------------------------------
   A segment  a[l … r]  (length L = r-l+1) can generate b_j iff
   - L == 1  and  b_j is 1        or  b_j == a[l]
   - L >= 2  and  1 <= b_j <= L
   ------------------------------------------------------------- */

inline bool canMake(long long firstElem, int len, long long target) {
    if (len == 1)
        return target == 1 || target == firstElem;
    else
        return 1 <= target && target <= len;
}

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

        /* dp[i][j] = true  ⇔  prefix a[0..i-1]  can become  prefix b[0..j-1] */
        vector<vector<char>> dp(n + 1, vector<char>(m + 1, 0));
        dp[0][0] = 1;

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < m; ++j) if (dp[i][j]) {

                /* try every possible segment starting at position i */
                for (int k = i; k < n; ++k) {
                    int len = k - i + 1;                 // segment length
                    if (canMake(a[i], len, b[j])) {
                        dp[k + 1][j + 1] = 1;
                    }
                }
            }
        }

        cout << (dp[n][m] ? "YES\n" : "NO\n");
    }
    return 0;
}
