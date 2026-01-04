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
 
    #if !ONLINE_JUDGE && !EVAL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #endif
 
    ll n, m; cin >> n >> m;
    ll k = 2000;
 
    auto cyc = [&](vector<ll> p) {
        vector<bool> vis(p.size(), false);
        ll ans = 0;
        for (ll i = 0; i < p.size(); i++) {
            if (vis[i]) continue;
            ans++;
            for (ll j = i; vis[j] == false; j = p[j]) vis[j] = true;
        }
 
        return ans;
    };
 
    auto print = [&](vector<vector<ll>> ans) {
        cout << ans.size() << nl;
        for (auto v : ans) {
            reverse(v.begin(), v.end());
            for (auto u : v) cout << n - u << ' ';
            cout << nl;
        }
    };
 
    auto resize_all = [&](vector<vector<ll>> &ans, ll len) {
        for (auto &v : ans) {
            ll old_len = v.size();
            v.resize(len);
            for (ll i = old_len; i < len; i++) v[i] = i;
        }
    };
 
    auto cut = [&](vector<ll> &v, ll n) {
        n = min(n, (ll)v.size());
        for (ll i = 0; i < n; i++) {
            if (v[i] >= n) return false;
        }
        return true;
    };
 
    auto filter = [&](ll n, ll m, ll k, ll len) {
        vector<vector<ll>> ans;
        vector<ll> p(n);
        for (ll mk = 0; mk < (1 << (n - 1)); mk++) {
            if (ans.size() == k) break;
 
            ll pos = 0;
            for (ll j = n - 2; j >= 0; j--) {
                if (mk >> j & 1) p[pos] = j + 1, pos++;
            }
            p[pos] = 0; pos++;
            for (ll j = 0; j <= n - 2; j++) {
                if (!(mk >> j & 1)) p[pos] = j + 1, pos++;
            }
            assert(pos == n);
 
            if (cyc(p) == m && cut(p, len) == true) ans.pb(p);
        }
 
        return ans;
    };
 
    if (n <= 18) {
        vector<vector<ll>> ans = filter(n, m, k, n);
        print(ans);
        return 0;
    }
 
    if (n - m >= 10) {
        ll start_n = 19;
        ll start_m = max((ll)1, start_n - (n - m));
        vector<vector<ll>> ans = filter(start_n, start_m, k, n);
        resize_all(ans, n);
        ll delta = (start_m - start_n) - (m - n);
        for (auto &v : ans) {
            ll l = v[0] + 1, r = v[0] + delta;
            v[0] = r;
            for (ll i = 1; i < n; i++) {
                if (l <= v[i] && v[i] <= r) v[i]--;
            }
        }
        print(ans);
        return 0;
    }
 
    ll diff = n - m;
    vector<vector<ll>> ans = filter(2 * diff + 1, diff + 1, k, n);
    resize_all(ans, n);
    print(ans);
 
    return 0;
}
