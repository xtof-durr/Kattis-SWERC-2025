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
        vector mt(n, vector<ll>(m, 0));
        map<array<ll, 2>, ll> row;
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                cin >> mt[i][j]; row[{mt[i][j], j}] = i;
            }
        }

        vector<ll> sol(n * m, -1);
        vector<bool> vis(n, false);

        function<void(ll, ll)> dfs = [&](ll s, ll pos) {
            // cout << "dfs" _ s _ pos << nf;
            if (vis[s]) return;
            vis[s] = true;
            for (ll i = 0; i < m; i++) {
                // cout << "fill" _ pos * m + i << nf;
                sol[pos * m + i] = mt[s][i];
            }

            for (ll i = 0; i < m; i++) {
                ll new_ext = (pos * m + i + n * m / 2) % (n * m);
                ll new_col = new_ext % m;
                ll new_pos = new_ext / m;
                assert(row.find({mt[s][i], new_col}) != row.end());
                ll match = row[{mt[s][i], new_col}];
                // cout << "match, new_pos =" _ match _ new_pos << nf;
                dfs(match, new_pos);
            }
        };

        ll ext = 0;
        for (ll i = 0; i < n; i++) {
            if (vis[i]) continue;
            while (ext < n * m && sol[ext] != -1) ext++;
            assert(ext != n * m);
            dfs(i, ext / m);
        }

        for (ll i = 0; i < n * m / 2; i++) {
            assert(sol[i] == sol[n * m / 2 + i]);
        }

        for (ll i = 0; i < n * m / 2; i++) {
            cout << sol[i] << ' ';
        }
        cout << nl;
    }

    return 0;
}
