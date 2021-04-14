#include <iostream>
#include <cstring>
using namespace std;
const int INF = 1061109567;
const int MAXA = 100000;
int memo[MAXA + 5][3][3][3];
int isi[MAXA + 5];
int dp(int pos, int a, int b, int c){
    if(pos > MAXA + 1) return 0;
    int &ret = memo[pos][a][b][c];
    if(~ret) return ret;
    ret = INF;
    
    int pre = (a == 2 ? isi[pos - 2] : 0) + (b == 1 ? isi[pos - 1] : 0) + (c == 0 ? isi[pos] : 0);
    int cur = (b == 2 ? isi[pos - 1] : 0) + (c == 1 ? isi[pos] : 0);
    
    int cost = ((cur + isi[pos + 1]) ? pre : 0);
    ret = min(ret, dp(pos + 1, b, c, 0) + cost + isi[pos + 1]);

    cost = (cur ? pre : 0);
    ret = min(ret, dp(pos + 1, b, c, 1) + cost);
    ret = min(ret, dp(pos + 1, b, c, 2) + cost + isi[pos + 1]);
    
    return ret;
}
    
inline void fasterios(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}

int main(){
    fasterios();
    memset(memo,-1,sizeof(memo));

    int n; cin >> n;
    for(int i = 1;i <= n;i++){
        int tmp; cin >> tmp;
        isi[tmp]++;
    }
    cout << dp(1, 1, 1, 1) << endl;
}