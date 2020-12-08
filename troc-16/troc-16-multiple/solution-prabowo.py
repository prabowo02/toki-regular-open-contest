MAXA = 10**5 + 1
MOD = 10**9 + 7


def get_largest_prime_divisors(N):
    prime_divisors = [1 for i in range(N)]
    for i in range(2, N):
        if prime_divisors[i] != 1:
            continue

        for j in range(i, N, i):
            prime_divisors[j] = i

    return prime_divisors


def main():
    n = int(input())
    a = [int(s) for s in input().split()]
    
    prime_divisors = get_largest_prime_divisors(MAXA)
    prime_power_locations = [[] for _ in range(MAXA)]

    for i, num in enumerate(a):
        while num > 1:
            p, pe = prime_divisors[num], 1
            while True:
                num, pe = num // p, pe * p
                prime_power_locations[pe].append(i)
                if num % p != 0:
                    break

    ans = 1
    for p in range(2, MAXA):
        if prime_divisors[p] != p:
            continue

        pe, cnt = p, 0
        while pe < MAXA:
            cnt += n * (n + 1) // 2
            lst = -1
            for loc in prime_power_locations[pe]:
                cnt -= (loc - lst) * (loc - lst - 1) // 2
                lst = loc
            cnt -= (n - lst) * (n - lst - 1) // 2
            pe *= p

        ans = ans * pow(p, cnt, MOD) % MOD

    print(ans)


if __name__ == '__main__':
    main()
