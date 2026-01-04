#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
  int _n;
  cin >> _n;
  vector<pair<int, int>> missions;
  const int k = 63;
  int n = k*k*k;
  
  for (int size = 1; size <= 250000; size *= k) {
    for (int offset = 0; offset + 1 < k; offset++) {
      for (int start = n / size - k + 1; start >= 0; start -= k) {
        missions.push_back({size *  (start + offset), size});
      }    
    }
  }
  // These missions are useless, so they should not make the checker
  // refuse the solution.
  missions.push_back({100000, 5});
  missions.push_back({1000, 1});
  missions.push_back({100, 1});
  missions.push_back({10, 1});
  missions.push_back({1, 5});
  
  cout << missions.size() << endl;
  for (auto m : missions) cout << m.first << " " << m.second << "\n";
}
