#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
  int q;
  scanf("%d", &q);
  while (q--) {
    ll a, b, c, d;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    ll k = (max(a, b) - 1) / (min(a, b) + 1) + 1;
    ll l = 0, r = a;
    while (l < r) {
      ll ma = (l + r + 1) >> 1;
      ll mb = max(0LL, (ma - 1) / k);
      if (b - mb <= (a - ma + 1) * k) {
        l = ma;
      } else {
        r = ma - 1;
      }
    }
    ll t = l + max(0LL, (l - 1) / k);
    for (ll i = c; i <= min(t, d); i++) {
      putchar(i % (k + 1) ? 'A' : 'B');
    }
    for (ll i = max(t + 1, c); i <= d; i++) {
      putchar((a + b + 1 - i) % (k + 1) ? 'B' : 'A');
    }
    puts("");
  }
}
