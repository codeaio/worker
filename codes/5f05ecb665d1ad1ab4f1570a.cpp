#include <iostream>
#include <vector>

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& x: a) cin >> x;
  
  int sum = 0;
  for (int x: a) sum += x;
  cout << sum << endl;
}