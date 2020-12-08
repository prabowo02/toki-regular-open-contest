#include <iostream>
using namespace std;
typedef long long LL;
LL n,q;
LL isi[100005];

int main(){
    cin >> n >> q;
    for(int i = 1;i <= n;i++){
        cin >> isi[i];
    }
    for(int i = 1;i <= q;i++){
        LL t,x,y,c; cin >> t >> x >> y >> c;
        if(t == 1){
            for(int j = x;j <= y;j++){
                isi[j] += c;
            }
        }else{
            LL mini = -1;
            LL maksi = -1;
            for(int j = x;j <= y;j++){
                if(mini == -1){
                    mini = isi[j]+abs(j-c);
                }
                if(maksi == -1){
                    maksi = isi[j]+abs(j-c);
                }
                LL now = isi[j]+abs(j-c);
                mini = min(now,mini);
                maksi = max(now,maksi);
            }
            cout << maksi-mini << endl;
        }
    }
    return 0;
}