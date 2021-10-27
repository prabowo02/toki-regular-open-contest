N, M = [int(s) for s in input().split()]
if N % 2 == 0 and M % 2 == 0:
    print(N * M // 4)
elif N % 2 == 0:
    print((M - 3) * N // 4 if M >= 3 else -1)
elif M % 2 == 0:
    print((N - 3) * M // 4 if N >= 3 else -1)
else:
    x = N * M - 3 * (N + M + 1)
    print(x // 4 if x >= 0 and x % 4 == 0 else -1)
