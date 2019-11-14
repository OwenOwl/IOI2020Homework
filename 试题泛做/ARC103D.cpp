#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1033;
int n;
ll x[N], y[N];
void solve(ll &x, ll &y, ll d) {
  ll man = 1ll << 55;
  int t = 0;
  if (abs(x - d) + abs(y) < man) man = abs(x - d) + abs(y), t = 1;
  if (abs(x + d) + abs(y) < man) man = abs(x + d) + abs(y), t = 2;
  if (abs(x) + abs(y - d) < man) man = abs(x) + abs(y - d), t = 3;
  if (abs(x) + abs(y + d) < man) man = abs(x) + abs(y + d), t = 4;
  if (t == 1) putchar('R'), x -= d;
  if (t == 2) putchar('L'), x += d;
  if (t == 3) putchar('U'), y -= d;
  if (t == 4) putchar('D'), y += d;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld%lld", &x[i], &y[i]);
    if (abs(x[1] + y[1] + x[i] + y[i]) & 1) return puts("-1"), 0;
  }
  int d = !(abs(x[1] + y[1]) & 1);
  printf("%d\n", 31 + d);
  for (int i = 30; ~i; i--) {
    printf("%lld ", 1ll << i);
  }
  if (d) printf("1 ");
  puts("");
  for (int i = 1; i <= n; i++) {
    for (int j = 30; ~j; j--) {
      solve(x[i], y[i], 1ll << j);
    }
    if (d) solve(x[i], y[i], 1);
    puts("");
  }
}
