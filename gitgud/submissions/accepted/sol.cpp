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

    ll n = 250047, k = 63;

    vector<array<ll, 2>> ans;
    for (ll len = 1; len < n; len *= k) {
        for (ll delta = 0; delta < len * (k - 1); delta += len) {
            for (ll left = n - len * (k - 1); left >= 1; left -= len * k) {
                ans.pb({left + delta, len});
            }
        }
    }

    cout << ans.size() << nl;
    for (auto [a, b] : ans) cout << a _ b << nl;

    return 0;
}
