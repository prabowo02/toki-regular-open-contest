## G. Toko Roti

### Author: Daniel C.M.

### Deskripsi

Pada hari kasih sayang, Daniel ingin membeli sebuah kue untuk orang yang disukainya di sebuah toko kue. Toko tersebut memiliki antrian $N$ pelanggan, berbaris dari pelanggan $1$ di depan sampai pelanggan $N$ di belakang. Waktu memanggang pelanggan $i$ adalah $T_i$, artinya roti dari pelanggan $i$ memerlukan $T_i$ menit untuk dipanggang di oven. 

Untuk memperpendek waktu menunggu, Daniel mengusulkan untuk mengelompokkan pelanggan ke dalam $k$ kelompok, sehingga semua roti dari suatu kelompok bisa dipanggang sekaligus. Kelompok-kelompok dibentuk dengan memilih $k$ bilangan $x_1$, $x_2$, $\ldots$, $x_k$ ($1 \le x_1 < x_2 < \ldots < x_k = N$), sehingga pelanggan $1$ sampai $x_1$ berada pada kelompok $1$, pelanggan $x_1 + 1$ sampai $x_2$ berada pada kelompok $2$, dan seterusnya, hingga pelanggan $x_{k-1} + 1$ sampai $x_k$ berada pada kelompok $k$.

Waktu memanggang dari suatu kelompok adalah waktu memanggang maksimum dari semua pelanggan di kelompok tersebut. Waktu menunggu sebuah kelompok adalah jumlah dari waktu memanggang semua kelompok di depannya ditambah waktu memanggang kelompok itu sendiri. Waktu menunggu seorang pelanggan adalah waktu menunggu dari kelompok tempat ia berada.

Daniel ingin meminimalkan jumlah total dari semua waktu menunggu pelanggan. Namun ia hanya bisa mengelompokkan pelanggan ke dalam **paling banyak** $K$ kelompok. Cari total waktu menunggu minimumnya.

### Batasan

- $1 ≤ K ≤ N ≤ 200\,000$.
- $1 ≤ T_i ≤ 10^9$.

### Masukan

<pre>
N K
T<sub>1</sub> T<sub>2</sub> ... T<sub>N</sub>
</pre>

### Keluaran

Sebuah baris yang berisi total waktu menunggu minimum.

### Contoh Masukan 1

```
5 5
1 3 2 6 3
```

### Contoh Keluaran 1

```
27
```

### Contoh Masukan 2

```
7 1
1 1 2 2 2 2 2
```

### Contoh Keluaran 2

```
14
```

### Penjelasan

Pada contoh pertama, pelanggan dikelompokkan ke dalam $2$ kelompok. Kelompok $1$ terdiri dari pelanggan $1$, $2$, dan $3$, dan kelompok $2$ terdiri dari pelanggan $4$ dan $5$.

Waktu menunggu dari kelompok $1$ adalah $\max(1, 3, 2) = 3$, dan waktu menunggu dari kelompok $2$ adalah $3 + \max(6, 3) = 9$. Sehingga total waktu menunggu adalah $3 + 3 + 3 + 9 + 9 = 27$. Tidak terdapat cara lain untuk membuat total waktu menunggu lebih singkat.

Pada contoh kedua, Daniel hanya bisa mengelompokkan semua pelanggan ke dalam satu kelompok, dan waktu menunggu masing-masing pelanggan adalah $2$ dengan total waktu menunggu $14$.
