#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Point;

const int maxn = 20000 + 10;

int n;
int tail;
int size[maxn], o[maxn];
int best[maxn];
vector<Point> e[maxn];
bool vis[maxn];
void dfs(int u, int pre, int cur, int *r) {
    o[++tail] = u;
    size[u] = 1;
    r[cur]++;
    best[u] = 0;
    for (vector<Point>::iterator i = e[u].begin(); i != e[u].end(); i++) 
        if ((*i).first != pre && !vis[ (*i).first ]) {
            dfs((*i).first, u, ((cur + (*i).second) % 3 + 3) % 3, r);
            size[u] += size[(*i).first];
            best[u] = max(best[u], size[ (*i).first ]);
        }
}

long long ans = 0;
void work(int u, int *r) {
    
    r[0] = r[1] = r[2] = 0;

    tail = -1;
    dfs(u, 0, 0, r);
    if (tail == 0) return ;

    for (int i = 0; i <= tail; i++) 
        best[ o[i] ] = max(best[ o[i] ], tail + 1 - best[ o[i] ]);
    int root = o[0];
    for (int i = 1; i <= tail; i++)
        if (best[ o[i] ] < best[root])
            root = o[i];

    int pre[3], cnt[3], tmp[3];
    pre[0] = 1; pre[1] = pre[2] = 0;
    
    vis[root] = true;
    for (vector<Point>::iterator i = e[root].begin(); i != e[root].end(); i++) 
        if (!vis[ (*i).first ]) {
            int t = ((*i).second % 3 + 3) % 3;
            work((*i).first, cnt);

            for (int j = 0; j < 3; j++) tmp[(j + t) % 3] = cnt[j];
            for (int j = 0; j < 3; j++) ans += tmp[j] * pre[(3 - j) % 3];
            for (int j = 0; j < 3; j++) pre[j] += tmp[j];
        }
}

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        e[u].push_back(Point(v, w));
        e[v].push_back(Point(u, w));
    }
    int cnt[3];
    work(1, cnt);
    long long down = n * n;
    ans = ans * 2 + n;

    cout << (ans / gcd(ans, down)) << '/' << (down / gcd(ans, down)) << endl;
    return 0;
}

