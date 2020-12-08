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
    //Do not use if interactive
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
        dirpar[v] = par;
        // cout << v << " has par " << dirpar[v] << endl;
        depth[v] = (par == -1 ? 0 : depth[par]+1);
        time[v] = T++;
        // Buang parent
        for(int i = 0;i < sz(C[v]);i++){
            if(C[v][i] == par) swap(C[v][i],C[v].back());
            int y = C[v][i]; if(y == par) continue;
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
        if(sz(C[v]) && C[v].back() == par) C[v].pop_back();
        las[v] = T-1;
        // cout << v << "'s preorder : " << time[v] << " " << las[v] << endl;
    }

    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    int dist(int a, int b){return (a == b ? 0 : depth[a] + depth[b] - 2*depth[lca(a,b)]);}
    bool isPar(int a, int b){
        // cout << "is par " << a << " of " << b << " : " << time[a] << " " << time[b] << " " << las[a] << endl;
        return (time[a] <= time[b] && time[b] <= las[a]);
    }
    int getDir(vector<vi>& C, int a, int b){
        // cout << a << " " << b << " " << time[a] << " " << time[b] << endl;
        if(!isPar(a,b)) return -1;
        int kiri = 0; int kanan = sz(C[a])-1;
        // cout << kiri << " " << kanan << endl;
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
    // Root jangan punya satu anak doang deh :"
    for(int i = 1;i <= n;i++){
        if(sz(edge[i]) == 1) root = i;
        if(sz(edge[i]) > 2){
            root = i, isChain = 0;
            break;
        }
    }
    LCA solver(edge,root);
    // cout << "isChain " << isChain << endl;
    // cout << "LCA computed " << root << endl;
    if(!isChain){
        for(int i = 1;i <= n;i++){
            if(!sz(edge[i])){
                // cout << "Computing " << i << endl;
                // Spoiled node here
                int pos = i; int dist = 0;
                while((sz(edge[pos])+(dirpar[pos] != -1)) < 3){
                    dist++;
                    chainIdx[pos] = i;
                    pos = dirpar[pos];
                    // cout << pos << endl;
                }
                head[i] = {pos,dist};
                // cout << "Retard head of " << i << " is " << head[i].fi << " with distance " << head[i].se << endl;
            }
        }
    }
    // return 0;
    while(q--){
        int a,b,r; cin >> a >> b >> r;
        // cout << a << " " << b << " " << r << " Answer is ";
        if(a == b){
            cout << 0 << endl;
            continue;
        }else if((sz(edge[r])+(dirpar[r] != -1)) > 1){
            // MVP
            cout << (a == r || b == r) << endl;
            continue;
        }else{
            // Retarded Node
            int ans = solver.dist(a,b);
            if(isChain){
                cout << ans << endl;
                continue;
            }
            chainIdx[head[r].fi] = r;
            bool isA = (chainIdx[a] == r);
            bool isB = (chainIdx[b] == r);
            // cout << "Computing " << a << " " << b << endl;
            // cout << "is stupid a: " << isA << endl;
            // cout << "is stupid b: " << isB << endl;
            // cout << "Temporary answer " << ans << endl;
            if(isA && isB){
            }else if(isA || isB){
                // One in retarded chain, you can use terma-jump
                // cout << "Where to jump " << solver.dist(head[r].fi,(isA ? a : b)) << endl;
                ans = min(ans,head[r].se+1+solver.dist(head[r].fi,(isA ? a : b)));
            }else{
                // cout << "Retard head is " << head[r].fi << endl;
                // Check whether this node is in separate subtree, if yes then one terma jump, else 2 terma jump
                // cout << "Direction of a " << solver.getDir(edge,head[r].fi,a) << endl;
                // cout << "Direction of b " << solver.getDir(edge,head[r].fi,b) << endl;
                // cout << "Direction of Root " << solver.getDir(edge,head[r].fi,39) << endl;
                if(solver.getDir(edge,head[r].fi,a) != solver.getDir(edge,head[r].fi,b)){
                    ans = min(ans, head[r].se);
                }else{
                    // Cari suatu node c, dimana c -> head[r].fi, c -> a, c -> b, beda dir semua
                    ans = min(ans, 2*head[r].se);
                    ans = min(ans, head[r].se + solver.dist(head[r].fi, a) + 1);
                    ans = min(ans, head[r].se + solver.dist(head[r].fi, b) + 1);
                    {
                        int c = solver.lca(a,b);
                        // cout << "Current LCA a, b " << c << endl;
                        if(c != a && c != b && c != head[r].fi){
                            vi dir = {solver.getDir(edge,c,a),solver.getDir(edge,c,b),solver.getDir(edge,c,head[r].fi)};
                            if(dir[0] != dir[1] && dir[1] != dir[2] && dir[0] != dir[2]){
                                ans = min(ans, solver.dist(r, c));
                            }
                        }
                    }
                    {
                        int c = solver.lca(a,head[r].fi);
                        // cout << "Current LCA a, retard head " << c << endl;
                        if(c != a && c != b && c != head[r].fi){
                            vi dir = {solver.getDir(edge,c,a),solver.getDir(edge,c,b),solver.getDir(edge,c,head[r].fi)};
                            if(dir[0] != dir[1] && dir[1] != dir[2] && dir[0] != dir[2]){
                                ans = min(ans, solver.dist(r, c));
                            }
                        }
                    }
                    {
                        int c = solver.lca(b,head[r].fi);
                        // cout << "Current LCA b, retard head " << c << endl;
                        if(c != a && c != b && c != head[r].fi){
                            vi dir = {solver.getDir(edge,c,a),solver.getDir(edge,c,b),solver.getDir(edge,c,head[r].fi)};
                            if(dir[0] != dir[1] && dir[1] != dir[2] && dir[0] != dir[2]){
                                ans = min(ans, solver.dist(r, c));
                            }
                        }
                    }
                }
            }
            // cout << a << " " << b << " " << r << " Answer is " << ans << endl;
            cout << ans << endl;
        }
    }
    return 0;
}