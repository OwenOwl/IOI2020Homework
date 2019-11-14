#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int n;
ll a[19];
ll f(int l, int r, ll xl, ll xr) {
  if (r - l == 1) return a[l] * xl + a[r] * xr;
  ll ans = 1ll << 60;
  for (int i = l + 1; i < r; i++) {
    ans = min(ans, f(l, i, xl, xl + xr) + f(i, r, xl + xr, xr) - (xl + xr) * a[i]);
  }
  return ans;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
  }
  printf("%lld\n", f(1, n, 1, 1));
}
