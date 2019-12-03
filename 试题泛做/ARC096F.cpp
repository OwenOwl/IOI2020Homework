#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 55;
ll n, p[N], v[N], a[N];
ll x, d, m[N], f[N * N * N], ans;
int main() {
  scanf("%lld%lld%lld%lld", &n, &x, &d, &m[1]);
  for (ll i = 2; i <= n; i++) {
    scanf("%lld%lld", &m[i], &p[i]);
  }
  for (ll i = 1; i <= n; i++) {
    v[i] = 1;
    a[i] = i;
  }
  for (ll i = n; i >= 2; i--) {
    v[p[i]] += v[i];
    m[p[i]] += m[i];
  }
  sort(a + 1, a + 1 + n, [&](const ll &a, const ll &b){return v[a] * m[b] > v[b] * m[a];});
  memset(f, 0x3f, sizeof f);
  f[0] = 0;
  for (ll i = 1; i <= n; i++) {
    ll z = a[i] == 1 ? n : min(n, d);
    for (ll c = 1; z; z -= c, c <<= 1) {
      c = c <= z ? c : z;
      for (ll j = n * n * n; j >= c * v[a[i]]; j--) {
        f[j] = min(f[j], f[j - c * v[a[i]]] + c * m[a[i]]);
      }
    }
  }
  for (ll i = 0; i <= n * n * n; i++) if (f[i] <= x) {
    ll res = x - f[i], cur = i;
    for (ll j = 1; j <= n; j++) {
      ll c = a[j] == 1 ? res / m[a[j]] : min(res / m[a[j]], max(0LL, d - n));
      res -= c * m[a[j]];
      cur += c * v[a[j]];
    }
    ans = max(ans, cur);
  }
  printf("%lld\n", ans);
}
