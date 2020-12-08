#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
typedef vector<LL> vi;
typedef vector<vi> vvi;
typedef pair<LL, LL> PLL;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define pb push_back

const LL MAXN = 50000;
const LL BLOCK = 223;
LL ans[MAXN+5];
bool isi[MAXN+5];
LL segt[4*MAXN+5];
bool lazy[4*MAXN+5];
bool isHeavy[MAXN+5];
LL onSubtree[MAXN+5];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
gp_hash_table<LL, LL, custom_hash> dir[MAXN+5];

void build(LL kiri, LL kanan, LL idx, vi&arr);
void upd(LL kiri, LL kanan, LL idx, LL l, LL r);
LL get(LL kiri, LL kanan, LL idx, LL l, LL r);
    
struct HLD{
    int N, dfscnt = 0;
    vector <vi> edge;
    vi par, subsz, depth, head, fir, las, rev;
    vector <PLL> persHeavy;
    HLD() {};
    // persHeavy[i].fi = next persistent Heavy,
    // persHeavy[i].se = -1 is end, else list of heavy node, subsize > sqrt(N)
    HLD(vector<vi> &edge_) : N(sz(edge_)), edge(edge_), par(N,-1), subsz(N,1), depth(N), head(N, 1), fir(N), las(N), rev(N), persHeavy(N,{-1, 0}) {
        N--;
        dfsSz();
        dfsHeavy();
        dfsHld();
        assert(N == rev.size()-1);
        build(1, N, 1, rev);
        rep(pos, 1, N+1){
            if(isHeavy[pos]){
                onSubtree[pos] += isi[pos];
                // cout << pos << "Initially " << onSubtree[pos] << endl;
                trav(nx, edge[pos]){
                    LL curSubtree = 0;
                    for(int i = fir[nx];i <= las[nx];i++){
                        dir[pos][rev[i]] = nx;
                        curSubtree += isi[rev[i]];
                    }
                    ans[pos] += onSubtree[pos]*curSubtree;
                    onSubtree[pos] += curSubtree;
                }
                // cout << pos << " answer is " << ans[pos] << endl;
            }
        }
    }
    void dfsSz(int pos = 1){
        if(par[pos] != -1){
            // Buang parent
            edge[pos].erase(find(all(edge[pos]),par[pos]));
        }
        trav(nx, edge[pos]){
            par[nx] = pos; depth[nx] = depth[pos]+1;
            dfsSz(nx);
            subsz[pos] += subsz[nx];
            if(subsz[nx] > subsz[edge[pos][0]]) swap(nx, edge[pos][0]);
        }
    }
    void dfsHeavy(int pos = 1, int lst = 0){
        persHeavy[pos] = {-1, lst};
        if(sz(edge[pos]) > BLOCK){
            isHeavy[pos] = 1;
            lst = pos;
            persHeavy[pos].fi = pos;
        };
        trav(nx, edge[pos]) dfsHeavy(nx, lst);
    }
    void dfsHld(int pos = 1){
        fir[pos] = ++dfscnt;
        rev[dfscnt] = pos;
        trav(nx, edge[pos]){
            head[nx] = (nx == edge[pos][0] ? head[pos] : nx);
            dfsHld(nx);
        }
        las[pos] = dfscnt;
    }
    template<class T>
    void process(int pos, T op){
        for(;head[pos] != 1;pos = par[head[pos]]){
            // cout << head[pos] << " " << pos << endl;
            op(fir[head[pos]], fir[pos]);
            // cout << get(1, N, 1, fir[head[pos]], fir[pos]) << endl;
        }
        // cout << 1 << " " << pos << endl;
        // cout << get(1, N, 1, fir[1], fir[pos]) << endl;
        op(fir[1], fir[pos]);
    }

