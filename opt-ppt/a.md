---
customTheme: acesrc
---

Cache Friendly

```cpp
for (int i = 0; i < maxn; i++) 
  for (int j = 0; j < maxn; j++) 
    for (int k = 0; k < maxn; k++) 
      a[i][j][k] <<= 1;
```

```cpp
for (int i = 0; i < maxn; i++) 
  for (int j = 0; j < maxn; j++) 
    for (int k = 0; k < maxn; k++) 
      a[k][j][i] <<= 1;
```

---

Vector  iterator

---

Cpu Concurrence

```cpp
for (int inx = 0; inx < times; inx++)
  for (long long i = 0; i < up; i++) {
    a[0]++; a[0]++;
  }
```

```cpp
for (int inx = 0; inx < times; inx++)
  for (long long i = 0; i < up; i++) {
    a[0]++; a[1]++;
  }
```

---

Interesting Cpu instruction

```cpp
int a = A / B;
int b = A % B;
int c = a + b;
```

```cpp
int c = A / B + A % B;
```

---

list vs vector

---

helpful memset/memcpy

---

if-else vs switch