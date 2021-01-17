N, X = [int(s) for s in input().split()]
A = [int(s) for s in input().split()]
MOD = 998244353

ans = 0
while A:
    for i in range(len(A) - 1):
        if A[i] > A[-1]:
            A[i], A[-1] = A[-1], A[i]

    bit = 1
    while bit * 2 <= A[-1]:
        bit <<= 1

    if bit * 2 <= X:
        break

    dp = [1, 0]
    for i in range(len(A) - 1):
        if A[i] < bit:
            dp[0] = dp[0] * (A[i] + 1) % MOD
            dp[1] = dp[1] * (A[i] + 1) % MOD
        else:
            dp[0], dp[1] = \
                (dp[0] * bit + dp[1] * (A[i] - bit + 1)) % MOD, \
                (dp[1] * bit + dp[0] * (A[i] - bit + 1)) % MOD

    ans += dp[X & bit > 0]
    X ^= bit
    A[-1] ^= bit
    if A[-1] == 0:
        A.pop()

ans += X == 0
print(ans % MOD)
