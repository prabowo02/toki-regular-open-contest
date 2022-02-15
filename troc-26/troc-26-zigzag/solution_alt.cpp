#include <iostream>
using namespace std;

int main() {
    long long n, b[100005], sum = 0, cur = 0;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> b[i];
        sum += b[i];
    }
    for(int i=1; i<=n; i++){
        if(cur < sum/2 && b[i] > sum/2){
            cout << "NO\n";
            return 0;
        }
        cur += b[i];
    }
    cout << "YES\n";
}