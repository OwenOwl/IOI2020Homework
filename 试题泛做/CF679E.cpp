#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100233;
int n, q;
ll tp[N << 2], ta[N << 2], mn[N << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)
ll get(ll d) {
  ll t = 1;
  while (t < d) t *= 42;
  return t - d;
}
void ud(int p) {
  mn[p] = min(mn[ls], mn[rs]);
}
void ca(int p, ll x) {
  if (tp[p]) {
    tp[p] += x;
    mn[p] -= x;
  } else {
    ta[p] += x;
    mn[p] -= x;
  }
}
void pd(int p) {
  if (tp[p]) {
    tp[ls] = tp[p], ta[ls] = 0, mn[ls] = mn[p];
    tp[rs] = tp[p], ta[rs] = 0, mn[rs] = mn[p];
    tp[p] = 0;
  } else if (ta[p]) {
    ca(ls, ta[p]);
    ca(rs, ta[p]);
    ta[p] = 0;
  }
}
void cov(int p, int l, int r, int ql, int qr, ll x, ll y) {
  if (l == ql && r == qr) {
    tp[p] = x;
    ta[p] = 0;
    mn[p] = y;
    return;
  }
  pd(p);
  if (qr <= mid) cov(ls, l, mid, ql, qr, x, y);
  else if (ql > mid) cov(rs, mid + 1, r, ql, qr, x, y);
  else cov(ls, l, mid, ql, mid, x, y), cov(rs, mid + 1, r, mid + 1, qr, x, y);
  ud(p);
}
void add(int p, int l, int r, int ql, int qr, ll x) {
  if (l == ql && r == qr) {
    ca(p, x);
    return;
  }
  pd(p);
  if (qr <= mid) add(ls, l, mid, ql, qr, x);
  else if (ql > mid) add(rs, mid + 1, r, ql, qr, x);
  else add(ls, l, mid, ql, mid, x), add(rs, mid + 1, r, mid + 1, qr, x);
  ud(p);
}
ll ask(int p, int l, int r, int x) {
  if (l == r) return tp[p];
  pd(p);
  if (x <= mid) return ask(ls, l, mid, x);
  else return ask(rs, mid + 1, r, x);
}
void norm(int p, int l, int r) {
  if (mn[p] >= 0) return;
  if (tp[p]) {
    mn[p] = get(tp[p]);
    return;
  }
  pd(p);
  norm(ls, l, mid);
  norm(rs, mid + 1, r);
  ud(p);
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    cov(1, 1, n, i, i, x, get(x));
  }
  while (q--) {
    int opt, l, r;
    ll x;
    scanf("%d%d", &opt, &l);
    if (opt == 1) {
      printf("%lld\n", ask(1, 1, n, l));
    } else {
      scanf("%d%lld", &r, &x);
      if (opt == 2) {
        cov(1, 1, n, l, r, x, get(x));
      } else {
        do {
          add(1, 1, n, l, r, x);
          norm(1, 1, n);
        } while (mn[1] == 0);
      }
    }
  }
}
