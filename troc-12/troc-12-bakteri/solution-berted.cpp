#include <iostream>
using namespace std;
char rs[101][101] = {};
int main()
{
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	if (k < (n + m + 1) / 2) {cout << "TIDAK\n";}
	else
	{
		cout << "YA\n";
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				rs[i][j] = '.';
			}
		}
		for (int i = 0; i < n; i += 2)
		{
			rs[i][0] = 'X';
		}
		for (int j = !(n % 2); j < m; j += 2)
		{
			rs[n - 1][j] = 'X';
		}
		if ((n + m) % 2 == 1) {rs[n - 1][m - 1] = 'X';}
		k -= (n + m + 1) / 2;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (rs[i][j] == '.' && k) {rs[i][j] = 'X'; k--;}
				cout<<rs[i][j];
			}
			cout << "\n";
		}
	}
	return 0;
}