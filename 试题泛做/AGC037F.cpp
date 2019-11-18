#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 200233, inf = 1100000007;
int n, L, a[N], lf[N], rf[N], lp[N], rp[N];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> s;
ll ans = 0;

int main() {
  scanf("%d%d", &n, &L);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    lf[i] = rf[i] = 1;
    lp[i] = i - 1;
    rp[i] = i + 1;
    s.push(make_pair(a[i], i));
  }
  rf[0] = 1;
  lf[n + 1] = n;
  while (1) {
    int x = s.top().second;
    s.pop();
    if (a[x] == inf) break;
    int y = x, cnt = 1;
    vector<int> v(1, x);
    while (a[rp[y]] == a[y]) {
      cnt++;
      y = rp[y];
      v.push_back(y);
      s.pop();
    }
    for (int i = 0, sum = 0; i < cnt; i++) {
      ans += (ll) lf[v[i]] * rf[v[i]];
      if (i - L + 1 >= 0) {
        sum += lf[v[i - L + 1]];
      }
      ans += (ll) sum * rf[v[i]];
    }
    int lt = lp[x], rt = rp[y];
    if (lt == 0 && rt == n + 1) {
      break;
    }
    int cnt2 = cnt / L;
    vector<int> nlf(cnt2, 0), nrf(cnt2, 0);
    for (int i = 0; i < cnt; i++) {
      if (cnt - i >= L) {
        nlf[cnt2 - 1 - (cnt - i - L) / L] += lf[v[i]];
      }
      if (i + 1 >= L) {
        nrf[(i + 1 - L) / L] += rf[v[i]];
      }
    }
    for (int i = 0, sum = 0; i < cnt2; i++) {
      ans -= (ll) nlf[i] * nrf[i];
      if (i - L + 1 >= 0) {
        sum += nlf[i - L + 1];
      }
      ans -= (ll) sum * nrf[i];
    }
    if (!cnt2) {
      ++cnt2;
      a[v[0]] = inf - 1;
      nlf.assign(1, 0);
      nrf.assign(1, 0);
    }
    for (int i = 0; i < cnt2; i++) {
      a[v[i]]++;
      s.push(make_pair(a[v[i]], v[i]));
      lf[v[i]] = nlf[i];
      rf[v[i]] = nrf[i];
    }
    lp[v[0]] = lt;
    rp[v[cnt2 - 1]] = rt;
    rp[lt] = v[0];
    lp[rt] = v[cnt2 - 1];
  }
  printf("%lld\n", ans);
}
