#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
  int _n;
  cin >> _n;
  vector<pair<int, int>> missions;
  const int k = 63;
  const int n = k*k*k;
  
  for (int size = 1; size <= 250000; size *= k) {
    for (int offset = 0; offset + 1 < k; offset++) {
      for (int start = n / size - k + 1; start >= 0; start -= k) {
        missions.push_back({size *  (start + offset), size});
      }    
    }
  }
  cout << missions.size() << endl;
  for (auto m : missions) cout << m.first << " " << m.second << "\n";
}
