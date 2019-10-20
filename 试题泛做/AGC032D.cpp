#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
  int n;
  ll a, b;
  scanf("%d%lld%lld", &n, &a, &b);
  vector<ll> f(n + 1, 1ll << 55);
  f[0] = 0;
  for (int _ = 1; _ <= n; _++) {
    int x;
    scanf("%d", &x);
    vector<ll> g(n + 1, 1ll << 55);
    for (int i = 0; i <= n; i++) if (f[i] != 1ll << 55) {
      if (x > i) {
        g[x] = min(g[x], f[i]);
        g[i] = min(g[i], f[i] + a);
      } else {
        g[i] = min(g[i], f[i] + b);
      }
    }
    f = g;
  }
  ll ans = f[0];
  for (int i = 1; i <= n; i++) {
    ans = min(ans, f[i]);
  }
  printf("%lld\n", ans);
}

