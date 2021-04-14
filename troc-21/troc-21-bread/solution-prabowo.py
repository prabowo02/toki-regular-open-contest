class DSU:
    def __init__(self, n):
        self.par = [i for i in range(n)]

    def find(self, u):
        v = u
        while v != self.par[v]:
            v = self.par[v]
        while u != v:
            self.par[u], u = v, self.par[u]
        return u

N = int(input())
A, P = zip(*[input().split() for _ in range(N)])

lft, rgt, ans = DSU(N), DSU(N), [None for _ in range(N)]

for i, (a, p) in enumerate(zip(A[::-1], P[::-1])):
    a = int(a) - 1
    u = (lft.find(a) if p == '0' else rgt.find(a))
    lft.par[u], rgt.par[u] = (u - 1) % N, (u + 1) % N
    ans[i] = (a - u) % N if p == '0' else (u - a) % N

print(*ans[::-1])
