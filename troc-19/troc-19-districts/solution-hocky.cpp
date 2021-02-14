/*
Author : Hocky Yudhiono
1/27/2021 10:02:11 AM

1. You can sort the query if offline!
2. Don't bring the dp remaining state when dfsing on DP on Tree.
3. Try to reverse (Think from the back) if you stuck.
4. Be careful when submitting Div. 2 D-F, dont waste it on stupid WAs.
5. Try to reduce a problem, think of it when you're making subtasks
   like when problemsetting.
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <limits>
#include <string>
#include <vector>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

typedef long long LL;
typedef long long ll;
typedef long double LD;
typedef vector<int> vi;
typedef pair<LL,LL> PLL;
typedef pair<LL,int> PLI;
typedef pair<int,int> PII;
typedef pair<int,int> pii;
typedef vector<vector<LL>> VVL;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define popf pop_front
#define pf push_front
#define popb pop_back
#define mp make_pair
#define pb push_back
#define remove erase
#define fi first
#define se second

// If the time limit is strict, try not to use long double

// Remember to undefine if the problem is interactive
#define endl '\n'
#define DEBUG(X) cout << ">>> DEBUG(" << __LINE__ << ") " << #X << " = " << (X) << endl

const double EPS = 1e-9;
const int INFMEM = 63;
const int INF = 1061109567;
const LL LINF = 4557430888798830399LL;
const double DINF = numeric_limits<double>::infinity();
const LL MOD = 1000000007;
const int dx[8] = {0,0,1,-1,1,-1,1,-1};
const int dy[8] = {1,-1,0,0,1,-1,-1,1};
// Do dir^1 to get reverse direction
const char dch[4] = {'R','L','D','U'};
// const string ds[8] = {"E","W","S","N","SE","NW","SW","NE"};
const double PI = 3.141592653589793;

inline void open(string a){
    freopen((a+".in").c_str(),"r",stdin);
    freopen((a+".out").c_str(),"w",stdout);
}

inline void fasterios(){
    // Do not use if interactive
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // cout << fixed << setprecision(10);
}

struct dt{
    int a,b,c,d;
    LL area;
} isi[100005];
vector <int> bucket[2][1000005];
struct edge{
    int u,v;
    LL c;
    bool operator<(const edge &other)const{
        return c < other.c;
    }
};
vector <edge> edges;

bool cmpx(int a, int b){
    return isi[a].b < isi[b].b;
}

bool cmpy(int a, int b){
    return isi[a].a < isi[b].a;
}

bool isOverlapping(int a, int b, bool x){
    if(x){
        if(isi[a].d <= isi[b].b || isi[b].d <= isi[a].b) return 0;
        return 1;
    }else{
        if(isi[a].c <= isi[b].a || isi[b].c <= isi[a].a) return 0;
        return 1;
    }
}

void make_edge(int a, int b){
    // cout << a << " " << b << " " << isi[a].area-isi[b].area << endl;
    edges.pb({a, b, abs(isi[a].area-isi[b].area)});
}

struct UF {
    vi e;
    UF(int n) : e(n+1, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main(){
    fasterios();
    int n; cin >> n;
    UF solve(n);
    for(int i = 1;i <= n;i++){
        cin >> isi[i].a >> isi[i].b >> isi[i].c >> isi[i].d;
        isi[i].area = (LL)(isi[i].d-isi[i].b) * (isi[i].c-isi[i].a);
        bucket[0][isi[i].a].pb(i);
        bucket[1][isi[i].c].pb(i);
    }
    for(int i = 1;i <= 1000000;i++){
        sort(all(bucket[0][i]), cmpx);
        sort(all(bucket[1][i]), cmpx);
        int asz = sz(bucket[0][i]);
        int bsz = sz(bucket[1][i]);
        int ptra = 0;
        int ptrb = 0;
        while(ptra < asz && ptrb < bsz){
            int a = bucket[0][i][ptra];
            int b = bucket[1][i][ptrb];
            if(isOverlapping(a, b, 1)) make_edge(a, b);
            if(isi[a].d < isi[b].d) ptra++;
            else ptrb++;
        }
        bucket[0][i].clear();
        bucket[1][i].clear();
    }

    for(int i = 1;i <= n;i++){
        bucket[0][isi[i].b].pb(i);
        bucket[1][isi[i].d].pb(i);
    }

    for(int i = 1;i <= 1000000;i++){
        sort(all(bucket[0][i]), cmpy);
        sort(all(bucket[1][i]), cmpy);
        int asz = sz(bucket[0][i]);
        int bsz = sz(bucket[1][i]);
        int ptra = 0;
        int ptrb = 0;
        while(ptra < asz && ptrb < bsz){
            int a = bucket[0][i][ptra];
            int b = bucket[1][i][ptrb];
            if(isOverlapping(a, b, 0)) make_edge(a, b);
            if(isi[a].c < isi[b].c) ptra++;
            else ptrb++;
        }
    }

    int edge_count = 0;
    LL ans = 0;

    sort(all(edges));

    trav(cur, edges){
        if(edge_count == n-2) break;
        if(solve.sameSet(cur.u, cur.v)) continue;
        edge_count++;
        solve.join(cur.u, cur.v);
        ans += cur.c;
    }
    if(edge_count != n-2) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}
