N, K = map(int, input().split())
print(K * 2**(N - K) if N > K else N)
