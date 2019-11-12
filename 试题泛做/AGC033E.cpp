#include <bits/stdc++.h>
using namespace std;

const int N = 200233, mod = 1000000007;
int n, m, f[N];
char s[N];

int main() {
  scanf("%d%d%s", &n, &m, s + 1);
  if (*min_element(s + 1, s + 1 + m) == *max_element(s + 1, s + 1 + m)) {
    int x = 2, y = 1;
    for (int i = 1; i <= n; i++) {
      y = (y + x) % mod;
      x = (mod + y - x) % mod;
    }
    printf("%d\n", x);
    return 0;
  }
  int limit, x = 1;
  while (x + 1 <= m && s[x + 1] == s[1]) x++;
  limit = x | 1;
  for (int i = x + 1, j = 0; i <= m; i++) {
    if (s[i] != s[1]) {
      if (j & 1) limit = min(limit, j);
      j = 0;
    } else {
      ++j;
    }
  }
  if (n & 1) {
    puts("0");
    return 0;
  }
  n >>= 1;
  limit = min(n, (limit + 1) >> 1);
  f[0] = 1;
  for (int i = 1; i <= n; i++) {
    f[i] = ((long long) mod + f[i - 1] + f[i - 1] - (i > limit ? f[i - limit - 1] : 0)) % mod;
  }
  int ans = 0;
  for (int i = 1; i <= limit; i++) {
    ans = (ans + (long long) (mod + f[n - i] - (n > i ? f[n - i - 1] : 0)) * i * 2) % mod;
  }
  printf("%d\n", ans);
}

