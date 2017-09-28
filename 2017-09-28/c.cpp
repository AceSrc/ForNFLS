#include <iostream>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
#ifndef __DEBUG__
  #define debug NULL
#else
  #define debug printf("%s %d\n", __FUNCTION__, __LINE__);
#endif
const int inf = 2147483647;
const int MAX_SIZE = 100000000;
char buf[MAX_SIZE];

int p;

namespace Network {
  const int maxn = 1000002;
  const int maxm = 8000002;

  struct Point {
    int v, f, rev;
    Point(int v = 0, int f = 0, int rev = 0): v(v), f(f), rev(rev) {
    }
  };

  vector<Point> e[maxn];

  void insert(int x, int y, int c) {
    e[x].push_back(Point(y, c, e[y].size()));
    e[y].push_back(Point(x, 0, e[x].size() - 1));
  }

  int st, ed, n;
  int o[maxn], dis[maxn];

  void init(int S, int T, int _n) {
    st = S; ed = T; n = _n;
    for (int i = 0; i <= n; i++) vector<Point>().swap(e[i]);
  }

  bool bfs() {
    Point tmp;
    memset(dis, -1, (n + 1) * sizeof(dis[0]));
    o[0] = st; dis[st] = 0;
    for (int h = 0, t = 0; h <= t; h++) {
      int u = o[h];
      for (int i = e[u].size() - 1; i >= 0; i--) {
        tmp = e[u][i];
        if (tmp.f > 0 && dis[ tmp.v ] == -1) {
          o[++t] = tmp.v;
          dis[ tmp.v ] = dis[u] + 1;
          if (tmp.v == ed) return true;
        }
      }
    }
    return false;
  }

  int cnt = 0;
  int dfs(int u, int limit) {
    //cout << u << ' ' << limit << endl;
    //cnt++;
    if (u == ed) return limit;
    int rt = 0;
    Point tmp;
    for (int i = e[u].size() - 1; i >= 0; i--) {
      tmp = e[u][i];
      if (dis[tmp.v] != -1 && dis[tmp.v ] == dis[u] + 1 && tmp.f > 0) {
        int o = dfs(tmp.v, min(tmp.f, limit - rt));
        if (o) {
          e[u][i].f -= o;
          e[tmp.v][ e[u][i].rev ].f += o;
          rt += o;
          if (rt == limit) return rt;
        }
      }    
    }
    dis[u] = -3;
    return rt;
  }

  int maxFlow() {
    int ans = 0;
     while (true) {
      if (!bfs()) break;
      ans += dfs(st, inf);
    }
    return ans;
  }
};

int main() {
  int cases;
  scanf("%d", &cases);
  while (cases--) {
    int n, m, s, t, a, b, c;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    Network::init(s, t, n);
    for (int i = 0; i < m; i++) {
      scanf("%d%d%d", &a, &b, &c);
      Network::insert(a, b, c * (m + 1) + 1);
    }
    cout << Network::maxFlow() % (m + 1) << endl;
  }
  return 0;
}
