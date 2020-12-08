#include <bits/stdc++.h>
using namespace std;

int main() {
    string x, y;
    cin >> x >> y;
    
    if (x.find(y) == string::npos) {
        cout << "YA\n";
        cout << x << "\n";
    } else {
        cout << "TIDAK\n";
    }
    return 0;
}
