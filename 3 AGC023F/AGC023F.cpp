#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct frac {
  int c0, c1;
  frac(int c0 = 0, int c1 = 0) : c0(c0), c1(c1) {}
  bool operator < (const frac &d) const {
    return (ll) c0 * d.c1 < (ll) d.c0 * c1;
  }
  frac operator + (const frac &d) const {
    return frac(c0 + d.c0, c1 + d.c1);
  }
};
const int N = 200010;
frac r[N];
priority_queue<pair<frac, int>> q;
int n, par[N], f[N];
ll ans = 0;
int F(int x) {
  while (x != f[x]) x = f[x] = f[f[x]];
  return x;
}
int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    scanf("%d", &par[i]);
  }
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    if (x == 0) {
      r[i] = frac(1, 0);
    } else {
      r[i] = frac(0, 1);
    }
    if (i > 1) q.push(make_pair(r[i], i));
    f[i] = i;
  }
  while (!q.empty()) {
    int v = q.top().second;
    frac d = q.top().first;
    q.pop();
    if (v != F(v) || d.c0 != r[v].c0 || d.c1 != r[v].c1) continue;
    int u = F(par[v]);
    f[v] = u;
    ans += (ll) r[u].c1 * r[v].c0;
    r[u] = r[u] + r[v];
    if (u != 1) q.push(make_pair(r[u], u));
  }
  printf("%lld\n", ans);
}
