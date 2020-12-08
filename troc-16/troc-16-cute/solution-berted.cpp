#include <iostream>
#define ll long long
using namespace std;

const int MD = 1e9 + 7;

int N, M;
ll F[2], R = 1;

int main()
{
	cin >> N >> M; F[0] = 1; F[1] = M; R = M - 1;
	for (int i = 2; i <= N; i++)
	{
		R *= M - 1; R %= MD;
		F[i & 1] = (M - 1) * (F[~i & 1] + F[i & 1]) % MD; 
	}
	cout << (F[N & 1] + MD - R) % MD << "\n";
	return 0;
}