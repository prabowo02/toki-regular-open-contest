N, K = map(int, input().split())
if N >= K:
  print(2**(N-K) * K)
else:
  print(N)