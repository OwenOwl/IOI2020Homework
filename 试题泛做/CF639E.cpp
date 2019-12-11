#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 150233;
int n, p[N], t[N], p1[N], p2[N];
double mn[N], mx[N];
ll T = 0;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &t[i]);
    T += t[i];
  }
  for (int i = 1; i <= n; i++) {
    p1[i] = p2[i] = i;
  }
  sort(p1 + 1, p1 + 1 + n, [&] (const int &x, const int &y) {return (ll) p[x] * t[y] > (ll) p[y] * t[x];});
  sort(p2 + 1, p2 + 1 + n, [&] (const int &x, const int &y) {return p[x] < p[y];});
  double cl = 0, cr = 1;
  for (int ct = 0; ct < 30; ct++) {
    double c = (cl + cr) / 2;
    ll s = 0;
    for (int l = 1, r = 1; l <= n; l = r) {
      for (; r <= n && (ll) p[p1[r]] * t[p1[l]] == (ll) p[p1[l]] * t[p1[r]]; r++);
      for (int i = l; i < r; i++) {
        mx[p1[i]] = p[p1[i]] * (1 - c * (s + t[p1[i]]) / T);
      }
      for (int i = l; i < r; i++) {
        s += t[p1[i]];
      }
      for (int i = l; i < r; i++) {
        mn[p1[i]] = p[p1[i]] * (1 - c * s / T);
      }
    }
    double mxx = 0;
    bool ok = true;
    for (int l = 1, r = 1; l <= n; l = r) {
      for (; r <= n && p[p2[r]] == p[p2[l]]; r++);
      for (int i = l; i < r; i++) {
        if (mn[p2[i]] < mxx) {
          ok = false;
        }
      }
      for (int i = l; i < r; i++) {
        mxx = max(mxx, mx[p2[i]]);
      }
    }
    (ok ? cl : cr) = c;
  }
  printf("%.10lf\n", cl);
}
