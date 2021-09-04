import __pypy__

int_add = __pypy__.intop.int_add
int_sub = __pypy__.intop.int_sub
int_mul = __pypy__.intop.int_mul

MOD = 998244353


def make_mod_mul(mod=MOD):
    fmod_inv = 1.0 / mod

    def mod_mul(a, b, c=0):
        res = int_sub(int_add(int_mul(a, b), c), int_mul(
            mod, int(fmod_inv * a * b + fmod_inv * c)))
        if res >= mod:
            return res - mod
        elif res < 0:
            return res + mod
        else:
            return res

    return mod_mul


mul = make_mod_mul()

N = int(input())
K = 2
P = [0] + [int(x) for x in input().split()]
for i in range(N):
    P[i] = int_sub(P[i], 1)


def id(i, u, x, y):
    return int_add(int_mul(i, int_mul(N, int_mul(N, 2))), int_add(int_mul(u, int_mul(N, 2)), int_add(int_mul(x, 2), y)))


def add(x, y):
    x = int_add(x, y)
    if x >= MOD:
        x = int_sub(x, MOD)
    return x


def solve():
    adj = [[] for i in range(N)]
    for i in range(1, N):
        adj[P[i]].append(i)
    choose = [[0 for i in range(K + 1)] for j in range(K + 1)]
    for i in range(K + 1):
        choose[i][0] = 1
        for j in range(1, i + 1):
            choose[i][j] = add(choose[i - 1][j - 1], choose[i - 1][j])
    dp = [0 for i in range((K + 1) * N * N * 2)]
    for u in reversed(range(N)):
        all_g = [0 for i in range(K + 1)]
        all_b = [0 for i in range(K + 1)]
        cur_g = [0 for i in range(K + 1)]
        cur_b = [0 for i in range(K + 1)]
        for x in reversed(range(N)):
            for y in range(2):
                if x == 0:
                    for i in range(K + 1):
                        dp[id(i, u, x, y)] = dp[id(i, u, 1, y)]
                    continue
                all_g[0] = 1
                all_b[0] = int(y == 0)
                for i in range(1, K + 1):
                    all_g[i] = mul(all_g[i - 1], x)
                    if y == 0:
                        all_b[i] = all_g[i]
                    else:
                        all_b[i] = 0
                for v in adj[u]:
                    for i in range(K + 1):
                        cur_g[i] = 0
                        cur_b[i] = 0
                        cur_g[i] = dp[id(i, v, x, int(x == 0))]
                        if y == 0:
                            cur_b[i] = dp[id(i, v, x, int(x == 0))]
                        if x > 0:
                            cur_g[i] = add(
                                cur_g[i], dp[id(i, v, x - 1, int(x - 1 == 0))])
                        if x + 1 < N:
                            cur_g[i] = add(cur_g[i], dp[id(i, v, x + 1, 1)])
                            if y == 0:
                                cur_b[i] = add(
                                    cur_b[i], dp[id(i, v, x + 1, 1)])
                    for i in reversed(range(K + 1)):
                        new_g = 0
                        new_b = 0
                        for j in range(i + 1):
                            new_g = add(new_g, mul(
                                int_mul(choose[i][j], all_g[j]), cur_g[i - j]))
                            new_b = add(new_b, mul(
                                int_mul(choose[i][j], all_b[j]), cur_b[i - j]))
                        all_g[i] = new_g
                        all_b[i] = new_b
                for i in range(K + 1):
                    dp[id(i, u, x, y)] = add(all_g[i], int_sub(MOD, all_b[i]))
    ans = 1
    for i in range(K):
        ans = mul(ans, int_sub(MOD, N))
    for i in range(1, N):
        ans = add(ans, dp[id(K, 0, i, int(i == 0))])
    ans = add(ans, ans)
    return ans


print(solve())
