/*
Author : Hocky Yudhiono
5/20/2020 12:48:08 AM
*/
#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <tuple>
using namespace std;

typedef pair<int,int> PII;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define pb push_back
#define fi first
#define se second
#define endl '\n'

inline void fasterios(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,0,sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

vector <int> dirpar;
struct LCA {
    int T = 0;
    vi time, path, ret, depth, las;
    RMQ<int> rmq;

    LCA(vector<vi>& C, int root, bool preOrder = 0) : time(sz(C)), rmq((dfs(C,root,-1), ret)), depth(sz(C)), las(sz(C)){}
    void dfs(vector<vi>& C, int v, int par) {
        dirpar[v] = par; time[v] = T++;
        depth[v] = (par == -1 ? 0 : depth[par]+1);
        for(int i = 0;i < sz(C[v]);i++){
            if(C[v][i] == par) swap(C[v][i],C[v].back());
            int y = C[v][i]; if(y == par) continue;
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
        if(sz(C[v]) && C[v].back() == par) C[v].pop_back();
        las[v] = T-1;
    }
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    int lca(int a, int b, int c){
        vector <int> lcas = {lca(a,b),lca(b,c),lca(a,c)};
        return *max_element(lcas.begin(), lcas.end(), [&](int x, int y){ return depth[x] < depth[y];});
    }
    int dist(int a, int b){return (a == b ? 0 : depth[a] + depth[b] - 2*depth[lca(a,b)]);}
    bool isPar(int a, int b){ return (time[a] <= time[b] && time[b] <= las[a]);}
    int getDir(vector<vi>& C, int a, int b){
        if(!isPar(a,b)) return -1;
        int kiri = 0; int kanan = sz(C[a])-1;
        while(kiri < kanan){
            int mid = (kiri+kanan+1)>>1;
            int nx = C[a][mid];
            if(time[b] < time[nx]) kanan = mid-1;
            else kiri = mid;
        }
        return kiri;
    }
};

int main(){
    fasterios();
    int n,q; cin >> n >> q;
    vector <vi> edge(n+1); dirpar.resize(n+1); vector <PII> head(n+1); vi chainIdx(n+1);
    for(int i = 1;i < n;i++){
        int u,v; cin >> u >> v;
        edge[u].pb(v);
        edge[v].pb(u);
    }
    int root = 1;
    bool isChain = 1;
    for(int i = 1;i <= n;i++){
        if(sz(edge[i]) == 1) root = i;
        if(sz(edge[i]) > 2){ root = i, isChain = 0; break; }
    }
    LCA solver(edge,root);
    if(!isChain){
        for(int i = 1;i <= n;i++){
            if(!sz(edge[i])){
                int pos = i;
                while((sz(edge[pos])+(dirpar[pos] != -1)) < 3){
                    head[i].se++;
                    chainIdx[pos] = i;
                    pos = dirpar[pos];
                }
                head[i].fi = pos;
            }
        }
    }
    while(q--){
        int a,b,r; cin >> a >> b >> r;
        if(a == b){
            cout << 0 << endl;
            continue;
        }else if((sz(edge[r])+(dirpar[r] != -1)) > 1){
            cout << (a == r || b == r) << endl;
            continue;
        }else{
            int ans = solver.dist(a,b);
            if(isChain){
                cout << ans << endl;
                continue;
            }
            chainIdx[head[r].fi] = r;
            bool isA = (chainIdx[a] == r);
            bool isB = (chainIdx[b] == r);
            if(isA || isB){
                ans = min(ans,head[r].se+1+solver.dist(head[r].fi,(isA ? a : b)));
            }else if(solver.getDir(edge,head[r].fi,a) != solver.getDir(edge,head[r].fi,b)){
                ans = min(ans, head[r].se);
            }else{
                ans = min(ans, 2*head[r].se);
                ans = min(ans, head[r].se + solver.dist(head[r].fi, a) + 1);
                ans = min(ans, head[r].se + solver.dist(head[r].fi, b) + 1);
                int c = solver.lca(a,b,head[r].fi);
                if(c != a && c != b) ans = min(ans, solver.dist(c, r));
            }
            cout << ans << endl;
        }
    }
    return 0;
}