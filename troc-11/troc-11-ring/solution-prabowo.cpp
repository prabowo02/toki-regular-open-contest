#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int n;
long long l, r;
long long d, m;

const int SZ = 7;
struct Matrix {
  int a[SZ][SZ];
  
  Matrix(int val = 0) {
    for (int i=0; i<SZ; i++) {
      for (int j=0; j<SZ; j++) a[i][j] = 0;
      a[i][i] = val;
    }
  }
  
  Matrix operator * (const Matrix &other) {
    Matrix ret;
    for (int i=0; i<SZ; i++) {
      for (int j=0; j<SZ; j++) {
        for (int k=0; k<SZ; k++) {
          ret.a[i][j] = (1LL * a[i][k] * other.a[k][j] + ret.a[i][j]) % MOD;
        }
      }
    }
    
    return ret;
  }

  Matrix operator + (const Matrix &other) {
    Matrix ret;
    for (int i = 0; i < SZ; ++i) {
      for (int j = 0; j < SZ; ++j) {
        ret.a[i][j] = (a[i][j] + other.a[i][j]) % MOD;
      }
    }

    return ret;
  }

  int * operator [] (int row) { return a[row]; }
};

Matrix power(Matrix A, long long y) {
  Matrix ret(1);
  
  for (; y; y >>= 1) {
    if (y & 1) ret = ret * A;
    A = A * A;
  }
  
  return ret;
}

Matrix solve(const Matrix &A, long long n) {
  if (n == 0) return Matrix(0);
  Matrix ret = (Matrix(1) + power(A, n/2)) * solve(A, n/2);
  if (n & 1) return Matrix(1) + ret * A;
  return ret;
}

int main() {
  scanf("%d %lld %lld", &n, &l, &r);
  scanf("%lld %lld", &d, &m);

  Matrix A; // 00 01 02 10 20 12 21
  A[0][0] = n-4; A[0][1] = 1; A[0][2] = 1;
  A[1][3] = n-3; A[1][5] = 1;
  A[2][4] = n-3; A[2][6] = 1;
  A[3][0] = n-3; A[3][2] = 1;
  A[4][0] = n-3; A[4][1] = 1;
  A[5][4] = n-2;
  A[6][3] = n-2;

  l = l/m + (l%m > d);
  r = r/m - (r%m < d);

  Matrix res = power(A, l*m + d - 2) * solve(power(A, m), r-l+1);

  printf("%lld\n", 1LL * (res[5][0] + res[5][4]) % MOD * n % MOD * (n-1) % MOD);
  return 0;
}
