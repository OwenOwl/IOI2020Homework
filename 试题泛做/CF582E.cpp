#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1000000007;
int m, fix[16];
char s[510];

void dft_and(int *a, int fl) {
  for (int i = 1; i < 1 << 16; i <<= 1) {
    for (int j = 0; j < 1 << 16; j += i << 1) {
      for (int k = 0; k < i; k++) {
        if (!fl) {
          a[j + k] = (a[j + k] + a[j + k + i]) % mod;
        } else {
          a[j + k] = (a[j + k] + mod - a[j + k + i]) % mod;
        }
      }
    }
  }
}
void dft_or(int *a, int fl) {
  for (int i = 1; i < 1 << 16; i <<= 1) {
    for (int j = 0; j < 1 << 16; j += i << 1) {
      for (int k = 0; k < i; k++) {
        if (!fl) {
          a[j + k + i] = (a[j + k + i] + a[j + k]) % mod;
        } else {
          a[j + k + i] = (a[j + k + i] + mod - a[j + k]) % mod;
        }
      }
    }
  }
}
int lab[8] = {21845, 43690, 13107, 52428, 3855, 61680, 255, 65280};

struct poly {
  int f[1 << 16];
  poly () {
    memset(f, 0, sizeof f);
  }
  poly (int x, int fl) {
    memset(f, 0, sizeof f);
    if (!~x) {
      for (int i = 0; i < 8; i++) {
        f[lab[i]] = 1;
      }
    } else {
      f[lab[x << 1 | fl]] = 1;
    }
  }
  poly operator + (const poly &d) const {
    poly r;
    for (int i = 0; i < 1 << 16; i++) {
      r.f[i] = (f[i] + d.f[i]) % mod;
    }
    return r;
  }
  poly operator & (const poly &d) const {
    static int a[1 << 16], b[1 << 16];
    memcpy(a, f, 1 << 18);
    memcpy(b, d.f, 1 << 18);
    dft_and(a, 0);
    dft_and(b, 0);
    poly r;
    for (int i = 0; i < 1 << 16; i++) {
      r.f[i] = (ll) a[i] * b[i] % mod;
    }
    dft_and(r.f, 1);
    return r;
  }
  poly operator | (const poly &d) const {
    static int a[1 << 16], b[1 << 16];
    memcpy(a, f, 1 << 18);
    memcpy(b, d.f, 1 << 18);
    dft_or(a, 0);
    dft_or(b, 0);
    poly r;
    for (int i = 0; i < 1 << 16; i++) {
      r.f[i] = (ll) a[i] * b[i] % mod;
    }
    dft_or(r.f, 1);
    return r;
  }
};

poly solve(int l, int r) {
  if (l == r) {
    if (s[l] == '?') {
      return poly(-1, -1);
    } else if (s[l] >= 'a' && s[l] <= 'd') {
      return poly(s[l] - 'a', 0);
    } else {
      return poly(s[l] - 'A', 1);
    }
  }
  for (int i = l + 1, x = 1; i <= r; i++) {
    if (s[i] == '(') x++;
    if (s[i] == ')') x--;
    if (x == 0) {
      ++i;
      poly a = solve(l + 1, i - 2);
      poly b = solve(i + 2, r - 1);
      if (s[i] == '&') return a & b;
      if (s[i] == '|') return a | b;
      return (a & b) + (a | b);
    }
  }
  return poly();
}

int main() {
  scanf("%s%d", s, &m);
  memset(fix, -1, sizeof fix);
  for (int i = 1, a, b, c, d, e; i <= m; i++) {
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
    fix[a << 0 | b << 1 | c << 2 | d << 3] = e;
  }
  poly t = solve(0, (int) strlen(s) - 1);
  int ans = 0;
  for (int i = 0; i < 1 << 16; i++) {
    int ok = 1;
    for (int j = 0; j < 16; j++) {
      if (~fix[j] && (i >> j & 1) != fix[j]) {
        ok = 0;
      }
    }
    if (ok) {
      ans = (ans + t.f[i]) % mod;
    }
  }
  printf("%d\n", ans);
}
