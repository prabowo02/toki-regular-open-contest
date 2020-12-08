#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, k, p;
int arr[N];
int result[N];

int dp[N][3][3];

void read() {
  scanf("%d %d %d", &n, &k, &p);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
  }
}

void answer(int optimal) {
  printf("%d\n", optimal);
  for (int i = 1 ; i <= n ; i++) {
    printf("%d%c", result[i], i == n ? '\n' : ' ');
  }
}

int getDifferentThan(int a, int b) {
  int c = 1;
  while (c == a || c == b) {
    c++;
  }
  return c;
}

int checkGeneral(int lim) {
  int cnt = 0;
  int ret = 0;

  for (int i = 1 ; i <= n ; i++) {
    if (arr[i] == result[i-1]) {
      cnt++;
    } else {
      cnt = 1;
    }

    if (cnt <= lim) {
      result[i] = arr[i];
    } else {
      int x = getDifferentThan(result[i-1], arr[i+1]);
      result[i] = x;

      cnt = 0;
      ret++;
    }
  }

  return ret;
}

int solve(int pos, int val, int lim) {
  if (pos > n) {
    return 0;
  }

  int &ret = dp[pos][val][lim];
  if (ret != -1) return ret;

  ret = 1e9;
  int diff = 0;
  for (int i = 0 ; i < lim && pos + i <= n ; i++) {
    diff += (arr[pos+i] != val);
    ret = min(ret, diff + solve(pos+i+1, val == 1 ? 2 : 1, lim));
  }

  return ret;
}

void backtrack(int pos, int val, int lim) {
  if (pos > n) {
    return;
  }

  int ret = solve(pos, val, lim);
  int diff = 0;
  int otherVal = val == 1 ? 2 : 1;
  for (int i = 0 ; i < lim && pos + i <= n ; i++) {
    diff += (arr[pos+i] != val);

    if (ret == diff + solve(pos+i+1, otherVal, lim)) {
      for (int j = 0 ; j <= i ; j++) {
        result[pos+j] = val;
      }

      backtrack(pos+i+1, otherVal, lim);
      return;
    }
  }

  assert(0);
}

// p = 2 hell
int checkSpecific(int lim) {
  if (lim <= 2) {
    if (solve(1, 1, lim) <= solve(1, 2, lim)) {
      backtrack(1, 1, lim);
      return solve(1, 1, lim);
    } else {
      backtrack(1, 2, lim);
      return solve(1, 2, lim);
    }
  }

  int ret = 0;
  int cnt = 0;

  for (int i = 1 ; i <= n ; i++) {
    if (arr[i] == result[i-1]) {
      cnt++;

      if (cnt == lim+2) {
        cnt = 1;
        ret++;

        result[i-1] = result[i-1] == 2 ? 1 : 2;
      }

      result[i] = arr[i];
    } else {
      if (cnt == lim+1) {
        ret++;
        result[i-2] = result[i-2] == 2 ? 1 : 2;
      }

      result[i] = arr[i];
      cnt = 1;
    }
  }

  if (cnt == lim+1) {
    ret++;
    result[n] = result[n] == 2 ? 1 : 2;
  }

  return ret;
}

void work() {
  if (p == 1) {
    for (int i = 1 ; i <= n ; i++) {
      result[i] = 1;
    }
    
    answer(n);
    return;
  }

  if (p >= 3) {
    int lo = 1, hi = n;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (checkGeneral(mid) <= k) {
        hi = mid;
      } else {
        lo = mid+1;
      }
    }

    checkGeneral(lo);
    answer(lo);
    return;
  }
  
  memset(dp, -1, sizeof dp);
  int lo = 1, hi = n;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (checkSpecific(mid) <= k) {
      hi = mid;
    } else {
      lo = mid+1;
    }
  }

  checkSpecific(lo);
  answer(lo);
  return;
}

int main() {
  read();
  work();
  return 0;
}