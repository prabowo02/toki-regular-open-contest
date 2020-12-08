#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9 + 1;
const int MAXN = 200000;
const int MAXM = 20;

int N, M, R;

int X[MAXN + 10], Y[MAXN + 10];
int A[MAXM + 10], B[MAXM + 10], C[MAXM + 10];

int dp[1 << MAXM];
int cost[MAXN + 10];

long long sq(long long x) {
	return x * x;
}

int main() {
	scanf("%d%d%d", &N, &M, &R);

	for(int i = 0; i < N; i++){
		scanf("%d%d", &X[i], &Y[i]);
	}

	for(int i = 0; i < M; i++){
		scanf("%d%d%d", &A[i], &B[i], &C[i]);
	}

	int mx = 0;
	for(int i = 0; i < N; i++){
		int mask = 0;
		for(int j = 0; j < M; j++){
			if(sq(X[i] - A[j]) + sq(Y[i] - B[j]) <= sq(R)) {
				mask |= 1 << j;
			}
		}

		mx = max(mx, (int) __builtin_popcount(mask));
		dp[mask]++;
	}

	// Supermask SOS
	for(int i = 0; i < M; i++){
		for(int mask = 0; mask < (1 << M); mask++) {
			if(mask & (1 << i));
			else dp[mask] += dp[mask ^ (1 << i)];
		}
	}

	for(int mask = 0; mask < (1 << M); mask++) {
		if(__builtin_popcount(mask) & 1);
		else dp[mask] = -dp[mask];
	}

	// Set dp[0] = 0
	dp[0] = 0;

	// Submask SOS
	for(int i = 0; i < M; i++) {
		for(int mask = (1 << M) - 1; mask >= 0; mask--) {
			if(mask & (1 << i)) dp[mask] += dp[mask ^ (1 << i)];
		}
	}

	for(int i = 1; i <= N; i++) cost[i] = INF;

	for(int mask = 0; mask < (1 << M); mask++) {
		int val = 0;
		for(int i = 0; i < M; i++){
			if(mask & (1 << i)){
				val += C[i];
			}
		}

		cost[dp[mask]] = min(cost[dp[mask]], val);
	}

	for(int i = N - 1; i; i--) {
		cost[i] = min(cost[i], cost[i + 1]);
	}

	for(int i = 1; i <= N; i++){
		printf("%d\n", cost[i] == INF ? -1 : cost[i]);
	}

	return 0;
}