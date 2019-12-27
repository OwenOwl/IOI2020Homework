#include <bits/stdc++.h>
using namespace std;

const int N = 800333;
namespace sa {
  int a[N], b[N], c[N];
  int SA[N], rnk[N], height[N], st[21][N], n;
  void call(char *s, int _n, int m) {
    n = _n;
    int *x = a, *y = b;
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[x[i] = s[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i; i--) SA[c[x[i]]--] = i;
    for (int j = 1, p = 0; j <= n && p != n + 1; j <<= 1) {
      p = 0;
      for (int i = n - j + 1; i <= n; i++) y[++p] = i;
      for (int i = 1; i <= n; i++) if (SA[i] > j) y[++p] = SA[i] - j;
      for (int i = 1; i <= m; i++) c[i] = 0;
      for (int i = 1; i <= n; i++) c[x[y[i]]]++;
      for (int i = 1; i <= m; i++) c[i] += c[i - 1];
      for (int i = n; i; i--) SA[c[x[y[i]]]--] = y[i];
      std::swap(x, y); x[SA[1]] = 1; p = 2;
      for (int i = 2; i <= n; i++) x[SA[i]] = (y[SA[i]] == y[SA[i - 1]] && y[SA[i] + j] == y[SA[i - 1] + j]) ? p - 1 : p++;
      m = p;
    }
    for (int i = 1; i <= n; i++) rnk[SA[i]] = i;
    for (int i = 1, p; i <= n; i++) if (rnk[i] != 1) {
      for (p = std::max(height[rnk[i - 1]] - 1, 0); s[SA[rnk[i] - 1] + p] == s[i + p]; p++);
      height[rnk[i]] = p;
    }
    for (int i = 1; i <= n; i++) {
      st[0][i] = height[i];
    }
    for (int k = 1; k <= 20; k++) {
      for (int i = 1; i + (1 << k) - 1 <= n; i++) {
        st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
      }
    }
  }
  inline int lcp(int x, int y) {
    if (x > y) std::swap(x, y);
    x++;
    int k = 31 - __builtin_clz(y - x);
    return std::min(st[k][x], st[k][y - (1 << k) + 1]);
  }
}

char s[N], t[N];
int n, q, L, len[N], pos[N], qx[N], tr[N], ans[N];
vector<int> Q[N];
void add(int x) {
  for (; x <= L; x += x & -x) {
    tr[x]++;
  }
}
int ask(int x) {
  int r = 0;
  for (; x; x -= x & -x) {
    r += tr[x];
  }
  return r;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%s", t + 1);
    int l = (int) strlen(t + 1);
    pos[i] = L + 1;
    len[i] = l;
    for (int j = 1; j <= l; j++) {
      s[++L] = t[j];
    }
    if (i != n) {
      s[++L] = '$';
    }
  }
  pos[n + 1] = L + 1;
  sa::call(s, L, 128);
  for (int i = 1, l, r; i <= q; i++) {
    scanf("%d%d%d", &l, &r, &qx[i]);
    Q[l - 1].push_back(-i);
    Q[r].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = pos[i]; j < pos[i] + len[i]; j++) {
      add(sa::rnk[j]);
    }
    for (auto p : Q[i]) {
      int x = qx[abs(p)], y = len[x], l, r, cl, cr;
      x = sa::rnk[pos[x]];
      l = 1, r = x;
      while (l < r) {
        int c = (l + r) >> 1;
        if (sa::lcp(c, x) >= y) {
          r = c;
        } else {
          l = c + 1;
        }
      }
      cl = l;
      l = x, r = L;
      while (l < r) {
        int c = (l + r + 1) >> 1;
        if (sa::lcp(x, c) >= y) {
          l = c;
        } else {
          r = c - 1;
        }
      }
      cr = r;
      if (p > 0) {
        ans[p] += ask(cr) - ask(cl - 1);
      } else {
        ans[-p] -= ask(cr) - ask(cl - 1);
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    printf("%d\n", ans[i]);
  }
}
