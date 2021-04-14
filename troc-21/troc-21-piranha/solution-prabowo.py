N = int(input())
A = [int(s) for s in input().split()]

cnt = [0 for i in range(max(A))]
for a in A:
    cnt[a - 2] += 1

for i in range(2, len(cnt)):
    cnt[i] += min(cnt[i - 1], cnt[i - 2])

print(cnt[-1])
