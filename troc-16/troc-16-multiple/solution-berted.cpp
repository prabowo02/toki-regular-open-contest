#include <iostream>
#include <vector>
#define ll long long
#define pii pair<int, int>
#define fst first
#define snd second
using namespace std;

const int MD = 1e9 + 7;

int N, dv[100001];
vector<pii> C[100001];
ll R = 1;

inline ll pw(ll b, ll e)
{
	ll t = 1; e %= MD - 1;
	while (e)
	{
		if (e & 1) {t = t * b % MD;}
		b = b * b % MD; e >>= 1;
	}
	return t;
}

inline void preProcess()
{
	for (int i = 2; i <= 100000; i++)
	{
		if (dv[i] == 0)
		{
			for (int j = i; j <= 100000; j += i) {dv[j] = i;}
		}
	}
}

inline void insert(int idx, int v)
{
	int pv = 0, cnt = 0;
	while (v > 1)
	{
		if (pv != dv[v])
		{
			if (pv) {C[pv].push_back({idx, cnt});}
			cnt = 1; pv = dv[v];
		}
		else {cnt++;}
		v /= dv[v];
	}
	if (pv) {C[pv].push_back({idx, cnt});}
}

inline void process(int idx)
{
	if (C[idx].size() == 0) {return;}
	int p = 0; long long pp = 0;
	vector<pii> s; s.push_back({-1, 100});
	C[idx].push_back({N, 0});
	for (int i = 0; i + 1 < C[idx].size(); i++)
	{
		p += (C[idx][i].fst - s.back().fst) * C[idx][i].snd;
		while (s.size() > 1 && s.back().snd <= C[idx][i].snd)
		{
			pii v = s.back(); s.pop_back();
			p += (v.fst - s.back().fst) * (C[idx][i].snd - v.snd);
		}
		s.push_back(C[idx][i]);
		pp += (long long)p * (C[idx][i + 1].fst - C[idx][i].fst);
	}
	//cerr << idx << ": " << pp << "\n";
	R = R * pw(idx, pp) % MD;
}

int main()
{
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	preProcess();
	cin >> N;
	for (int i = 0; i < N; i++) {int x; cin >> x; insert(i, x);}
	for (int i = 2; i <= 100000; i++) {process(i);}
	cout << R << "\n";
	return 0;
}