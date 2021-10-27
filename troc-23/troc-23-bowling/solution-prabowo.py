K = int(input())


ls = []
def add_edge(u, l, r):
    if r < l:
        return
    ls.append((u + 1, l + 1, r + 1))


def add_cc(K, N):
    k, n = 0, 0

    while (n + 1) * (n * (n - 1) * (n - 2) // 6) <= K:
        add_edge(N + n, N, N + n - 1)
        n += 1

    k = n * (n - 1) * (n - 2) * (n - 3) // 6
    
    for i in range(n, 0, -1):
        while k + i * (i - 1) * (i - 2) // 6 + i * (n - 1) * (n - 2) // 2 <= K:
            add_edge(N + n, N, N + i - 1)
            k += i * (i - 1) * (i - 2) // 6 + i * (n - 1) * (n - 2) // 2
            n += 1

    return k, n


N = 0
while K > 0:
    k, n = add_cc(K, N)
    K -= k
    N += n


print(len(ls))
for row in ls:
    print(*row)
