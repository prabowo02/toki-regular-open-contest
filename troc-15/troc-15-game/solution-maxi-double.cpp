#include <iostream>
#include <iomanip>
using namespace std;

#define ld double
const int MX = 5005;
#define max(x, y) (x > y ? x : y)

ld sm[MX], a[MX], b[MX];

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	int n, d, sa, sb;
	cin >> n >> d >> sa >> sb;
	
	sa = min(sa, n - d); sb = min(sb, n - d);

	ld p = 1.0 / (ld)d;
	a[sa] = 1.0; b[sb] = 1.0;
	ld ans = 0.0, cr = 1.0;

	for(int i = 0; i < n; i ++){
		ans += cr * a[n - d] * p;
		cr -= b[n - d] * p;
		a[n - d] *= (1 - p);
		b[n - d] *= (1 - p);

		sm[0] = 0.0;
		for(int i = 1; i < n - d; i ++)
			sm[i] = sm[i - 1] + a[i];
		for(int i = 1; i < n - d; i ++)
			a[i] = (sm[i - 1] - sm[max(0, i - d - 1)]) * p;
		for(int i = 1; i <= d; i ++)
			a[n - d] += (sm[n - d - 1] - sm[max(0, n - d - i - 1)]) * p;

		sm[0] = 0.0;
		for(int i = 1; i < n - d; i ++)
			sm[i] = sm[i - 1] + b[i];
		for(int i = 1; i < n - d; i ++)
			b[i] = (sm[i - 1] - sm[max(0, i - d - 1)]) * p;
		for(int i = 1; i <= d; i ++)
			b[n - d] += (sm[n - d - 1] - sm[max(0, n - d - i - 1)]) * p;		
	}

	ans += a[n - d] * cr * ((ld)d / (2.0 * (ld)d - 1.0));

	cout << fixed << setprecision(10) << ans << endl;
	return 0;
}
