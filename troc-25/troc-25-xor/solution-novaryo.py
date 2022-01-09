N, M, K = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

row_mx1 = 0
row_mn1 = 1e9

ans = 0

sum1 = 0
for i in range(N):
  sum1 += A[i]
  if i >= K:
    sum1 -= A[i-K]
  if i >= K-1:
    row_mn1 = min(row_mn1, sum1)
    row_mx1 = max(row_mx1, sum1)

sum1 = 0
for i in range(M):
  if i >= K:
    sum1 -= B[i-K]
  sum1 += B[i]
  if i >= K-1:
    ans = max(ans, sum1 * (K - row_mn1) + (K - sum1) * row_mn1)
    ans = max(ans, sum1 * (K - row_mx1) + (K - sum1) * row_mx1)

print(ans)