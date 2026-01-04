#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define nf endl
#define ll int
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

    vector next_char(n + 2, vector<ll>(26, n + 1));
    for (ll i = n; i >= 1; i--) {
        for (ll c = 0; c < 26; c++) {
            next_char[i][c] = next_char[i + 1][c];
        }
        next_char[i][(ll)s[i] - 'a'] = i;
    }

    auto find_char = [&](ll c, ll l) {
        ll ans = next_char[l][c];
        assert(ans != n + 1);
        return ans;
    };

    vector<vector<ll>> adj_switch(26);
    vector next_switch(n + 2, vector<ll>(26, n + 1));
    for (ll c = 0; c < 26; c++) {
        auto &v = adj_pos[c];
        for (ll i = 0; i < (ll)v.size() - 1; i++) {
            ll p = v[i], q = v[i + 1];
            assert(p + 1 <= n);
            if (q + 1 > n || s[p + 1] != s[q + 1]) {
                adj_switch[c].pb(q);
                next_switch[q - 1][c] = q;
            }
        }
    }

    for (ll i = n; i >= 1; i--) {
        for (ll c = 0; c < 26; c++) {
            next_switch[i][c] = min(next_switch[i][c], next_switch[i + 1][c]);
        }
    }

    while (q--) {
        ll l, r; cin >> l >> r;
        ll mx_freq = 0;
        for (ll c = 0; c < 26; c++) {
            mx_freq = max(mx_freq, calc_freq(c, l, r));
        }

        vector<ll> adj_small(26);
        for (ll c = 0; c < 26; c++) {
            adj_small[c] = c;
            if (calc_freq(c, l, r) != mx_freq) continue;
            if ((ll)s[r] - 'a' == c) continue;
            ll p = find_char(c, l);
            assert(p <= r - 1);
            ll d = (ll)s[p + 1] - 'a';
            ll sw = next_switch[p][c];
            if (sw > r) {
                adj_small[c] = d;
                // cout << "edge" _ c _ d << nf;
            }
        }

        vector<bool> vis(26, false);
        for (ll c = 0; c < 26; c++) {
            if (calc_freq(c, l, r) != mx_freq) vis[c] = true;
        }

        ll ans = 0;
        vector<ll> dist(26, 0);
        function<void(ll)> dfs = [&](ll s) {
            vis[s] = true; dist[s] = 1;
            ll u = adj_small[s];
            if (u != s) {
                dfs(u); dist[s] = dist[u] + 1;
            }
            ans = max(ans, dist[s]);
        };

        for (ll c = 0; c < 26; c++) {
            if (vis[c]) continue;
            dfs(c);
        }

        assert(ans >= 1);
        cout << ans << nl;
    }

    return 0;
}
