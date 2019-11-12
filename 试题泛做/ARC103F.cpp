#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100233;
int n, size[N], fa[N], dep[N];
pair<int, ll> p[N];
map<ll, int> q;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &p[i].second);
    p[i].first = i;
    q[p[i].second] = i;
    size[i] = 1;
  }
  sort(p + 1, p + 1 + n, [&](pair<int, ll> a, pair<int, ll> b){return a.second < b.second;});
  for (int i = n; i >= 2; i--) {
    int x = p[i].first;
    ll t = p[i].second + 2 * size[x] - n;
    if (t >= p[i].second) return puts("-1"), 0;
    int y = q[t];
    if (!y) return puts("-1"), 0;
    size[y] += size[x];
    fa[x] = y;
  }
  ll t = 0;
  for (int i = 2; i <= n; i++) {
    int x = p[i].first;
    dep[x] = dep[fa[x]] + 1;
    t += dep[x];
  }
  if (t != p[1].second) return puts("-1"), 0;
  for (int i = 2; i <= n; i++) {
    int x = p[i].first;
    printf("%d %d\n", x, fa[x]);
  }
}
