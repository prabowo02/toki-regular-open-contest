#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back

int isi[100005];
int dirpar[100005];

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



struct LCA {
    int T = 0;
    vi time, path, ret, depth, las;
    RMQ<int> rmq;

    LCA(vector<vi>& C, int root) : time(sz(C)), rmq((dfs(C,root,-1), ret)), depth(sz(C)), las(sz(C)){}
    void dfs(vector<vi>& C, int v, int par) {
        dirpar[v] = par;
        time[v] = T++;
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,q;
    cin >> n >> q;
    vvi edge(n+1);
    for(int i = 1;i <= n;i++) cin >> isi[i];
    for(int i = 1;i < n;i++){
        int u,v; cin >> u >> v;
        edge[u].pb(v);
        edge[v].pb(u);
    }
    LCA solver(edge, 1);
    while(q--){
        int o, x; cin >> o >> x;
        if(o == 1){
            while(x != -1){
                isi[x] = !isi[x];
                x = dirpar[x];
            }
        }else{
            int ans = 0;
            for(int i = 1;i <= n;i++){
                for(int j = i+1;j <= n;j++){
                    if(isi[i] && isi[j] && solver.lca(i,j) == x) ans++;
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
