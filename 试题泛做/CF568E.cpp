#include <bits/stdc++.h>
using namespace std;

const int N = 100233, inf = 0x3f3f3f3f;
int n, a[N], m, len[N], from[N], f[N], last[N];
multiset<int> s;
vector<int> v, pos[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  scanf("%d", &m);
  for (int i = 1, x; i <= m; i++) {
    scanf("%d", &x);
    s.insert(x);
    v.push_back(x);
  }
  sort(v.begin(), v.end(), greater<int>());
  v.erase(unique(v.begin(), v.end()), v.end());
  for (int i = 1; i <= n; i++) {
    f[i] = inf;
  }
  a[n + 1] = 1e9 + 5;
  for (int i = 1; i <= n + 1; i++) {
    if (~a[i]) {
      int l = 0, r = n;
      while (l < r) {
        int c = (l + r + 1) >> 1;
        if (f[c] < a[i]) {
          l = c;
        } else {
          r = c - 1;
        }
      }
      len[i] = l + 1;
      from[i] = last[l];
      f[l + 1] = a[i];
      last[l + 1] = i;
    } else {
      int p = n;
      for (auto x : v) {
        for (; f[p] >= x; p--);
        f[p + 1] = x;
        last[p + 1] = i;
      }
    }
  }
  for (int i = 1; i <= n; i++) if (~a[i]) {
    pos[len[i]].push_back(i);
  }
  reverse(v.begin(), v.end());
  for (int p = from[n + 1], b = a[n + 1], nw = len[n + 1] - 1; nw && p; nw--) {
    if (~a[p]) {
      b = a[p];
      p = from[p];
    } else {
      while (v.back() >= b) v.pop_back();
      b = a[p] = v.back();
      s.erase(s.find(a[p]));
      int q = -1;
      for (auto x : pos[nw - 1]) {
        if (x < p && a[x] < a[p]) {
          q = x;
          break;
        }
      }
      if (~q) {
        p = q;
      } else {
        for (p--; ~a[p]; p--);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!~a[i]) {
      a[i] = *s.begin();
      s.erase(s.begin());
    }
    printf("%d%c", a[i], i == n ? '\n' : ' ');
  }
}
