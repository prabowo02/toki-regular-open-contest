/*
Author : Hocky Yudhiono
1/15/2020 9:33:07 AM
*/

#include <iostream>
#include <queue>
using namespace std;

typedef long long LL;
typedef pair<LL,LL> PLL;
#define pb push_back
#define fi first
#define se second
#define endl '\n'
const LL MOD = 1000000007LL;
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
gp_hash_table<LL, LL, custom_hash> dist,distb;

LL expo(LL a, LL b, LL MODULO = MOD){
    if(b == 0) return 1;
    LL tmp = expo(a,b/2);
    tmp = (tmp*tmp)%MODULO;
    if(b&1) tmp = (tmp*a)%MODULO;
    return tmp;
}

struct dt{
    LL pos,step;
    bool operator<(const dt &other)const{
        return step > other.step;
    }
};
queue <dt> antri;

void bfsa(dt now){
    if(now.step > dist[now.pos]) return;
    LL nx = now.pos+2019;
    if(nx >= MOD) nx -= MOD;
    if(!dist[nx]){
        dist[nx] = now.step+1;
        if(now.step+1 < 13) antri.push({nx,now.step+1});
    }
    nx = (now.pos*2020)%MOD;
    if(!dist[nx]){
        dist[nx] = now.step+1;
        if(now.step+1 < 13) antri.push({nx,now.step+1});
    }
    nx = expo(now.pos,2021);
    if(!dist[nx]){
        dist[nx] = now.step+1;
        if(now.step+1 < 13) antri.push({nx,now.step+1});
    }
} 

LL a,b;

int main(){
    cin >> a >> b;
    dist[a] = 1;
    antri.push({a,1});
    while(!antri.empty()){
        dt tmp = antri.front();
        antri.pop();
        bfsa(tmp);
    }
    distb[b] = 1;
    antri.push({b,1});
    while(!antri.empty()){
        dt tmp = antri.front();
        antri.pop();
        bfsb(tmp);
    }
}
