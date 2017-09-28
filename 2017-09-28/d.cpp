#include <iomanip>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#ifndef __DEBUG__
  #define debug NULL
#else
  #define debug printf("%s %d\n", __FUNCTION__, __LINE__);
#endif
#define Assert(cond, ...) \
  do { \
    if (!cond) { \
      printf("%d ", __LINE__); \
      printf(__VA_ARGS__); \
      assert(cond); \
    } \
  } while (0)
const int inf = 2147483647;
const int maxn = 500000 + 10;
typedef pair<int, int> Pair;

const int N = 4000000;
const double pi = 3.1415926535897932384626433832795;

struct Point {
	double x, y;
	Point (double a = 0, double b = 0) : x(a), y(b) {
	}
} x[N / 2], y[N / 2], z[N / 2], w[N];

char a[N/2],b[N/2];  
int sum[N]; 

Point operator + (const Point &a, const Point &b) {
	return Point(a.x + b.x, a.y + b.y);
}

Point operator - (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

Point operator * (const Point &a, const Point &b) {
	return Point(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

Point operator * (const Point &a, const double &x) {
    return Point(a.x * x, a.y * x);
}

Point operator ! (const Point &a) {
    return Point(a.x, -a.y);
}

void fft(Point *y, int bit, int on) {
  for (int i = 0, j = 0; i < (1 << bit); i++) {
      if (i > j) swap(y[i], y[j]);
      for (int l = (1 << bit - 1); (j ^= l) < l; l >>= 1);
  }

	int n = (1 << bit);
  w[0] = Point(1, 0);
	for (int s = 0; s < bit; s++) {
		int m = (1 << s) << 1, p = (1 << s);
		Point g = Point(cos(on * 2 * pi / m), sin(on * 2 * pi / m));
		for(int j = p; j >= 0; j -= 2) w[j] = w[j >> 1];
		for(int j = 1; j < p; j += 2) w[j] = w[j - 1] * g;

		for (int i = 0; i < n; i += m) {
            Point *a = &y[i], *b = &y[i + p];
			for (int j = 0; j < p; j++, a++, b++) {
				Point s = *b * w[j];
				*b = *a - s;
				*a = *a + s;
			}
		}
	}

	if (on == -1) 
		for (int i = 0; i < n; i++) y[i].x /= n, y[i].y /= n;
}

void calc(int *a, int n, int *b, int m, int *ans) {
	int bit = 0;
	while ((1 << bit) <= (n + m) >> 1) bit++;
  int k = (1 << bit);
  for (int i = 0; i < k; i++) x[i].x = x[i].y = y[i].x = y[i].y = 0;

	for (int i = 0; i <= n; i++)
		if (i & 1) x[i >> 1].y = a[i];
    else x[i >> 1].x = a[i];
	for (int i = 0; i <= m; i++)
    if (i & 1) y[i >> 1].y = b[i];
    else y[i >> 1].x = b[i];


  fft(x, bit, 1);
  fft(y, bit, 1);
	for(int i = 0; i < k; i++){
		int j = k - 1 & k - i;
		z[i] = (x[i] * y[i] * 4.0 - (x[i] - !x[j]) * (y[i] - !y[j]) * (((i & k >> 1)? Point(1, 0) - w[i ^ k >> 1] : w[i] + Point(1,0)))) * 0.25;
	}

  fft(z, bit, -1);
  for (int i = 0; i <= n + m; i++) 
      if (i & 1) ans[i] = (int)(z[i >> 1].y + 0.1);
      else ans[i] = (int)(z[i >> 1].x + 0.1);
}

int n;
vector<int> orie[maxn];
vector<Pair> e[maxn];
bool vis[maxn];
int size[maxn];
int tail;
int o[maxn], anc[maxn];
bool pre_edge[maxn];

void dfs(int u, int pre) {
  o[++tail] = u;
  anc[u] = pre; 

  size[u] = 1;
  for (vector<Pair>::iterator i = e[u].begin(); i != e[u].end(); i++) 
    if ((*i).first != pre && !vis[(*i).first]) {
      dfs((*i).first, u);
      size[u] += size[(*i).first];
      pre_edge[ (*i).first ] = (*i).second;
    }
}

int origin_n;
int upper;
int prime[maxn], primecnt, mu[maxn], phi[maxn];
bool notprime[maxn];
long long ans;
void Get(int u, int pre, int dep, int *r) {
  while (u <= origin_n && dep > upper) {
    upper++;
    r[upper] = 0;
  }

  if (u <= origin_n) r[dep]++;
  for (vector<Pair>::iterator i = e[u].begin(); i != e[u].end(); i++) 
    if ((*i).first != pre && !vis[(*i).first]) Get((*i).first, u, dep + (*i).second, r);
}

int A[4 * maxn], B[4 * maxn], C[4 * maxn];
int counter = 0;
void work(int u) {
  tail = -1;
  dfs(u, 0);
  if (tail == 0) return ;

  int root = o[1];
  for (int i = 2; i <= tail; i++) 
    if (max(size[ o[i] ], tail + 1 - size[ o[i] ]) < max(size[root], tail + 1 - size[root])) 
      root = o[i];
  int cache = anc[root];

  upper = -1;
  vis[cache] = true;
  Get(root, 0, 0, A);
  vis[cache] = false;
  int n = upper;

  upper = -1;
  vis[root] = true;
  Get(cache, 0, 0, B);
  vis[root] = false;
  int m = upper;

  //cout << root << ' ' << cache << endl;
  //for (int i = 0; i <= n; i++) cout << A[i] << ' ';
  //cout << endl;
  //for (int i = 0; i <= m; i++) cout << B[i] << ' ';
  //cout << endl;
  calc(A, n, B, m, C);
  for (int i = 1; i <= n + m; i++) 
    if (!notprime[i + pre_edge[root]]) {ans += C[i];}

  //cout << pre_edge[root] << endl;
  //for (int i = 0; i <= n + m; i++) cout << C[i] << ' ';
  //cout << endl;
  //cout << ans << endl;
  //cout << endl;

  vis[cache] = true;
  work(root);
  vis[cache] = false;

  vis[root] = true;
  work(cache);
  vis[root] = false;
}

void sieve() {
  mu[1] = phi[1] = 1;
  for (int i = 2; i < maxn; i++) {
    if (!notprime[i]) prime[primecnt++] = i, mu[i] = -1, phi[i] = i - 1;
    for (int j = 0; prime[j] * i < maxn; j++) {
      notprime[ prime[j] * i ] = true;
      if (i % prime[j] == 0)
        break;
    }
  }
} 

void construct(int u, int x, int y) {
  if (x > y) return ;
  if (x == y) {
    e[u].push_back(Pair(o[x], 1));
    e[ o[x] ].push_back(Pair(u, 1));
    return ;
  }


  int mid = (x + y) >> 1;
  if (x == mid) {
    e[u].push_back(Pair(o[x], 1));
    e[o[x]].push_back(Pair(u, 1));
  }
  else {
    n++;
    e[u].push_back(Pair(n, 0));
    e[n].push_back(Pair(u, 0));
    construct(n, x, mid);
  }

  //cout << u << ' ' << x << ' ' << y << ' ' << mid + 1 << endl;

  if (mid + 1 == y) {
    e[u].push_back(Pair(o[y], 1));
    e[o[y]].push_back(Pair(u, 1));
  }
  else {
    n++;
    e[u].push_back(Pair(n, 0));
    e[n].push_back(Pair(u, 0));
    construct(n, mid + 1, y);
  }
}
void rebuild(int u, int pre) {
  int tail = -1;
  for (vector<int>::iterator i = orie[u].begin(); i != orie[u].end(); i++) 
    if ((*i) != pre) o[++tail] = (*i);
  construct(u, 0, tail);
  for (vector<int>::iterator i = orie[u].begin(); i != orie[u].end(); i++) 
    if ((*i) != pre) rebuild((*i), u);
}

int main(int argc, char **argv) {
  sieve();
  scanf("%d", &n);
  for (int i = 1, u, v; i < n; i++) {
    scanf("%d%d", &u, &v);
    orie[u].push_back(v);
    orie[v].push_back(u);
  }
  notprime[1] = true;
  
  origin_n = n;
  long long down = 1LL * n * (n - 1) / 2;
  rebuild(1, 0);
  work(1);
  printf("%.12lf\n", 1.0 * ans / down);
  return 0;
}
