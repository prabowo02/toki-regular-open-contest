#include <stdio.h>
#include <functional>
#include <vector>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;

#define ll long long
const int MX = 305;
const ll mod = 998244353;

int n;
vector<int> v;
bitset<MX> vis;
ll C[MX][MX], dp[MX][MX];

vector<int> par;
inline int find(int nw){
    if(par[nw] == nw) return nw;
    par[nw] = find(par[nw]);
    return par[nw];
}

int main(){
    scanf("%d", &n);
    v.resize(n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &v[i]);

    C[0][0] = 1;
    for(int i = 1; i < MX; i ++){
        C[i][0] = 1;
        for(int j = 1; j <= i; j ++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }

    for(int i = n - 1; i >= 0; i --){
        for(int j = i; j < n; j ++){
            if(i == j) dp[i][j] = 1;
            else{
                par.resize(j - i + 1);
                iota(par.begin(), par.end(), 0);
                vis.reset();

                vector<int> q;
                for(int k = i; k <= j; k ++) q.push_back(v[k]);
                sort(q.begin(), q.end());

                vector<int> rev(n + 1, -1);
                for(int k = 0; k <= j - i; k ++)
                    rev[q[k]] = k;

                for(int k = i; k < j; k ++){
                    int ps = rev[v[k]];
                    vis[ps] = 1;
                    if(ps > 0 && vis[ps - 1]){
                        int x = find(ps - 1), y = find(ps);
                        if(x != y) par[x] = y;
                    }
                    if(ps < j - i && vis[ps + 1]){
                        int x = find(ps + 1), y = find(ps);
                        if(x != y) par[x] = y;
                    }

                    if((k == i || (find(k - 1 - i) == find(0)) && vis[0] && vis[k - 1 - i]) && vis[k + 1 - i])
                        (dp[i][j] += (dp[i][k] * 1ll * dp[k + 1][j]) % mod * 1ll * C[j - i - 1][k - i] % mod) %= mod;
                }
            }
        }
    }

    printf("%lld\n", dp[0][n - 1]);
    return 0;
}