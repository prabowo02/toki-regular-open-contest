#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int arr[N];
int pos[N];
int psum[N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for (int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }
}

int work() {
    for (int i = 1 ; i <= n ; i++) {
        pos[arr[i]] = i;
    }
    
    for (int i = 1 ; i < n ; i++) {
        int a = pos[i];
        int b = pos[i+1];
        
        if (a > b) swap(a, b);
        
        psum[a]++;
        psum[b]--;
    }
    
    vector<int> v;
    for (int i = 1 ; i <= n ; i++) {
        psum[i] += psum[i-1];
        v.push_back(psum[i]);
    }
    
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    
    int tot = 0;
    for (int i = 0 ; i < n ; i++) {
        tot += v[i];
        if (tot >= k) {
            return i+1;
        }
    }
    
    return -1;
}

int main() {
    read();
    printf("%d\n", work());
    return 0;
}

