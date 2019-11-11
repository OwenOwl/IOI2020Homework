#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 100005;
const int INF = 1e9;
const ll INF_LL = 1e18, bound = 1e15+3;

int e_num = 1, S, T, maxf = 0;
ll mincost = 0;
int hed[maxn];
ll ct[maxn];
struct Edge {
  int from, to, nxt, c;
  ll cost;
} edge[maxn];
void addedge(int from, int to, int c, ll cost) {
  edge[++e_num] = (Edge){from, to, hed[from], c, cost};
  hed[from] = e_num;
}
void adde(int from, int to, int c, ll cost) {
  addedge(from, to, c, cost);
  addedge(to, from, 0, -cost);
}
queue<int> q;
#define prev prv
int inq[maxn], prev[maxn], pree[maxn];
bool SPFA() {
  for (int i = 0; i <= T; i++) ct[i] = INF_LL;
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
  if (ct[T] == INF_LL) return 0;
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
  maxf += flow;
  mincost += flow * ct[T];
  return 1;
}

const int N = 233;
int n, m, L[N], R[N], U[N], D[N], x[N], y[N];
int type[N], tt[N], vv[N];
ll v[N];

ll Main(int k) {
  memset(L, 0, sizeof L);
  memset(D, 0, sizeof D);
  memset(R, 0x3f, sizeof R);
  memset(U, 0x3f, sizeof U);
  for (int x = 1; x <= m; x++) {
    int t = tt[x], v = vv[x];
    if (type[x] == 'L') {
      for (int i = v + 1; i <= k; i++) {
        L[i] = max(L[i], t + 1);
      }
    } else if (type[x] == 'R') {
      for (int i = 1; i <= k - v; i++) {
        R[i] = min(R[i], t - 1);
      }
    } else if (type[x] == 'D') {
      for (int i = v + 1; i <= k; i++) {
        D[i] = max(D[i], t + 1);
      }
    } else {
      for (int i = 1; i <= k - v; i++) {
        U[i] = min(U[i], t - 1);
      }
    }
  }
  S = n * 4 + 1, T = n * 4 + 2;
  mincost = maxf = 0;
  e_num = 1;
  memset(hed, 0, sizeof hed);
  for (int i = 1; i <= k; i++) {
    adde(S, i, 1, 0);
    adde(i + k, T, 1, 0);
    for (int j = 1; j <= n; j++) {
      if (L[i] <= x[j] && x[j] <= R[i]) {
        adde(i, j + k + k, 1, 0);
      }
      if (D[i] <= y[j] && y[j] <= U[i]) {
        adde(j + k + k + n, i + k, 1, 0);
      }
    }
  }
  for (int j = 1; j <= n; j++) {
    adde(j + k + k, j + k + k + n, 1, bound - v[j]);
  }
  while (SPFA());
  if (maxf != k) return 0;
  return maxf * bound - mincost;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%lld", &x[i], &y[i], &v[i]);
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    char c[4];
    scanf("%s%d%d", c, &tt[i], &vv[i]);
    type[i] = c[0];
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, Main(i));
  }
  printf("%lld\n", ans);
  return 0;
}
