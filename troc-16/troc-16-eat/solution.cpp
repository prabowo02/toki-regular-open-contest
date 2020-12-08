#include <iostream>
#include <algorithm>
using namespace std;

int N, M, A[200001];

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {cin >> A[i];}
	sort(A, A + N);
	int MX = 0;
	for (int i = 0; i + 1 < N; i++) {MX = max(MX, A[i + 1] - A[i]);}
	MX = max(MX, M + A[0] - A[N - 1]);
	cout << M - MX << "\n";
	return 0;
}
