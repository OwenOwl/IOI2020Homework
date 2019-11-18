#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
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
  for (int i = 0; i <= T; i++) dep[i] = 0;
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

const int N = 103;
int n, m, a[N][N], x[N][N], y[N][N], row1[N * N], row2[N * N], ban[N * N], id[N * N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
      row1[a[i][j]] = i;
      row2[m * (i - 1) + j] = i;
    }
  }
  S = 0, T = n * 2 + 1;
  for (int c = 1; c <= m; c++) {
    for (int i = 0; i <= T; i++) hed[i] = 0;
    e_num = 1;
    for (int i = 1; i <= n; i++) {
      adde(S, i, 1);
      adde(i + n, T, 1);
    }
    for (int i = 1; i <= n * m; i++) {
      if (!ban[i]) {
        adde(row1[i], row2[i] + n, 1);
        id[i] = e_num - 1;
      }
    }
    dinic();
    for (int i = 1; i <= n * m; i++) {
      if (!ban[i] && !edge[id[i]].c) {
        ban[i] = 1;
        x[row1[i]][c] = i;
        y[row2[i]][c] = i;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      printf("%d ", x[i][j]);
    }
    puts("");
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      printf("%d ", y[i][j]);
    }
    puts("");
  }
  return 0;
}
