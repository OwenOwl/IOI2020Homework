#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2000233;
int n, L;
ll t[N], x[N], y[N];
int cx[N], cy[N];
struct data {ll k; int b; ll x;} p[N];
void GG() {
  puts("NO");
  exit(0);
}
void solve(int *c, ll *d) {
  for (int i = 1; i <= n; i++) {
    if (abs(d[i] - t[i]) & 1) GG();
  }
  for (int i = 1; i <= n; i++) {
    p[i] = (data) {t[i] / L, (int) (t[i] % L), d[i]};
  }
  p[n + 1] = (data) {0, 0, 0};
  p[n + 2] = (data) {-1, L, 0};
  sort(p + 1, p + n + 3, [&](data a, data b){return a.b < b.b;});
  ll xl = -L, xr = L;
  for (int i = 1; i <= n + 1; i++) {
    ll k0 = p[i + 1].k - p[i].k;
    ll r0 = p[i + 1].x - p[i].x + p[i + 1].b - p[i].b;
    ll l0 = p[i + 1].x - p[i].x + p[i].b - p[i + 1].b;
    if (k0 == 0) {
      if (l0 > 0 || r0 < 0) GG();
      continue;
    }
    if (k0 < 0) {
      k0 = -k0;
      r0 = -r0;
      l0 = -l0;
      swap(l0, r0);
    }
    if (r0 >= 0) xr = min(xr, r0 / k0);
    else xr = min(xr, r0 / k0 - 1 + !(r0 % k0));
    if (l0 <= 0) xl = max(xl, l0 / k0);
    else xl = max(xl, l0 / k0 + 1 - !(l0 % k0));
  }
  if (xl > xr || (xl == xr && (abs(xl - L) & 1))) GG();
  ll x0 = (abs(xl - L) & 1) ? xl + 1 : xl;
  for (int i = 1; i <= n + 1; i++) {
    ll k0 = p[i + 1].k - p[i].k;
    ll t0 = k0 * x0 - (p[i + 1].x - p[i].x);
    int j;
    for (j = p[i].b + 1; j <= p[i].b + abs(t0); j++) {
      c[j] = t0 > 0 ? 1 : -1;
    }
    for (; j <= p[i + 1].b; j += 2) {
      c[j] = 1;
      c[j + 1] = -1;
    }
  }
}
int main() {
  scanf("%d%d", &n, &L);
  for (int i = 1; i <= n; i++) {
    scanf("%lld%lld%lld", &t[i], &x[i], &y[i]);
    y[i] = x[i] - y[i];
    x[i] += x[i] - y[i];
  }
  solve(cx, x);
  solve(cy, y);
  for (int i = 1; i <= L; i++) {
    if (cx[i] < 0 && cy[i] < 0) putchar('R');
    if (cx[i] > 0 && cy[i] > 0) putchar('L');
    if (cx[i] < 0 && cy[i] > 0) putchar('U');
    if (cx[i] > 0 && cy[i] < 0) putchar('D');
  }
}
