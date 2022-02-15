#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, M;
	cin >> N >> M;
	vector<vector<int>> A(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> A[i][j];
		}
	}
	vector<int> B(M);
	for (int j = 0; j < M; j++) cin >> B[j];

	vector<pair<long long, int>> ord(M);
	for (int j = 0; j < M; j++) {
		long long total = B[j];
		for (int i = 0; i < N; i++) {
			total += A[i][j];
		}
		ord[j] = { total, j };
	}
	sort(ord.begin(), ord.end());

	long long res = 1e18;
	vector<int> picked;
	for (int j = 0; j < M; j++) {
		long long cur = 0;
		picked.push_back(ord[j].second);
		for (int i = 0; i < N; i++) {
			int min_val = 1e9;
			for (int x : picked) {
				min_val = min(min_val, A[i][x]);
			}
			cur += min_val;
		}
		for (int x : picked) {
			cur += B[x];
		}
		res = min(res, cur);
	}
	cout << res << '\n';
}