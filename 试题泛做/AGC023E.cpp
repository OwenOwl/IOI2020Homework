#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 200233, mod = 1000000007;
int n, a[N], ans = 0;

int qpow(int b, int p) {
  int r = 1;
  for (; p; p >>= 1) {
    if (p & 1) r = (ll) r * b % mod;
    b = (ll) b * b % mod;
  }
  return r;
}

struct int0 {
  int a, b;
  int0 (int a = 0, int b = 0) : a(a), b(b) {}
  int0 operator + (const int0 &d) const {
    if (b < d.b) return *this;
    if (b > d.b) return d;
    return int0((a + d.a) % mod, b);
  }
  int0 operator * (const int0 &d) const {
    return int0((ll) a * d.a % mod, b + d.b);
  }
  int0 operator * (const int &d) const {
    return d == 0 ? int0(a, b + 1) : int0((ll) a * d % mod, b);
  }
  int0 inv() {
    return int0(qpow(a, mod - 2), -b);
  }
  int val() {
    return b ? 0 : a;
  }
};

int S, cnt[N];
int0 d[N], c[N];
inline int0 ask(int x) {
  int0 ret(0, 0);
  for (; x; x -= x & -x) {
    ret = ret + c[x];
  }
  return ret;
}
inline void add(int x, int0 y) {
  for (; x <= n; x += x & -x) {
    c[x] = c[x] + y;
  }
}
inline int solve(int *a, int flag) {
  S = 1;
  int ret = 0;
  for (int i = 1; i <= n; i++) {
    cnt[i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    cnt[a[i]]++;
  }
  for (int i = n; i; i--) {
    cnt[i - 1] += cnt[i];
    cnt[i] -= n - i;
    S = (ll) S * (cnt[i] <= 0 ? 0 : cnt[i]) % mod;
  }
  if (!S) return 0;
  d[0] = int0(1, 0);
  for (int i = 1; i <= n; i++) {
    d[i] = d[i - 1] * ((ll) (cnt[i] - 1) * qpow(cnt[i], mod - 2) % mod);
  }
  for (int i = 1; i <= n; i++) {
    c[i] = int0(0, 0);
  }
  for (int i = 1; i <= n; i++) {
    int0 t = ask(a[i] - flag);
    ret = (ret + (ll) (t * d[a[i]]).val() * S) % mod;
    add(a[i], d[a[i]].inv());
  }
  return (ll) ret * (mod + 1) / 2 % mod;
}

inline int solve2(int *a) {
  for (int i = 1; i <= n; i++) {
    c[i] = int0(0, 0);
  }
  int ret = 0;
  for (int i = 1; i <= n; i++) {
    ret = (ret + ask(a[i] - 1).val()) % mod;
    add(a[i], int0(1, 0));
  }
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  ans = solve(a, 0);
  reverse(a + 1, a + n + 1);
  ans = (ans + mod - solve(a, 1)) % mod;
  ans = (ans + (ll) S * solve2(a)) % mod;
  printf("%d\n", ans);
}
