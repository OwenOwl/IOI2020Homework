#include <bits/stdc++.h>
using namespace std;
int main() {
  int p, n, q;
  scanf("%d%d%d", &p, &n, &q);
  n = min(n, p - 1);
  auto mul = [&] (vector<unsigned> a, vector<unsigned> b) -> vector<unsigned> {
    vector<unsigned> c(min((int) a.size() + (int) b.size() - 1, n + 1), 0);
    for (int i = 0; i < (int) a.size(); i++) {
      for (int j = 0; j < (int) b.size() && i + j < (int) c.size(); j++) {
        c[i + j] = c[i + j] + a[i] * b[j];
      }
    }
    return c;
  };
  vector<unsigned> r(1, 1), b(2, 1);
  for (; p; p >>= 1) {
    if (p & 1) {
      r = mul(r, b);
    }
    b = mul(b, b);
  }
  unsigned ans = 0;
  for (int d = 1; d <= q; d++) {
    unsigned ret = 0, w = 1;
    for (int i = 0; i <= n && i < (int) r.size(); i++) {
      ret = ret + w * r[i];
      w = w * d;
    }
    ans ^= d * ret;
  }
  printf("%u\n", ans);
}
