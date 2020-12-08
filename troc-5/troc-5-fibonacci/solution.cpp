#include <bits/stdc++.h>
using namespace std;

const int M = 2005;

set<int> seen;
bool vis[M][M];

int a, b, m;

int main() {
    cin >> a >> b >> m;
    
    while (!vis[a][b]) {
        vis[a][b] = 1;
        
        seen.insert(a);
        seen.insert(b);
        
        int c = (a + b) % m;
        a = b;
        b = c;
    }
    
    cout << seen.size() << "\n";
    return 0;
}
