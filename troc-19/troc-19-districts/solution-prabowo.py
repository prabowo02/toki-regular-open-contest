from itertools import chain


class DSU:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, u):
        v = u
        while v != self.parent[v]:
            v = self.parent[v]
        while u != v:
            self.parent[u], u = v, self.parent[u]
        return v


def intersects(segments):
    currents = set()
    for x, t, i in sorted([(l, 1, i) for l, _, i in segments] + [(r, -1, i) for _, r, i in segments]):
        if t == -1:
            currents.remove(i)
        else:
            for j in currents:
                yield i, j
            currents.add(i)


def main():
    N = int(input())

    horizontalSegments, verticalSegments, areas = dict(), dict(), [0 for i in range(N)]
    for i in range(N):
        a, b, c, d = [int(s) for s in input().split()]
        horizontalSegments.setdefault(b, []).append((a, c, i))
        horizontalSegments.setdefault(d, []).append((a, c, i))
        verticalSegments.setdefault(a, []).append((b, d, i))
        verticalSegments.setdefault(c, []).append((b, d, i))
        areas[i] = (c - a) * (d - b)

    dsu, addedEdge, ans = DSU(N), 0, 0
    for u, v in sorted(chain(*[intersects(segments) for segments in horizontalSegments.values()],
                             *[intersects(segments) for segments in verticalSegments.values()]),
                       key=lambda edge: abs(areas[edge[0]] - areas[edge[1]])):
        if dsu.find(u) != dsu.find(v):
            dsu.parent[dsu.parent[u]], addedEdge, ans = dsu.parent[v], addedEdge + 1, ans + abs(areas[u] - areas[v])
            if addedEdge == N - 2:
                break

    print(ans if addedEdge == N - 2 else -1)


if __name__ == '__main__':
    main()
