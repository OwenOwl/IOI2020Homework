#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

namespace flow {
  const int maxn = 600006;
  const int INF = (int)1e9;
  int e_num = 1, S, T;
  int hed[maxn], dep[maxn];
  struct Edge {
    int from, to, nxt, c;
  } edge[maxn * 4];
  void addedge(int from, int to, int c) {
    edge[++e_num] = (Edge){from, to, hed[from], c};
    hed[from] = e_num;
  }
  void adde(int from, int to, int c) {
    addedge(from, to, c);
    addedge(to, from, 0);
  }
  int que[maxn + 5], head = 0, tail = 0;
  bool bfs() {
    head = tail = 0;
    que[tail++] = S;
    for (int i = 0; i <= T; i++) {
      dep[i] = 0;
    }
    dep[T + 1] = dep[T + 2] = -1;
    dep[S] = 1;
    while (head != tail) {
      int cur = que[head++]; head %= maxn;
      for (int i = hed[cur]; i; i = edge[i].nxt) {
        int to = edge[i].to;
        if (!dep[to] && edge[i].c) {
          dep[to] = dep[cur] + 1;
          que[tail++] = to; tail %= maxn;
        }
      }
    }
    return dep[T];
  }
  int hed2[maxn];
  int dfs(int x, int flow) {
    if (x == T) return flow;
    int ret = 0;
    for (int &i = hed2[x]; i; i = edge[i].nxt) {
      int to = edge[i].to;
      if (dep[to] == dep[x] + 1 && edge[i].c) {
        int tmp = dfs(to, min(flow, edge[i].c));
        edge[i].c -= tmp;
        edge[i ^ 1].c += tmp;
        flow -= tmp;
        ret += tmp;
        if (!flow) {
          break;
        }
      }
    }
    if (!ret) dep[x] = 0;
    return ret;
  }
  int dinic() {
    int ret = 0;
    while (bfs()) {
      memcpy(hed2, hed, sizeof hed);
      ret += dfs(S, INF);
    }
    return ret;
  }
}

const int N = 100233;
int n, m, r, b;
int x[N], y[N], unix[N], uniy[N], cx, cy, bx[N], by[N], nx[N], ny[N], edd[N];
int addon = 0;
void add2(int x, int y, int l, int r) {
  if (r - l) {
    flow::adde(x, y, r - l);
  }
  if (l) {
    flow::adde(flow::S, y, l);
    flow::adde(x, flow::T, l);
    addon += l;
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m, &r, &b);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &x[i], &y[i]);
    unix[i] = x[i];
    uniy[i] = y[i];
  }
  sort(unix + 1, unix + 1 + n);
  sort(uniy + 1, uniy + 1 + n);
  cx = (int) (unique(unix + 1, unix + 1 + n) - unix - 1);
  cy = (int) (unique(uniy + 1, uniy + 1 + n) - uniy - 1);
  for (int i = 1; i <= cx; i++) bx[i] = n;
  for (int i = 1; i <= cy; i++) by[i] = n;
  for (int i = 1; i <= n; i++) {
    x[i] = (int) (lower_bound(unix + 1, unix + 1 + cx, x[i]) - unix);
    y[i] = (int) (lower_bound(uniy + 1, uniy + 1 + cy, y[i]) - uniy);
    nx[x[i]]++;
    ny[y[i]]++;
  }
  flow::S = cx + cy + 3, flow::T = cx + cy + 4;
  int SS = cx + cy + 1, TT = cx + cy + 2;
  for (int i = 1; i <= m; i++) {
    int ty, a, b;
    scanf("%d%d%d", &ty, &a, &b);
    if (ty == 1) {
      int x = (int) (lower_bound(unix + 1, unix + 1 + cx, a) - unix);
      if (a != unix[x]) continue;
      bx[x] = min(bx[x], b);
    } else {
      int y = (int) (lower_bound(uniy + 1, uniy + 1 + cy, a) - uniy);
      if (a != uniy[y]) continue;
      by[y] = min(by[y], b);
    }
  }
  for (int i = 1; i <= cx; i++) {
    bx[i] = min(bx[i], nx[i]);
    int l = max(0, (nx[i] - bx[i] + 1) / 2);
    int r = min(nx[i], (nx[i] + bx[i]) / 2);
    if (l > r) return puts("-1"), 0;
    add2(SS, i, l, r);
  }
  for (int i = 1; i <= cy; i++) {
    by[i] = min(by[i], ny[i]);
    int l = max(0, (ny[i] - by[i] + 1) / 2);
    int r = min(ny[i], (ny[i] + by[i]) / 2);
    if (l > r) return puts("-1"), 0;
    add2(i + cx, TT, l, r);
  }
  for (int i = 1; i <= n; i++) {
    flow::adde(x[i], y[i] + cx, 1);
    edd[i] = flow::e_num;
  }
  flow::adde(TT, SS, flow::INF);
  int fl = flow::dinic();
  if (fl < addon) return puts("-1"), 0;
  int R = flow::edge[flow::e_num].c;
  flow::S = SS;
  flow::T = TT;
  flow::edge[flow::e_num].c = 0;
  flow::edge[flow::e_num ^ 1].c = 0;
  R += flow::dinic();
  ll ans = (ll) R * min(r, b) + (ll) (n - R) * max(r, b);
  printf("%lld\n", ans);
  for (int i = 1; i <= n; i++) {
    if (flow::edge[edd[i]].c) {
      putchar(r <= b ? 'r' : 'b');
    } else {
      putchar(r <= b ? 'b' : 'r');
    }
  }
}
