#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 250033, mod1 = 1000000007, mod2 = 1000109107;
int qpow(int b, int p, int m) {
  int r = 1;
  for (; p; p >>= 1, b = (ll) b * b % m) if (p & 1) r = (ll) r * b % m;
  return r;
}
struct data {
  int x, y;
  data(int x = 0, int y = 0) : x(x), y(y) {}
  data operator + (const data &d) const {return data((x + d.x) % mod1, (y + d.y) % mod2);}
  data operator - (const data &d) const {return data((x + mod1 - d.x) % mod1, (y + mod2 - d.y) % mod2);};
  data operator * (const data &d) const {return data((ll) x * d.x % mod1, (ll) y * d.y % mod2);}
  data operator / (const data &d) const {return data((ll) x * qpow(d.x, mod1 - 2, mod1) % mod1, (ll) y * qpow(d.y, mod2 - 2, mod2) % mod2);}
  ll get() {return (ll) x << 30 | y;}
};
data X(159623, 102647), f[N], g[N], h[N], k(1, 1), b;
int n;
ll ans;
char s[N];
map<ll, int> mp;

int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; i++) {
    if (s[i] == '+') b = b + k;
    if (s[i] == '-') b = b - k;
    if (s[i] == '>') k = k * X;
    if (s[i] == '<') k = k / X;
    f[i] = b;
  }
  g[0] = k = data(1, 1), h[0] = b = data(0, 0);
  for (int i = 1; i <= n; i++) {
    if (s[i] == '+') b = b - data(1, 1);
    if (s[i] == '-') b = b + data(1, 1);
    if (s[i] == '>') k = k / X, b = b / X;
    if (s[i] == '<') k = k * X, b = b * X;
    g[i] = k, h[i] = b;
  }
  for (int i = n; i >= 0; i--) {
    data t = (f[n] - h[i]) / g[i];
    ans += mp[t.get()];
    mp[f[i].get()]++;
  }
  printf("%lld\n", ans);
}
