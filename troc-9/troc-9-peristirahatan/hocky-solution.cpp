#include <algorithm>
#include <iostream>

using namespace std;
typedef long long LL;
#define endl '\n'
const LL LINF = 4557430888798830399LL;

struct dt{
    LL mini,maksi;
};
dt segt[2][400005];

LL n,q;
LL isi[400005];
LL lazy[400005];

dt fix(dt &a, dt &b){
    return {min(a.mini,b.mini),max(a.maksi,b.maksi)};
}

void prop(LL kiri, LL kanan,LL idx){
    if(lazy[idx] == 0) return;
    segt[0][idx].mini += lazy[idx];
    segt[0][idx].maksi += lazy[idx];
    segt[1][idx].mini += lazy[idx];
    segt[1][idx].maksi += lazy[idx];
    if(kiri != kanan){
        lazy[idx*2] += lazy[idx];
        lazy[idx*2+1] += lazy[idx];
    }
    lazy[idx] = 0;
}

void build(LL kiri, LL kanan, LL idx){
    if(kiri == kanan){
        segt[0][idx] = {isi[kiri]+n-kiri+1,isi[kiri]+n-kiri+1};
        segt[1][idx] = {isi[kiri]+kiri,isi[kiri]+kiri};
        return;
    }
    LL mid = (kiri+kanan)>>1;
    build(kiri,mid,idx*2);
    build(mid+1,kanan,idx*2+1);
    segt[0][idx] = fix(segt[0][idx*2],segt[0][idx*2+1]);
    segt[1][idx] = fix(segt[1][idx*2],segt[1][idx*2+1]);
}

void upd(LL kiri, LL kanan, LL idx, LL l, LL r, LL val){
    prop(kiri,kanan,idx);
    if(kiri > r || kanan < l) return;
    if(l <= kiri && kanan <= r){
        lazy[idx] += val;
        prop(kiri,kanan,idx);
        return;
    }
    LL mid = (kiri+kanan)>>1;
    upd(kiri,mid,idx*2,l,r,val);
    upd(mid+1,kanan,idx*2+1,l,r,val);
    segt[0][idx] = fix(segt[0][idx*2],segt[0][idx*2+1]);
    segt[1][idx] = fix(segt[1][idx*2],segt[1][idx*2+1]);
}

dt get(LL kiri, LL kanan, LL idx,LL l, LL r,bool tipe){
    prop(kiri,kanan,idx);
    if(kiri > r || kanan < l) return {LINF,-LINF};
    if(l <= kiri && kanan <= r) return segt[tipe][idx];
    LL mid = (kiri+kanan)>>1;
    dt lchild = get(kiri,mid,idx*2,l,r,tipe);
    dt rchild = get(mid+1,kanan,idx*2+1,l,r,tipe);
    return fix(lchild,rchild);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for(int i = 1;i <= n;i++){
        cin >> isi[i];
    }
    build(1,n,1);
    while(q--){
        LL t,l,r,k; cin >> t >> l >> r >> k;
        if(t == 1){
            upd(1,n,1,l,r,k);
        }else{
            dt ans = {LINF,-LINF};
            //Get yang di sebelah kiri k
            LL kiri = l;
            LL kanan = min(k,r);
            dt tmp = get(1,n,1,kiri,kanan,0);
            tmp.mini -= (n-k+1); tmp.maksi -= (n-k+1);
            ans = fix(ans,tmp);

            //Get yang di sebelah kanan k
            kiri = max(k,l);
            kanan = r;
            tmp = get(1,n,1,kiri,kanan,1);
            tmp.mini -= k; tmp.maksi -= k;
            ans = fix(ans,tmp);

            cout << ans.maksi-ans.mini << endl;
        }
    }
    return 0;
}