#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> fours(n + 1), eights(n + 1);

    for (int i = 0; i < n; ++i) {
        fours[i + 1] = fours[i] + (s[i] == '4');
        eights[i + 1] = eights[i] + (s[i] == '8');
    }

    for (int i = 0; i < q; ++i) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        x = abs(x);
        y = abs(y);
        int four = fours[r] - fours[l - 1];
        int eight = eights[r] - eights[l - 1];
        if (max(0, x - eight) + max(0, y - eight) <= four)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
