#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> freq(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        ++freq[x];
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (freq[i] < i)
            ans += freq[i];
        else
            ans += freq[i] - i;
    }
    std::cout << ans << '\n';
}
