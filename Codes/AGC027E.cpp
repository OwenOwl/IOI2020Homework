#include <bits/stdc++.h>
using namespace std;
const int N = 100010, mod = 1000000007;
char s[N];
int g[N], f[N], n, sum[N];

int main() {
  scanf("%s", s + 1);
  n = (int)strlen(s + 1);
  g[n + 1] = n + 1;
  sum[n + 1] = 0;
  for (int i = n; i; i--) {
    g[i] = s[i] == s[i + 1] ? i + 1 : g[i + 1];
    sum[i] = (sum[i + 1] + s[i] - 'a' + 1) % 3;
  }
  if (g[1] == n + 1) {
    puts("1");
    return 0;
  }
  f[0] = 1;
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    if (i && sum[i + 1] == 0) {
      ans = (ans + f[i]) % mod;
    }
    f[i + 1] = (f[i + 1] + f[i]) % mod;
    f[g[i + 1]] = (f[g[i + 1]] + f[i]) % mod;
  }
  printf("%d\n", ans);
  return 0;
}

