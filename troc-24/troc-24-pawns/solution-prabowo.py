MOD = 998244353
MAXN = 200000

fact, ifact = [1 for i in range(MAXN + 1)], [1 for i in range(MAXN + 1)]

def C(n, k):
    if k < 0 or k > n:
        return 0
    return fact[n] * ifact[k] * ifact[n - k] % MOD


def init():
    for i in range(1, MAXN + 1):
        fact[i] = fact[i - 1] * i % MOD

    ifact[MAXN] = pow(fact[MAXN], MOD - 2, MOD)
    for i in range(MAXN, 0, -1):
        ifact[i - 1] = ifact[i] * i % MOD


def solve(N, M):
    if N == 3:
        return M - 2

    if N % 2 == 0:
        return C(M, N) - C(M - N + 1, N) - C(M - N + 1, N // 2) - C(M - N - 1, N // 2 - 1)

    return C(M, N) - C(M - N + 1, N) - C(M - N, N // 2) * 2


def main():
    init()
    for _ in range(int(input())):
        print(solve(*[int(s) for s in input().split()]) % MOD)


if __name__ == '__main__':
    main()
