N, K = [int(s) for s in input().split()]
S = [int(c) for c in input()]

def inv(S):
    cnt, ret = 0, 0
    for s in S:
        if s == 1:
            cnt += 1
        else:
            ret += cnt
    return ret

ans = N * N
for i in range(K + 1):
    flip0, flip1, T = i, K - i, [s for s in S]
    for j, t in enumerate(T):
        if t == 1 and flip1 > 0:
            T[j], flip1 = 0, flip1 - 1
    for j, t in enumerate(T[::-1]):
        if t == 0 and flip0 > 0:
            T[-j-1], flip0 = 1, flip0 - 1
    ans = min(ans, inv(T))
print(ans)
