//new.cpp
/*
Author : Hocky Yudhiono
Jum 15 Nov 2019 11:42:11  WIB
*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<long long,long long> PLL;
//If the time limit is strict, try not to use long double
#define popb pop_back
#define pb push_back
#define fi first
#define se second

//Remember to undefine if the problem is interactive
#define endl '\n'

const int INFMEM = 63;
const LL LINF = 4557430888798830399LL;
const LL MOD = 1000000007;

inline void fasterios(){
    //Do not use if interactive
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}

LL n,q;
LL a[40005];
LL refAns[20005];
PLL ansa[40005];
LL minLen[40005];
LL prehash[40005][2];
vector <LL> b[20005];
vector <LL> pos[40005];
LL base[2] = {14951,16249};

#include <unordered_map>
#include <chrono>
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

int main(){
    fasterios();
    cin >> n >> q;
    memset(minLen,INFMEM,sizeof(minLen));
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    n--;
    for(int i = 1;i <= n;i++){
        a[i] = (a[i]^a[i+1]);
    }
    // for(int i = 1;i <= n;i++){
    //  cout << a[i] << " \n"[i == n];
    // }
    for(int j = 1;j <= q;j++){
        ansa[j] = {0,-1};
        LL k; cin >> k;
        b[j].resize(k+1);
        b[j][0] = 0;
        for(int i = 1;i <= k;i++){
            cin >> b[j][i];
        }
        k--;
        for(int i = 1;i <= k;i++){
            b[j][i] = (b[j][i]^b[j][i+1]);
        }
        b[j].popb();
        pos[k].pb(j);
    }
    LL decbase[2] = {1,1};
    for(int i = 1;i <= 40000-1;i++){
        for(int j = 0;j <= 1;j++){
            decbase[j] = (decbase[j]*base[j])%MOD;
        }

        if(pos[i].size() == 0) continue;
        // cout << "Computing " << i << " has: " << endl;
        // for(int j = 0;j < pos[i].size();j++){
        //  cout << pos[i][j] << " \n"[j == pos[i].size()-1];
        // }
        unordered_map <LL,LL,hash<LL>> table;
        for(int j = 0;j < pos[i].size();j++){
            // Hash current sequence
            LL curhash[2] = {0,0};
            LL curidx = pos[i][j];
            for(int l = 1;l < b[curidx].size();l++){
                // cout << b[curidx][l] << " \n"[l == b[curidx].size()-1];
                for(int k = 0;k <= 1;k++){
                    curhash[k] = (curhash[k]*base[k])%MOD;
                    curhash[k] = (curhash[k]+b[curidx][l])%MOD;
                }
            }
            LL nowhash = (curhash[0]<<31)+curhash[1];
            if(table.count(nowhash)) refAns[curidx] = table[nowhash];
            else table[nowhash] = pos[i][j];
        }

        LL curhash[2] = {0,0};
        for(int j = 1;j <= n;j++){
            LL kanan = j;
            LL kiri = j-i+1;
            for(int k = 0;k <= 1;k++){
                curhash[k] = (curhash[k]*base[k])%MOD;
                curhash[k] = (curhash[k]+a[j])%MOD;
                if(kiri > 0) curhash[k] = (curhash[k]-((decbase[k]*a[kiri-1])%MOD)+MOD)%MOD;
            }
            if(kiri <= 0) continue;

            LL nowhash = (curhash[0]<<31)+curhash[1];
            if(table.count(nowhash)){
                LL curmatch = table[nowhash];
                minLen[kiri] = min(minLen[kiri], kanan+1);
                // cout << "Making segments " << kiri << " " << kanan+1 << endl;
                if(ansa[curmatch].se < kiri){
                    ansa[curmatch].fi++;
                    ansa[curmatch].se = kanan+1;
                }
            }
        }
    }
    for(int i = 1;i <= q;i++){
        if(refAns[i]) ansa[i] = ansa[refAns[i]];
        cout << ansa[i].fi << endl;
    }
    PLL ansb = {0,-1};
    for(int i = 1;i <= n+1;i++){
        if(minLen[i] == LINF) continue;
        if(ansb.se < i){
            ansb.fi++;
            ansb.se = minLen[i];
        }
        ansb.se = min(ansb.se,minLen[i]);
    }
    cout << ansb.fi << endl;
    return 0;
}
