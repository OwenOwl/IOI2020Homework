#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll k;
const int N = 50010;
int n, m, mod, s[N];
pair<ll, int> c[N];
struct mat {
  int a, b, c, d;
  mat(int a = 0, int b = 0, int c = 0, int d = 0) : a(a), b(b), c(c), d(d) {}
  mat operator * (const mat &h) const {
    mat r;
    r.a = ((ll) a * h.a + (ll) b * h.c) % mod;
    r.b = ((ll) a * h.b + (ll) b * h.d) % mod;
    r.c = ((ll) c * h.a + (ll) d * h.c) % mod;
    r.d = ((ll) c * h.b + (ll) d * h.d) % mod;
    return r;
  }
};

mat qpow(mat b, ll p) {
  mat r(1, 0, 0, 1);
  for (; p; p >>= 1) {
    if (p & 1) r = r * b;
    b = b * b;
  }
  return r;
}
mat ss[N << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)
inline void build(int p, int l, int r) {
  if (l == r) {
    ss[p] = mat(s[l], 1, s[(l + n - 1) % n], 0);
    return;
  }
  build(ls, l, mid);
  build(rs, mid + 1, r);
  ss[p] = ss[ls] * ss[rs];
}
mat query(int p, int l, int r, int ql, int qr) {
  if (l == ql && r == qr) {
    return ss[p];
  }
  if (qr <= mid) {
    return query(ls, l, mid, ql, qr);
  } else if (ql > mid) {
    return query(rs, mid + 1, r, ql, qr);
  } else {
    return query(ls, l, mid, ql, mid) * query(rs, mid + 1, r, mid + 1, qr);
  }
}
mat ran(ll l, ll r) {
  if (l / n == r / n) {
    return query(1, 0, n - 1, l % n, r % n);
  } else {
    return query(1, 0, n - 1, l % n, n - 1) * qpow(ss[1], r / n - l / n - 1) * query(1, 0, n - 1, 0, r % n);
  }
}
map<ll, int> mp;
int get(ll x) {
  if (mp.count(x)) return mp[x];
  return s[x % n];
}

int main() {
  scanf("%lld%d%d", &k, &mod, &n);
  if (k <= 1) {
    printf("%d\n", (int) (k % mod));
    return 0;
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &s[i]);
    s[i] %= mod;
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%lld%d", &c[i].first, &c[i].second);
    c[i].second %= mod;
    mp[c[i].first] = c[i].second;
  }
  c[m++] = make_pair(k - 2, 0);
  sort(c, c + m);
  build(1, 0, n - 1);
  ll last = 1;
  mat f(1, 0, 0, 0);
  for (int i = 0; i < m && last < k; i++) {
    ll x = c[i].first;
    if (last < x) {
      f = f * ran(last, x - 1);
      last = x;
    }
    if (last == x) {
      f = f * mat(get(x), 1, get(x - 1), 0);
      last = x + 1;
    }
    if (last == x + 1) {
      f = f * mat(get(x + 1), 1, get(x), 0);
      last = x + 2;
    }
  }
  printf("%d\n", f.a);
}
