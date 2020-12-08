#include <iostream>
using namespace std;

const int MX = 1e9;
int N, M, adj[1001][1001];
int calc[1001];

bool DFS(int u, int c)
{
	if (calc[u] == -1)
	{
		calc[u] = c;
		for (int i = 0; i < N; i++)
		{
			if (i == u) continue;
			if (adj[u][i] <= M && !DFS(i, !c)) {return 0;}
		}
		return 1;
	}
	else {return calc[u] == c;}
}

int main()
{
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> adj[i][j];
		}
	}
	int L = 0, R = MX;
	while (L < R)
	{
		M = L + R >> 1;
		for (int i = 0; i < N; i++) {calc[i] = -1;}
		bool val = 1;
		for (int i = 0; i < N; i++) 
		{
			if (calc[i] == -1) {val &= DFS(i, 0);}
		}
		if (val) {L = M + 1;}
		else {R = M;}
	}
	cout << L << "\n";
	return 0;
}
