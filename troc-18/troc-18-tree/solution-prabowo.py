from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


class BIT:
    sums = []

    def __init__(self, n):
        self.sums = [0 for i in range(n)]

    def update(self, x, val):
        x += 1
        while x <= len(self.sums):
            self.sums[x - 1] ^= val
            x += x & -x

    def query(self, x):
        ret, x = 0, x + 1
        while x > 0:
            ret ^= self.sums[x - 1]
            x -= x & -x
        return ret


n = int(input())
adj = [[] for i in range(n)]
depth = [0 for i in range(n)]
order = [[-1, -1] for i in range(n)]
for i in range(1, n):
    u, v = [int(s) for s in input().split()]
    u, v = u - 1, v - 1
    adj[u].append(v)
    adj[v].append(u)


o = 0
@bootstrap
def dfs(u, p=-1):
    global o
    order[u] = [o, -1]
    for v in adj[u]:
        if v == p:
            continue
        depth[v] = depth[u] + 1
        yield dfs(v, u)
    o += 1
    order[u][1] = o
    yield


dfs(0)

bit = (BIT(n), BIT(n))
q = int(input())
for _ in range(q):
    op = input().split()
    if op[0] == '1':
        u, x = int(op[1]) - 1, int(op[2])
        bit[depth[u] & 1].update(order[u][0], x)
        bit[depth[u] & 1].update(order[u][1], x)
    elif op[0] == '2':
        u = int(op[1]) - 1
        print(bit[depth[u] & 1].query(order[u][1] - 1))
