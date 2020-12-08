n = int(input())
a = [int(s) for s in input().split()]
sum = 0
for num in a:
    sum ^= num

print(max([num | (sum ^ num) | (1 << len(bin(num & (sum ^ num))) - 3) - 1 for num in a]))
