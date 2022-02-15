#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 16;

int N, M;
int A[MAXN][MAXM];
int B[MAXM];

long long dp[MAXM + 1][MAXM][1 << MAXM];

int main() {
    memset(dp, 0, sizeof(dp));
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int j = 0; j < M; ++j) scanf("%d", &B[j]);

    for (int i = 0; i < N; ++i) {
        vector<pair<int, int>> prices(M);
        for (int j = 0; j < M; ++j) {
            prices[j] = { A[i][j], j };
        }
        sort(prices.begin(), prices.end());

        int mask = (1 << M) - 1;
        for (int j = 0; j < M; ++j) {
            int bit = prices[j].second;
            mask ^= 1 << bit;
            dp[0][bit][mask] += prices[j].first;
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 1 << M; k++) {
                if (i == j) {
                    dp[j + 1][i][k] += dp[j][i][k];
                }
                else if (k & (1 << j)) {
                    dp[j + 1][i][k] += dp[j][i][k];
                    dp[j + 1][i][k ^ (1 << j)] += dp[j][i][k];
                }
                else {
                    dp[j + 1][i][k] += dp[j][i][k];
                }
            }
        }
    }

    long long sum = 1e18;
    for (int mask = 1; mask < 1 << M; ++mask) {
        long long cur = 0;
        for (int nmask = mask; nmask > 0; ) {
            int bit = __builtin_ctz(nmask & -nmask);
            cur += dp[M][bit][mask ^ (1 << bit)] + B[bit];
            nmask ^= 1 << bit;
        }
        sum = min(sum, cur);
    }
    printf("%lld\n", sum);
    return 0;
}