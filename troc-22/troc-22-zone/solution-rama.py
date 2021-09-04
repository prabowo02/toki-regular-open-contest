import sys
import heapq

N, M = [int(x) for x in sys.stdin.readline().split()]
adj = [[] for _ in range(N)]

for _ in range(M):
    u, v, w = [int(x) for x in sys.stdin.readline().split()]
    u -= 1
    v -= 1
    adj[u].append((v, w))
    adj[v].append((u, w))

K = int(sys.stdin.readline())
P = []
for _ in range(K):
    p, a = [int(x) for x in sys.stdin.readline().split()]
    p -= 1
    P.append((p, a))


def solve(L):
    dist = [int(2e9)] * N
    queue = []
    for i in range(0, L):
        dist[i] = 0
        heapq.heappush(queue, (0, i))

    while queue:
        path_len, u = heapq.heappop(queue)
        if path_len == dist[u]:
            for v, w in adj[u]:
                if w + path_len < dist[v]:
                    dist[v] = w + path_len
                    heapq.heappush(queue, (w + path_len, v))

    res = -1
    for i in range(K):
        p, a = P[i]
        if dist[p] > a:
            res = max(res, i)
    return res


lo, hi = 0, N - 1
while lo < hi:
    md = (lo + hi + 1) // 2
    if solve(md) != -1:
        lo = md
    else:
        hi = md - 1

print(solve(lo) + 1)