    void heavyUpdate(LL a, LL b, bool reduce){
        LL curSolo = get(1,N,1,fir[a],fir[a]);
        LL curNx = 0;
        if(a != b){
            LL nx = dir[a][b];
            // cout << a << " " << b << " " <<  nx << " " << fir[nx] << " sampai " << las[nx] << endl;
            curNx += get(1,N,1,fir[nx],las[nx]);
        }
        // cout << a << " " << b << " " << reduce << " " << onSubtree[a] << " " << curNx << " " << curSolo << endl;
        if(reduce){
            onSubtree[a] -= curSolo+curNx;
            ans[a] -= (curSolo*(onSubtree[a]+curNx));
            ans[a] -= onSubtree[a]*curNx;
        }else{
            ans[a] += curSolo*(onSubtree[a]+curNx);
            ans[a] += onSubtree[a]*curNx;
            onSubtree[a] += curSolo+curNx;
        }
        // cout << ans[a] << endl;

    }

    void update(int pos){

        LL cur = pos;
        while(cur){
            if(persHeavy[cur].fi != -1){
                // cout << "Updating " << persHeavy[cur].fi << " " << pos << endl;
                heavyUpdate(persHeavy[cur].fi, pos, 1);
            }
            cur = persHeavy[cur].se;
        }
        process(pos, [&](LL a, LL b){upd(1,N,1,a,b);});
        cur = pos;
        while(cur){
            if(persHeavy[cur].fi != -1){
                heavyUpdate(persHeavy[cur].fi, pos, 0);
            }
            cur = persHeavy[cur].se;
        }
    }

    void query(int pos){
        if(isHeavy[pos]) cout << ans[pos] << endl;
        else{
            // light query here
            LL curans = 0;
            LL curSubtree = get(1, N, 1, fir[pos], fir[pos]);
            // cout << curSubtree << endl;
            trav(nx, edge[pos]){
                LL tmp = get(1, N, 1, fir[nx], las[nx]);
                curans += tmp*curSubtree;
                curSubtree += tmp;
            }
            cout << curans << endl;
        }
    }
}solver;

void build(LL kiri, LL kanan, LL idx, vi &arr){
    if(kiri == kanan){
        segt[idx] = isi[arr[kiri]];
        return;
    }
    LL mid = (kiri+kanan)>>1;
    build(kiri, mid, idx*2, arr);
    build(mid+1, kanan, idx*2+1, arr);
    segt[idx] = segt[idx*2]+segt[idx*2+1];
    // assert(0 <= segt[idx] && segt[idx] <= (kanan-kiri+1));
}

void prop(LL kiri, LL kanan, LL idx){
    if(!lazy[idx]) return;
    assert(0 <= segt[idx] && segt[idx] <= (kanan-kiri+1));
    segt[idx] = (kanan-kiri+1)-segt[idx];
    if(kiri != kanan){
        lazy[idx*2] ^= 1;
        lazy[idx*2+1] ^= 1;
    }
    lazy[idx] = 0;
}

void upd(LL kiri, LL kanan, LL idx, LL l, LL r){
    // assert(l <= r);
    prop(kiri, kanan, idx);
    if(kiri > r || kanan < l) return;
    if(l <= kiri && kanan <= r){
        lazy[idx] ^= 1;
        prop(kiri, kanan, idx);
        return;
    }
    LL mid = (kiri+kanan)>>1;
    upd(kiri, mid, idx*2,l,r);
    upd(mid+1,kanan,idx*2+1,l,r);
    segt[idx] = segt[idx*2]+segt[idx*2+1];
    // assert(0 <= segt[idx] && segt[idx] <= (kanan-kiri+1));
}

LL get(LL kiri, LL kanan, LL idx, LL l, LL r){
    prop(kiri, kanan, idx);
    if(kiri > r || kanan < l) return 0;
    if(l <= kiri && kanan <= r) return segt[idx];
    LL mid = (kiri+kanan)>>1;
    return get(kiri, mid, idx*2, l, r)+get(mid+1, kanan, idx*2+1, l, r);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    LL n,q;
    cin >> n >> q;
    vvi edge(n+1);
    for(int i = 1;i <= n;i++) cin >> isi[i];
    for(int i = 1;i < n;i++){
        int u,v; cin >> u >> v;
        edge[u].pb(v);
        edge[v].pb(u);
    }
    solver = HLD(edge);
    while(q--){
        LL t,x; cin >> t >> x;
        if(t == 1) solver.update(x);
        else solver.query(x);
    }
    return 0;
}