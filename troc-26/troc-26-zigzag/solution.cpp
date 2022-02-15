#include <iostream>
using namespace std;

int main() {
    long long n, b[100005], sum = 0;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> b[i];
        sum += b[i];
    }
    bool possible = 1;
    for(int i = 1; i <= n - 1; i++){
        if(b[i] > sum/2){
            possible = 0;
        }
    }
    if(b[n] > (sum+1)/2){
        possible = 0;
    }
    if(possible){
        cout << "YES\n";
    }
    else{
        cout << "NO\n";
    }
}