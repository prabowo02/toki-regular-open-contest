#include <bits/stdc++.h>
using namespace std;
const int AMX = 250;
int n, l, r, ar[251][251] = {};
int pr[251][251][251] = {}, pl[251][251][251] = {};
long long rs = 0;
inline int qryr(int x1, int y1, int x2, int y2, int t1, int t2)
{
	if (x2 >= n) {y2 -= (x2 - n + 1); x2 = n - 1;}
	if (y2 >= n) {x2 -= (y2 - n + 1); y2 = n - 1;}
	if (x1 < 0) {y1 -= x1; x1 = 0;}
	if (y1 < 0) {x1 -= y1; y1 = 0;}
	if (min({x1, y1, x2, y2}) < 0 || max({x1, y1, x2, y2}) >= n) {return 0;}
	int to = pr[x2][y2][t2];
	if (t1) {to -= pr[x2][y2][t1 - 1];}
	if (x1 && y1) {to -= pr[x1 - 1][y1 - 1][t2];}
	if (x1 && y1 && t1) {to += pr[x1 - 1][y1 - 1][t1 - 1];}
	return to;
}
inline int qryl(int y1, int x1, int y2, int x2, int t1, int t2)
{
	if (x2 < 0) {y2 += x2; x2 = 0;}
	if (y2 >= n) {x2 += (y2 - n + 1); y2 = n - 1;}
	if (x1 >= n) {y1 += (x1 - n + 1); x1 = n - 1;}
	if (y1 < 0) {x1 += y1; y1 = 0;}
	if (min({y1, x1, x2, y2}) < 0 || max({x1, y1, x2, y2}) >= n) {return 0;}
	int to = pl[y2][x2][t2];
	if (t1) {to -= pl[y2][x2][t1 - 1];}
	if (y1 && x1 < n - 1) {to -= pl[y1 - 1][x1 + 1][t2];}
	if (y1 && x1 < n - 1 && t1) {to += pl[y1 - 1][x1 + 1][t1 - 1];}
	return to;
}
int main()
{
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {cin >> ar[i][j];}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			pr[i][j][ar[i][j]]++;
			pl[i][j][ar[i][j]]++;
			for (int k = 1; k <= AMX; k++)
			{
				pl[i][j][k] += pl[i][j][k - 1];
				pr[i][j][k] += pr[i][j][k - 1];
			}
			if (i && j)
			{
				for (int k = 0; k <= AMX; k++) {pr[i][j][k] += pr[i - 1][j - 1][k];}
			}
			if (i && j < n - 1)
			{
				for (int k = 0; k <= AMX; k++)	{pl[i][j][k] += pl[i - 1][j + 1][k];}
			}
		}
	}
	int tp, lf, rg;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 1; k < 2 * n; k++)
			{
				lf = min(AMX + 1, (l * k + ar[i][j] - 1) / ar[i][j]);
				rg = min(AMX, r * k / ar[i][j]);
				tp = qryl(i - k, j, i - 1, j - k + 1, lf, rg);
				tp += qryl(i + 1, j + k - 1, i + k, j, lf, rg);
				tp += qryr(i, j - k, i + k - 1, j - 1, lf, rg);
				tp += qryr(i - k + 1, j + 1, i, j + k, lf, rg);
				rs += tp * tp;
			}
		}
	}
	cout << rs << "\n";
	return 0;
}