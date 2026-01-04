#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
typedef vector<int> vi;
#define f first
#define s second
#define derr if(1) cerr

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#define debug(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << flush;
// END NO SAD

template<class Fun>
class y_combinator_result {
  Fun fun_;
public:
  template<class T>
  explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

  template<class ...Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

template<class T>
bool updmin(T& a, T b) {
  if(b < a) {
    a = b;
    return true;
  }
  return false;
}
template<class T>
bool updmax(T& a, T b) {
  if(b > a) {
    a = b;
    return true;
  }
  return false;
}
typedef int64_t ll;
typedef long double ld;

struct node {
  int depth;
  node* lhs;
  node* rhs;
  node* par;
  vector<int> known;
};
node* makenode(int d, node* p) {
  node* ret = new node;
  ret->depth = d;
  ret->lhs = NULL;
  ret->rhs = NULL;
  ret->par = p;
  ret->known.clear();
  return ret;
}

void rsolve() {
  int n;
  cin >> n;
  map<array<int, 2>, int> dp;
  auto qry = [&](int x, int y) -> int {
    array<int, 2> key = {min(x, y), max(x, y)};
    if(!dp.count(key)) {
      cout << "? " << x << " " << y << endl;
      int ans;
      cin >> ans;
      dp[key] = ans;
    }
    return dp[key];
  };
  node* root = makenode(0, NULL);
  map<int, node*> nodedp;
  auto dfs = y_combinator([&](auto self, node* curr, vector<int> v, int b) -> void {
    if(b < 0 || sz(v) <= 1) {
      for(int out: v) {
        curr->known.pb(out);
        nodedp[out] = curr;
      }
      return;
    }
    node* lhs = makenode(curr->depth+1, curr);
    node* rhs = makenode(curr->depth+1, curr);
    curr->lhs = lhs;
    curr->rhs = rhs;
    sort(all(v));
    double lpen = 0, rpen = 0;
    for(int i = 1; i < sz(v); i++) lpen += 1/(v[i] - v[0] + 1.);
    for(int i = 0; i + 1 < sz(v); i++) rpen += 1/(v.back()-v[i]+1.);
    if(lpen <= rpen) {
      vector<int> lv, rv;
      lv.pb(v[0]);
      for(int i = 1; i < sz(v); i++) {
        int cand = qry(v[0]+1, v[i]);
        if(cand != b) lv.pb(v[i]);
        else rv.pb(v[i]);
      }
      self(curr->lhs, lv, b-1);
      self(curr->rhs, rv, b-1);
    }
    else {
      vector<int> lv, rv;
      lv.pb(v.back());
      for(int i = 0; i+1 < sz(v); i++) {
        int cand = qry(v[i]+1, v.back());
        if(cand != b) lv.pb(v[i]);
        else rv.pb(v[i]);
      }
      self(curr->lhs, lv, b-1);
      self(curr->rhs, rv, b-1);
    }
  });
  vector<int> cand(n+1);
  iota(all(cand), 0);
  dfs(root, cand, 29);
  cout << "!" << endl;
  for(int i = 1; i <= n; i++) {
    for(int j = i; j <= n; j++) {
      node* pl = nodedp[i-1];
      node* pr = nodedp[j];
      while(pl != pr) {
        if(pl->depth > pr->depth) pl = pl->par;
        else pr = pr->par;
      }
      cout << (29 - pl->depth);
      if(j == n) cout << endl;
      else cout << " ";
    }
  }
}

void solve() {
  int t = 1;
  cin >> t; cin.ignore();
  for(int cn = 1; cn <= t; cn++) {
    // cout << "Case #" << cn << ": ";
    rsolve();
  }
}

// what would chika do
// are there edge cases (N=1?)
// are array sizes proper (scaled by proper constant, for example 2* for koosaga tree)
// integer overflow?
// are you doing geometry in floating points
// have you tried rereading the problem statement

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
}