#include<bits/stdc++.h>


#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define pf push_front
#define pb2 pop_back
#define pf2 pop_front
#define line printf("\n")
#define pq priority_queue
#define rep(k,i,j) for(int k = (int)i;k<(int)j;k++)
#define repd(k,i,j) for(int k = (int)i;k>=(int)j;k--)
#define ll long long
#define ALL(a) a.begin(),a.end()
#define vi vector<int>

using namespace std;

double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);
int dirx[8] = {-1,0,0,1,-1,-1,1,1};
int diry[8] = {0,1,-1,0,-1,1,-1,1};

clock_t first_attempt = clock();
inline void cek_time(){
	clock_t cur = clock()- first_attempt;
	cerr<<"TIME : "<<(double) cur/CLOCKS_PER_SEC<<endl;
}
inline void OPEN (string s) {
	freopen ((s + ".in").c_str (), "r", stdin);
	freopen ((s + ".out").c_str (), "w", stdout);
}

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> bbst;
//find_by_order(idx) : i-th index 
//order_of_key(val)  : val has which index

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
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

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

//end of template

/*
Diberikan graph dengan N node dan M edge. 
Node ke-i punya value V_i. 
Weight dari suatu path adalah gcd dari value dari semua node di path tersebut.
Diberikan Q query, 
- A_i B_i : weight maksimum path dari Ai ke Bi

Batasan
- 1 <= N, M, V_i <= 100,000
- 1 <= A_i, B_i <= N
*/

const int maxn = 1e5 + 5;
int N, M;
int W[maxn];
vector<pii> edges[maxn];
int Q;
int A[maxn], B[maxn];

vi faktor[maxn];
vi cek[maxn];

int flag[maxn];
int par[maxn], lvl[maxn], day = 1;
int rt(int a) { 
	if (flag[a] != day) par[a] = a, flag[a] = day;
	if (par[a] == a) return a;
	return par[a] = rt(par[a]); 
}

void join(int a, int b) {
	a = rt(a), b = rt(b);
	if (a != b) {
		if (lvl[a] > lvl[b]) swap(a, b);
		par[a] = b;
		lvl[b] += lvl[a];
	}
}

void reset() {
	day++;
}

int ans[maxn];

int main() {
	rep(i, 1, maxn) {
		for (int k = i; k < maxn; k+= i)
			faktor[k].pb(i);
	}
	
	cin >> N >> M;
	rep(i, 1, N + 1) 
		scanf("%d", &W[i]);
		
	rep(k, 0, M) {
		int u, v;
		scanf("%d%d", &u, &v);
        int w = __gcd(W[u], W[v]);
        for (int x : faktor[w])
		    edges[x].pb({u, v});
	}
	
	cin >> Q;
	rep(k, 0, Q) {
		scanf("%d%d", &A[k], &B[k]);
		for (auto x : faktor[__gcd(W[A[k]], W[B[k]])])
			cek[x].pb(k);
	}
	
	iota(par, par + maxn, 0);
	rep(w, 1, maxn) {
		for (auto e : edges[w]) 
			join(e.fi, e.se);
			
		for (auto x : cek[w]) {
			if (rt(A[x]) == rt(B[x]))
				ans[x] = w;
		}
		reset();
	}
	
	rep(k, 0, Q)
		printf("%d\n", ans[k]);
}
