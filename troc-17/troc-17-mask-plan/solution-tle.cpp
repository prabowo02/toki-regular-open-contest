#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n, d;
bool isOn[200005];

int main(){
    cin >> n >> d;
    for(int i = 1;i <= n;i++){
        char ch; cin >> ch;
        isOn[i] = (ch == '1');
    }
    int q; cin >> q;
    while(q--){
        LL t, x; cin >> t >> x;
        if(t == 1) isOn[x] = !isOn[x];
        else{
            LL cnt = 0;
            bool flag = 0;
            for(int i = 1;i <= n;i++){
                cnt += isOn[i];
                LL kiri = i-d+1;
                if(cnt > x){
                    cout << i << endl;
                    flag = 1;
                    break;
                }
                if(kiri >= 1) cnt -= isOn[kiri];
            }
            if(!flag) cout << -1 << endl;
        }
    }
    
    return 0;
}
