/*
Author : Hocky Yudhiono
5/20/2020 1:09:19 PM

1. You can sort the query if offline!
2. Don't bring the dp remaining state when dfsing on DP on Tree.
3. Try to reverse (Think from the back) if you stuck.
4. Be careful when submitting Div. 2 D-F, dont waste it on stupid WAs.
5. Try to reduce a problem
*/

#include <algorithm>
#include <iostream>
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

//If the time limit is strict, try not to use long double

//Remember to undefine if the problem is interactive
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
    //Do not use if interactive
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}



const LL logN = 19;
const LL maxN = 300015;
LL n,q;
LL depth[maxN];
vector <LL> edge[maxN]; 
vector <PLL> newedge[maxN];
LL sparset[maxN][logN+3];

void dfs(LL pos, LL par){
    for(int i = 0;i < edge[pos].size();i++){
        LL nx = edge[pos][i];
        if(par == nx) continue;
        depth[nx] = depth[pos]+1;
        sparset[nx][0] = pos;
        dfs(nx,pos);
    }
    return;
}

LL lca(LL a, LL b){
    if(depth[a] > depth[b]) swap(a,b);
    for(int i = logN;i >= 0;i--){
        if(depth[b]-(1LL<<i) < depth[a]) continue;
        b = sparset[b][i];
    }
    if(a == b) return a;
    for(int i = logN;i >= 0;i--){
        if(sparset[a][i] == sparset[b][i]) continue;
        a = sparset[a][i];
        b = sparset[b][i];
    }
    return sparset[a][0];
}

LL dist(LL a, LL b){
    LL curlca = lca(a,b);
    return depth[a]+depth[b]-2*depth[curlca];
}

struct dt{
    LL pos,step;
    bool operator<(const dt &other)const{
        return step > other.step;
    }
};
LL distDijk[maxN],ed;
priority_queue <dt> antri;
void dijk(dt now){
    if(now.step > distDijk[now.pos]) return;
    if(now.pos == ed){
        while(!antri.empty()) antri.pop();
    }
    trav(nx,newedge[now.pos]){
        if(distDijk[nx.fi] <= now.step+nx.se) continue;
        distDijk[nx.fi] = now.step+nx.se;
        antri.push({nx.fi,distDijk[nx.fi]});
    }
}

int main(){
    fasterios();
    cin >> n >> q;
    for(int i = 1;i < n;i++){
        int u,v; cin >> u >> v;
        edge[u].pb(v);
        edge[v].pb(u);
    }
    // cout << "Here " << endl;
    while(q--){
        LL a,b,r; cin >> a >> b >> r; ed = b;
        memset(sparset,-1,sizeof(sparset));
        dfs(r,-1);
        for(int i = 0;i < logN;i++){
            for(int j = 1;j <= n;j++){
                if(sparset[j][i] == -1) continue;
                sparset[j][i+1] = sparset[sparset[j][i]][i];
            }
        }
        for(int i = 1;i <= n;i++){
            newedge[i].clear();
            trav(now,edge[i]) newedge[i].pb({now,1});
        }
        for(int i = 1;i <= n;i++){
            for(int j = i+1;j <= n;j++){
                LL curlca = lca(i,j);
                LL w = dist(curlca,r);
                if(curlca != i && curlca != j){
                    newedge[i].pb({j,w});
                    newedge[j].pb({i,w});
                }
            }
        }
        // for(int i = 1;i <= n;i++){
        //     trav(now,newedge[i]){
        //         cout << i << " to " << now.fi << " with weight " << now.se << endl;
        //     }
        // }
        memset(distDijk,INFMEM,sizeof(distDijk));
        distDijk[a] = 0;
        antri.push({a,0});
        while(!antri.empty()){
            dt tmp = antri.top();
            antri.pop();
            dijk(tmp);
        }
        // cout << a << " " << b << " " << r << " Answer is " << distDijk[b] << endl;
        cout << distDijk[b] << endl;
    }
    return 0;
}
