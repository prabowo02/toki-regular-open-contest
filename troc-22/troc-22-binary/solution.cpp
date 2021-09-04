#include <cstdio>
#include <queue>
using namespace std;

int query(long long ind) {
	printf("? %lld\n", ind);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	return ret;
}
int main() {
	long long n;
	scanf("%lld", &n);
	int first = query(1);
	int length1, length2;
	{
		int low = 1, high = min(1000000000ll, n);//[]
		while (low < high) {
			int mid = min(low * 2, (low + high + 1) / 2);
			if (query(mid) == first){
				low = mid;
			} else {
				high = mid - 1;
			}
		}
		length1 = low;
	}
	{
		int low = length1, high = min(1000000000ll, n - length1);//[]
		while (low < high) {
			int mid = min(low * 2, (low + high + 1) / 2);
			if (query(mid + length1) == first) {
				high = mid - 1;
			} else {
				low = mid;
			}
		}
		length2 = low;
	}
	int x = length2;
	int a = first ? 2 * x - length1 : x - length1;
	int b = (-n - a) % (2 * x);
	if (b < 0)
		b += 2 * x;
	int y = (n + a + b) / (2 * x);
	printf("! %d %d %d %d\n", x, y, a, b);
}
