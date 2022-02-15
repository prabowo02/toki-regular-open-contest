## G. Bakery

### Author: Daniel C.M.

### Description

On valentine's day, Daniel wants to buy a cake for his crush in a bakery. This bakery has a queue of $N$ customers, lined from customer $1$ at the front to customer $N$ at the back. The bake time of customer $i$ is $T_i$, meaning the bread of customer $i$ requires $T_i$ minutes to bake in the oven.

To shorten the waiting time, Daniel proposes to group the customers into $k$ groups, so all the bread from a group can be baked at once. The groups are formed by choosing $k$ integers $x_1$, $x_2$, $\ldots$, $x_k$ ($1 \le x_1 < x_2 < \ldots < x_k = N$), such that customer $1$ to $x_1$ belong to group $1$, customer $x_1 + 1$ to $x_2$ belong to group $2$, and so on, until customer $x_{k-1} + 1$ to $x_k$ belong to group $k$.

The bake time of a group is the maximum bake time of all the customers in the group. The waiting time of a group is the sum of all the bake times of the groups in front of it plus the bake time of the group itself. The waiting time of a customer is the waiting time of the group it belongs to.

Daniel wants to minimize the total sum of all the customer waiting times. However, he can only group the customers into **at most** $K$ groups. Find the minimum total waiting time.

### Constraints

- $1 ≤ K ≤ N ≤ 200\,000$.
- $1 ≤ T_i ≤ 10^9$.

### Input

<pre>
N K
T<sub>1</sub> T<sub>2</sub> ... T<sub>N</sub>
</pre>

### Output

An integer consisting the minimum total waiting time.

### Sample Input 1

```
5 5
1 3 2 6 3
```

### Sample Output 1

```
27
```

### Sample Input 2

```
7 1
1 1 2 2 2 2 2
```

### Sample Output 2

```
14
```

### Explanation

In the first sample, the customers are grouped into $2$ groups. Group $1$ consists of customer $1$, $2$, and $3$, and group $2$ consists of customer $4$ and $5$.

The waiting time of group $1$ is $\max(1, 3, 2) = 3$, and the waiting time of group $2$ is $3 + \max(6, 3) = 9$. Hence, the total waiting time is $3 + 3 + 3 + 9 + 9 = 27$. There is no other way to make the total waiting time shorter.

In the second sample, Daniel can only group all the customers into a single group, and the waiting time of each customer is $2$ with a total waiting time of $14$.
