#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int p[26], sz[26];
    DSU() { iota(p, p+26, 0); fill(sz, sz+26, 1); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
    }
    int size(int x){ return sz[find(x)]; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if(!(cin >> n >> q)) return 0;
    string s; cin >> s;
    // 1-index the string for convenience
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) a[i] = s[i-1]-'a';

    // Per-letter structures
    array<vector<int>,26> pos;
    array<vector<unsigned char>,26> nxt;
    array<vector<int>,26> chg;
    // firstIdx[c][i] = first index j such that pos[c][j] >= i
    // size n+2 so we can safely query r+1 == n+1
    array<vector<int>,26> firstIdx;

    for(int c=0;c<26;c++){
        pos[c].reserve(n/26 + 4);
    }
    for(int i=1;i<=n;i++) pos[a[i]].push_back(i);

    for(int c=0;c<26;c++){
        int m = (int)pos[c].size();
        nxt[c].resize(m);
        chg[c].resize(m);
        for(int j=0;j<m;j++){
            int p = pos[c][j];
            if(p < n) nxt[c][j] = (unsigned char)a[p+1];
            else      nxt[c][j] = (unsigned char)255; // sentinel, never queried
        }
        if(m>0){
            chg[c][0] = 0;
            for(int j=1;j<m;j++){
                chg[c][j] = chg[c][j-1] + (nxt[c][j] != nxt[c][j-1]);
            }
        }
        firstIdx[c].assign(n+2, 0);
        int j = 0;
        for(int i=1;i<=n+1;i++){
            while(j < m && pos[c][j] < i) ++j;
            firstIdx[c][i] = j; // first index with pos >= i (or m if none)
        }
    }

    // Process queries
    while(q--){
        int l, r; cin >> l >> r;
        int cnt[26];
        int f = 0;
        bool inS[26] = {false};
        for(int c=0;c<26;c++){
            // count occurrences of c in [l, r]
            int leftIdx  = firstIdx[c][l];
            int rightIdx = firstIdx[c][r+1]; // first >= r+1
            cnt[c] = rightIdx - leftIdx;
            if(cnt[c] > f) f = cnt[c];
        }
        vector<int> Sf;
        Sf.reserve(26);
        for(int c=0;c<26;c++){
            if(cnt[c] == f && f>0){
                Sf.push_back(c);
                inS[c] = true;
            }
        }

        // Build tiny graph among Sf via the "unique follower" rule
        DSU dsu;
        // We'll only union nodes that are in Sf; others are irrelevant
        // But DSU has all 26 nodes; we just ignore sizes of nodes not in Sf later.

        for(int c: Sf){
            int follow = cnt[c] - (a[r]==c ? 1 : 0);
            if(follow <= 0) continue; // no follower constraint inside [l,r-1]
            int L = firstIdx[c][l];
            int R = firstIdx[c][r] - 1; // indices in pos[c] such that pos in [l, r-1]
            if(L > R) continue; // should coincide with follow==0
            // all followers identical?
            int changes = chg[c][R] - (L ? chg[c][L] : 0);
            if(changes == 0){
                int d = (int)nxt[c][L];
                if(0 <= d && d < 26 && inS[d]){
                    dsu.unite(c, d);
                }
            }
        }

        // Compute max component size restricted to Sf
        int best = 0;
        // mark representatives seen to avoid recounting unrelated letters
        bool seen[26] = {false};
        for(int c: Sf){
            int rcp = dsu.find(c);
            if(!seen[rcp]){
                seen[rcp] = true;
                // size counts all letters (0..25); we must cap to those in Sf
                // To be precise on Sf only, re-count:
                int sz = 0;
                for(int x: Sf) if(dsu.find(x)==rcp) ++sz;
                best = max(best, sz);
            }
        }
        cout << best << '\n';
    }
    return 0;
}
