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

        /* two bit-vectors for reachable positions */
        vector<char> cur(n + 1, 0), nxt(n + 1, 0);
        cur[0] = 1;

        for (int j = 0; j < m; ++j) {
            fill(nxt.begin(), nxt.end(), 0);
            vector<int> diff(n + 2, 0);               // difference array
            long long x = b[j];

            for (int i = 0; i < n; ++i) if (cur[i]) {
                long long lenMin;
                if (x == 1 || x == a[i])  lenMin = 1;
                else                       lenMin = max<long long>(2, x);

                if (i + lenMin <= n)
                    diff[i + lenMin] += 1;            // add range [i+lenMin , n]
            }

            /* prefix sum of 'diff' → reachable positions for column j+1 */
            int acc = 0;
            for (int p = 0; p <= n; ++p) {
                acc += diff[p];
                nxt[p] = (acc > 0);
            }
            cur.swap(nxt);
        }

        cout << (cur[n] ? "YES\n" : "NO\n");
    }
    return 0;
}
