#include <bits/stdc++.h>
using namespace std;


int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n, m;
    cin >> n >> m;
    long long min3 = (n+n%2)*(m+m%2)-n*m;
    if(3*min3>n*m){
        cout << -1 << endl;
    }else{
        cout << (n*m-3*min3)/4 << endl;
    }
}
