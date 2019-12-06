#include <bits/stdc++.h>
using namespace std;

const int N = 400233;
int n, p = 1, cnt = 1;
int ch[N][26], par[N], len[N], rit[N];
char s[N];
int bas[N], top[N];
void extend(int c, int pos) {
  int np = ++cnt;
  rit[np] = pos;
  len[np] = len[p] + 1;
  for (; p && !ch[p][c]; p = par[p]) {
    ch[p][c] = np;
  }
  if (p) {
    int q = ch[p][c];
    if (len[q] != len[p] + 1) {
      int nq = ++cnt;
      len[nq] = len[p] + 1;
      par[nq] = par[q];
      rit[nq] = 0;
      memcpy(ch[nq], ch[q], sizeof *ch);
      for (; p && ch[p][c] == q; p = par[p]) {
        ch[p][c] = nq;
      }
      par[np] = par[q] = nq;
    } else {
      par[np] = q;
    }
  } else {
    par[np] = 1;
  }
  p = np;
}
int rt[N], ls[N * 30], rs[N * 30], pc = 0;
void modify(int &p, int l, int r, int x) {
  if (!p) p = ++pc;
  if (l == r) return;
  int mid = (l + r) >> 1;
  if (x <= mid) modify(ls[p], l, mid, x);
  else modify(rs[p], mid + 1, r, x);
}
int merge(int x, int y) {
  if (!x || !y) return x | y;
  int p = ++pc;
  ls[p] = merge(ls[x], ls[y]);
  rs[p] = merge(rs[x], rs[y]);
  return p;
}
bool query(int p, int l, int r, int ql, int qr) {
  if (!p || qr < ql) return false;
  if (l == ql && r == qr) return true;
  int mid = (l + r) >> 1;
  if (qr <= mid) return query(ls[p], l, mid, ql, qr);
  else if (ql > mid) return query(rs[p], mid + 1, r, ql, qr);
  else return query(ls[p], l, mid, ql, mid) || query(rs[p], mid + 1, r, mid + 1, qr);
}
int f[N], bel[N];
int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; i++) {
    extend(s[i] - 'a', i);
  }
  for (int i = 1; i <= cnt; i++) {
    bas[len[i]]++;
  }
  for (int i = 1; i <= n; i++) {
    bas[i] += bas[i - 1];
  }
  for (int i = cnt; i; i--) {
    top[bas[len[i]]--] = i;
  }
  for (int i = 1; i <= cnt; i++) if (rit[i]) {
    modify(rt[i], 1, n, rit[i]);
  }
  for (int i = cnt; i > 1; i--) {
    int x = top[i];
    rt[par[x]] = merge(rt[par[x]], rt[x]);
    rit[par[x]] = rit[x];
  }
  for (int i = 2; i <= cnt; i++) {
    int x = top[i], y = par[x], z = bel[y];
    if (y == 1) {
      f[x] = 1;
      bel[x] = x;
    } else if (query(rt[z], 1, n, rit[x] - len[x] + len[z], rit[x] - 1)) {
      f[x] = f[y] + 1;
      bel[x] = x;
    } else {
      f[x] = f[y];
      bel[x] = z;
    }
  }
  printf("%d\n", *max_element(f + 1, f + cnt + 1));
}
