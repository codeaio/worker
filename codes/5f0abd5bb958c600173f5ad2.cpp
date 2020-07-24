#include <bits/stdc++.h>
	
using namespace std;
 
#define int long long
 
#define PB	push_back
#define ALL(x)	(x).begin(), (x).end()
#define ALLR(x)	(x).rbegin(), (x).rend()
#define MP	make_pair
 
template <typename A, typename B>
string to_string(pair<A, B> p);
 
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);
 
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);
 
string to_string(const string& s) {
  return '"' + s + '"';
}
 
string to_string(const char* s) {
  return to_string((string) s);
}
 
string to_string(bool b) {
  return (b ? "true" : "false");
}
 
string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
 
template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}
 
template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
 
template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
 
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}
 
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}
 
void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#define LOCAL
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
 
#define FAST_IO ios::sync_with_stdio(false); cin.tie(0)
 
typedef pair<int, int> ii;
typedef pair<pair<int, int>, int> iii;
typedef vector<int> vi;
typedef vector<iii> viii;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef unsigned long long ull;
 
const int INF = LONG_LONG_MAX/2;
const int NINF = LONG_LONG_MIN/2;
const double PI = 3.141592653589793238;

const int N = 100009;
vi adj[N];
vector<double> val1;
vector<double> val2;
vi node_at_dist[N];
int a, b, n;
vi dist;

void dfs1(int v, int p) {
	node_at_dist[dist[v]].PB(v);
	for (int u: adj[v]) {
		if (u != p) {
			dist[u] = dist[v] + 1;
			dfs1(u, v);
		}
	}
	for (int x: node_at_dist[dist[v]+a]) {
		val1[v] += val1[x];
	}
}

void dfs2(int v, int p) {
	for (int u: adj[v]) {
		if (u != p) {
			dfs2(u, v);
		}
	}
	for (int x: node_at_dist[dist[v]+b]) {
		val2[v] += val2[x];
	}
}

int32_t main() {
	FAST_IO;
	
	int TC;
	cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {
		cin >> n >> a >> b;
		
		for (vi& v: adj) v.clear();
		for (vi& v: node_at_dist) v.clear();
		val1.clear();
		val2.clear();
		dist.clear();
		vi p(n+5);
		for (int i = 1; i < n; i++) {
			int x;
			cin >> x;
			
			p[i+1] = x;
			adj[i+1].PB(x);
			adj[x].PB(i+1);
		}
		
		val1.resize(n+1, 0);
		val2.resize(n+1, 0);
		dist.resize(n+1, 0);
		
		for (int i = 1; i <= n; i++) {
			val1[i] = 1.0/(double)n;
			val2[i] = 1.0/(double)n;
		}
		
		dfs1(1, 0);
		dfs2(1, 0);
		
		double ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += val1[i]*(1-val2[i]);
			ans += val2[i]*(1-val1[i]);
			ans += val1[i]*val2[i];
		}
		cout << "Case #" << tc << ": " << fixed << setprecision(10) << ans << endl;
	}
}
// g++ -Wall -Wextra -Wshadow -fsanitize=undefined -std=c++17
