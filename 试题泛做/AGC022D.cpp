#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 300233;
int n;
ll m, x[N], t[N], ans;
bool l[N], r[N];

int main() {
  scanf("%d%lld", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", x + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%lld", t + i);
    if (t[i] % (m << 1) == 0) {
      ans += t[i] / (m << 1);
    } else {
      ans += 1 + t[i] / (m << 1);
      t[i] %= m << 1;
      if (t[i] <= x[i] << 1) l[i] = true;
      if (t[i] <= (m - x[i]) << 1) r[i] = true;
    }
  }
  int L = 0, LR = 0;
  for (int i = 1; i < n; i++) {
    if (L && r[i]) {
      if (l[i]) {
        LR++;
      }
      L--;
      ans--;
    } else if (!l[i] && r[i]) {
      if (LR) {
        LR--;
        L++;
      }
    } else if (l[i]) {
      L++;
    }
  }
  if (!r[n]) {
    ans++;
  }
  printf("%lld\n", ans * m << 1);
}
