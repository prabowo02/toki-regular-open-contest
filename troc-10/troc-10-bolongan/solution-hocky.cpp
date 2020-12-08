/*
Author : Hocky Yudhiono
1/15/2020 8:55:55 AM
*/

#include <iostream>
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

LL n; 

int main(){
    cin >> n;
    if(n == 0) cout << 1 << endl;
    else if(n == 1) cout << 0 << endl;
    else{
        if(n%2 == 1) cout << 4;
        for(int i = 1;i <= n/2;i++) cout << 8;
        cout << endl;
    }
    return 0;
}