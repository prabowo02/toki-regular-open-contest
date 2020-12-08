n = int(input())
print(1 if n == 0 else 0 if n == 1 else '4' * (n & 1) + '8' * (n // 2))
