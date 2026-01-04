#pragma GCC optimize ("Ofast,inline")
#include "bits/stdc++.h"
using namespace std;

//#define int long long
#define ll long long
#define ld long double

#define endl '\n'
#define st first
#define nd second
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) begin(x),end(x)
#define FOR(i,l,r) for (int i=(l);i<=(r);i++)
#define ROF(i,r,l) for (int i=(r);i>=(l);i--)
auto& operator<<(auto&o,pair<auto,auto>p){
	return o << "("<<p.st <<", "<<p.nd<<")";
}
auto operator<<(auto&o,auto x)->decltype(end(x),o){
	o << "{";int i=0;for (auto e:x) o<<","+!i++<<e;
	return o << "}";
}
#ifdef LOCAL
#define debug(x...) cerr << "[" #x "]: ", [](auto...$) {\
	((cerr << $ << "; "),...) << endl; }(x)
#else
#define debug(...)
#endif
#define rep(i,a,b) for (int i=(a);i<(b);i++)
using pii=pair<int,int>;
using vi=vector<int>;

const int inf=1e9+7;

const int N = 1e6 + 7;
const int A = 26;

int n, q;
string s;
int cnt[N][A];
int lst[N][A];
vi pos[A][A];

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	
	cin >> n >> q;
	cin >> s;
	s = '#' + s;

	rep(j,0,A)
		lst[0][j]=-10;

	FOR(i,1,n) {
		rep(j,0,A){
			cnt[i][j] = cnt[i-1][j];
			lst[i][j] = lst[i-1][j];
		}
		cnt[i][s[i]-'a']++;
		lst[i][s[i]-'a']=i;
	}

	FOR(i,2,n)
		pos[s[i-1]-'a'][s[i]-'a'].pb(i-1);

	FOR(i,1,q){
		int l, r;
		cin >> l >> r;

		vector<pii> best;
		rep(j,0,A) {
			pii now{cnt[r][j]-cnt[l-1][j],j};
			if(sz(best)==0||best[0].st < now.st)
				best = {now};
			else
			if (best[0].st == now.st)
				best.pb(now);
		}

	
		int ile = best[0].st;
		int good=0;
		for (auto[v,j]:best)
			good|=1<<j;

		auto chk = [&](int a, int b) {
			if (sz(pos[a][b]) < ile)
				return false;
			auto aa = lower_bound(all(pos[a][b]),l);
			auto bb = upper_bound(all(pos[a][b]),r-1);

			return (int)(bb-aa) == ile;
		};

		int ans=1;
		for (auto [v, j] : best) {
			int L = j, R = j, now = 1;
			if ((good>>j&1)==0)
				continue;

			bool ok=1;
			while (ok) { ok=0;
				int jj = lst[r][L]-1;
				if (l <= jj && jj <= r) {
					int k = s[jj] - 'a';
					if ((good>>k&1)&&chk(k, L)) {
						now++;
						L = k;
						ok=1;
						good^=1<<k;
					}
				}
			}
			ok=1;
			while (ok) { ok=0;
				int jj = lst[r][R]+1;
				if (l <= jj && jj <= r) {
					int k = s[jj] - 'a';
					if ((good>>k&1)&&chk(R, k)) {
						now++;
						R = k;
						ok=1;
						good^=1<<k;
					}
				}
			}
			ans = max(ans, now);
		}

		cout << ans << '\n';
	}

	return 0;
}