#include <iostream>

using namespace std;

const int N = 100;
long long a[N];

int main() {
	for (int i = 0; i < N; i++) {
      a[i] = i;
      cout << a[i] << endl;
    }
}