#include <bits/stdc++.h>

using namespace std;

const int md = 998244353;

inline void add(int &x, int y) {
  x += y;
  if (x >= md) {
    x -= md;
  }
}

inline void sub(int &x, int y) {
  x -= y;
  if (x < 0) {
    x += md;
  }
}

inline int mul(int x, int y) {
  return (int) ((long long) x * y % md);
}

inline int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) {
      res = mul(res, x);
    }
    x = mul(x, x);
    y >>= 1;
  }
  return res;
}

inline int inv(int a) {
  int b = md, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= t * a;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  if (u < 0) {
    u += md;
  }
  return u;
}

namespace ntt {
int base = 1, root = -1, max_base = -1;
vector<int> rev = {0, 1}, roots = {0, 1};
void init() {
  int temp = md - 1;
  max_base = 0;
  while (temp % 2 == 0) {
    temp >>= 1;
    ++max_base;
  }
  root = 2;
  while (true) {
    if (power(root, 1 << max_base) == 1 && power(root, 1 << (max_base - 1)) != 1) {
      break;
    }
    ++root;
  }
}
void ensure_base(int nbase) {
  if (max_base == -1) {
    init();
  }
  if (nbase <= base) {
    return;
  }
  assert(nbase <= max_base);
  rev.resize(1 << nbase);
  for (int i = 0; i < 1 << nbase; ++i) {
    rev[i] = rev[i >> 1] >> 1 | (i & 1) << (nbase - 1);
  }
  roots.resize(1 << nbase);
  while (base < nbase) {
    int z = power(root, 1 << (max_base - 1 - base));
    for (int i = 1 << (base - 1); i < 1 << base; ++i) {
      roots[i << 1] = roots[i];
      roots[i << 1 | 1] = mul(roots[i], z);
    }
    ++base;
  }
}
void dft(vector<int> &a) {
  int n = a.size(), zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; ++i) {
    if (i < rev[i] >> shift) {
      swap(a[i], a[rev[i] >> shift]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        int x = a[j + k], y = mul(a[j + k + i], roots[i + k]);
        a[j + k] = (x + y) % md;
        a[j + k + i] = (x + md - y) % md;
      }
    }
  }
}
}

int n, m, fac[16384], ifac[16384];

int main() {
  scanf("%d%d", &n, &m);
  vector<int> f(16384), g(16384);
  int I = inv(16384);
  fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i < 16384; i++) {
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(md - md / i, ifac[md % i]);
  }
  for (int i = 2; i < 16384; i++) {
    ifac[i] = mul(ifac[i], ifac[i - 1]);
  }
  f[0] = 1;
  for (int i = 1; i < 8192; i++) {
    g[i] = ifac[i + 2];
  }
  ntt::dft(g);
  for (int i = 1; i <= m; i++) {
    vector<int> h(16384);
    for (int i = 0; i < 8192; i++) {
      h[i] = mul(f[i], 1 + i + i * (i - 1) / 2);
      f[i] = mul(f[i], ifac[i]);
    }
    ntt::dft(f);
    for (int i = 0; i < 16384; i++) {
      f[i] = mul(f[i], mul(g[i], I));
    }
    reverse(f.begin() + 1, f.end());
    ntt::dft(f);
    for (int i = 0; i < 8192; i++) {
      add(h[i], mul(f[i], fac[i + 2]));
    }
    f = h;
  }
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    add(ans, mul(mul(fac[n], mul(ifac[i], ifac[n - i])), f[i]));
  }
  printf("%d\n", ans);
}
