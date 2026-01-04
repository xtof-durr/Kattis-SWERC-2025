#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n; long long l, r;
        cin >> n >> l >> r;

        vector<long long> lower, upperL, upperR, lowerR, all;
        lower.reserve(n);  upperL.reserve(n);
        upperR.reserve(n); lowerR.reserve(n);
        all.reserve(n);

        for (int i = 0; i < n; ++i) {
            long long a; cin >> a;
            all.push_back(a);
            if (a <  l) lower.push_back(l - a);          // for S>0, +1
            if (a >  l) upperL.push_back(a - l);         // for S>0, -1
            if (a >  r) upperR.push_back(a - r);         // for S<0, -1
            if (a <  r) lowerR.push_back(r - a);         // for S<0, +1
        }

        auto sum_vec = [](const vector<long long>& v){
            return accumulate(v.begin(), v.end(), 0LL);
        };

        /* ----------  positive slope  ---------- */
        long long best_pos = LLONG_MIN;
        if (!lower.empty()) {
            sort(upperL.begin(), upperL.end(), greater<>());
            int k = min<int>( (int)lower.size() - 1, (int)upperL.size() );
            long long takeUpper = accumulate(upperL.begin(), upperL.begin()+k, 0LL);
            best_pos = sum_vec(lower) + takeUpper;
        }

        /* ----------  negative slope  ---------- */
        long long best_neg = LLONG_MIN;
        if (!upperR.empty()) {
            sort(lowerR.begin(), lowerR.end(), greater<>());
            int k = min<int>( (int)upperR.size() - 1, (int)lowerR.size() );
            long long takeLower = accumulate(lowerR.begin(), lowerR.begin()+k, 0LL);
            best_neg = sum_vec(upperR) + takeLower;
        }

        /* ----------  zero slope  ---------- */
        long long best_zero = LLONG_MIN;
        if (n >= 2) {
            sort(all.begin(), all.end());
            int k = n / 2;
            long long sum_small = accumulate(all.begin(), all.begin()+k, 0LL);
            long long sum_large = accumulate(all.end()-k, all.end(), 0LL);
            best_zero = sum_large - sum_small;
        }

        long long ans = 0;
        ans = max(ans, best_pos);
        ans = max(ans, best_neg);
        ans = max(ans, best_zero);

        cout << ans << '\n';
    }
    return 0;
}
