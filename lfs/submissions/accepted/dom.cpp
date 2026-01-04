#include <bits/stdc++.h>
using namespace std;

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n, q; cin >> n >> q;
    
    string s; cin >> s;
    s = "0" + s;
    
    vector <int> a(n + 1);
    vector <int> prev(26, -1);
    vector<vector<int>> dp(n + 1, vector<int>(27, 0));
    
    for (int i = 1; i <= n; i++){
        int c = s[i] - 'a';
        
        if (prev[c] != -1){
            for (int j = 1; j <= 26; j++){
                if (i + j - 1 > n) break;
                if (s[prev[c] + j - 1] != s[i + j - 1]){
                    break;
                }
                a[i]++;
            }
            
            for (int j = 1; j <= 26; j++){
                if (j > a[i]){
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[prev[c]][j] + 1;
                }
            }
        }
        
        prev[c] = i;
    }
    
    vector<vector<pair<int, int>>> qq(n + 1);
    for (int i = 1; i <= q; i++){
        int l, r; cin >> l >> r;
        qq[r].push_back({l, i});
    }
    
    vector <int> ans(q + 1);
    
    vector<vector<int>> pref(n + 1, vector<int>(26, 0));
    for (int i = 1; i <= n; i++){
        pref[i] = pref[i - 1];
        pref[i][s[i] - 'a']++;
    }
    
    vector <int> last(26, 0);
    for (int r = 1; r <= n; r++){
        last[s[r] - 'a'] = r;
        
        for (auto [l, id] : qq[r]){
            int f = 0;
            for (int i = 0; i < 26; i++){
                f = max(f, pref[r][i] - pref[l - 1][i]);
            }
            
            if (f == 1){
                ans[id] = (r - l + 1);
                continue;
            }
            
            int res = 1;
            for (int i = 0; i < 26; i++){
                if (pref[r][i] - pref[l - 1][i] == f){
                    // cout << "FOR " << id << "  TRY " << i << "\n";
                    int lst = last[i];
                    while (res + 1 <= 26 && lst + res <= r && dp[lst][res + 1] >= f - 1){
                        res++;
                    }
                }
            }
            
            ans[id] = res;
        }
    }
    
    for (int i = 1; i <= q; i++){
        cout << ans[i] << "\n";
    }
}

int32_t main() 
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // freopen("in",  "r", stdin);
    // freopen("out", "w", stdout);
    
 //   cin >> t;
    for(int i = 1; i <= t; i++) 
    {
        //cout << "Case #" << i << ": ";
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}