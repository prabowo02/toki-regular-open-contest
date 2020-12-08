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

int main(){
    cin >> n >> k >> l;
    if(k >= l || k >= n-1) cout << "A" << endl;
    else cout << "B" << endl;
}