#include <iostream>
#include <vector>
#include <cassert>
#include <climits>
#include <set>
#define ll long long
#define fst first
#define snd second

using namespace std;

// Line and LineContainer taken from KACTL Library - Modified to allow modification of all lines.

int MERGE_COUNT = 0;
int MAX_SIZE = 0;

struct Line 
{
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LC : multiset<Line, less<>> 
{
	static const ll inf = LLONG_MAX;
	ll addVal = 0;

	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		k = -k; m = -(m - addVal);
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return -(l.k * x + l.m) + addVal;
	}
};

int N, D[100001]; ll C;
vector<int> adj[100001];
ll A[100001], DP[100001];

LC* DFS(int u)
{
	ll sum = 0;
	LC* ret = nullptr;

	for (const auto &v : adj[u])
	{
		A[v] = A[u] + D[v];
		LC* tmp = DFS(v); 
		sum += DP[v]; tmp -> addVal -= DP[v];
		if (ret == nullptr || tmp -> size() > ret -> size()) swap(ret, tmp);
		if (tmp != nullptr) 
		{
			MERGE_COUNT += tmp -> size();
			for (const auto &x : *tmp) {ret -> add(-x.k, -x.m + tmp -> addVal);}
			delete tmp; 
		}
	}

	if (ret == nullptr) {ret = new LC();}
	ret -> add(-2 * A[u], A[u] * A[u] + C);
	ret -> addVal += sum;
	DP[u] = ret -> query(A[u]) + A[u] * A[u];
	MAX_SIZE = max(MAX_SIZE, (int)ret -> size());
	
	return ret;
}

int main()
{
	ios :: sync_with_stdio(0); cin.tie(0);
	cin >> N >> C;
	for (int i = 1; i < N; i++)
	{
		int p; cin >> p >> D[i];
		adj[p - 1].push_back(i);
	}
	DFS(0);
	cout << DP[0] << "\n";
	
	// Debug code, used for verifying testcases.
	cerr << "N = " << N << "\n";
	cerr << "Number of merges = " << MERGE_COUNT << " " << 1.0 * MERGE_COUNT / N << "\n";
	cerr << "Max size = " << MAX_SIZE << " " << 1.0 * MAX_SIZE / N << "\n";
	
	return 0;
}
