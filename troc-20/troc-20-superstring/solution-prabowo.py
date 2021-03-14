MOD = 998244353
MODF = float(MOD)
ROOT = 3.0

MAGIC = 6755399441055744.0
SHRT = 65536.0

MODF_INV = 1.0 / MODF
SHRT_INV = 1.0 / SHRT

fround = lambda x: (x + MAGIC) - MAGIC
fmod = lambda a: a - MODF * fround(MODF_INV * a)
fmul = lambda a, b, c=0.0: fmod(fmod(a * SHRT) * fround(SHRT_INV * b) + a * (b - SHRT * fround(b * SHRT_INV)) + c)


def fpow(x, y):
    if y == 0:
        return 1.0

    res = 1.0
    while y > 1:
        if y & 1 == 1:
            res = fmul(res, x)
        x = fmul(x, x)
        y >>= 1

    return fmul(res, x)


def ntt(a, inv=False):
    n = len(a)
    w = [1.0] * (n >> 1)

    if (n >> 1) > 1:
        w[1] = fpow(ROOT, (MOD - 1) // n)
        if inv:
            w[1] = fpow(w[1], MOD - 2)

    for i in range(2, (n >> 1)):
        w[i] = fmul(w[i - 1], w[1])

    rev = [0] * n
    for i in range(n):
        rev[i] = rev[i >> 1] >> 1
        if i & 1 == 1:
            rev[i] |= n >> 1
        if i < rev[i]:
            a[i], a[rev[i]] = a[rev[i]], a[i]

    step = 2
    while step <= n:
        half, diff = step >> 1, n // step
        for i in range(0, n, step):
            pw = 0
            for j in range(i, i + half):
                v = fmul(w[pw], a[j + half])
                a[j + half] = a[j] - v
                a[j] += v
                pw += diff

        step <<= 1

    if inv:
        inv_n = fpow(n, MOD - 2)
        for i in range(n):
            a[i] = fmul(a[i], inv_n)


def ntt_conv(a, b):
    s = len(a) + len(b) - 1
    n = 1 << s.bit_length()

    a.extend([0.0] * (n - len(a)))
    b.extend([0.0] * (n - len(b)))

    ntt(a)
    ntt(b)

    for i in range(n):
        a[i] = fmul(a[i], b[i])

    ntt(a, True)
    del a[s:]


class Poly:
    a = []
    def __init__(self, a=[0]):
        self.a = a

    def __add__(self, p):
        q = Poly(self.a[:])
        if len(q.a) < len(p.a):
            q.a.extend([0 for _ in range(len(p.a) - len(q.a))])
        for i in range(len(p.a)):
            q.a[i] = (q.a[i] + p.a[i]) % MOD
        return q

    def __sub__(self, p):
        return self + Poly([(-x) % MOD for x in p.a])

    def __mul__(self, p):
        a = self.a[:]
        ntt_conv(a, p.a[:])
        return Poly([int(x) for x in a])

    def __invert__(self):
        n, length, res = len(self.a), 2, Poly([pow(self.a[0], MOD - 2, MOD)])
        self.a.extend([0 for _ in range(len(self.a))])
        while length < n << 1:
            tmp = res * res * Poly(self.a[:length])
            res.a.extend([0 for _ in range(len(res.a))])
            for i in range(len(res.a)):
                res.a[i] = (2 * res.a[i] - tmp.a[i]) % MOD
            length <<= 1
        res.a, self.a = res.a[:n], self.a[:n]
        return res

    def __pow__(self, n):
        ret = Poly(self.a[:])
        for _ in range(1, n):
            ret = ret * self
        return ret

    def __repr__(self):
        return self.a.__repr__();

def solve(n):
    odd_catalans, even_catalans, twos, odd_catalans2, even_catalans2, twos2 = [[0] * (n + 1) for _ in range(6)]

    fact = [1]
    for i in range(n): fact.append(fact[-1] * len(fact) % MOD)
    ifact = [0 for i in range(len(fact))]; ifact[-1] = pow(fact[-1], MOD - 2, MOD)
    for i in range(len(fact) - 2, -1, -1): ifact[i] = ((i + 1) * ifact[i + 1]) % MOD

    for i in range(1, n + 1, 2):
        odd_catalans[i] = fact[i-1] * ifact[i//2] * ifact[i//2 + 1] % MOD
        odd_catalans2[i] = odd_catalans[i] * (i//2 + 1) % MOD

    for i in range(2, n + 1, 2):
        even_catalans[i] = fact[i - 2] * ifact[i//2 - 1] * ifact[i//2] % MOD
        even_catalans2[i] = even_catalans[i] * (i//2) % MOD

    twos[0] = 1
    for i in range(1, n + 1):
        twos[i] = 2 * twos[i - 1] % MOD
    twos2 = [0] + twos[:-1]

    ans = (Poly(odd_catalans2) * ~(Poly([1]) - Poly(odd_catalans))**2 + Poly(even_catalans2) * Poly(twos) + Poly(twos2)) * ~(Poly([1, MOD - 1]) - Poly(even_catalans))
    return (n - ans.a[n] * pow(pow(2, n, MOD), MOD - 2, MOD)) % MOD


if __name__ == '__main__':
    print(solve(int(input())))