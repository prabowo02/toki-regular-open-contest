// Range Tree + Dynamic Li Chao Tree
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL,LL> PLL;

#define sz(x) (int)(x).size()
#define pb push_back
#define fi first
#define se second
#define endl '\n'
const LL LINF = 4557430888798830399LL;

inline void fasterios(){
    //Do not use if interactive
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}

#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
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

template <class T>
struct LiChao_min
{
    const LL inf = LINF;
    struct line
    {
        T a, b;
        line() { a = 0; b = 0; }
        line(T _a, T _b) { a = _a; b = _b; }
        T eval(T x) { return a * x + (T)b; }
    };
 
    struct node
    {
        node *l, *r; line f;
 
        node() { f = line(); l = nullptr; r = nullptr; }
        node(T a, T b) { f = line(a, b); l = nullptr; r = nullptr; }
        node(line v) { f = v; l = nullptr; r = nullptr; }
    };
 
    typedef node* pnode;
 
    pnode root; T sz;
    // Initing sz too big can cause overflow!
    void init(T _sz) { sz = _sz + 1; root = nullptr; }
 
    void add_line(T a, T b) { line v = line(a, b); insert(v, -sz, sz, root); }
    T query(T x) { return query(x, -sz, sz, root); }
 
    void insert(line &v, T l, T r, pnode &nd)
    {
        if(!nd) { nd = new node(v); return; }
 
        T trl = nd->f.eval(l), trr = nd->f.eval(r);
        T vl = v.eval(l), vr = v.eval(r);

        if(trl <= vl && trr <= vr) return;
        if(trl > vl && trr > vr) { nd->f = v; return; }
 
        T mid = (T)(l+r)/2;

        if(trl > vl) swap(nd->f, v);
        if(nd->f.eval(mid) < v.eval(mid)) insert(v, mid + 1, r, nd->r);
        else swap(nd->f, v), insert(v, l, mid, nd->l);


        // if(trl >= vl && trr >= vr) return;
        // if(trl < vl && trr < vr) { nd->f = v; return; }
 
        // T mid = (l + r)/(T)(2);
        // if(trl < vl) swap(nd->f, v);
        // if(nd->f.eval(mid) > v.eval(mid)) insert(v, mid + 1, r, nd->r);
        // else swap(nd->f, v), insert(v, l, mid, nd->l);
    }
 
    T query(T x, T l, T r, pnode &nd)
    {
        if(!nd) return LINF;
        // if(!nd) return -inf;
        if(l == r) return nd->f.eval(x);
 
        T mid = (T)(l+r)/2;

        if(mid >= x) return min(nd->f.eval(x), query(x, l, mid, nd->l));
        return min(nd->f.eval(x), query(x, mid + 1, r, nd->r));

        // if(mid >= x) return max(nd->f.eval(x), query(x, l, mid, nd->l));
        // return max(nd->f.eval(x), query(x, mid + 1, r, nd->r));
    }
};

LiChao_min<LL> lines[1200005];

void update(LL kiri, LL kanan, LL idx, LL l, LL r, PLL tar){
    if(kiri > r || kanan < l) return;
    if(l <= kiri && kanan <= r){
        lines[idx].add_line(tar.fi, tar.se);
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

void update(int x, LL dist) {
    ans[x] = dist;
    // Only use stairs
    add(1, isi[x], isi[x]*s + dist, -s);
    add(isi[x], h, -isi[x]*s + dist, s);

    // Use lift
    add(lift[x].kiri, isi[x], isi[x]*lift[x].cost + lift[x].wait + dist, -lift[x].cost);
    add(isi[x], lift[x].kanan, -isi[x]*lift[x].cost + lift[x].wait + dist, lift[x].cost);

    // Use stairs after lift
    add(1, lift[x].kiri, lift[x].kiri*s + (isi[x]-lift[x].kiri)*lift[x].cost + lift[x].wait + dist, -s);
    add(lift[x].kanan, h, -lift[x].kanan*s + (lift[x].kanan-isi[x])*lift[x].cost + lift[x].wait + dist, s);
}


int main(){
    for(int i = 0;i <= 1200000;i++) lines[i].init(1000000000);

    fasterios(); cin >> h >> n;
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
        if(l == 0) ++r, update(r, query(isi[r]));
        else if(r+1 == n) --l, update(l, query(isi[l]));
        else{
            LL distL = query(isi[l-1]), distR = query(isi[r+1]);
            if(distL < distR) update(--l, distL);
            else update(++r, distR);
        }
    }

    for(int i = 0;i < n;i++) cout << ans[i] << endl;
    return 0;
}