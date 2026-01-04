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
    vector<ll> p4(n + 1, 0), p8(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        p4[i] = p4[i - 1] + (s[i] == '4');
        p8[i] = p8[i - 1] + (s[i] == '8');
    }

    while (q--) {
        ll l, r, x, y; cin >> l >> r >> x >> y;
        x = abs(x); y = abs(y);
        ll a = p4[r] - p4[l - 1];
        ll b = p8[r] - p8[l - 1];
        if (a + 2 * b < x + y) cout << "NO" << nl;
        else if (a + b < max(x, y)) cout << "NO" << nl;
        else cout << "YES" << nl;
    }

    return 0;
}
