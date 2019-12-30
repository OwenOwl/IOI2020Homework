#include <bits/stdc++.h>
using namespace std;

int k;
struct data {
  int id[5], cnt[5];
  data() {
    memset(cnt, 0, sizeof cnt);
  }
  void insert(int x, int y) {
    if (y <= 0) return;
    for (int i = 0; i < k; i++) {
      if (id[i] == x && cnt[i] > 0) {
        cnt[i] += y;
        return;
      }
    }
    int z = (int) (min_element(cnt, cnt + k) - cnt);
    if (cnt[z] >= y) {
      for (int i = 0; i < k; i++) {
        cnt[i] -= y;
      }
    } else {
      for (int i = 0; i < k; i++) if (i != z) {
        cnt[i] -= cnt[z];
      }
      id[z] = x;
      cnt[z] = y - cnt[z];
    }
  }
  data operator + (const data &d) const {
    data x = *this;
    for (int i = 0; i < k; i++) {
      x.insert(d.id[i], d.cnt[i]);
    }
    return x;
  }
};

const int N = 150233;
int n, m, p, a[N];
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)
data s[N << 2];
int tg[N << 2];
void cd(int p, int x, int l, int r) {
  tg[p] = x;
  s[p] = data();
  s[p].id[0] = x;
  s[p].cnt[0] = r - l + 1;
}
void pd(int p, int l, int r) {
  if (!tg[p]) return;
  cd(ls, tg[p], l, mid);
  cd(rs, tg[p], mid + 1, r);
  tg[p] = 0;
}
void ud(int p) {
  s[p] = s[ls] + s[rs];
}
void bd(int p, int l, int r) {
  if (l == r) {
    s[p].id[0] = a[l];
    s[p].cnt[0] = 1;
    return;
  }
  bd(ls, l, mid);
  bd(rs, mid + 1, r);
  ud(p);
}
void md(int p, int l, int r, int ql, int qr, int x) {
  if (l == ql && r == qr) {
    cd(p, x, l, r);
    return;
  }
  pd(p, l, r);
  if (qr <= mid) md(ls, l, mid, ql, qr, x);
  else if (ql > mid) md(rs, mid + 1, r, ql, qr, x);
  else md(ls, l, mid, ql, mid, x), md(rs, mid + 1, r, mid + 1, qr, x);
  ud(p);
}
data qx(int p, int l, int r, int ql, int qr) {
  if (l == ql && r == qr) {
    return s[p];
  }
  pd(p, l, r);
  if (qr <= mid) return qx(ls, l, mid, ql, qr);
  else if (ql > mid) return qx(rs, mid + 1, r, ql, qr);
  else return qx(ls, l, mid, ql, mid) + qx(rs, mid + 1, r, mid + 1, qr);
}

int main() {
  scanf("%d%d%d", &n, &m, &p);
  k = 100 / p;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  bd(1, 1, n);
  while (m--) {
    int op, l, r;
    scanf("%d%d%d", &op, &l, &r);
    if (op == 1) {
      int x;
      scanf("%d", &x);
      md(1, 1, n, l, r, x);
    } else {
      data t = qx(1, 1, n, l, r);
      printf("%d ", k);
      for (int i = 0; i < k; i++) {
        printf("%d%c", t.cnt[i] ? t.id[i] : 1, i == k - 1 ? '\n' : ' ');
      }
    }
  }
}
