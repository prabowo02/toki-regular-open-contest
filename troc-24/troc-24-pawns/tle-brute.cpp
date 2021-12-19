#include <bits/stdc++.h> 
using namespace std;

template <class T>
inline bool mnto(T& a, T b) {return a > b ? a = b, 1 : 0;}
template <class T>
inline bool mxto(T& a, T b) {return a < b ? a = b, 1: 0;}
#define REP(i, s, e) for (int i = s; i < e; i++)
#define RREP(i, s, e) for (int i = s; i >= e; i--)
typedef long long ll;
typedef long double ld;
#define MP make_pair
#define FI first
#define SE second
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define MT make_tuple
typedef tuple<int, int, int> iii;
#define ALL(_a) _a.begin(), _a.end()
#define pb push_back
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

#ifdef DEBUG
#define debug(args...) printf(args)
#else
#define debug(args...)
#endif

#define INF 1000000005
#define LINF 1000000000000000005
#define MOD 1000000007
#define MAXN 200005

int t;
int n, m;
vi state;

set<vi> st;
void dfs(vi state) {
	if (st.find(state) != st.end()) return;
	REP (i, 0, m) {
		debug("%d ", state[i]);
	}
	debug("\n");
	st.insert(state);
	vi nstate = state;
	reverse(ALL(nstate));
	dfs(nstate);
	vi pos;
	REP (i, 0, m) {
		if (state[i] == 1) {
			pos.pb(i);
		}
	}
	assert(pos.size() == n);
	REP (i, 0, n - 2) {
		nstate = state;
		if (pos[i + 2] + 1 >= m) break;
		nstate[pos[i]]--;
		int p = pos[i + 2] + 1;
		nstate[p]++;
		while (nstate[p] >= 2) {
			nstate[p]--;
			p--;
			nstate[p]++;
		}
		dfs(nstate);
	}
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		state.clear();
		state.resize(m, 0);
		REP (i, 0, n) {
			state[i] = 1;
		}
		st.clear();
		dfs(state);
		printf("%d\n", (int) st.size());
	}
	return 0;
}
