#include <iostream>
#define ll long long
using namespace std;

const int SZ = (1 << 20) + 69, INF = 2e9 + 7;

int N, M; ll R;
int X[200001], Y[200001];
int A[21], B[21], C[21];
int DP[2][SZ], res[200001];

int main()
{
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> M >> R;
	for (int i = 0; i < N; i++) {cin >> X[i] >> Y[i]; res[i + 1] = INF;}
	for (int i = 0; i < M; i++) {cin >> A[i] >> B[i] >> C[i];}
	for (int i = 0; i < N; i++)
	{
		int msk = 0;
		for (int j = 0; j < M; j++)
		{
			ll x = (X[i] - A[j]), y = (Y[i] - B[j]);
			if (x * x + y * y <= R * R) {msk ^= 1 << j;}
		}
		DP[0][msk]++;
	}
	for (int i = 1; i <= M; i++)
	{
		for (int j = 0; j < (1 << M); j++)
		{
			DP[i & 1][j] = DP[~i & 1][j];
			if ((j & (1 << (i - 1))) == 0) {DP[i & 1][j] += DP[~i & 1][j ^ (1 << (i - 1))];}
		}
	}
	for (int j = 0; j < (1 << M); j++) 
	{
		if (__builtin_popcount(j) & 1) DP[0][j] = DP[M & 1][j];
		else DP[0][j] = -DP[M & 1][j];
	}
	DP[0][0] = 0;
	for (int i = 1; i <= M; i++)
	{
		for (int j = 0; j < (1 << M); j++)
		{
			DP[i & 1][j] = DP[~i & 1][j];
			if (j & (1 << (i - 1))) {DP[i & 1][j] += DP[~i & 1][j ^ (1 << (i - 1))];}
		}
	}
	for (int j = 0; j < (1 << M); j++)
	{
		int S = 0;
		for (int i = 0; i < M; i++)
		{
			if (j & (1 << i)) S += C[i];
		}
		res[DP[M & 1][j]] = min(res[DP[M & 1][j]], S);
	}
	for (int i = N - 1; i; i--) {res[i] = min(res[i], res[i + 1]);}
	for (int i = 1; i <= N; i++) 
	{
		if (res[i] < INF) cout << res[i] << "\n";
		else cout << "-1\n";
	}
	return 0;
}