#include <bits/stdc++.h>
using namespace std;


long long c3(long long x){
    return x*(x-1)*(x-2)/6;
}
long long c2(long long x){
    return x*(x-1)/2;
}

long long ans[100069][3];

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    long long nbans = 0;
    long long k = 0;
    cin >> k;
    long long l = 1;
    long long r = 2;
    while(k>0){
        while((r-l+1)*c3(r-l) - (r-l)*c3(r-l-1) <= k){
            k -= ((r-l+1)*c3(r-l) - (r-l)*c3(r-l-1));
            ans[nbans][0] = r;
            ans[nbans][1] = l;
            ans[nbans][2] = r-1;
            nbans++; r++;
        }
        long long toAdd = 0;
        while(c2(r-l-1) + c2(toAdd) <= k){
            k -= c2(r-l-1) + c2(toAdd);
            toAdd++;
        }
        if(toAdd != 0){
            ans[nbans][0] = r;
            ans[nbans][1] = l;
            ans[nbans][2] = l+toAdd-1;
            nbans++; r++;
        }
        l = r; r++;
    }
    cout << nbans << endl;
    for(int i=0; i<nbans; i++){
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << endl;
    }
}
