#include <bits/stdc++.h>
using namespace std;

const int maxn = 500015;
const int INF = (int) 1e9;
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
  for (int i = S; i <= T; i++) dep[i] = 0;
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
int dfs(int x, int flow) {
  if (x == T) return flow;
  int ret = 0;
  for (int i = hed[x]; i; i = edge[i].nxt) {
    int to = edge[i].to;
    if (dep[to] == dep[x] + 1 && edge[i].c) {
      int tmp = dfs(to, std::min(flow, edge[i].c));
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
    ret += dfs(S, INF);
  }
  return ret;
}

const int N = 100233;
int n, visit[N], son[N], fa[N];
vector<int> e[N], g[N];
int main() {
  scanf("%d", &n);
  S = 0, T = n * 2 + 1;
  for (int i = 1, t, x; i < n; i++) {
    adde(S, i, 1);
    scanf("%d", &t);
    while (t--) {
      scanf("%d", &x);
      e[i].push_back(x);
      g[x].push_back(i);
      if (x > 1) adde(i, x + n, 1);
    }
  }
  for (int i = 2; i <= n; i++) {
    adde(i + n, T, 1);
  }
  int p = dinic();
  if (p < n - 1) return puts("-1"), 0;
  for (int i = 1; i < n; i++) {
    for (int e = hed[i]; e; e = edge[e].nxt) {
      if (edge[e].to > n && !edge[e].c) {
        son[i] = edge[e].to - n;
      }
    }
  }
  queue<int> q;
  for (auto x : g[1]) {
    q.push(x);
    visit[x] = 1;
    fa[x] = 1;
  }
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (auto y : g[son[x]]) {
      if (!visit[y]) {
        q.push(y);
        visit[y] = 1;
        fa[y] = son[x];
      }
    }
  }
  if (accumulate(visit + 1, visit + n, 0) != n - 1) return puts("-1"), 0;
  for (int i = 1; i < n; i++) {
    printf("%d %d\n", fa[i], son[i]);
  }
}
