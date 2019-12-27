#include <bits/stdc++.h>
using namespace std;
const int maxn = 50005;
const int INF = 1e9;
int e_num = 1, S, T, ans = 0, mincost = 0;
int hed[maxn], ct[maxn];

struct Edge {
  int from, to, nxt, c, cost;
} edge[maxn * 4];
void addedge(int from, int to, int c, int cost) {
  edge[++e_num] = (Edge){from, to, hed[from], c, cost};
  hed[from] = e_num;
}
void adde(int from, int to, int c, int cost) {
  addedge(from, to, c, cost);
  addedge(to, from, 0, -cost);
}
queue <int> q;
#define prev prv
int inq[maxn], prev[maxn], pree[maxn];
bool SPFA() {
  for (int i = 0; i <= T; i++) ct[i] = INF;
  inq[S] = 1;
  ct[S] = 0;
  q.push(S);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (int i = hed[cur]; i; i = edge[i].nxt) {
      int to = edge[i].to;
      if (ct[to] > ct[cur] + edge[i].cost && edge[i].c) {
        if (!inq[to]) {
          inq[to] = 1;
          q.push(to);
        }
        ct[to] = ct[cur] + edge[i].cost;
        prev[to] = cur;
        pree[to] = i;
      }
    }
    inq[cur] = 0;
  }
  if (ct[T] == INF) return 0;
  int flow = INF;
  for (int cur = T; prev[cur]; cur = prev[cur]) {
    int ed = pree[cur];
    flow = min(flow, edge[ed].c);
  }
  for (int cur = T; prev[cur]; cur = prev[cur]) {
    int ed = pree[cur];
    edge[ed].c -= flow;
    edge[ed ^ 1].c += flow;
  }
  ans += flow;
  mincost += flow * ct[T];
  return 1;
}

int n, m, deg[maxn];

int main() {
  scanf("%d%d", &n, &m);
  S = n + 1, T = n + 2;
  for (int i = 1; i <= m; i++) {
    int u, v, c, f;
    scanf("%d%d%d%d", &u, &v, &c, &f);
    deg[u] += f;
    deg[v] -= f;
    if (c >= f) {
      adde(v, u, f, 1);
      adde(u, v, c - f, 1);
      adde(u, v, INF, 2);
    } else {
      mincost += f - c;
      adde(v, u, f - c, 0);
      adde(v, u, c, 1);
      adde(u, v, INF, 2);
    }
  }
  adde(n, 1, INF, 0);
  for (int i = 1; i <= n; i++) {
    if (deg[i] > 0) {
      adde(i, T, deg[i], 0);
    } else {
      adde(S, i, -deg[i], 0);
    }
  }
  while (SPFA());
  printf("%d\n", mincost);
  return 0;
}
