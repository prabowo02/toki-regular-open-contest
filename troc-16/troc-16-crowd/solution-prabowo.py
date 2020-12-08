n = int(input())

par, col, comp = [i for i in range(n)], [0 for i in range(n)], [[i] for i in range(n)]
def root(u):
    ucopy = u
    while u != par[u]:
       u = par[u]
    while ucopy != u:
        par[ucopy], ucopy = u, par[ucopy]
    return u


for w, u, v in sorted([(int(s), row, col) for row in range(n) for col, s in enumerate(input().split()) if row < col]):
    if root(u) == root(v):
        if col[u] == col[v]:
            print(w)
            exit(0)
    else:
        if col[u] == col[v]:
            for node in comp[par[v]]:
                col[node] ^= 1

        comp[par[u]].extend(comp[par[v]])
        par[par[v]] = par[u]
