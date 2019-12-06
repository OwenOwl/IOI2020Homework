#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100233;
ll n, m, k, p, h[N], a[N], f[N];

bool check(ll ed) {
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
  for (ll i = 1; i <= n; i++) {
    f[i] = ed;
    ll d = f[i] / a[i]; if (d < m) q.push(make_pair(d, i));
  }
  ll step = 0;
  for (; step < m * k; step++) {
    if (q.empty()) break;
    auto t = q.top();
    q.pop();
    if (t.first <= step / k) return false;
    ll i = t.second;
    f[i] += p;
    ll d = f[i] / a[i]; if (d < m) q.push(make_pair(d, i));
  }
  for (ll i = 1; i <= n; i++) {
    ll fin = f[i] - m * a[i];
    if (fin < h[i]) step += (h[i] - fin - 1) / p + 1;
  }
  return step <= m * k;
}

int main() {
  scanf("%lld%lld%lld%lld", &n, &m, &k, &p);
  for (ll i = 1; i <= n; i++) {
    scanf("%lld%lld", &h[i], &a[i]);
  }
  ll l = 0, r = 1ll << 55;
  while (l < r) {
    ll mid = (l + r) >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%lld\n", l);
}
