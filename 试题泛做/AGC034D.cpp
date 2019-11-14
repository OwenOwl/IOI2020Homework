#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 50005;
const int INF = 1e9;
const ll INF_LL = 1e18;
int e_num = 1, S, T, ans = 0;
ll mincost = 0;
int hed[maxn];
ll ct[maxn];

struct Edge {
  int from, to, nxt, c; ll cost;
} edge[maxn * 4];
void addedge(int from, int to, int c, ll cost) {
  edge[++e_num] = (Edge){from, to, hed[from], c, cost};
  hed[from] = e_num;
}
void adde(int from, int to, int c, ll cost) {
  addedge(from, to, c, cost);
  addedge(to, from, 0, -cost);
}
queue <int> q;
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
  ans += flow;
  mincost += flow * ct[T];
  return 1;
}

int n;
int main() {
  scanf("%d", &n);
  S = n * 2 + 5, T = n * 2 + 6;
  for (int i = 1; i <= n; i++) {
    ll x, y; int c;
    scanf("%lld%lld%d", &x, &y, &c);
    adde(S, i, c, 0);
    adde(i, n * 2 + 1, c, x + y);
    adde(i, n * 2 + 2, c, - x - y);
    adde(i, n * 2 + 3, c, x - y);
    adde(i, n * 2 + 4, c, - x + y);
  }
  for (int i = 1; i <= n; i++) {
    ll x, y; int c;
    scanf("%lld%lld%d", &x, &y, &c);
    adde(i + n, T, c, 0);
    adde(n * 2 + 1, i + n, c, - x - y);
    adde(n * 2 + 2, i + n, c, x + y);
    adde(n * 2 + 3, i + n, c, - x + y);
    adde(n * 2 + 4, i + n, c, x - y);
  }
  while (SPFA());
  printf("%lld\n", -mincost);
  return 0;
}
