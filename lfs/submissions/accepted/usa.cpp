#include <bits/stdc++.h>

using namespace std;

const int K = 26;

int n, q;

string str;

vector<vector<pair<int, int>>> queries;
vector<int> ans;

vector<int> lastindex(K, -1);
vector<array<int, K>> freq;

set<int> lasts;
vector<bool> ismax(K);

vector<vector<vector<int>>> graph(K, vector<vector<int>>(K));

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    cin >> str;
    str = '$' + str;

    queries.assign(n + 1, {});
    ans.assign(q + 1, 1);

    for(int i = 1; i <= q; i++){
        int l, r;
        cin >> l >> r;
        queries[r].push_back({l, i});
    }

    freq.assign(n + 1, {});

    for(int r = 1; r <= n; r++){
        freq[r] = freq[r - 1];
        freq[r][str[r] - 'a']++;

        if(lastindex[str[r] - 'a'] != -1) lasts.erase(lastindex[str[r] - 'a']);

        lastindex[str[r] - 'a'] = r;
        lasts.insert(r);

        if(r > 1) graph[str[r] - 'a'][str[r - 1] - 'a'].push_back(r - 1);

        for(auto [l, qi] : queries[r]){
            int mx = 0;
            for(int i = 0; i < K; i++) mx = max(mx, freq[r][i] - freq[l - 1][i]);
            for(int i = 0; i < K; i++) ismax[i] = (freq[r][i] - freq[l - 1][i]) == mx;

            int prvc = -1, curlen = 0;

            for(auto it = lasts.rbegin(); it != lasts.rend(); it++){
                int curc = str[*it] - 'a';

                if(!ismax[curc]) continue;

                if(prvc != -1 && graph[prvc][curc].size() >= mx && graph[prvc][curc].end()[-mx] >= l){
                    prvc = curc;
                    curlen++;

                    ans[qi] = max(ans[qi], curlen);
                }
                else prvc = curc, curlen = 1;
            }
        }
    }

    for(int i = 1; i <= q; i++) cout << ans[i] << "\n";
}