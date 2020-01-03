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
void clear() {
  for (int i = 0; i <= T; i++) {
    hed[i] = 0;
  }
  e_num = 1;
}
int dinic() {
  int ret = 0;
  while (bfs()) {
    for (int i = 0; i <= T; i++) {
      hed2[i] = hed[i];
    }
    ret += dfs(S, INF);
  }
  return ret;
}
int k;

int e[9][9], cnt[9];
int getlen(int x) {
  int cc = 0;
  while (x) {
    x /= 10;
    cc++;
  }
  return cc;
}

int pru[9];

vector<pair<int, int>> gettree() {
  vector<pair<int, int>> E(0);
  set<int> s;
  s.clear();
  static int vis[9];
  memset(vis, 0, sizeof vis);
  for (int i = 1; i <= k - 2; i++) {
    vis[pru[i]] = i;
  }
  for (int i = 1; i <= k; i++) if (!vis[i]) {
    s.insert(i);
  }
  for (int i = 1; i <= k - 2; i++) {
    E.emplace_back(pru[i], *s.begin());
    s.erase(*s.begin());
    if (vis[pru[i]] == i) {
      s.insert(pru[i]);
    }
  }
  E.emplace_back(*s.begin(), *s.rbegin());
  return E;
}

void solve() {
  vector<pair<int, int>> E = gettree();
  for (auto &x : E) {
    int &u = x.first, &v = x.second;
    if (!e[u][v] && !e[v][u]) {
      return;
    }
    if (!e[u][v]) {
      swap(u, v);
    }
  }
  for (auto x : E) {
    int u = x.first, v = x.second;
    e[u][v]--;
  }
  clear();
  S = k * k + k + 1, T = k * k + k + 2;
  for (int u = 1, w = k; u <= k; u++) {
    for (int v = 1; v <= k; v++) {
      ++w;
      adde(S, w, e[u][v]);
      adde(w, u, e[u][v]);
      adde(w, v, e[u][v]);
    }
  }
  int all = 0;
  for (int i = 1; i <= k; i++) {
    adde(i, T, cnt[i] - 1);
    all += cnt[i] - 1;
  }
  int flow = dinic();
  if (flow != all) {
    for (auto x : E) {
      int u = x.first, v = x.second;
      e[u][v]++;
    }
    return;
  }
  static int pw[9], pd[9];
  pw[1] = 1;
  for (int i = 2; i <= k; i++) pw[i] = pw[i - 1] * 10;
  for (int i = 1; i <= k; i++) pd[i] = pw[i];
  for (auto x : E) {
    int u = x.first, v = x.second;
    printf("%d %d\n", pw[u], pw[v]);
  }
  for (int u = 1, w = k; u <= k; u++) {
    for (int v = 1; v <= k; v++) {
      ++w;
      for (int e = hed[w]; e; e = edge[e].nxt) {
        if (edge[e].to == u) {
          for (int i = 1; i <= edge[e ^ 1].c; i++) {
            printf("%d %d\n", ++pd[u], pw[v]);
          }
        } else if (edge[e].to == v) {
          for (int i = 1; i <= edge[e ^ 1].c; i++) {
            printf("%d %d\n", pw[u], ++pd[v]);
          }
        }
      }
    }
  }
  exit(0);
}

void dfs(int x) {
  if (x == k - 1) {
    solve();
    return;
  }
  for (int i = 1; i <= k; i++) {
    pru[x] = i;
    dfs(x + 1);
  }
}

int n;
int main() {
  mt19937 rng(3);
  scanf("%d", &n);
  if (n <= 9) {
    for (int j = 2; j <= n; j++) {
      printf("1 %d\n", j);
    }
    return 0;
  }
  k = (int) getlen(n);
  for (int i = 1; i <= n; i++) {
    cnt[getlen(i)]++;
  }
  for (int i = 1; i < n; i++) {
    char x[11], y[11];
    scanf("%s%s", x, y);
    int u = (int) strlen(x), v = (int) strlen(y);
    e[u][v]++;
  }
  dfs(1);
  puts("-1");
}
