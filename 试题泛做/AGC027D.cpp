#include <bits/stdc++.h>
using namespace std;

const int N = 233333;
int notp[N], pri[N], pc = 0;

int main() {
  notp[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!notp[i]) {
      pri[++pc] = i;
    }
    for (int j = 1; j <= pc && i * pri[j] < N; j++) {
      notp[i * pri[j]] = 1;
      if (!(i % pri[j])) break;
    }
  }
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if ((i + j) & 1) {
        printf("%lld ", (long long) pri[(i - j + n + 3) / 2] * pri[(i + j + n * 2 + 3) / 2]);
      } else {
        long long x = 1;
        if (i > 1 || j > 1) x *= pri[(i + j - 1 + n * 2 + 3) / 2];
        if (i < n || j < n) x *= pri[(i + j + 1 + n * 2 + 3) / 2];
        if (i > 1 || j < n) x *= pri[(i - j - 1 + n + 3) / 2];
        if (i < n || j > 1) x *= pri[(i - j + 1 + n + 3) / 2];
        if (n == 2 && i == 1 && j == 1) x <<= 1;
        printf("%lld ", x + 1);
      }
    }
    puts("");
  }
}
