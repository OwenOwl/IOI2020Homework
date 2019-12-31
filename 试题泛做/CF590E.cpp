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
int dinic() {
  int ret = 0;
  while (bfs()) {
    memcpy(hed2, hed, sizeof hed);
    ret += dfs(S, INF);
  }
  return ret;
}

const int N = 760, M = 10000233;
int n, cnt = 1, ch[M][2], ed[M], fail[M];
vector<int> pos[N];
char s[M];
bitset<N> f[N];

int main() {
  scanf("%d", &n);
  for (int x = 1; x <= n; x++) {
    scanf("%s", s + 1);
    int L = (int) strlen(s + 1);
    int cur = 1;
    for (int i = 1; i <= L; i++) {
      if (!ch[cur][s[i] - 'a']) {
        ch[cur][s[i] - 'a'] = ++cnt;
      }
      cur = ch[cur][s[i] - 'a'];
      pos[x].push_back(cur);
    }
    ed[cur] = x;
  }
  queue<int> q;
  ch[0][0] = ch[0][1] = 1;
  q.push(1);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    if (!ed[x]) {
      ed[x] = ed[fail[x]];
    }
    for (int i = 0; i < 2; i++) {
      if (!ch[x][i]) {
        ch[x][i] = ch[fail[x]][i];
      } else {
        fail[ch[x][i]] = ch[fail[x]][i];
        q.push(ch[x][i]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    f[i][i] = 1;
    for (auto x : pos[i]) {
      if (ed[x]) {
        f[i][ed[x]] = 1;
      }
    }
    if (ed[fail[pos[i].back()]]) {
      f[i][ed[fail[pos[i].back()]]] = 1;
    }
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) if (f[i][k]) {
      f[i] |= f[k];
    }
  }
  S = n * 2 + 1, T = n * 2 + 2;
  for (int i = 1; i <= n; i++) {
    adde(S, i, 1);
    adde(i + n, T, 1);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) if (i != j) {
      if (f[i][j]) {
        adde(i, j + n, 1);
      }
    }
  }
  printf("%d\n", n - dinic());
  for (int i = 1; i <= n; i++) {
    if (dep[i] && !dep[i + n]) {
      printf("%d ", i);
    }
  }
}
