#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

vector<int> first_half(const vector<int>& b) {
  return vector<int>(b.begin(), b.begin() + b.size() / 2);
}
vector<int> second_half(const vector<int>& b) {
  return vector<int>(b.begin() + b.size() / 2, b.end());
}

vector<int> solve(const vector<vector<int>>& blocks) {
  int n = blocks.size();
  int m = blocks[0].size();
  if (n % 2 == 0) {
    vector<int> res;
    set<vector<int>> seen;
    for (const vector<int>& b : blocks) {
      if (seen.find(b) != seen.end()) continue;
      seen.insert(b);
      res.insert(res.end(), b.begin(), b.end());
    }
    return res;
  }
  assert(m % 2 == 0);
  map<vector<int>, int> second_half_to_index;
  for (int i = 0; i < blocks.size(); ++i) {
    const auto second = second_half(blocks[i]);
    assert(second_half_to_index.find(second) == second_half_to_index.end());
    second_half_to_index[second] = i;
  }

  // Naively, we try every block as middle block (so we don't have to
  // convince ourselves that any block works).
  vector<int> ans;
  for (int middle = 0; middle < n; ++middle) {
    set<int> used;
    vector<vector<int>> res;
    const vector<int>* cur_block = &blocks[middle];
    for (int i = 0; i < n; ++i) {
      auto it = second_half_to_index.find(first_half(*cur_block));
      if (it == second_half_to_index.end()) break;
      int next = it->second;
      if (used.find(next) != used.end()) break;
      used.insert(next);
      cur_block = &blocks[next];
      if (i % 2 == 1) {
	res.push_back(blocks[next]);
      }
    }
    if (used.size() != n) continue; // Did not work.
    reverse(res.begin(), res.end());
    vector<int> flattened_res;
    for (const auto& b : res) {
      flattened_res.insert(flattened_res.end(), b.begin(), b.end());
    }
    flattened_res.insert(flattened_res.end(),
			 blocks[middle].begin(), blocks[middle].begin() + m / 2);
    ans = flattened_res;
  }
  assert(!ans.empty());
  return ans;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> blocks;
    for (int i = 0; i < n; ++i) {
      vector<int> b;
      for (int j = 0; j < m; ++j) {
	cin >> b.emplace_back();
      }
      blocks.push_back(b);
    }
    auto v = solve(blocks);
    for (int x : v) cout << x << " ";
    cout << endl;
  }
}
