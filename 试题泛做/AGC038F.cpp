#include <bits/stdc++.h>
using namespace std;
const int maxn = 200006;
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
  memset(dep, 0, sizeof dep);
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

int n, p[maxn], q[maxn], bp[maxn], bq[maxn], cnt;
void solve(int *p, int *bel) {
  for (int i = 1; i <= n; i++) if (!bel[i]) {
    int x = i;
    ++cnt;
    do {
      bel[x] = cnt;
      x = p[x];
    } while (x != i);
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
    ++p[i];
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &q[i]);
    ++q[i];
  }
  solve(p, bp);
  solve(q, bq);
  S = 0, T = ++cnt;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (p[i] == i && q[i] == i) {
      ans++;
    } else if (q[i] == i) {
      adde(S, bp[i], 1);
    } else if (p[i] == i) {
      adde(bq[i], T, 1);
    } else {
      addedge(bq[i], bp[i], 1);
      addedge(bp[i], bq[i], p[i] == q[i]);
    }
  }
  ans += dinic();
  printf("%d\n", n - ans);
  return 0;
}
