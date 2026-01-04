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

    ll n, q; cin >> n >> q;
    string s; cin >> s; s = '#' + s;

    vector<vector<ll>> adj_pos(26);
    for (ll i = 1; i <= n; i++) adj_pos[(ll)s[i] - 'a'].pb(i);

    vector freq(n + 1, vector<ll>(26, 0));
    for (ll i = 1; i <= n; i++) {
        for (ll c = 0; c < 26; c++) {
            freq[i][c] = freq[i - 1][c];
        }
        freq[i][(ll)s[i] - 'a']++;
    }

    auto calc_freq = [&](ll c, ll l, ll r) {
        return freq[r][c] - freq[l - 1][c];
    };

    auto find_next = [&](ll c, ll l) {
        auto it = lower_bound(adj_pos[c].begin(), adj_pos[c].end(), l);
        assert(it != adj_pos[c].end());
        return *it;
    };

    vector<vector<ll>> adj_switch(26);
    for (ll c = 0; c < 26; c++) {
        auto &v = adj_pos[c];
        for (ll i = 0; i < (ll)v.size() - 1; i++) {
            ll p = v[i], q = v[i + 1];
            assert(p + 1 <= n);
            if (q + 1 > n || s[p + 1] != s[q + 1]) {
                adj_switch[c].pb(q);
            }
        }
    }

    while (q--) {
        ll l, r; cin >> l >> r;
        ll mx_freq = 0;
        for (ll c = 0; c < 26; c++) {
            mx_freq = max(mx_freq, calc_freq(c, l, r));
        }

        vector<vector<ll>> adj_small(26);
        for (ll c = 0; c < 26; c++) {
            if (calc_freq(c, l, r) != mx_freq) continue;
            if ((ll)s[r] - 'a' == c) continue;
            ll p = find_next(c, l);
            assert(p <= r - 1);
            ll d = (ll)s[p + 1] - 'a';
            auto &v = adj_switch[c];
            auto it = upper_bound(v.begin(), v.end(), p + 1);
            if (it == v.end() || (*it) > r) {
                adj_small[c].pb(d); adj_small[d].pb(c);
                // cout << "edge" _ c _ d << nf;
            }
        }

        vector<bool> vis(26, false);
        for (ll c = 0; c < 26; c++) {
            if (calc_freq(c, l, r) != mx_freq) vis[c] = true;
        }
        ll sz = 0, ans = 0;
        function<void(ll)> dfs = [&](ll s) {
            vis[s] = true; sz++;
            for (auto u : adj_small[s]) {
                if (vis[u]) continue;
                dfs(u);
            }
        };

        for (ll c = 0; c < 26; c++) {
            if (vis[c]) continue;
            sz = 0; dfs(c);
            ans = max(ans, sz);
        }

        assert(ans >= 1);
        cout << ans << nl;
    }

    return 0;
}
