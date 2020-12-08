#include <cstdio>
#include <vector>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);

  vector<int> cnt(N+1, 1);
  vector<bool> primes(N+1, true);
  for (int i = 3; i <= N; i += 2) {
    if (!primes[i]) continue;
    for (int j = i; j <= N; j += i) {
      primes[j] = false;
      int e = 0, num = j;
      do {
        ++e;
        num /= i;
      } while (num % i == 0);

      if (i % 4 == 3 && e % 2 == 0) cnt[j] = 0;
      else if (i % 4 == 1) cnt[j] *= e + 1;
    }
  }

  for (int i = N; i > 0; --i) if (cnt[i] == 2) return 0 * printf("%d\n", i);
  printf("-1\n");
  return 0;
}
