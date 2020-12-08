n, m = input().split()
[print(('B' if i & 1 else 'W') * int(m)) for i in range(int(n))]
