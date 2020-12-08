#include <iostream>
#define pii pair<int, int>
#define ppi pair<pii, int>
#define fst first
#define snd second
using namespace std;
ppi rs(int d, int x, int y)
{
	if (d == 0) {return {{x, y}, 0};}
	else
	{
		int s = 1 << (d - 1), b = s << 1, t = b + s;
		if ((x <= s && y <= b) || (y <= s && x <= b)) {return rs(d - 1, x, y);}
		else if ((x <= s) || (y >= t)) 
		{
			ppi ret = rs(d - 1, (1 << (d + 1)) - y, x);
			return {ret.fst, (ret.snd + 1) % 4};
		}
		else if ((y <= s) || (x >= t)) 
		{
			ppi ret = rs(d - 1, y, (1 << (d + 1)) - x);
			return {ret.fst, (ret.snd + 3) % 4};
		}
		else {return rs(d - 1, x - s, y - s);}
	}
}
int main()
{
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int q; cin >> q;
	while (q--)
	{
		int x, y, c; cin >> x >> y;
		c = 0;
		while ((1 << (c + 1)) < max(x, y)) {c++;}
		if (min(x, y) > (1 << c)) {c++;}
		if (rs(c, x, y) == make_pair(make_pair(1, 1), 0)) {cout << x + y + 2 << "\n";}
		else {cout << x + y << "\n";}
	}
	return 0;
}