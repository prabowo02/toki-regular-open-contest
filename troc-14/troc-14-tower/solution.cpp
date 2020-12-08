#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m; cin >> n >> m;
    for(int i = 1;i <= n;i++) for(int j = 1;j <= m;j++)
        cout << (i%2 == 0 ? 'B' : 'W') << (j == m ? "\n" : "");
}