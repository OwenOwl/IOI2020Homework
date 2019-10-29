#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int n, c[500233];
pair<int, int> a[1000233];

int main() {
  scanf("%d", &n);
  ll s1 = 0, s2 = 0;
  for (int i = 1, x, y; i <= n; i++) {
    scanf("%d%d", &x, &y);
    a[i] = make_pair(x, i);
    a[i + n] = make_pair(y, i);
    s1 += x;
    s2 += y;
  }
  sort(a + 1, a + 1 + n * 2, greater<pair<int, int>>());
  ll ans = max(s1, s2), cur = 0;
  int ok = 0;
  for (int i = 1; i <= n; i++) {
    if (c[a[i].second]) ok = 1;
    c[a[i].second] = 1;
    cur += a[i].first;
  }
  if (ok) {
    ans = max(ans, cur);
  } else {
    for (int i = n + 1; i <= n * 2; i++) {
      if (a[i].second != a[n].second) {
        ans = max(ans, cur + a[i].first - a[n].first);
      } else {
        ans = max(ans, cur + a[i].first - a[n - 1].first);
      }
    }
  }
  printf("%lld\n", s1 + s2 - ans);
}
