#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N, M;
	cin >> N >> M;
	vector<long long> f(M + 1, 1);
	for (int i = 1; i <= M; i++) f[i] = 3 * f[i - 1];
	vector<vector<long long>> dp(2, vector<long long>(f[M]));
	vector<vector<pair<int, int>>> A(N, vector<pair<int, int>>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> A[i][j].first;
			A[i][j].second = j;
		}
		sort(A[i].begin(), A[i].end());
		int mask = f[M] - 1;
		for (int j = 0; j < M; j++) {
			mask -= f[A[i][j].second];
			dp[0][mask] += A[i][j].first;
			mask -= f[A[i][j].second];
		}
	}
	vector<long long> B(M);
	for (int i = 0; i < M; i++) cin >> B[i];

	for (int t = 0; t < M; t++) {
		bool p = t & 1;
		bool q = !p;
		for (int u = 0; u < f[M]; u++) {
			int v = (u / f[t]) % 3;
			if (v == 0 || v == 2) dp[q][u - v * f[t]] += dp[p][u];
			if (v == 1 || v == 2) dp[q][u - (v - 1) * f[t]] += dp[p][u];
			dp[p][u] = 0;
		}
	}

	int MM = 1 << M;
	long long res = INF, con = MM - 1;
	for (int u = 1, p = M & 1; u < MM; u++) {
		int uu = 0;
		long long cur = 0;
		for (int j = 0, bit = 1; j < M; j++, bit <<= 1) {
			if (u & bit) {
				cur += B[j];
				uu += f[j];
			}
		}
		cur += dp[p][uu];
		if (cur < res) {
			res = cur;
			con = u;
		}
	}

	cout << res << '\n';

	/*
	vector<bool> C(M);
	for (int j = 0, bit = 1; j < M; j++, bit <<= 1) {
		if (con & bit) C[j] = true;
	}
	for (int i = 0; i < N; i++) {
		int best = -1;
		for (int j = 0; j < M; j++) {
			if (C[A[i][j].second]) {
				if (best < 0) best = j;
				else if (A[i][j].first < A[i][best].first) {
					best = j;
					return -1;
				}
			}
		}
		if (i > 0) cout << ' ';
		cout << A[i][best].second + 1;
	}
	cout << '\n';
	*/
}
