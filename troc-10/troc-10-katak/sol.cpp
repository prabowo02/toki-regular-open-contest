/*
Author : Hocky Yudhiono
1/15/2020 9:08:59 AM
*/

#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
typedef pair<LL,LL> PLL;
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

LL t,n,k,l;

LL memo[2005][2005][2];


LL dp(LL posa,LL posb,bool turn){
    LL &ret = memo[posa][posb][turn];
    if(posa == n) return ret = 0;
    if(posb == n) return ret = 1;
    if(ret != -1) return ret;
    if(turn == 0){
        for(int i = posa+1;i <= n;i++){
            LL dist = i-posa;
            LL distb = abs(i-posb);
            if(dist > l || distb > k) break;
            if(dp(i,posb,!turn) == turn) return ret = 0;
        }
        return ret = 1;
    }
    if(turn == 1){
        for(int i = posb+1;i <= n;i++){
            LL dist = i-posb;
            LL dista = abs(i-posa);
            if(dist > l || dista > k) break;
            if(dp(posa,i,!turn) == turn) return ret = 1;
        }
        return ret = 0;
    }
    return ret = 0;
}


int main(){
    cin >> t >> k >> l;
    for(int i = 2;i <= t;i++){
        memset(memo,-1,sizeof(memo));
        n = t;
        if(dp(1,1,0) == 0) cout << "A" << endl;
        else cout << "B" << endl;
    }
}