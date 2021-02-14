MOD = 998244353

n, m, a, b, c = [int(s) for s in input().split()]


def memoize(func):
    memo = dict()
    def wrapper(*args):
        if args not in memo:
            memo[args] = func(*args)
        return memo[args]
    return wrapper


@memoize
def C(n, k):
    if k == 0 or k == n:
        return 1
    return (C(n - 1, k - 1) + C(n - 1, k)) % MOD


@memoize
def power(n, k):
    if k == 0:
        return 1
    return n * power(n, k - 1) % MOD


@memoize
def count(n, m):
    return pow(n * (n + 1) // 2, m, MOD)


@memoize
def countCc(n, m):
    ret = count(n, m)
    for i in range(1, n):
        for j in range(i - 1, m + 1):
            ret -= countCc(i, j) * count(n - i, m - j) * C(n - 1, i - 1) * C(m, j)
    return ret % MOD


@memoize
def count2Edge(n, m):
    ret = countCc(n, m)
    for i in range(1, n):
        for j in range(m + 1):
            for k in range(1, n - i + 1):
                ret -= count2Edge(i, j) * countCcs(k, False, n - i, m - j) * C(n - 1, i - 1) * C(m, j) * power(i, k)
    return ret % MOD


@memoize
def countCcs(num, nopar, n, m):
    if num == 0:
        if nopar:
            return count(n, m)
        return 1 if n == 0 and m == 0 else 0
    ret = 0
    for i in range(1, n + 1):
        for j in range(m + 1):
            if j < m:
                ret += countCc(i, j) * countCcs(num - 1, nopar, n - i, m - j - 1) * C(n - 1, i - 1) * C(m, j) * (m - j) * i
            if nopar:
                ret += count(i, j) * countCcs(num, False, n - i, m - j) * C(n - 1, i - 1) * C(m, j)
    return ret % MOD


@memoize
def count2Cc(n, m):
    ret = 0
    for i in range(1, n):
        for j in range(i - 1, m + 1):
            ret += countCc(i, j) * countCc(n - i, m - j) * C(n - 1, i - 1) * C(m, j) * i * (n - i)
    return ret % MOD


@memoize
def solve(n, m):
    ret = c * m * power(n * (n + 1) // 2, m)
    for edge in range(m):
        for i in range(2, n + 1):
            for j in range(i - 2, edge + 1):
                ret += count2Cc(i, j) * count(n - i, edge - j) * C(n, i) * C(edge, j) * (a - c) * power(n * (n + 1) // 2, m - edge - 1)

    for edge in range(m):
        for i in range(1, n + 1):
            for j in range(edge + 1):
                for k in range(n - i + 1):
                    ret += count2Edge(i, j) * countCcs(k, True, n - i, edge - j) * C(n, i) * C(edge, j) * power(i, k) * i * (i + 1) // 2 * (b - c) * power(n * (n + 1) // 2, m - edge - 1)
    return ret % MOD


print(solve(n, m) * pow(pow(n * (n + 1) // 2, m, MOD), -1, MOD) % MOD)
