---
title: Network Flow
---

## 普通网络流

在不考虑指向源点的边的情况下， 根据网络流的要求可以知道， 最大流问题实际上求解的是下面一组线性方程组。

$$
\begin{align}
  & 0 \le f(u, v) \le c(u, v) \\
  & \forall u \in V - \{S, T\},  \sum_{v \in V} f(v, u) = \sum_{v \in V} f(u, v)
\end{align}
$$

$$
  maximize : W = \sum_{v \in V} f(S, v) = \sum_{u \in V} f(u, T)
$$


## 最小割

相应的， 最小割问题实际上是一个染色问题， 形如一个线性方程组。

$$
\begin{align}
  & \forall u, \chi_u \in \{ 0, 1 \} \\
  & \chi_S = 0 \\
  & \chi_T = 1
\end{align}
$$

$$
  minimize : W = \sum_{u, v \in V} max(\chi_v - \chi_u, 0) c_{u, v}
$$

## 循环流

循环流问题就是在一个有流量限制的图中， 寻找一个可行流满足：

$$
\begin{align}
  & l(u, v) \le f(u, v) \le c(u, v) \\
  & \forall u,  \sum_{v \in V} f(v, u) = \sum_{v \in V} f(u, v)
\end{align}
$$

添加两个点 $S, T$. 
令 $g(u, v) = f(u, v) - l(u, v)$ 相应的转化为, $c(S, u) = \sum_{v \in V} l(v, u), c(u, T) = \sum_{v \in V} l(u, v)$

$$
\begin{align}
  l(u, v) \le f(u, v) \le c(u, v) &\to 0 \le g(u, v) \le c(u, v) - l(u, v) \\
  \forall u, \sum_{v \in V} f(v, u) = \sum_{v \in V} f(u, v) &\to 
  \forall u, \sum_{v \in V} g(v, u) + c(S, u) = \sum_{v \in V} g(u, v) + c(u, T) 
\end{align}
$$

对下面一个网络流模型求解。 

$$
\begin{align}
  &0 \le g(u, v) \le c(u, v) - l(u, v) \\
  &\forall u, \sum_{v \in V} g(v, u) + g(S, u) = \sum_{v \in V} g(u, v) + g(u, T) \\
  &maximize : \sum_{v \in V} g(S, v)
\end{align}
$$

有解的情况就是 $g(S, u) = c(S, u), g(u, T) = c(u, T)$, 即满流。

这应该比较容易看出来。 
必要性. 如果原循环流有解， 那么直接在原循环流的解中让 $g(S, u) = c(S, u), g(u, T) = c(u, T)$ 就找到了网络流模型的一个解， 由于 $g(S, u) \le c(S, u), g(u, T) \le c(u, T)$, 所以这个解是最大流。 

充分性. 如果找到了一个最大流， 使得 $\sum_{v \in V} g(S, v) = \sum_{v \in V} c(S, v)$, 这时候就有 $g(S, v) = c(S, v)$, 对汇点也是一样的。 将这个流带回去就是一个循环流的可行解。 

