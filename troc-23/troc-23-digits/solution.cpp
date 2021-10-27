#include <bits/stdc++.h>
using namespace std;


int main(){
    int n;
    cin >> n;
    cout << min(max((n+1)/10-1, 0), 9) << endl;
}