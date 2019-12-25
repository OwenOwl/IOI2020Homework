#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5010;
int n, s, e, x[N], a[N], b[N], c[N], d[N];
ll f[N], g[N];

int main() {
  scanf("%d%d%d", &n, &s, &e);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &x[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i] += x[i];
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
    b[i] -= x[i];
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &c[i]);
    c[i] += x[i];
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &d[i]);
    d[i] -= x[i];
  }
  memset(f, 0x3f, sizeof f);
  f[0] = 0;
  for (int i = 1; i <= n; i++) {
    memset(g, 0x3f, sizeof g);
    for (int x = (i > s) + (i > e); x < i; x++) {
      g[x + 1] = min(g[x + 1], f[x] + (i == e ? 0 : d[i]) + (i == s ? 0 : b[i]));
      if (i != e && x >= 1 + (i > s)) g[x] = min(g[x], f[x] + c[i] + (i == s ? 0 : b[i]));
      if (i != s && x >= 1 + (i > e)) g[x] = min(g[x], f[x] + (i == e ? 0 : d[i]) + a[i]);
      if (i != s && i != e && x >= 2) g[x - 1] = min(g[x - 1], f[x] + c[i] + a[i]);
    }
    memcpy(f, g, sizeof g);
  }
  printf("%lld\n", f[1]);
}
