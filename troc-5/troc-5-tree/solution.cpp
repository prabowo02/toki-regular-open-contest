#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

const int N = 1e5 + 5;
const int K = 15;

int f[N];
int cumulativeF[N];
int dp[N][K];

int d, k;

void init() {
    f[0] = 1;
    f[1] = 1;
    cumulativeF[0] = 1;
    cumulativeF[1] = 2;
    
    for (int i = 2 ; i < N ; i++) {
        f[i] = 2ll * f[i-1] * cumulativeF[i-1] % MOD;
        f[i] = (f[i] - 1ll * f[i-1] * f[i-1]) % MOD;
        f[i] = (f[i] + MOD) % MOD;
        
        cumulativeF[i] = (cumulativeF[i-1] + f[i]) % MOD;
    }
    
    dp[1][1] = 1;
    dp[1][0] = 1;
    
    for (int i = 2 ; i < N ; i++) {
        dp[i][0] = cumulativeF[i-1];
        
        for (int j = 1 ; j < K ; j++) {
            for (int j2 = 0 ; j2 <= j ; j2++) {
                dp[i][j] = (dp[i][j] + 1ll * dp[i-1][j2] * dp[i-1][j - j2]) % MOD;
            }
        }
    }
}

int main() {
    init();
    
    cin >> d >> k;
    cout << dp[d][k] << endl;
    return 0;
}

