//new.cpp
/*
Author : Hocky Yudhiono
1/15/2020 8:09:42 AM
*/
#include <iostream>
#include <vector>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PLL;
const int dx[8] = {1,0,-1,0,1,1,-1,-1};
const int dy[8] = {0,1,0,-1,1,-1,1,-1};

LL n,m,q;
LL ans[100005];
LL val[250005];
vector <PLL> que[100005];
vector <PLL> isi[100005];
LL rubah(LL x,LL y){
    return ((x-1)*m)+y;
}
LL par[250005];
LL curans[250005];
LL findpar(LL now){
    if(par[now] == now) return now;
    return par[now] = findpar(par[now]);
}

int main(){
    cin >> n >> m >> q;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            LL now = rubah(i,j);
            par[now] = now;
            curans[now] = i+j-2;
            LL tmp; cin >> tmp;
            val[now] = tmp;
            isi[tmp].pb({i,j});
        }
    }
    for(int i = 1;i <= q;i++){
        LL x,y,l; cin >> x >> y >> l;
        que[l].pb({rubah(x,y),i});
    }
    for(int i = 1;i <= 100000;i++){
        for(int j = 0;j < isi[i].size();j++){
            PLL cur = isi[i][j];
            for(int l = 0;l < 4;l++){
                LL nx = dx[l]+cur.fi;
                LL ny = dy[l]+cur.se;
                if(nx <= 0 || ny <= 0 || nx > n || ny > m) continue;
                LL u = rubah(cur.fi,cur.se);
                LL v = rubah(nx,ny);
                if(val[v] > val[u]) continue;
                if(findpar(u) == findpar(v)) continue;
                // cout << "Gabung " << cur.fi << " " << cur.se << " " << nx << " " << ny << endl;
                curans[par[v]] = min(curans[par[v]],curans[par[u]]);
                par[par[u]] = par[v];
            }
        }
        for(int j = 0;j < que[i].size();j++){
            PLL cur = que[i][j];
            ans[cur.se] = curans[findpar(cur.fi)];
        }
    }
    for(int i = 1;i <= q;i++) cout << ans[i] << endl;
    return 0;
}