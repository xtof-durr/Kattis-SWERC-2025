#include <iostream>
#include <vector>
using namespace std;

int solve(){
	int n;
	cin >> n;
	vector<int> v(n);
	for(auto &x: v)cin >> x;
	for(int i = 1; i < n; ++i)
		if(v[i] <= v[i-1])
			return max(v[i-1]/(v[i] - 1), v[i]);
	int delta = v.back() - v[n-2];
	return max(delta, v.back()/delta);

}

int main(){
	int t; 
	cin >> t;
	while(t--)cout << solve() << endl;
}
