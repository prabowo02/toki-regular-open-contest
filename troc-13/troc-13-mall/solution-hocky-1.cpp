// Range Tree + Line Container
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
typedef long long ll;
typedef pair<LL,LL> PLL;
#define fi first
#define se second
#define pb push_back
const LL LINF = 4557430888798830399LL;

#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
inline void fasterios(){
    //Do not use if interactive
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
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

gp_hash_table<LL, LL, custom_hash> comp;
vector <LL> all;

struct Lift{
    LL kiri, kanan, cost, wait;
}lift[100005];

LL h,n,s,curn;
LL isi[100005], ans[100005];

bool Q;
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const {
        return Q ? p < o.p : k > o.k;
    }
};
 
struct LineContainer : multiset<Line> {
    const ll inf = LINF;
    ll div(ll a, ll b) { 
        return a / b - ((a ^ b) < 0 && a % b); 
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? -inf : inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        if(empty()) return LINF;
        assert(!empty());
        Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
        return l.k * x + l.m;
    }
};


struct RangeTree{
    vector <LineContainer> lines;
    RangeTree(): lines(1200005){}
    void update(LL kiri, LL kanan, LL idx, LL l, LL r, PLL tar){
        if(kiri > r || kanan < l) return;
        if(l <= kiri && kanan <= r){
            lines[idx].add(tar.fi, tar.se);
            return;
        }
        LL mid = (kiri+kanan)>>1;
        update(kiri, mid, idx*2+1, l, r, tar);
        update(mid+1, kanan, idx*2+2, l, r, tar);
    }
    LL query(LL kiri, LL kanan, LL idx, LL tar){
        if(kiri > tar || kanan < tar) return LINF;
        LL curans = lines[idx].query(all[tar]);
        if(kiri == kanan) return curans;
        LL mid = (kiri + kanan)>>1;
        return min(curans,min(query(kiri,mid,idx*2+1,tar), query(mid+1,kanan,idx*2+2,tar)));
    }
    void add(LL l, LL r, LL c, LL m){
        l = comp[l]; r = comp[r];
        update(0,curn-1,0,l,r,{m, c});
    }
    LL query(LL x){
        x = comp[x];
        return query(0,curn-1,0,x);
    }
} rtree;

void update(int x, LL dist) {
    ans[x] = dist;
    // Only use stairs
    rtree.add(1, isi[x], isi[x]*s + dist, -s);
    rtree.add(isi[x], h, -isi[x]*s + dist, s);

    // Use lift
    rtree.add(lift[x].kiri, isi[x], isi[x]*lift[x].cost + lift[x].wait + dist, -lift[x].cost);
    rtree.add(isi[x], lift[x].kanan, -isi[x]*lift[x].cost + lift[x].wait + dist, lift[x].cost);

    // Use stairs after lift
    rtree.add(1, lift[x].kiri, lift[x].kiri*s + (isi[x]-lift[x].kiri)*lift[x].cost + lift[x].wait + dist, -s);
    rtree.add(lift[x].kanan, h, -lift[x].kanan*s + (lift[x].kanan-isi[x])*lift[x].cost + lift[x].wait + dist, s);
}


int main(){
    fasterios();
    cin >> h >> n;
    for(int i = 0;i < n;i++) cin >> isi[i];
    cin >> s;
    all.pb(1); all.pb(h);
    for(int i = 0;i < n;i++){
        cin >> lift[i].kiri >> lift[i].kanan >> lift[i].cost >> lift[i].wait;
        all.pb(isi[i]), all.pb(lift[i].kiri), all.pb(lift[i].kanan);
    }
    sort(all.begin(),all.end());
    all.erase(unique(all.begin(),all.end()),all.end());

    for(int i = 0;i < sz(all);i++) comp[all[i]] = i;

    curn = sz(all);
    LL x; cin >> x; --x;
    LL l,r; l = r = x;
    update(x, 0LL);

    while(l > 0 || r+1 < n){
        if(l == 0) ++r, update(r, rtree.query(isi[r]));
        else if(r+1 == n) --l, update(l, rtree.query(isi[l]));
        else{
            LL distL = rtree.query(isi[l-1]), distR = rtree.query(isi[r+1]);
            if(distL < distR) update(--l, distL);
            else update(++r, distR);
        }
    }

    for(int i = 0;i < n;i++){
        cout << ans[i] << endl;
    }
    return 0;
}
