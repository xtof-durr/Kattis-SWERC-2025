#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (auto &x : v) cin >> x;

    auto check_zero = [&]() {
        vector<int> freq(2 * n + 1, 0);
        for (auto x : v) ++freq[x];
        for (auto x : freq)
            if (x > k) return false;
        return true;
    };

    if (check_zero()) {
        cout << 0 << endl;
        return;
    }

    auto run = [&](int num_iter) {
        vector<int> freq(4 * n, 0);
        vector<int> zeros;
        zeros.reserve(4 * n);
        for (auto x : v) ++freq[x];
        for (int i = 4 * n; i--;) {
            if (freq[i] == 0) zeros.push_back(i);
            while (freq[i] > 1 && zeros.back() <= i + num_iter) {
                --freq[i];
                ++freq[zeros.back()];
                zeros.pop_back();
            }
            if (freq[i] > 1) {
                freq[i + num_iter] += freq[i] - 1;
                freq[i] = 1;
            }
        }
        for (auto x : freq)
            if (x > k) return false;
        return true;
    };

    int bs = 0;
    for (int i = 1 << 20; i; i /= 2) {
        if (run(bs + i) == false) bs += i;
    }
    cout << bs + 1 << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}
