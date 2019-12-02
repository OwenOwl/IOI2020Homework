#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x = 0, m, k;
  scanf("%d", &n);
  while (n--) {
    scanf("%d%d", &m, &k);
    while (m % k && m >= k) {
      m -= ((m - m / k * k - 1) / (m / k + 1) + 1) * (m / k + 1);
    }
    x ^= m / k;
  }
  puts(x ? "Takahashi" : "Aoki");
}
