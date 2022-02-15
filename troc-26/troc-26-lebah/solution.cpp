#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9 + 10;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N, M, K, L;
	cin >> K >> L;
	cin >> N;
	vector<int> A1, A2;
	for (int i = 0; i < N; i++) {
		int A, B;
		cin >> A >> B;
		if (B == 1) A1.push_back(A);
		else A2.push_back(A);
	}
	cin >> M;
	vector<pair<int, int>> CD(M);
	for (int i = 0; i < M; i++) {
		cin >> CD[i].first >> CD[i].second;
	}

	sort(A1.begin(), A1.end());
	sort(A2.begin(), A2.end());
	vector<pair<int, int>> ord;
	for (int i = 0; i < M; i++) {
		int idx_A1 = upper_bound(A1.begin(), A1.end(), CD[i].first) - A1.begin() - 1;
		int idx_A2 = lower_bound(A2.begin(), A2.end(), CD[i].first) - A2.begin();
		int min_day = INF;
		if (0 <= idx_A1 && idx_A1 < A1.size()) min_day = min(min_day, CD[i].first - A1[idx_A1]);
		if (0 <= idx_A2 && idx_A2 < A2.size()) min_day = min(min_day, A2[idx_A2] - CD[i].first);
		if (min_day != INF) ord.push_back({ min_day, CD[i].second });
	}
	sort(ord.begin(), ord.end());

	priority_queue<int> pq;
	long long answer = 0;
	for (int i = 0; L < K;) {
		while (i < ord.size() && ord[i].first <= L) {
			pq.push(-ord[i].second);
			i++;
		}
		if (pq.empty()) break;
		answer += -pq.top();
		pq.pop();
		L++;
	}

	if (L < K) cout << -1 << '\n';
	else cout << answer << '\n';
}