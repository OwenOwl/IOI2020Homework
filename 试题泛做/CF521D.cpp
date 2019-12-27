#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100233;
struct frac {
  ll a, b; int id;
  frac (ll a = 0, ll b = 1, int id = 0) : a(a), b(b), id(id) {}
  bool operator < (const frac &d) const {
    return (a - b) * d.b > b * (d.a - d.b);
  }
};
vector<frac> d, s2[N];
frac s3[N];
int n, q, m, a[N], type[N];

int main() {
  scanf("%d%d%d", &n, &q, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= q; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    type[i] = x;
    if (x == 1) {
      s3[y] = min(s3[y], frac(z, 1, i));
    } else if (x == 2) {
      s2[y].emplace_back(z, 1, i);
    } else {
      d.emplace_back(z, 1, i);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (s3[i].a > a[i]) {
      s2[i].emplace_back(s3[i].a - a[i], 1, s3[i].id);
    }
  }
  for (int i = 1; i <= n; i++) {
    ll s = a[i];
    sort(s2[i].begin(), s2[i].end());
    for (auto x : s2[i]) {
      d.emplace_back(s + x.a, s, x.id);
      s += x.a;
    }
  }
  sort(d.begin(), d.end());
  int x = min((int) d.size(), m);
  sort(d.begin(), d.begin() + x, [&](const frac &a, const frac &b){return type[a.id] == type[b.id] ? a < b : type[a.id] < type[b.id];});
  printf("%d\n", x);
  for (int i = 0; i < x; i++) {
    printf("%d%c", d[i].id, i == x - 1 ? '\n' : ' ');
  }
}
