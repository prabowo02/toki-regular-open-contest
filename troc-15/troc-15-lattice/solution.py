N = int(input())
cnt = [0 for i in range(N*N*2 + 1)]
for i in range(N + 1):
  for j in range(1, N + 1):
    cnt[i*i + j*j] += 1

for i in range(N, 0, -1):
  if cnt[i*i] == 3:
    print(i)
    exit(0)

print(-1)
