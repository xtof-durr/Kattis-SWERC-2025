#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define nf endl
#define ll long long
#define pb push_back
#define _ << ' ' <<

#define INF (ll)1e18
#define mod 998244353
#define maxn 110

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<ll> a(n + 1, 0), b(m + 1, 0);
        for (ll i = 1; i <= n; i++) cin >> a[i];
        for (ll i = 1; i <= m; i++) cin >> b[i];

        vector dp(n + 1, vector<array<bool, 2>>(m + 1, {false, false}));
        dp[0][0][0] = true;

        for (ll i = 0; i <= n; i++) {
            for (ll j = 0; j <= m; j++) {
                for (ll k = 0; k <= 1; k++) {
                    if (i + 1 <= n && k == 1) {
                        dp[i + 1][j][1] |= dp[i][j][k];
                    }
                    if (j + 1 <= m && i + b[j + 1] <= n) {
                        dp[i + b[j + 1]][j + 1][1] |= dp[i][j][k];
                    }
                    if (i + 1 <= n && j + 1 <= m && a[i + 1] == b[j + 1]) {
                        dp[i + 1][j + 1][0] |= dp[i][j][k];
                    }
                }
            }
        }

        if (dp[n][m][0] || dp[n][m][1]) cout << "YES" << nl;
        else cout << "NO" << nl;
    }

    return 0;
}
