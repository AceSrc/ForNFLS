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
      printf("\33[4;31mLINE NUMBER:\33[0m %d \n", __LINE__); \
      printf(__VA_ARGS__); \
      assert(cond); \
    } \
  } while (0)
const int inf = 2147483647;
const int maxn = 1200000 + 10;

int e_nxt[maxn], e_head[maxn], e_v[maxn], e_N;
bool vis[maxn];
void insert(int x, int y, int *e_nxt, int *e_v, int *e_head, int &N) {
  assert(x);
  assert(y);

  e_nxt[N] = e_head[x];
  e_v[N] = y;
  e_head[x] = N;
  N++;
}

void init_edge(int n) {
  memset(e_head, -1, sizeof(int) * (n + 1));
  e_N = 0;
}

int n, m, S, T;
int need_in_cnt, need_out_cnt;
int out_deg[maxn], in_deg[maxn];
int need_out[maxn], need_in[maxn];

int my_stack[maxn], stack_tail;
int ptr[maxn];
bool in_stack[maxn];
int output_list[maxn];
int o[maxn];
void output(int u) {
  int tail = 0;
  int ans_tail = -1;
  o[tail] = u;
  while (tail >= 0) {
    int u = o[tail];
    //cout << u << ' ' << ptr[u] << endl;
    while (ptr[u] != -1 && vis[ ptr[u] ]) ptr[u] = e_nxt[ ptr[u] ];
    //cout << u << ' ' << nxt << ' ' << ptr[u] << endl;
    if (ptr[u] == -1) {
      tail--;
      output_list[++ans_tail] = u;
      continue;
    }
    int nxt = e_v[ ptr[u] ];
    //cout << u << ' ' << nxt << endl;
    vis[ ptr[u] ^ 1 ] = true;
    vis[ ptr[u] ] = true;

    ptr[u] = e_nxt[ ptr[u] ];
    while (ptr[u] != -1 && vis[ ptr[u] ]) ptr[u] = e_nxt[ ptr[u] ];
    //cout << u << ' ' << nxt << ' ' << ptr[u] << endl;
    o[++tail] = nxt;
  }
}

char ch;
void get(int &x) {
  x = 0;
  for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
  for ( ; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

int main(int argc, char **argv) {
  int t;
  for (t = 1; t <= 1; t++) {
    get(n); get(m);
    init_edge(n);
    memset(out_deg, 0, sizeof(int) * (n + 1));
    memset(in_deg, 0, sizeof(int) * (n + 1));

    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      insert(u, v, e_nxt, e_v, e_head, e_N);
      insert(v, u, e_nxt, e_v, e_head, e_N);
      in_deg[v]++;
      in_deg[u]++;
    }

    int S = 1;
    for (int i = 1; i <= n; i++) {
      if (in_deg[i] & 1) S = i;
      ptr[i] = e_head[i];
    }

    output(S);
    for (int i = m; i >= 0; i--) printf("%d ", output_list[i]);
    puts("");
  }
  return 0;
}
