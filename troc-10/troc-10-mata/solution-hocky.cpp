/*
Author : Hocky Yudhiono
1/15/2020 8:52:34 AM
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

string s,t;
char rubah(char a){
    if('A' <= a && a <= 'Z') return (char)(a-'A'+'a');
    return a;
}

void cant(){
    cout << "x_x" << endl;
    // cout << "Impossible" << endl;
    exit(0);
}

int main(){
    cin >> s >> t;
    for(int i = 0;i < s.length();i++){
        if(rubah(s[i]) != rubah(t[i])) cant();
    }
    cout << "20/20 Vision" << endl;
    return 0;
}