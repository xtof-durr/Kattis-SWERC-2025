#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define SZ(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()

// Returns the time elapsed in nanoseconds from 1 January 1970, at 00:00:00.
LL get_time() {
    return chrono::duration_cast<chrono::nanoseconds>(
        chrono::steady_clock::now().time_since_epoch())
        .count();
}

// Returns a random integer from the range [l, r].
LL randint(LL l, LL r) {
	#if LOCAL && !ONLINE_JUDGE
	static mt19937_64 gen; // Deterministic on the local machine.
	#else
	static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
	#endif
	return uniform_int_distribution<LL>(l, r)(gen);
}

template <typename Iterator>
string print_iterable(Iterator begin, Iterator end, string bef, string aft,
        function<string(typename iterator_traits<Iterator>::value_type)>* f = nullptr);

template <typename S, typename T>
ostream& operator <<(ostream& out, const pair<S, T>& p);

#define _define_print_container(Container, bef, aft)        \
template <typename T>                                       \
ostream& operator <<(ostream& out, const Container<T>& v) { \
    out << print_iterable(v.begin(), v.end(), bef, aft);    \
    return out;                                             \
}                                                           \

_define_print_container(vector, "[", "]");
_define_print_container(set, "{", "}");
_define_print_container(unordered_set, "{", "}");
_define_print_container(multiset, "{", "}");
_define_print_container(unordered_multiset, "{", "}");
_define_print_container(deque, "[", "]");

#define _define_print_dictionary(Dictionary, bef, aft)                      \
template <typename T1, typename T2>                                         \
ostream& operator <<(ostream& out, const Dictionary<T1, T2>& v) {           \
    out << print_iterable(v.begin(), v.end(), bef, aft);                    \
    return out;                                                             \
}                                                                           \

_define_print_dictionary(map, "{", "}");
_define_print_dictionary(unordered_map, "{", "}");

#define _define_print_container_adaptor(Adaptor, OP)                        \
template <typename T>                                                       \
ostream& operator <<(ostream& out, Adaptor<T> a) {                          \
    vector<T> v;                                                            \
    while (!a.empty()) v.push_back(a.OP()), a.pop();                        \
    out << v;                                                               \
    return out;                                                             \
}                                                                           \

_define_print_container_adaptor(stack, top)
_define_print_container_adaptor(queue, front)
_define_print_container_adaptor(priority_queue, top)

template <typename Iterator>
string print_iterable(Iterator begin, Iterator end, string bef, string aft,
        function<string(typename iterator_traits<Iterator>::value_type)>* f) {
    stringstream res;
    res << bef;
    bool is_first = true;
    for (Iterator it = begin; it != end; ++it) {
        if (!is_first) res << ", ";
        if (f != nullptr) res << (*f)(*it);
        else res << *it;
        is_first = false;
    }
    res << aft;
    return res.str();
}

template <typename S, typename T>
ostream& operator <<(ostream& out, const pair<S, T>& p) {
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}

template<class TH>
void _dbg(const char* name, TH val){
    clog << name << ": " << val << endl;
}
template<class TH, class... TA>
void _dbg(const char* names, TH curr_val, TA... vals) {
    while(*names != ',') clog << *names++;
    clog << ": " << curr_val << ", ";
    _dbg(names+1, vals...);
}

#if LOCAL && !ONLINE_JUDGE
    ifstream input_from_file("input.txt");
    #define cin input_from_file

    #define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
    #define dbg_arr(x, len) \
    clog << #x << ": " << print_iterable(x, x+len, "[", "]") << endl;
    #define dbg_arr1(x, len) \
    clog << #x << ": " << print_iterable(x+1, x+len+1, "[", "]") << endl;
#else
    #define dbg(...)
    #define dbg_arr(x, len)
    #define dbg_arr1(x, len)
#endif

///////////////////////////////////////////////////////////////////////////
//////////////////// DO NOT TOUCH BEFORE THIS LINE ////////////////////////
///////////////////////////////////////////////////////////////////////////

const int MAXN = 1'000'010;
int last_occ[26][MAXN];
int cnt[26][MAXN];
int last_diff[MAXN];


void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    for (int c = 0; c < 26; c++)
        last_occ[c][0] = -1;
    last_occ[s[0]-'a'][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int c = 0; c < 26; c++)
            last_occ[c][i] = last_occ[c][i-1];
        last_occ[s[i]-'a'][i] = i;
    }

    for (int c = 0; c < 26; c++)
        cnt[c][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++)
            cnt[c][i+1] = cnt[c][i];
        cnt[s[i]-'a'][i+1]++;
    }
    for (int i = 0; i < n-1; i++) {
        int prev_occ = (i == 0)? -1 : last_occ[s[i]-'a'][i-1];
        if (prev_occ == -1)
            last_diff[i] = -1;
        else {
            if (s[prev_occ+1] != s[i+1])
                last_diff[i] = prev_occ;
            else
                last_diff[i] = last_diff[prev_occ];
        }
    }

    vector<int> freq(26, 0);
    vector<bool> good(26, false);
    vector<int> follow(26, -1);
    vector<int> depth(26, 0);
    function<int(int)> dfs = [&](int c) {
        if (c == -1)
            return 0;
        if (depth[c] == 0)
            depth[c] = 1 + dfs(follow[c]);
        return depth[c];
    };
    for (int _ = 0; _ < q; _++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        for (int c = 0; c < 26; c++)
            freq[c] = cnt[c][r+1] - cnt[c][l];
        int max_freq = 0;
        for (int c = 0; c < 26; c++)
            max_freq = max(max_freq, freq[c]);
        for (int c = 0; c < 26; c++)
            good[c] = freq[c] == max_freq;

        for (int c = 0; c < 26; c++) {
            if (s[r]-'a' == c)
                follow[c] = -1;
            else if (!good[c])
                follow[c] = -1;
            else {
                int pos = last_diff[last_occ[c][r]];
                if (pos >= l)
                    follow[c] = -1;
                else {
                    int maybe = s[last_occ[c][r]+1]-'a';
                    if (good[maybe])
                        follow[c] = maybe;
                    else
                        follow[c] = -1;
                }
            }
        }

        for (int c = 0; c < 26; c++)
            depth[c] = 0;
        int ans = 0;
        for (int c = 0; c < 26; c++) {
            if (depth[c] != 0 or !good[c])
                continue;
            ans = max(ans, dfs(c));
        }
        cout << ans << "\n";

    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); // Remove in problems with online queries!

    solve();
}